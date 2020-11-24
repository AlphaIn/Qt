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
		//��������������6666�˿ڣ������������������Ϣ�����ر�
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

	m_pTcpSocket = m_pTcpServer->nextPendingConnection();//��ȡ�Ѿ����������ӵ����׽���
	if (NULL == m_pTcpSocket)
	{
		qDebug() << "newConnectionSlot: m_pTcpSocket is null";
		return;
	}
	m_qiBlockSize = 0;
	m_strMessage = "";
	//�������ܿͻ��˷������ݵĲ�
	this->connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(DataReceived()));
	connect(m_pTcpSocket, SIGNAL(disconnected()), m_pTcpSocket, SLOT(deleteLater()));

	qDebug() << "newConnectionSlot:: successful!!!";
}
void Server::DataReceived()
{
	qDebug() << "Server::DataReceived";
	QDataStream l_qdsIn(m_pTcpSocket);
	l_qdsIn.setVersion(QDataStream::Qt_5_7); //�����������汾������Ҫ�ͷ���������ͬ

	if (m_qiBlockSize == 0) //����Ǹտ�ʼ��������
	{
		//�жϽ��յ������Ƿ������ֽڣ�Ҳ�����ļ��Ĵ�С��Ϣ
		//������򱣴浽blockSize�����У�û���򷵻أ�������������
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

	//���û�еõ�ȫ�������ݣ��򷵻أ�������������
	l_qdsIn >> m_strMessage; //�����յ������ݴ�ŵ�������
	qDebug() << "DataReceived:: success to get msg[" << m_strMessage << "] from client, so return msg";

	//���ͻ��˷�������
	QByteArray l_baBlock;//�����ݴ�����Ҫ���͵�����
	QDataStream l_dsOut(&l_baBlock, QIODevice::WriteOnly); //ʹ��������д������
	l_dsOut.setVersion(QDataStream::Qt_5_7);//�����������İ汾���ͻ��˺ͷ�������ʹ�õİ汾Ҫ��ͬ
	l_dsOut << (quint16)0;//Ԥ�����������ַ����ĳ���
	if (m_strMessage.contains("client1"))
	{
		l_dsOut << (quint16)9527;
	}
	else
	{
		l_dsOut << (quint16)8888;
	}
	l_dsOut << tr("hello Tcp!!!");//�ļ�����
	l_dsOut.device()->seek(0);//����ָ�������ͷ
	l_dsOut << (quint16)(l_baBlock.size() - 2 * sizeof(quint16));//���ַ����ĳ��ȷ�����ǰ��Ԥ����λ��
	m_pTcpSocket->write(l_baBlock);

	m_pTcpSocket->disconnectFromHost();//�ͷŽ��յ���socket
	qDebug() << "DataReceived:: successful!!!";
}
