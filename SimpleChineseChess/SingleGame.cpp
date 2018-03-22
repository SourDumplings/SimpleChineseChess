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

static const int INF = 999999;

SingleGame::SingleGame()
{

}

void SingleGame::clickStone(int id, int row, int col)
{
    if (!_isRedTurn) return;

    Board::clickStone(id, row, col);

    if (!_isRedTurn)
    {
        auto step = getBestMove();
        killStone(step->_killId);
        moveStone(step->_moveId, step->_rowTo, step->_colTo);
        _selectedId = -1;
        update();
    }
    return;
}

void SingleGame::getAllPossibleMove(QVector<std::shared_ptr<Step> > &steps)
{
    for (auto p : _posMap)
    {
        if (p.second < 16)
            continue;

        for (int row = 0; row < 10; ++row)
        {
            for (int col = 0; col < 9; ++col)
            {
                int killId = getStoneId(row, col);
                if (_s[p.second]._red == _s[killId]._red)
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

void SingleGame::relieveStone(int id, int row, int col)
{
    if (id == -1) return;
    auto p = std::make_pair(row, col);
    _s[id]._row = row;
    _s[id]._col = col;
    _posMap[p] = id;
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
    static int chessScore[] = {1500, 100, 50, 50, 20, 10, 10};

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
        int score = calcScore();
        unfakeMove(step);

        if (score > maxScore)
        {
            maxScore = score;
            ret = step;
        }
    }

    return ret;
}
