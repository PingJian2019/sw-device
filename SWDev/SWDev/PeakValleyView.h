#pragma once

#include"ui_PeakValley.h"
#include "common_type.h"
#include "ReceiveDataManage.h"
#include "Log.h"

#include <QDateTime>

class PeakValleyView : public QMainWindow
{
	Q_OBJECT
public:
	PeakValleyView(QWidget * parent = NULL, ReceiveDataManage * receiveData = NULL);
	~PeakValleyView();

private slots:
	void OnRecDispPeakValley(int type, QString data);
	void OnRecLoadPeakValley(int type, QString data);
	void OnRecDispAndLoadPeakValley(int type, QString data);

private:
	void InitTable();
	void InitTableData();
	void CreateConnection();

	long long int GetCurrentTimeStamp();

private:
	Ui::PeakValleyForm ui;


	Log						m_log;

	long long int			m_lastTimeStamp;

	ReceiveDataManage *		m_receiveData;
};