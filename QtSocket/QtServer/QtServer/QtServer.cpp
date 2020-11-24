#include "QtServer.h"
#include "Server.h"
QtServer::QtServer(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	Server *ser = new Server;
	ser->Init();
}
