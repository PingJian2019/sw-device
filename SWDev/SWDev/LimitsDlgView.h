#pragma once

#include "ui_LimitsDlg.h"
#include "ReceiveDataManage.h"

class LimitsDlgView : public QDialog
{
	Q_OBJECT
public:
	LimitsDlgView(QWidget * parent = nullptr, ReceiveDataManage * data = NULL);

private slots:
	void OnOKBtnClicked();



	void OnRecSetDispAlarmLimitis(int type, QString data);
	void OnRecSetLoadAlarmLimits(int type, QString data);

	void OnRecGetDispAlramLimitis(int type, QString data);
	void OnRecGetLoadAlramLimitis(int type, QString data);


private:
	void InitTable();
	void InitTableData();

private:
	Ui::LimitsDlg ui;

	bool				m_isRecDisp;
	bool				m_isRecLoad;

	ReceiveDataManage * m_receiveData;

	
};