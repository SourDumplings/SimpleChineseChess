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
#include <QDialog>

#include "MainWindow.h"
#include "ChooseDlg.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChooseDlg choosDlg;
    if (choosDlg.exec() != QDialog::Accepted)
        return 0;

    MainWindow w(choosDlg._selected);
    w.show();

    return app.exec();
}
