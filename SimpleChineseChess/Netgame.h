#pragma once
#include "Board.h"
#include "encoding.h"

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

/*
	信息及报文结构：
	1.执红方还是黑方，服务端发出，客户端接收
	第一个字节固定是1，第二个字节1表示接收方走红棋，0表示接收方走黑棋
	2.点击信息
	第一个字节固定是2，第二个字节是row，第三个是col，第四个是点击的棋子id

*/

class NetGame :
	public Board
{
	Q_OBJECT
public:
	NetGame(bool isServer);
	~NetGame();
	void clickStone(int id, int row, int col) override;

private:
	QTcpServer *_server;
	QTcpSocket *_socket;

public slots:
	void slotNewConnecion();
	void slotRecv();

};

