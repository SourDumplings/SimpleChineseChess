/*
 @Date    : 2018-03-21 16:54:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */


#include "Stone.h"

Stone::Stone()
{

}

void Stone::init(int id)
{
    struct
    {
        int row, col;
        Stone::TYPE type;
    } pos[16] =
    {
    {0, 0, Stone::CHE},
    {0, 1, Stone::MA},
    {0, 2, Stone::XIANG},
    {0, 3, Stone::SHI},
    {0, 4, Stone::JIANG},
    {0, 5, Stone::SHI},
    {0, 6, Stone::XIANG},
    {0, 7, Stone::MA},
    {0, 8, Stone::CHE},

    {2, 1, Stone::PAO},
    {2, 7, Stone::PAO},
    {3, 0, Stone::BING},
    {3, 2, Stone::BING},
    {3, 4, Stone::BING},
    {3, 6, Stone::BING},
    {3, 8, Stone::BING},
    };

    _id = id;
    _red = _id < 16;

    if (_id > 15)
    {
        _row = pos[_id-16].row;
        _col = pos[_id-16].col;
        _type = pos[_id-16].type;
    }
    else
    {
        _row = 9 - pos[_id].row;
        _col = 8 - pos[_id].col;
        _type = pos[_id].type;
    }
    return;
}

QString Stone::getText()
{
    if (_red)
    {
        switch (_type)
        {
        case CHE:
            return "车";
        case JIANG:
            return "帅";
        case PAO:
            return "炮";
        case MA:
            return "马";
        case XIANG:
            return "相";
        case SHI:
            return "侍";
        case BING:
            return "兵";
        default:
            return "错";
        }
    }
    else
    {
        switch (_type)
        {
        case CHE:
            return "车";
        case JIANG:
            return "将";
        case PAO:
            return "砲";
        case MA:
            return "马";
        case XIANG:
            return "象";
        case SHI:
            return "士";
        case BING:
            return "卒";
        default:
            return "错";
        }
    }
}
