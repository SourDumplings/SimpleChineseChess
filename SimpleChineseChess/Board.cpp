/*
 @Date    : 2018-03-21 16:54:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */


#include "Board.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>

Board::Board(QWidget *parent) : QFrame(parent)
{
    init();
}


void Board::init()
{
    for (int i = 0; i != 32; ++i)
    {
        _s[i].init(i);
        _posMap[std::make_pair(_s[i]._row, _s[i]._col)] = i;
    }
    setMinimumSize(_r*20+1, _r*23+1);
    _selectedId = -1;
    _isRedTurn = true;
    return;
}

void Board::slotReStart()
{
    _steps.clear();
    _posMap.clear();
    init();
    update();
    return;
}


void Board::paintEvent(QPaintEvent *)
{
    // 绘制线条
    int d = _r * 2;
    QPainter painterL(this);
    // 线的颜色为浅灰色
    painterL.setPen(QColor(220, 220, 220));
    // 画10条横线
    for (int i = 1; i != 11; ++i)
    {
        painterL.drawLine(QPoint(d, i*d), QPoint(9*d, i*d));
    }
    // 画9条竖线
    for (int i = 1; i != 10; ++i)
    {
        if (i == 1 || i == 9)
            painterL.drawLine(QPoint(i*d, d), QPoint(i*d, 10*d));
        else
        {
            painterL.drawLine(QPoint(i*d, d), QPoint(i*d, 5*d));
            painterL.drawLine(QPoint(i*d, 6*d), QPoint(i*d, 10*d));
        }
    }
    // 9宫格
    painterL.drawLine(QPoint(4*d, d), QPoint(6*d, 3*d));
    painterL.drawLine(QPoint(6*d, d), QPoint(4*d, 3*d));
    painterL.drawLine(QPoint(4*d, 8*d), QPoint(6*d, 10*d));
    painterL.drawLine(QPoint(4*d, 10*d), QPoint(6*d, 8*d));

    // 绘制32颗棋子
    QPainter painterS(this);
    painterS.setFont(QFont("Microsoft YaHei", _r * 0.7, QFont::Normal));
    for (auto p : _posMap)
    {
        int i = p.second;
        drawStone(painterS, i);
    }
    return;
}

QPoint Board::center(int row, int col)
{
    QPoint ret;
    ret.rx() = (col + 1) * _r * 2;
    ret.ry() = (row + 1) * _r * 2;
    return ret;
}

QPoint Board::center(int id)
{
    return center(_s[id]._row, _s[id]._col);
}

void Board::drawStone(QPainter &painter, int id)
{
    QPoint c = center(id);
    QRect rect = QRect(c.x()-_r, c.y()-_r, _r*2, _r*2);
    QColor darkGray(130, 130, 130);
    QColor selectedColorDark(50, 50, 50), selectedColorBright(200, 200, 200);
    if (id < 16)
    {
        painter.setPen(darkGray);
        if (id == _selectedId)
            painter.setBrush(QBrush(selectedColorBright));
        else
            painter.setBrush(Qt::white);
    }
    else
    {
        painter.setPen(Qt::white);
        if (id == _selectedId)
            painter.setBrush(QBrush(selectedColorDark));
        else
            painter.setBrush(darkGray);
    }
    painter.drawEllipse(c, _r, _r);

    if (id < 16)
        painter.setPen(darkGray);
    else
        painter.setPen(Qt::white);
    painter.drawText(rect, _s[id].getText(), QTextOption(Qt::AlignCenter));

    return;
}

bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for (row = 0; row != 10; ++row)
    {
        for (col = 0; col != 9; ++col)
        {
            QPoint c = center(row, col);
            int dx = c.x() - pt.x();
            int dy = c.y() - pt.y();
            int dist2 = dx * dx + dy * dy;
            if (dist2 < _r * _r)
                return true;
        }
    }
    return false;
}

int Board::getStoneId(int row, int col)
{
    auto p = std::make_pair(row, col);
    if (_posMap.find(p) == _posMap.end()) return -1;
    return _posMap[p];
}

void Board::trySelectStone(int id)
{
    if (id == -1) return;
    if (_isRedTurn == _s[id]._red)
    {
        _selectedId = id;
        update();
    }
    return;
}

 void Board::saveStep(int moveId, int row, int col, QVector<std::shared_ptr<Step>>& steps, int killId)
{
     int colS = _s[moveId]._col, rowS = _s[moveId]._row;
     std::shared_ptr<Step> step(new Step);
     step->_colFrom = colS;
     step->_colTo = col;
     step->_rowFrom = rowS;
     step->_rowTo = row;
     step->_moveId = moveId;
     step->_killId = killId;

     steps.append(step);

    return;
}

