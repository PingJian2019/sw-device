#include "SWMainWindow.h"

#include <QDesktopWidget>
#include <QRect>

SWMainWindow::SWMainWindow(QWidget *parent)
	: QMainWindow(parent)
	, m_testSetupView(this)
{
	ui.setupUi(this);

	QRect rect = QApplication::desktop()->screenGeometry();
	setMinimumSize(QSize(rect.width(), rect.height()));

	InitCommunication();
}

void SWMainWindow::InitView()
{
	m_testSetupView.show();
}

void SWMainWindow::InitCommunication()
{
	//init serial port
	SWCommunication * pInstance = SWCommunication::GetInstance();
	pInstance->InitializeCommunication("COM1", "9600");
	pInstance->SetIReceiveData(&m_receiveDataManage);

	//init device
	pInstance->StartCommunication();
	pInstance->ReadDM0to10();
	pInstance->ReadMR500to503();
	pInstance->ReadAlarmInfo();
	pInstance->WriteJog1Start();
	pInstance->WriteJog1Stop();

	//pInstance->RDDMData(200);
	//pInstance->RDSDMData(200, 3);

	//pInstance->RDMRData(500);
	//pInstance->RDSMRData(500,3);


	/*pInstance->WRDMData(200, "0540000");
	std::vector<char *>datalist;
	datalist.push_back("04555");
	datalist.push_back("djklajd");
	pInstance->WRSDMData(200, datalist);*/


	//init device
	//pInstance->StartCommunication();
	/*DownlinkMessage message;
	message.m_downlinkDataLen = 3;
	unsigned char command[3] = { 0x43,0x52,0x0D };
	memcpy(message.m_downlinkData, command, 3);
	pInstance->SendDownlinnkMessage(message);*/
}

void SWMainWindow::CreateConnection()
{

}
