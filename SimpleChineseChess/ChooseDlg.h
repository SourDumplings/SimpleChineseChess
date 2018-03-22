/*
 @Date    : 2018-03-21 16:54:08
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#ifndef CHOOSEDLG_H
#define CHOOSEDLG_H

#include <QDialog>
#include <QPushButton>


class ChooseDlg: public QDialog
{
public:
    explicit ChooseDlg(QWidget *parent = 0);

    QPushButton *_buttons[2];
    int _selected;

signals:

public slots:
    void slotClicked();

};

#endif // CHOOSEDLG_H
