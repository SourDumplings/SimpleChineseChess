/*
 @Date    : 2018-03-23 12:52:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
中国象棋-简洁版
 */

#ifndef CTRLPANEL_H
#define CTRLPANEL_H

// 控制面板，上面有个悔棋按钮

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class CtrlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CtrlPanel(QWidget *parent = nullptr);

    QPushButton  *_back, *_reStart;
    QLabel *_label;

signals:
    void sigBack();
    void sigReStart();

public slots:
};

#endif // CTRLPANEL_H
