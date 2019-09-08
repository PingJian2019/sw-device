#pragma once
#include "ui_AlignLoadSensor.h"
#include "ReceiveDataManage.h"
#include "common_type.h"

class AligLoadSensorDlgView : public QDialog
{
	Q_OBJECT
public:
	AligLoadSensorDlgView(QWidget * parent = nullptr, ReceiveDataManage * data = NULL);

private slots:
	void OnCalibrationBtnClicked();

	void OnRecClaibrationValue(int type, QString data);
	void OnRecSetCalibrationValue(int type, QString data);

private:
	void CreateConnection();

private:
	Ui::AlignLoadSensorDlg ui;

	ReceiveDataManage *		m_receiveData;
};