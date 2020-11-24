#ifndef _CLIENT_H
#define _CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	~Client();
	void Init();
	static Client* GetInstance();
	void NewConnect(); //连接服务器
private slots:
	void ReadMessage();  //接收数据
	void DisplayError(QAbstractSocket::SocketError);  //显示错误
	
private:
	static Client         *m_pInstance;
	QTcpSocket            *m_pTcpSocket;
	QString                m_strMessage;  //存放从服务器接收到的字符串
	quint16                m_qiBlockSize;  //存放文件的大小信息

};
#endif // _CLIENT_H
