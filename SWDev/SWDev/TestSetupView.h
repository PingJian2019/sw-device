#pragma once

#include "ui_TestSetup.h"

#include "TestSatusGroup.h"
#include "WaveFormView.h"
#include "PeakValleyView.h"
#include "DispLoadAxialView.h"


#include "LimitsDlgView.h"
#include "UnderPeakDlgView.h"
#include "AdjustMoverDlgView.h"
#include "PresetPropDlgView.h"
#include "WaveFormSetupDlgView.h"
#include "WaveFormCompensationDlgView.h"
#include "StandardDataSetupDlgView.h"
#include "PeakValleyDataSetupDlgView.h"
#include "AlignLoadSensorDlgView.h"
#include "AlarmInfoView.h"

#include "ReceiveDataManage.h"

class TestSetupView : public QMainWindow
{
	Q_OBJECT
public:
	TestSetupView(QWidget * parent = NULL, ReceiveDataManage * receiveData = NULL);

protected:
	bool eventFilter(QObject *watched, QEvent *event);

private:
	void CreateConnection();

	void InitView();
	void InitMoverTable();
	void InitMoverTableData();

	void InitInstallEvent();

private slots:
	void OnPeakValleyAction();
	void OnDispLoadAction();
	void OnWaveFormAction();
	void OnLimitsAction();
	void OnStandardDataAction();
	void OnPeakValleyDataAction();
	void OnCalibrationAction();
	void OnTestAlarmInfoAction();

	void OnLimitsBtnClicked();
	void OnUndePeakBtnClicked();
	void OnAdjustMoverBtnClicked();
	void OnPresetOneBtnClicked();
	void OnPresetTwoBtnClicked();
	
	void OnWaveFormSetupBtnClicked();
	void OnWaveFormCompenBtnClicked();

	void OnStandardDataSetupBtnClicked();
	void OnPeakValleyDataSetupBtnClicked();


	void OnStartStopBtnClicked();
	void OnServerBtnClicked();

	void OnRecSetPreDispValue(QString data);
	void OnRecSetPreLoadVlaue(QString data);


	void OnRecPreDispValue(int type, QString data);
	void OnRecPreLoadValue(int type, QString data);


	void OnRecStartStop(int type, QString data);
	void OnServerOnOff(int type, QString data);

	void OnRecStatus(int type, QString data);

private:
	Ui::TestSetupForm ui;

	TestSatusGroupView m_testGroupView;
	WaveFormView m_waveFormView;
	PeakValleyView m_peakValleyView;
	DispLoadAxialView m_dispLoadAxialView;

	LimitsDlgView	m_limitsDlgView;
	UnderPeakDlgView m_underPeakDlgView;
	AdjustMoverDlgView m_adjustMoverDlgView;
	PresetPropDlgView m_presetPropDlgView;
	WaveFormSetupDlgView m_waveFormSetupDlgView;
	WaveFormCompensationDlgView m_waveFormCompenDlgView;
	StandardDataSetupDlgView m_standardDataSetupDlgView;
	PeakValleyDataSetupDlgView m_peakValleyDataSetupDlgView;
	AligLoadSensorDlgView	m_alignLoadSensorDlgView;
	AlarmInfoView	m_alarmInfoView;



	ReceiveDataManage *		m_receiveData;

};