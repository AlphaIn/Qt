#include "QtSocketClient.h"
#include "Client.h"
QtSocketClient::QtSocketClient(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	cli = new Client;
	cli->Init();
}
