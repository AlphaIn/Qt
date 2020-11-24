#pragma once

#include <QtWidgets/QDialog>
#include "ui_QtServer.h"

class QtServer : public QDialog
{
	Q_OBJECT

public:
	QtServer(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtServerClass ui;
};
