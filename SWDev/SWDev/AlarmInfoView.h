#pragma once

#include "ReceiveDataManage.h"
#include "common_type.h"

#include "ui_AlarmInfo.h"

class AlarmInfoView : public QMainWindow
{
	Q_OBJECT
public:
	AlarmInfoView(QWidget * parent = nullptr, ReceiveDataManage * receiveData = NULL);
	~AlarmInfoView();

private slots:
	void OnRecAlarmInfo(int type, QString data);
	void OnRecClearError(int type, QString data);
	void OnRecRestorError(int type, QString data);
	void OnClearBtnClicked();

private:
	void CreateConnection();

	void InitTable();
	void InitData();

private:
	ReceiveDataManage *			m_receiveData;

	Ui::AlarmInfoForm			ui;

};
