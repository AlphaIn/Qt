#include "QtSocketClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtSocketClient w;
	
	w.show();
	return a.exec();
}
