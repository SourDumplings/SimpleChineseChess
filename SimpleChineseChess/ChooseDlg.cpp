/*
 @Date    : 2018-03-23 12:52:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#include "ChooseDlg.h"
#include <QVBoxLayout>

ChooseDlg::ChooseDlg(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(onePGameMode = new QPushButton("人机对战"));
    lay->addWidget(twoPGameMode = new QPushButton("人人对战"));
	lay->addWidget(netGameMode = new QPushButton("网络对战"));

    _label = new QLabel;
    _label->setText("--by SourDumplings");
    lay->addWidget(_label);

    setMinimumSize(300, 100);

    connect(onePGameMode, SIGNAL(clicked()), this, SLOT(slotClicked()));
    connect(twoPGameMode, SIGNAL(clicked()), this, SLOT(slotClicked()));
	connect(netGameMode, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void ChooseDlg::slotClicked()
{
    QObject *s = sender();
    if (s == onePGameMode)
        _selected = 1;
    else if (s == twoPGameMode)
        _selected = 2;
	else if (s == netGameMode)
	{
		_selected = 3;
	}
    accept();
    return;
}


