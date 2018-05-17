/*
 @Date    : 2018-03-23 12:52:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#include "CtrlPanel.h"
#include <QGridLayout>
#include <QVBoxLayout>

CtrlPanel::CtrlPanel(QWidget *parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout(this);
    QVBoxLayout *bLay = new QVBoxLayout, *lLay = new QVBoxLayout;
    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(2, 1);
    grid->setRowStretch(0, 1);
    grid->setRowStretch(2, 1);

    grid->addLayout(bLay, 1, 1);
    grid->addLayout(lLay, 2, 1);

    _label = new QLabel;
    _label->setText("--by SourDumplings");
    lLay->addWidget(_label);

    bLay->addWidget(_back = new QPushButton("悔一步"));
    bLay->addWidget(_reStart = new QPushButton("重来"));
    connect(_back, SIGNAL(clicked()), this, SIGNAL(sigBack()));
    connect(_reStart, SIGNAL(clicked()), this, SIGNAL(sigReStart()));
}
