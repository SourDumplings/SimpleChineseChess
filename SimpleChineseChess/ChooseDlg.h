/*
 @Date    : 2018-03-23 12:52:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

// 初始的选择游戏模式的对话框

#ifndef CHOOSEDLG_H
#define CHOOSEDLG_H

#include "encoding.h"

#include <QDialog>
#include <QPushButton>
#include <QLabel>

class ChooseDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseDlg(QWidget *parent = nullptr);

    QPushButton *onePGameMode,  *twoPGameMode;
    int _selected;
    QLabel *_label;

signals:

public slots:
    void slotClicked();
};

#endif // CHOOSEDLG_H
