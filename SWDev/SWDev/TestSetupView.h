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

class TestSetupView : public QMainWindow
{
	Q_OBJECT
public:
	TestSetupView(QWidget * parent = NULL);

private:
	void CreateConnection();

	void InitView();
	void InitMoverTable();
	void InitMoverTableData();

private slots:
	void OnPeakValleyAction();
	void OnDispLoadAction();

	void OnLimitsBtnClicked();
	void OnUndePeakBtnClicked();
	void OnAdjustMoverBtnClicked();
	void OnPresetOneBtnClicked();
	void OnPresetTwoBtnClicked();
	void OnWaveFormSetupBtnClicked();

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

};