void Board::saveStep(std::shared_ptr<Step> step, QVector<std::shared_ptr<Step> > &steps)
{
    saveStep(step->_moveId, step->_rowTo, step->_colTo, steps, step->_killId);
    return;
}

void Board::killStone(int id)
{
    if (id == -1) return;
    auto p = std::make_pair(_s[id]._row, _s[id]._col);
    _posMap.erase(p);
    return;
}

void Board::moveStone(int moveId, int row, int col)
{
    auto p = std::make_pair(_s[moveId]._row, _s[moveId]._col);
    _posMap.erase(p);
    _s[moveId]._row = row;
    _s[moveId]._col = col;
    p = std::make_pair(_s[moveId]._row, _s[moveId]._col);
    _posMap[p] = moveId;

    _isRedTurn = !_isRedTurn;

    return;
}

void Board::tryMoveStone(int killId, int row, int col)
{
    // 相同色不能走，换选择
    if (killId != -1 && _s[killId]._red == _s[_selectedId]._red)
    {
        trySelectStone(killId);
        return;
    }

    bool ret = canMove(_selectedId, row, col, killId);
    if (ret)
    {
        saveStep(_selectedId, row, col, _steps, killId);
        killStone(killId);
        moveStone(_selectedId, row, col);
        if (_s[killId]._type == Stone::JIANG)
        {
            if (_s[killId]._red)
            {
                emit sigBlackWin();
            }
            else
                emit sigRedWin();
        }
        _selectedId = -1;
        update();
    }
    return;
}

void Board::clickStone(int id, int row, int col)
{
    if (_selectedId == -1)
        trySelectStone(id);
    else
        tryMoveStone(id, row, col);
    return;
}

void Board::click(QPoint pt)
{
    int row, col;
    bool clickOnBoard = getRowCol(pt, row, col);
    if (!clickOnBoard) return;
    int id = getStoneId(row, col);
    clickStone(id, row, col);
    return;
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton)
        return;
    click(ev->pos());
    return;
}

bool Board::isBottom(int id)
{
    return _s[id]._red;
}


bool Board::canMove(int moveId, int row, int col, int killId)
{
    switch (_s[moveId]._type)
    {
    case Stone::JIANG:
        return canMoveJIANG(moveId, row, col, killId);
    case Stone::SHI:
        return canMoveSHI(moveId, row, col, killId);
    case Stone::CHE:
        return canMoveCHE(moveId, row, col, killId);
    case Stone::MA:
        return canMoveMA(moveId, row, col, killId);
    case Stone::PAO:
        return canMovePAO(moveId, row, col, killId);
    case Stone::BING:
        return canMoveBING(moveId, row, col, killId);
    case Stone::XIANG:
        return canMoveXIANG(moveId, row, col, killId);
    }
    return false;
}

int Board::countStonesInLine(int moveId, int row, int col)
{
    /*
     * 给出从movedId所在位置到row, col所在位置的直线上的棋子数
     * 不包含首尾棋子
    */
    if (_s[moveId]._col != col && _s[moveId]._row != row) // 不在一条直线上
        return -1;

    int res = 0;
    if (_s[moveId]._row == row)
    {
        int step = col > _s[moveId]._col ? 1 : -1;
        for (int c = _s[moveId]._col + step; c != col; c += step)
        {
            auto p = std::make_pair(row, c);
            if (_posMap.find(p) != _posMap.end())
                ++res;
        }
        return res;
    }
    else
    {
        int step = row > _s[moveId]._row ? 1 : -1;
        for (int r = _s[moveId]._row + step; r != row; r += step)
        {
            auto p = std::make_pair(r, col);
            if (_posMap.find(p) != _posMap.end())
                ++res;
        }
        return res;
    }
}

