/*
 @Date    : 2018-03-23 12:52:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(int gameType, QWidget *parent = nullptr);

signals:

public slots:
    void slotBlackWin();
    void slotRedWin();
};

#endif // MAINWINDOW_H
