#include "SWMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SWMainWindow w;
	w.showMaximized();
	w.Init();
	return a.exec();
}
