/*
 @Date    : 2018-03-21 16:54:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#include <QApplication>
#include "SingleGame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    // 人机对战
//    SingleGame board;
//     双人模式
    Board board;

    board.show();

    return app.exec();
}
