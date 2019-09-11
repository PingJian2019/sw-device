#pragma once
#include "ui_WaveFormSetupDlg.h"

#include "SineWaveSetupView.h"

#include "common_type.h"
#include "ReceiveDataManage.h"

class WaveFormSetupDlgView : public QDialog
{
	Q_OBJECT
public:
	WaveFormSetupDlgView(QWidget * parent = nullptr, ReceiveDataManage * data = NULL);

private:
	void CreateConnection();

private slots:
	void OnSetBtnClicked();
	void OnCompleteSetParas();

signals:
	void SigModelChanged(int index);
	void SigUpdateTotalCountValue(QString value);

private:
	ReceiveDataManage *	m_receiveData;
	SineWaveSetupView m_sineWaveSetupView;


private:
	Ui::WaveFormSetupDlg ui;
};