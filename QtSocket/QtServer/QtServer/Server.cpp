#include "server.h"
#include <QDebug>
#include <QTcpSocket>
#include <QDataStream>
Server* Server::m_pInstance = 0;
Server::Server(QObject *paren) : QObject(paren)
{
	m_pTcpServer = NULL;
	m_pTcpSocket = NULL;
}
Server::~Server()
{
}

Server* Server::GetInstance()
{
	if (0 == m_pInstance)
	{
		m_pInstance = new Server;
	}
	return m_pInstance;
}
void Server::Init()
{
	qDebug() << "Server::Init";
	m_pTcpServer = new QTcpServer(this);

	if (!m_pTcpServer->listen(QHostAddress::Any, 5550))
	{
		//监听本地主机的6666端口，如果出错就输出错误信息，并关闭
		qDebug() << "Init: fail to listen 6666";
		delete m_pTcpServer;
		m_pTcpServer = NULL;
		return;
	}
	connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()));
	qDebug() << "success::Init";
}
void Server::newConnectionSlot()
{
	qDebug() << "Server::newConnectionSlot1";

	m_pTcpSocket = m_pTcpServer->nextPendingConnection();//获取已经建立的连接的子套接字
	if (NULL == m_pTcpSocket)
	{
		qDebug() << "newConnectionSlot: m_pTcpSocket is null";
		return;
	}
	m_qiBlockSize = 0;
	m_strMessage = "";
	//关联接受客户端发来数据的槽
	this->connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(DataReceived()));
	connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));

	qDebug() << "newConnectionSlot:: successful!!!";
}
void Server::DataReceived()
{
	qDebug() << "Server::DataReceived";
	QDataStream l_qdsIn(m_pTcpSocket);
	l_qdsIn.setVersion(QDataStream::Qt_5_7); //设置数据流版本，这里要和服务器端相同

	if (m_qiBlockSize == 0) //如果是刚开始接收数据
	{
		//判断接收的数据是否有两字节，也就是文件的大小信息
		//如果有则保存到blockSize变量中，没有则返回，继续接收数据
		if (m_pTcpSocket->bytesAvailable() < (int)sizeof(quint16))
		{
			qDebug() << "DataReceived: m_pTcpSocket->bytesAvailable<(int)sizeof(quint16) when m_qiBlockSize=0";
			return;
		}
		l_qdsIn >> m_qiBlockSize;
	}

	qDebug() << "m_qiBlockSize:" << m_qiBlockSize;
	qDebug() << "bytesAvailable:" << m_pTcpSocket->bytesAvailable();
	
	if (m_pTcpSocket->bytesAvailable() < m_qiBlockSize)
	{
		qDebug() << "DataReceived: m_pTcpSocket->bytesAvailable() < m_qiBlockSize";
		return;
	}

	//如果没有得到全部的数据，则返回，继续接收数据
	l_qdsIn >> m_strMessage; //将接收到的数据存放到变量中
	qDebug() << "DataReceived:: success to get msg[" << m_strMessage << "] from client, so return msg";

	//给客户端返回数据
	QByteArray l_baBlock;//用于暂存我们要发送的数据
	QDataStream l_dsOut(&l_baBlock, QIODevice::WriteOnly); //使用数据流写入数据
	l_dsOut.setVersion(QDataStream::Qt_5_7);//设置数据流的版本，客户端和服务器端使用的版本要相同
	l_dsOut << (quint16)0;//预留出来保存字符串的长度
	if (m_strMessage.contains("client1"))
	{
		l_dsOut << (quint16)9527;
	}
	else
	{
		l_dsOut << (quint16)8888;
	}
	l_dsOut << tr("hello Tcp!!!");//文件内容
	l_dsOut.device()->seek(0);//将流指针调整到头
	l_dsOut << (quint16)(l_baBlock.size() - 2 * sizeof(quint16));//将字符串的长度放在流前面预留的位置
	m_pTcpSocket->write(l_baBlock);

	m_pTcpSocket->disconnectFromHost();//释放接收到的socket
	qDebug() << "DataReceived:: successful!!!";
}
