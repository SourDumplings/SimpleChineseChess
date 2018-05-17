/*
 @Date    : 2018-03-21 16:54:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#include "SingleGame.h"
#include <QTimer>

static const int INF = 999999;

SingleGame::SingleGame(QWidget *parent): Board(parent)
{
    _level = 3;
}

void SingleGame::computerMove()
{
    auto step = getBestMove();
    saveStep(step, _steps);
    killStone(step->_killId);
    moveStone(step->_moveId, step->_rowTo, step->_colTo);
    if (_s[step->_killId]._type == Stone::JIANG)
    {
        if (_s[step->_killId]._red)
        {
            emit sigBlackWin();
        }
        else
            emit sigRedWin();
    }
    _selectedId = -1;
    update();
}

void SingleGame::clickStone(int id, int row, int col)
{
    if (!_isRedTurn) return;

    Board::clickStone(id, row, col);

    if (!_isRedTurn)
    {
        // 启动0.1秒定时器，在0.1秒后电脑再思考
        QTimer::singleShot(100, this, SLOT(computerMove()));
    }
    return;
}

void SingleGame::getAllPossibleMove(QVector<std::shared_ptr<Step> > &steps)
{
    int min= 16, max = 32;
    if (_isRedTurn)
    {
        min = 0;
        max = 16;
    }
    for (auto p : _posMap)
    {
        if (p.second < min || p.second >= max)
            continue;

        for (int row = 0; row < 10; ++row)
        {
            for (int col = 0; col < 9; ++col)
            {
                int killId = getStoneId(row, col);
                if (killId != -1 && _s[p.second]._red == _s[killId]._red)
                    continue;
                if (canMove(p.second, row, col, killId))
                {
                    saveStep(p.second, row, col, steps, killId);
                }
            }
        }
    }
    return;
}

void SingleGame::fakeMove(std::shared_ptr<Step> step)
{
    killStone(step->_killId);
    moveStone(step->_moveId, step->_rowTo, step->_colTo);
    return;
}

void SingleGame::unfakeMove(std::shared_ptr<Step> step)
{
    moveStone(step->_moveId, step->_rowFrom, step->_colFrom);
    relieveStone(step->_killId, step->_rowTo, step->_colTo);
    return;
}

int SingleGame::calcScore()
{
//    enum TYPE {JIANG, CHE, PAO, MA, BING, SHI, XIANG};
    static int chessScore[] = {50000, 100, 50, 50, 20, 5, 5};

    // 黑棋分的总数-红旗分的总数
    int sumRedSocore = 0, sumBlackScore = 0;
    for (auto p : _posMap)
    {
        if (p.second < 16)
            sumRedSocore += chessScore[_s[p.second]._type];
        else
            sumBlackScore += chessScore[_s[p.second]._type];
    }
    return sumBlackScore - sumRedSocore;
}

int SingleGame::getMaxScore(int level, int currMinScore)
{
    if (level == 0) return calcScore();
    QVector<std::shared_ptr<Step>> steps;
    getAllPossibleMove(steps);

    int maxScore = -INF;
    for (auto step : steps)
    {
        fakeMove(step);
        int score = getMinScore(level - 1, maxScore);
        unfakeMove(step);

        if (score >= currMinScore)
        {
            return score;
        }

        if (score > maxScore)
        {
            maxScore = score;
        }
    }
    return maxScore;
}

int SingleGame::getMinScore(int level, int currMaxScore)
{
    if (level == 0) return calcScore();
    QVector<std::shared_ptr<Step>> steps;
    getAllPossibleMove(steps);

    int minScore = INF;
    for (auto step : steps)
    {
        fakeMove(step);
        int score = getMaxScore(level - 1, minScore);
        unfakeMove(step);

        if (score <= currMaxScore)
        {
            return score;
        }

        if (score < minScore)
        {
            minScore = score;
        }
    }
    return minScore;
}

std::shared_ptr<Step> SingleGame::getBestMove()
{
    /*
     * 看看有哪些步骤可以走
     * 试着走一下
     * 评估走的结果
     * 取最好的结果作为参考
     */
    QVector<std::shared_ptr<Step>> steps;
    getAllPossibleMove(steps);

    int maxScore = -INF;
    std::shared_ptr<Step> ret = nullptr;
    for (auto step : steps)
    {
        fakeMove(step);
        int score = getMinScore(_level - 1, -INF);
        unfakeMove(step);

        if (score > maxScore)
        {
            maxScore = score;
            ret = step;
        }
    }

    return ret;
}
