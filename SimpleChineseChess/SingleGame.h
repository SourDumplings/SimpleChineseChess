/*
 @Date    : 2018-03-21 16:54:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "Board.h"

class SingleGame: public Board
{
    Q_OBJECT
public:
    virtual void clickStone(int id, int row, int col);
    SingleGame(QWidget *parent = nullptr);
    std::shared_ptr<Step> getBestMove();
    void getAllPossibleMove(QVector<std::shared_ptr<Step>> &steps);

    void fakeMove(std::shared_ptr<Step> step);
    void unfakeMove(std::shared_ptr<Step> step);
    int calcScore();
    int getMinScore(int level, int currMaxScore);
    int getMaxScore(int level, int currMinScore);

    int _level;
public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
