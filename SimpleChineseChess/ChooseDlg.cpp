/*
 @Date    : 2018-03-21 16:54:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#include "ChooseDlg.h"
#include <QVBoxLayout>

ChooseDlg::ChooseDlg(QWidget *parent): QDialog(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(_buttons[0] = new QPushButton("单人对弈"));
    lay->addWidget(_buttons[1] = new QPushButton("双人对弈"));

    for (int i = 0; i != 2; ++i)
    {
        connect(_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }
}

void ChooseDlg::slotClicked()
{
    QObject *s = sender();
    for(int i = 0; i != 2; ++i)
    {
        if(_buttons[i] == s)
        {
            _selected = i;
            break;
        }
    }
    accept();
    return;
}
