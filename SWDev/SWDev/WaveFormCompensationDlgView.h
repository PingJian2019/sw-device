#pragma once

#include "ui_WaveFormCompensation.h"
#include "common_type.h"
#include "ReceiveDataManage.h"

class WaveFormCompensationDlgView : public QDialog
{
	Q_OBJECT
public:
	WaveFormCompensationDlgView(QWidget * parent = nullptr,ReceiveDataManage * data = NULL);

private slots:
	void OnSetBtnClicked();

	void OnRecWaveCompensation(int type, QString data);
	void OnRecReadWaveCompensation(int type, QString data);
private:
	void CreateConnection();

private:
	Ui::WaveFormCompensationDlg ui;

	ReceiveDataManage * m_receiveData;
};