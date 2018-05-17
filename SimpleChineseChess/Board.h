/*
 @Date    : 2018-03-21 16:54:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#ifndef BOARD_H
#define BOARD_H

#include "encoding.h"

#include <QFrame>
#include "Stone.h"
#include <map>
#include "Step.h"
#include <QVector>
#include <memory>

// 棋盘,10横9竖

class Board : public QFrame
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);

    void init();

    const int _r = 20; // 棋子的半径

    Stone _s[32];
    std::map<std::pair<int, int>, int> _posMap; // 存储各个棋子的棋盘坐标
    int _selectedId;
    bool _isRedTurn;

    QVector<std::shared_ptr<Step>> _steps;

    // draw fuctions
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    void drawStone(QPainter &painter, int id);


    // information functions
    QPoint center(int row, int col); // 返回棋子横纵坐标所对应的像素点坐标
    QPoint center(int id);
    bool getRowCol(QPoint pt, int &row, int &col); // 由像素点坐标得到相对于棋盘的坐标
    int countStonesInLine(int moveId, int row, int col);
    bool isBottom(int id);
    int getStoneId(int row, int col);

    // moving functions
    void click(QPoint pt);
    virtual void clickStone(int id, int row, int col);
    void saveStep(int moveid, int row, int col, QVector<std::shared_ptr<Step>>& steps, int killid);
    void saveStep(std::shared_ptr<Step> step, QVector<std::shared_ptr<Step>>& steps);
    void trySelectStone(int id);
    void tryMoveStone(int killid, int row, int col);
    void moveStone(int moveId, int row, int col);
    void killStone(int id);
    void relieveStone(int id, int row, int col);
    void backOneStep();

    // moving rules
    bool canMove(int moveId, int row, int col, int killId);
    bool canMoveJIANG(int moveId, int row, int col, int killId);
    bool canMoveSHI(int moveId, int row, int col, int killId);
    bool canMoveCHE(int moveId, int row, int col, int killId);
    bool canMoveMA(int moveId, int row, int col, int killId);
    bool canMovePAO(int moveId, int row, int col, int killId);
    bool canMoveBING(int moveId, int row, int col, int killId);
    bool canMoveXIANG(int moveId, int row, int col, int killId);

signals:
    void sigRedWin();
    void sigBlackWin();
public slots:
    void slotBack();
    void slotReStart();
};

#endif // BOARD_H
