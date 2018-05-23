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
#include <QMessageBox>

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
        connect(panel, SIGNAL(sigReStart()), game, SLOT(slotReStart()));
        connect(game, SIGNAL(sigBlackWin()), this, SLOT(slotBlackWin()));
        connect(game, SIGNAL(sigRedWin()), this, SLOT(slotRedWin()));
    }
    else if(gameType == 2)
    {
        MultiGame *game = new MultiGame;
        CtrlPanel *panel = new CtrlPanel;

        QHBoxLayout *hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
        connect(panel, SIGNAL(sigReStart()), game, SLOT(slotReStart()));
        connect(game, SIGNAL(sigBlackWin()), this, SLOT(slotBlackWin()));
        connect(game, SIGNAL(sigRedWin()), this, SLOT(slotRedWin()));
    }
	else if (gameType == 3)
	{
		QMessageBox::StandardButton ret = QMessageBox::question(nullptr, "server or client", "是否作为服务器启动？");
		NetGame *game = new NetGame(ret == QMessageBox::Yes);
		CtrlPanel *panel = new CtrlPanel;

		QHBoxLayout *hLay = new QHBoxLayout(this);
		hLay->addWidget(game, 1);
		hLay->addWidget(panel);
		connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
		connect(panel, SIGNAL(sigReStart()), game, SLOT(slotReStart()));
		connect(game, SIGNAL(sigBlackWin()), this, SLOT(slotBlackWin()));
		connect(game, SIGNAL(sigRedWin()), this, SLOT(slotRedWin()));
	}
}

void MainWindow::slotBlackWin()
{
    QMessageBox::about(nullptr, "Game Over", "黑方胜。");
    return;
}

void MainWindow::slotRedWin()
{
    QMessageBox::about(nullptr, "Game Over", "红方胜。");
    return;
}