bool Board::canMoveJIANG(int moveId, int row, int col, int killId)
{
    /*
     * 棋子必须在九宫格内
     * 移动步长为一格
     * 老将直线照面则吃
     * */
    if (_s[killId]._type == Stone::JIANG && _s[killId]._col == _s[moveId]._col)
    {
        int num = countStonesInLine(moveId, row, col);
        if (num == 0) return true;
    }

    if (col < 3 || col > 5) return false;
    if (isBottom(moveId))
    {
        if (row < 7) return false;
    }
    else
    {
        if (row > 2) return false;
    }

    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int d = abs(dr) * 10 + abs(dc);
    if (d == 1 || d == 10) return true;
    else return false;
}
bool Board::canMoveSHI(int moveId, int row, int col, int)
{
    /*
     * 棋子必须在九宫格内
     * 移动步长为一格
     * 只能走对角线
     * */
    if (col < 3 || col > 5) return false;
    if (isBottom(moveId))
    {
        if (row < 7) return false;
    }
    else
    {
        if (row > 2) return false;
    }

    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int d = abs(dr) * 10 + abs(dc);
    if (d == 11) return true;
    else return false;
}
bool Board::canMoveCHE(int moveId, int row, int col, int)
{
    /*
     * 只能走直线
     * 直线上无障碍物
     * */
    int num = countStonesInLine(moveId, row, col);
    return num == 0;
}
bool Board::canMoveMA(int moveId, int row, int col, int)
{
    /*
     * 只能走日字型
     * 不能被拌腿
     * */
    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int d = abs(dr) * 10 + abs(dc);
    if (d == 12)
    {
        int step = dc < 0 ? 1 : -1;
        auto leg = std::make_pair(_s[moveId]._row, _s[moveId]._col + step);
        if (_posMap.find(leg) != _posMap.end())
            return false;
        return true;
    }
    else if (d == 21)
    {
        int step = dr < 0 ? 1 : -1;
        auto leg = std::make_pair(_s[moveId]._row + step, _s[moveId]._col);
        if (_posMap.find(leg) != _posMap.end())
            return false;
        return true;
    }
    else
        return false;
}
bool Board::canMovePAO(int moveId, int row, int col, int killId)
{
    /*
     * 要么走无障碍物的直线，要么支个架子打对方
     */
    int num = countStonesInLine(moveId, row, col);
    if ((num == 0 && killId == -1) ||
           (num == 1 && killId != -1)) return true;
    return false;
}
bool Board::canMoveBING(int moveId, int row, int col, int)
{
    /*
     * 过河前，只能向前走；过河后，可以向两边走
     * 每次只能移动一格
     */
    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int d = abs(dr) * 10 + abs(dc);
    if (isBottom(moveId))
    {
        if (_s[moveId]._row > 4)
            return dr == 1 && dc == 0;
        else
        {
            if (d == 10)
            {
                if (dr == 1) return true;
            }
            if (d == 1) return true;
        }
        return false;
    }
    else
    {
        if (_s[moveId]._row < 5)
            return dr == -1 && dc == 0;
        else
        {
            if (d == 10)
            {
                if (dr == -1) return true;
            }
            if (d == 1) return true;
        }
        return false;
    }
}
bool Board::canMoveXIANG(int moveId, int row, int col, int)
{
    /*
     * 只能走田字型
     * 不能过河
     * 不能被拌眼
     * */
    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int d = abs(dr) * 10 + abs(dc);
    if (d == 22)
    {
        if (isBottom(moveId))
        {
            if (row < 5)
            {
                return false;
            }
        }
        else
        {
            if (row > 4) return false;
        }

        int stepR = dr < 0 ? 1 : -1;
        int stepC = dc < 0 ? 1 : -1;
        auto eye = std::make_pair(_s[moveId]._row + stepR, _s[moveId]._col + stepC);
        if (_posMap.find(eye) != _posMap.end())
            return false;
        return true;
    }
    return false;
}

void Board::relieveStone(int id, int row, int col)
{
    if (id == -1) return;
    auto p = std::make_pair(row, col);
    _s[id]._row = row;
    _s[id]._col = col;
    _posMap[p] = id;
    return;
}

void Board::slotBack()
{
    backOneStep();
    return;
}

void Board::backOneStep()
{
    if (_steps.empty()) return;

    std::shared_ptr<Step> lastStep = _steps.back(); _steps.pop_back();
    moveStone(lastStep->_moveId, lastStep->_rowFrom, lastStep->_colFrom);
    if (lastStep->_killId != -1)
    {
        relieveStone(lastStep->_killId, lastStep->_rowTo, lastStep->_colTo);
    }

    if (_steps.empty())
    {
        _isRedTurn = !_isRedTurn;
        update();
        return;
    }

    lastStep = _steps.back(); _steps.pop_back();
    moveStone(lastStep->_moveId, lastStep->_rowFrom, lastStep->_colFrom);
    if (lastStep->_killId != -1)
    {
        relieveStone(lastStep->_killId, lastStep->_rowTo, lastStep->_colTo);
    }
    update();
    return;
}
