/*
 @Date    : 2018-03-23 12:52:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#include "MainWindow.h"
#include "CtrlPanel.h"
#include <QHBoxLayout>
#include "MultiGame.h"
#include "SingleGame.h"

MainWindow::MainWindow(int gameType, QWidget *parent) : QWidget(parent)
{
    if(gameType == 1)
    {
        SingleGame *game = new SingleGame;
        CtrlPanel *panel = new CtrlPanel;

        QHBoxLayout *hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    }
    else if(gameType == 2)
    {
        MultiGame *game = new MultiGame;
        CtrlPanel *panel = new CtrlPanel;

        QHBoxLayout *hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    }
}
