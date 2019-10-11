#include "Directory.h"

#include <QtCore>
#include <QDir>
#include <QDateTime>

QString Directory::GetApplicationDir()
{
	QString execDir = QCoreApplication::applicationDirPath();
	// the path is like this: D:/aa/bb, why it is '/', not '\'?
	return execDir.left(execDir.lastIndexOf('/'));
}

QString Directory::GetRecordDir()
{
	QString dirpath = GetApplicationDir() + "/Record";
	QDir dir;
	bool isExist = false;
	isExist = dir.exists(dirpath);

	if (!isExist)
	{
		isExist = dir.mkdir(dirpath);
	}

	return isExist?dirpath:"";
}

QString Directory::GetLatestRecordDir()
{
	QString recordPath = GetApplicationDir() + "/Record";
	
	bool isExist = false;
	QDir dir;
	
	isExist = dir.exists(recordPath) || dir.mkdir(recordPath);
	if (!isExist) return "";

	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString year = currentDateTime.toString("yyyy");
	QString yearPath = recordPath + "/" + year;

	isExist = dir.exists(yearPath) || dir.mkdir(yearPath);
	if (!isExist)return "";
	
	QString month = currentDateTime.toString("MM");
	QString monthPath = yearPath + "/" + month;

	isExist = dir.exists(monthPath) || dir.mkdir(monthPath);
	if (!isExist)return "";

	QString day = currentDateTime.toString("dd");
	QString dayPath = monthPath + "/" + day;

	isExist = dir.exists(dayPath) || dir.mkdir(dayPath);
	if (isExist)
	{
		return dayPath;
	}
	else
	{
		return "";
	}
}

bool Directory::CreateDir(QString dirpath)
{
	bool isExist = false;

	QDir dir;
	isExist = dir.exists(dirpath);

	if (!isExist)
	{
		isExist = dir.mkdir(dirpath);
	}
	
	return isExist;
}