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
	void NewConnect(); //���ӷ�����
private slots:
	void ReadMessage();  //��������
	void DisplayError(QAbstractSocket::SocketError);  //��ʾ����
	
private:
	static Client         *m_pInstance;
	QTcpSocket            *m_pTcpSocket;
	QString                m_strMessage;  //��Ŵӷ��������յ����ַ���
	quint16                m_qiBlockSize;  //����ļ��Ĵ�С��Ϣ

};
#endif // _CLIENT_H
