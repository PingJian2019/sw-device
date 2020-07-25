#include "SWMainWindow.h"
#include <QtWidgets/QApplication>

#include "Directory.h"
#include "Log.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SWMainWindow w;
	w.showMaximized();
	w.Init();

	Log log;

	QString currentPath = Directory::GetLatestRecordDir();

	int at = 0;
	return a.exec();
}
