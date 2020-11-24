#include "Client.h"
#include <QDebug>
#include <QDataStream>
Client* Client::m_pInstance = 0;
Client::Client(QObject *paren) : QObject(paren)
{
	m_pTcpSocket = NULL;
	//Init();
}
Client::~Client()
{
}
Client* Client::GetInstance()
{
	if (0 == m_pInstance)
	{
		m_pInstance = new Client;
	}
	return m_pInstance;
}
void Client::Init()
{
	qDebug() << "Client::Init";
	m_pTcpSocket = new QTcpSocket(this);
	//3. 与服务器端建立连接
	m_pTcpSocket->connectToHost("127.0.0.1", 5550);
		//4. 同步处理-等待数据可读
		//m_pTcpSocket->waitForReadyRead();
	//当有数据到来时发出readyRead()信号，执行读取数据的readMessage()函数
	NewConnect();
	connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
	
	//当出现错误时发出error()信号，执行displayError()槽函数
	connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
		this, SLOT(DisplayError(QAbstractSocket::SocketError)));
}
void  Client::NewConnect()
{
	qDebug() << "Client::NewConnect";
	m_qiBlockSize = 0; //初始化其为0
	m_pTcpSocket->abort(); //取消已有的连接
	QString l_strHostIp("127.0.0.1"), l_strHostPort("5550");

	//发送数据
	QByteArray l_baBlock;//用于暂存我们要发送的数据
	QDataStream l_dsOut(&l_baBlock, QIODevice::WriteOnly); //使用数据流写入数据
	l_dsOut.setVersion(QDataStream::Qt_4_6);//设置数据流的版本，客户端和服务器端使用的版本要相同

	l_dsOut << (quint16)0;//预留出来保存字符串的长度

	l_dsOut << tr("msg from client1");//文件内容

	l_dsOut.device()->seek(0);//将流指针调整到头
	l_dsOut << (quint16)(l_baBlock.size() - sizeof(quint16));//将字符串的长度放在流前面预留的位置


	//连接服务器
	m_pTcpSocket->connectToHost(l_strHostIp, l_strHostPort.toInt());//连接到主机，这里从界面获取主机地址和端口号
	m_pTcpSocket->write(l_baBlock);
}
void Client::ReadMessage()
{
	qDebug() << "Client::ReadMessage1";
	QDataStream l_qdsIn(m_pTcpSocket);
	l_qdsIn.setVersion(QDataStream::Qt_4_6); //设置数据流版本，这里要和服务器端相同
	quint16 l_iTemp;

	if (m_qiBlockSize == 0) //如果是刚开始接收数据
	{
		qDebug() << "Client::m_qiBlockSize==0";
		//判断接收的数据是否有两字节，也就是文件的大小信息
		//如果有则保存到blockSize变量中，没有则返回，继续接收数据
		if (m_pTcpSocket->bytesAvailable() < (int)sizeof(quint16))
		{
			qDebug() << "ReadMessage: m_pTcpSocket->bytesAvailable<(int)sizeof(quint16) when m_qiBlockSize=0";
			return;
		}
		l_qdsIn >> m_qiBlockSize;
		l_qdsIn >> l_iTemp;
	}

	qDebug() << "m_qiBlockSize:" << m_qiBlockSize;
	qDebug() << "l_iTemp:" << l_iTemp;
	qDebug() << "bytesAvailable:" << m_pTcpSocket->bytesAvailable();

	if (m_pTcpSocket->bytesAvailable() < m_qiBlockSize)
	{
		qDebug() << "ReadMessage: m_pTcpSocket->bytesAvailable() < m_qiBlockSize";
		return;
	}

	//如果没有得到全部的数据，则返回，继续接收数据
	l_qdsIn >> m_strMessage; //将接收到的数据存放到变量中

	qDebug() << "ReadMessage: m_strMessage:" << m_strMessage;
	//ui->messageLabel->setText(message);//显示接收到的数据
}
void Client::DisplayError(QAbstractSocket::SocketError)
{
	qDebug() << "SocketError is:" << m_pTcpSocket->errorString(); //输出错误信息
}
