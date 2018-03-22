#ifndef NETGAME_H
#define NETGAME_H

#include "Board.h"
#include <QTcpServer>
#include <QTcpSocket>

// 一个程序为服务器，一个为客户端

/*
 * 红方还是黑方，由服务端发出，客户端接收
 * 点击信息
 */


class NetGame: public Board
{
    Q_OBJECT
public:
    NetGame(bool server);

    std::shared_ptr<QTcpServer> _server;
    std::shared_ptr<QTcpSocket> _socket;

public slots:
    void slotNewConnection();
};

#endif // NETGAME_H
