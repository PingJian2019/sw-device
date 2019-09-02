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
	~SWMainWindow();

	void Init();

private slots:
	void OnRecStartCom(int type, QString data);
	void OnRecStopCom(int type, QString data);

private:
	void InitView();
	void InitCommunication();
	void InitDev();

	void ReadDMData();

	void CreateConnection();

private:
	Ui::SWMainWindowClass ui;

	bool				m_isInitCom;
	bool				m_isInitDev;
	bool				m_isRecEndDev;

	ReceiveDataManage	m_receiveDataManage;


	TestSetupView m_testSetupView;
};
