#include <QTcpSocket>
#include <QObject>
#include <QString>
#include "QtServer.h"
#include <QTcpServer>
class Server : public QObject
{
	Q_OBJECT
public:
	explicit Server(QObject *parent = 0);
	~Server();
	static Server* GetInstance();
	void Init();
private slots:
	void newConnectionSlot();
	void DataReceived();
private:
	static Server         *m_pInstance;
	QTcpServer            *m_pTcpServer;
	QTcpSocket            *m_pTcpSocket;
	QString                m_strMessage;  //存放从服务器接收到的字符串
	quint16                m_qiBlockSize;  //存放文件的大小信息
};
