#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SWMainWindow.h"
#include "TestSetupView.h"
#include "TestSatusGroup.h"
#include "WaveFormView.h"
#include "PeakValleyView.h"
#include "DispLoadAxialView.h"

#include "SWCommunication.h"
#include "ReceiveDataManage.h"

class SWMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SWMainWindow(QWidget *parent = Q_NULLPTR);

	void InitView();

private:
	void InitCommunication();

	void CreateConnection();

private:
	Ui::SWMainWindowClass ui;

	ReceiveDataManage	m_receiveDataManage;


	TestSetupView m_testSetupView;
	/*TestSatusGroupView m_testGroupView;
	WaveFormView m_waveFormView;
	PeakValleyView m_peakValleyView;
	DispLoadAxialView m_dispLoadAxialView;*/
};
