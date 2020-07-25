#pragma once

#include <QObject>

class Directory : public QObject
{
public:
	static QString GetApplicationDir();
	static QString GetRecordDir();

	static QString GetLatestRecordDir();

	static QString GetLatestFileName();

	static bool CreateDir(QString dir);
};