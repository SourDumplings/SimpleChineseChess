/*
 @Date    : 2018-03-23 12:52:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#ifndef MULTIGAME_H
#define MULTIGAME_H

#include "encoding.h"

// 两人游戏模式

#include "Board.h"

class MultiGame: public Board
{
public:
    MultiGame(QWidget *parent = nullptr);
};

#endif // MULTIGAME_H
