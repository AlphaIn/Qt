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
	//3. ��������˽�������
	m_pTcpSocket->connectToHost("127.0.0.1", 5550);
		//4. ͬ������-�ȴ����ݿɶ�
		//m_pTcpSocket->waitForReadyRead();
	//�������ݵ���ʱ����readyRead()�źţ�ִ�ж�ȡ���ݵ�readMessage()����
	NewConnect();
	connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
	
	//�����ִ���ʱ����error()�źţ�ִ��displayError()�ۺ���
	connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
		this, SLOT(DisplayError(QAbstractSocket::SocketError)));
}
void  Client::NewConnect()
{
	qDebug() << "Client::NewConnect";
	m_qiBlockSize = 0; //��ʼ����Ϊ0
	m_pTcpSocket->abort(); //ȡ�����е�����
	QString l_strHostIp("127.0.0.1"), l_strHostPort("5550");

	//��������
	QByteArray l_baBlock;//�����ݴ�����Ҫ���͵�����
	QDataStream l_dsOut(&l_baBlock, QIODevice::WriteOnly); //ʹ��������д������
	l_dsOut.setVersion(QDataStream::Qt_4_6);//�����������İ汾���ͻ��˺ͷ�������ʹ�õİ汾Ҫ��ͬ

	l_dsOut << (quint16)0;//Ԥ�����������ַ����ĳ���

	l_dsOut << tr("msg from client1");//�ļ�����

	l_dsOut.device()->seek(0);//����ָ�������ͷ
	l_dsOut << (quint16)(l_baBlock.size() - sizeof(quint16));//���ַ����ĳ��ȷ�����ǰ��Ԥ����λ��


	//���ӷ�����
	m_pTcpSocket->connectToHost(l_strHostIp, l_strHostPort.toInt());//���ӵ�����������ӽ����ȡ������ַ�Ͷ˿ں�
	m_pTcpSocket->write(l_baBlock);
}
void Client::ReadMessage()
{
	qDebug() << "Client::ReadMessage1";
	QDataStream l_qdsIn(m_pTcpSocket);
	l_qdsIn.setVersion(QDataStream::Qt_4_6); //�����������汾������Ҫ�ͷ���������ͬ
	quint16 l_iTemp;

	if (m_qiBlockSize == 0) //����Ǹտ�ʼ��������
	{
		qDebug() << "Client::m_qiBlockSize==0";
		//�жϽ��յ������Ƿ������ֽڣ�Ҳ�����ļ��Ĵ�С��Ϣ
		//������򱣴浽blockSize�����У�û���򷵻أ�������������
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

	//���û�еõ�ȫ�������ݣ��򷵻أ�������������
	l_qdsIn >> m_strMessage; //�����յ������ݴ�ŵ�������

	qDebug() << "ReadMessage: m_strMessage:" << m_strMessage;
	//ui->messageLabel->setText(message);//��ʾ���յ�������
}
void Client::DisplayError(QAbstractSocket::SocketError)
{
	qDebug() << "SocketError is:" << m_pTcpSocket->errorString(); //���������Ϣ
}
