#include "QtServer.h"
#include <QtWidgets/QApplication>
#include "Server.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtServer w;
	
	w.show();
	return a.exec();
}
