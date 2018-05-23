#include "NetGame.h"

NetGame::NetGame(bool isServer)
{
	_server = nullptr;
	_socket = nullptr;

	if (isServer)
	{
		_server = new QTcpServer(this);
		_server->listen(QHostAddress::Any, 8888);

		connect(_server, SIGNAL(newConnection()), this, SLOT(slotNewConnecion()));
	}
	else
	{
		_socket = new QTcpSocket(this);
		_socket->connectToHost(QHostAddress("127.0.0.1"), 8888);

		connect(_socket, SIGNAL(readyRead()), this, SLOT(slotRecv()));
	}
}


NetGame::~NetGame()
{
}

void NetGame::slotNewConnecion()
{
	// 如果_socket不为空，这说明已经建立好了连接，不再接受第三个人的连接了
	if (_socket != nullptr)	return;

	_socket = _server->nextPendingConnection();
	connect(_socket, SIGNAL(readyRead()), this, SLOT(slotRecv()));

	// 给对方发送数据
	char buf[2];
	buf[0] = 1;
	char isClientHasRed = 0; // 给客户端为黑棋，服务端为红棋
	buf[1] = isClientHasRed;

	_socket->write(buf, 2);

	init(isClientHasRed == 0);
}

void NetGame::slotRecv()
{
	QByteArray ba = _socket->readAll();
	char cmd = ba[0];
	if (cmd == 1)
	{
		// 初始化
		char isClientHasRed = ba[1];
		init(isClientHasRed == 1); // 看是否执红棋
	}
	else if (cmd == 2)
	{
		// 棋子动态数据
		int row = ba[1];
		int col = ba[2];
		int id = ba[3];
		Board::clickStone(id, row, col);
	}
}

void NetGame::clickStone(int id, int row, int col)
{
	// 不能走对方的棋子
	if (_selectedId == -1 && id != -1 &&
		(_s[id]._red != _isRedAtBottom))
		return;

	Board::clickStone(id, row, col);

	// 将点击信息发送给对方
	char buf[4];
	buf[0] = 2;
	buf[1] = 9 - row;
	buf[2] = 8 - col;
	buf[3] = id;
	_socket->write(buf, 4);
}
