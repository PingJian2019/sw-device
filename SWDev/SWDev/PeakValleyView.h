#pragma once

#include"ui_PeakValley.h"
#include "common_type.h"
#include "ReceiveDataManage.h"

class PeakValleyView : public QMainWindow
{
	Q_OBJECT
public:
	PeakValleyView(QWidget * parent = NULL, ReceiveDataManage * receiveData = NULL);

private slots:
	void OnRecDispPeakValley(int type, QString data);
	void OnRecLoadPeakValley(int type, QString data);

private:
	void InitTable();
	void InitTableData();
	void CreateConnection();

private:
	Ui::PeakValleyForm ui;

	ReceiveDataManage *		m_receiveData;
};