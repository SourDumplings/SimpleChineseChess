#include "NetGame.h"
#include <QDebug>

NetGame::NetGame(bool server)
{
    _server = nullptr;
    _socket = nullptr;

    if (server)
    {
        _server = std::make_shared<QTcpServer>(this);
        _server->listen(QHostAddress::Any, 9999);

        connect(_server.get(), SIGNAL(newConnection()),
                this, SLOT(slotNewConnection()));
    }
    else
    {
        _socket = std::make_shared<QTcpSocket>(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"), 9999);
    }
}

void NetGame::slotNewConnection()
{
    // 如果_socket不为空则不再接受连接
    // 因为下棋只能两个人下
    if (_socket) return;

    _socket = std::make_shared<QTcpSocket>(_server->nextPendingConnection());

    // 给对方发数据

}
