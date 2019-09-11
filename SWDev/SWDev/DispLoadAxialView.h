#pragma once
#include"ui_DispLoadAxial.h"
#include "common_type.h"
#include "ReceiveDataManage.h"

class DispLoadAxialView : public QMainWindow
{
	Q_OBJECT
public:
	DispLoadAxialView(QWidget * parent = NULL, ReceiveDataManage * receiveData = NULL);

private:
	void CreateConnection();

private slots:
	void OnRecRTDispAndLoadValue(int type, QString data);


private:
	Ui::DispLoadAxialForm ui;

	ReceiveDataManage *		m_receiveData;
};