#pragma once

#include "ui_TestSetup.h"

#include "TestSatusGroup.h"
#include "WaveFormView.h"
#include "PeakValleyView.h"
#include "DispLoadAxialView.h"

class TestSetupView : public QMainWindow
{
	Q_OBJECT
public:
	TestSetupView(QWidget * parent = NULL);

private:
	void CreateConnection();

	void InitView();
	void InitMoverTable();

private slots:
	void OnPeakValleyAction();
	void OnDispLoadAction();

private:
	Ui::TestSetupForm ui;


	TestSatusGroupView m_testGroupView;
	WaveFormView m_waveFormView;
	PeakValleyView m_peakValleyView;
	DispLoadAxialView m_dispLoadAxialView;
};