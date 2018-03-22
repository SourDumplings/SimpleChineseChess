/*
 @Date    : 2018-03-21 16:54:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */


#ifndef STONE_H
#define STONE_H

#include <QString>

// 棋子

class Stone
{
public:
    Stone();
    ~Stone() = default;

    enum TYPE {JIANG, CHE, PAO, MA, BING, SHI, XIANG};

    int _row;
    int _col;
    int _id;
    bool _red;
    TYPE _type;

    void init(int id);

    QString getText();
};

#endif // STONE_H
