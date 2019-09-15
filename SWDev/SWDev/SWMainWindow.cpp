#include "SWMainWindow.h"

#include <QDesktopWidget>
#include <QRect>

SWMainWindow::SWMainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_testSetupView(this,&m_receiveDataManage)
	, m_isInitCom(false)
	, m_isInitDev(false)
	, m_isRecEndDev(false)
{
	ui.setupUi(this);

	char cmd[2] = { 0x0D, 0x0A };

	QRect rect = QApplication::desktop()->screenGeometry();
	setMinimumSize(QSize(rect.width(), rect.height()));

	//InitCommunication();
	CreateConnection();
}

SWMainWindow::~SWMainWindow()
{
	SWCommunication * pInstance = SWCommunication::GetInstance();
	pInstance->StopCommnuication();
	/*while (!m_isRecEndDev)
	{
		Sleep(10);
	}*/

	int a = 0;
}

void SWMainWindow::Init()
{
	InitView();
	InitCommunication();
	InitDev();
}

void SWMainWindow::InitView()
{
	m_testSetupView.show();
}

void SWMainWindow::InitCommunication()
{
	//init serial port
	SWCommunication * pInstance = SWCommunication::GetInstance();
	m_isInitCom = pInstance->InitializeCommunication("COM3", "115200");
	pInstance->SetIReceiveData(&m_receiveDataManage);
}

void SWMainWindow::InitDev()
{
	SWCommunication * pInstance = SWCommunication::GetInstance();
	pInstance->StartCommunication();
}

void SWMainWindow::CreateConnection()
{
	connect(&m_receiveDataManage, SIGNAL(SigRecStartCommunication(int, QString)), this, SLOT(OnRecStartCom(int,QString)));
	connect(&m_receiveDataManage, SIGNAL(SigRecStopCommunication(int, QString)), this, SLOT(OnRecStopCom(int,QString)));
}

void SWMainWindow::ReadDMData()
{
	SWCommunication * pInstance = SWCommunication::GetInstance();
	pInstance->ReadMR300to303();
	pInstance->ReadDMSection1();
	pInstance->ReadDMSection2();
	pInstance->ReadDMSection3();
}

void SWMainWindow::OnRecStartCom(int type, QString data)
{
	if (data == "CC\r\n")
	{
		m_isInitDev = true;
		ReadDMData();

		SWCommunication::GetInstance()->StartReadRealData();
	}
	else
	{
		m_isInitDev = false;
	}
}

void SWMainWindow::OnRecStopCom(int type, QString data)
{
	m_isRecEndDev = true;
}
