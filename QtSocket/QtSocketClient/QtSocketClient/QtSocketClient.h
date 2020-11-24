#pragma once

#include <QtWidgets/QDialog>
#include "ui_QtSocketClient.h"
#include "Client.h"
class QtSocketClient : public QDialog
{
	Q_OBJECT

public:
	QtSocketClient(QWidget *parent = Q_NULLPTR);
	Client *cli;
private:
	Ui::QtSocketClientClass ui;
};
