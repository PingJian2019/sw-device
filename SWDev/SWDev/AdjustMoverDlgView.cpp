#include "AdjustMoverDlgView.h"

#include "SWCommunication.h"

#include <QDebug>

AdjustMoverDlgView::AdjustMoverDlgView(QWidget * parent,ReceiveDataManage * receiveData)
	: QDialog(parent)
	, m_receiveData(receiveData)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(430, 300);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);

	CreateConnection();
}

void AdjustMoverDlgView::CreateConnection()
{
	connect(ui.m_homeBtn, SIGNAL(clicked()), this, SLOT(OnHomeBtnClicked()));
	connect(ui.m_speedBtn, SIGNAL(clicked()), this, SLOT(OnJogSpeedBtnClicked()));

	connect(ui.m_jog1UpBtn, SIGNAL(pressed()), this, SLOT(OnJog1BtnUpPressed()));
	connect(ui.m_jog2UpBtn, SIGNAL(pressed()), this, SLOT(OnJog2BtnUpPressed()));
	connect(ui.m_jog3UpBtn, SIGNAL(pressed()), this, SLOT(OnJog3BtnUpPressed()));

	connect(ui.m_jog1DownBtn, SIGNAL(pressed()), this, SLOT(OnJog1BtnDownPressed()));
	connect(ui.m_jog2DownBtn, SIGNAL(pressed()), this, SLOT(OnJog2BtnDownPressed()));
	connect(ui.m_jog3DownBtn, SIGNAL(pressed()), this, SLOT(OnJog3BtnDownPressed()));

	connect(ui.m_jog1UpBtn, SIGNAL(released()), this, SLOT(OnJog1BtnUpReleased()));
	connect(ui.m_jog2UpBtn, SIGNAL(released()), this, SLOT(OnJog2BtnUpReleased()));
	connect(ui.m_jog3UpBtn, SIGNAL(released()), this, SLOT(OnJog3BtnUpReleased()));

	connect(ui.m_jog1DownBtn, SIGNAL(released()), this, SLOT(OnJog1BtnDownReleased()));
	connect(ui.m_jog2DownBtn, SIGNAL(released()), this, SLOT(OnJog2BtnDownReleased()));
	connect(ui.m_jog3DownBtn, SIGNAL(released()), this, SLOT(OnJog3BtnDownReleased()));

	connect(&m_timer, SIGNAL(timeout()), this, SLOT(OnTimeOut()));


	connect(m_receiveData, SIGNAL(SigRecDMSection2(int, QString)), this, SLOT(OnRecReadJogSpeed(int, QString)));
	connect(m_receiveData, SIGNAL(SigSetJogSpeed(int, QString)), this, SLOT(OnRecSetJogSpeed(int, QString)));
	connect(m_receiveData, SIGNAL(SigClearDisp(int, QString)), this, SLOT(OnRecSetHome(int, QString)));

	connect(m_receiveData, SIGNAL(SigJogMove(int, QString)), this, SLOT(OnRecJogMove(int, QString)));

}

void AdjustMoverDlgView::OnTimeOut()
{
	switch (m_jogFlag)
	{
	case JOG1UP:
		SWCommunication::GetInstance()->WriteJog1UpStart();
		break;
	case JOG1DOWN:
		SWCommunication::GetInstance()->WriteJog1DownStart();
		break;
	case JOG2UP:
		SWCommunication::GetInstance()->WriteJog2UpStart();
		break;
	case JOG2DOWN:
		SWCommunication::GetInstance()->WriteJog2DownStart();
		break;
	case JOG3UP:
		SWCommunication::GetInstance()->WriteJog3UpStart();
		break;
	case JOG3DOWN:
		SWCommunication::GetInstance()->WriteJog3DownStart();
		break;
	default:
		break;
	}
}

void AdjustMoverDlgView::OnRecReadJogSpeed(int type,QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 7)
		return;

	QString jogSpeed = stringList[6];
	float fjogSpeed = jogSpeed.toFloat();
	fjogSpeed = fjogSpeed / 100;
	jogSpeed = QString::number(fjogSpeed);

	ui.m_speedLineEdit->setText(jogSpeed);
}

void AdjustMoverDlgView::OnRecSetJogSpeed(int type, QString data)
{
	if (data == "OK\r\n")
	{
	}

}

void AdjustMoverDlgView::OnRecSetHome(int type, QString data)
{
	if (data == "OK\r\n")
	{
	}
}

void AdjustMoverDlgView::OnRecJogMove(int type, QString data)
{
	switch (type)
	{
	case MESS_WRITE_JOG1_UP_START:
		break;
	case MESS_WRITE_JOG1_UP_STOP:
		break;
	case MESS_WRITE_JOG1_DOWN_START:
		break;
	case MESS_WRITE_JOG1_DOWN_STOP:
		break;
	case MESS_WRITE_JOG2_UP_START:
		break;
	case MESS_WRITE_JOG2_UP_STOP:
		break;
	case MESS_WRITE_JOG2_DOWN_START:
		break;
	case MESS_WRITE_JOG2_DOWN_STOP:
		break;
	case MESS_WRITE_JOG3_UP_START:
		break;
	case MESS_WRITE_JOG3_UP_STOP:
		break;
	case MESS_WRITE_JOG3_DOWN_START:
		break;
	case MESS_WRITE_JOG3_DOWN_STOP:
		break;
	default:
		break;
	}
}

void AdjustMoverDlgView::OnHomeBtnClicked()
{
	SWCommunication::GetInstance()->WriteDispClear0();
}

void AdjustMoverDlgView::OnJogSpeedBtnClicked()
{
	QString jogSpeed = ui.m_speedLineEdit->text();
	float fjogSpeed = jogSpeed.toFloat();
	fjogSpeed = fjogSpeed / 100;

	jogSpeed = QString::number(fjogSpeed);

	SWCommunication::GetInstance()->WriteJogSpeed(jogSpeed.toStdString());
}

void AdjustMoverDlgView::OnJog1BtnUpClicked()
{

}

void AdjustMoverDlgView::OnJog1BtnDownClicked()
{

}

void AdjustMoverDlgView::OnJog2BtnUpClicked()
{

}

void AdjustMoverDlgView::OnJog2BtnDownClicked()
{

}

void AdjustMoverDlgView::OnJog3BtnUpClicked()
{

}

void AdjustMoverDlgView::OnJog3BtnDownClicked()
{

}


void AdjustMoverDlgView::OnJog1BtnUpPressed()
{
	qDebug() << "OnJog1BtnUpPressed\n";

	m_jogFlag = JOG1UP;
	SWCommunication::GetInstance()->WriteJog1UpStart();

	m_timer.start(TIMEFREQ);
}

void AdjustMoverDlgView::OnJog1BtnDownPressed()
{
	qDebug() << "OnJog1BtnDownPressed\n";
	m_jogFlag = JOG1DOWN;

	SWCommunication::GetInstance()->WriteJog1DownStart();

	m_timer.start(TIMEFREQ);

}

void AdjustMoverDlgView::OnJog2BtnUpPressed()
{
	qDebug() << "OnJog2BtnUpPressed\n";
	m_jogFlag = JOG2UP;

	SWCommunication::GetInstance()->WriteJog2UpStart();

	m_timer.start(TIMEFREQ);

}

void AdjustMoverDlgView::OnJog2BtnDownPressed()
{
	qDebug() << "OnJog2BtnDownPressed\n";
	m_jogFlag = JOG2DOWN;

	SWCommunication::GetInstance()->WriteJog2DownStart();

	m_timer.start(TIMEFREQ);

}

void AdjustMoverDlgView::OnJog3BtnUpPressed()
{
	qDebug() << "OnJog3BtnUpPressed\n";
	m_jogFlag = JOG3UP;

	SWCommunication::GetInstance()->WriteJog3UpStart();

	m_timer.start(TIMEFREQ);

}

void AdjustMoverDlgView::OnJog3BtnDownPressed()
{
	qDebug() << "OnJog3BtnDownPressed\n";
	m_jogFlag = JOG3DOWN;

	SWCommunication::GetInstance()->WriteJog3DownStart();

	m_timer.start(TIMEFREQ);

}

void AdjustMoverDlgView::OnJog1BtnUpReleased()
{
	qDebug() << "OnJog1BtnUpReleased\n";
	m_timer.stop();
	SWCommunication::GetInstance()->WriteJog1UpStop();
}

void AdjustMoverDlgView::OnJog1BtnDownReleased()
{
	qDebug() << "OnJog1BtnDownReleased\n";
	m_timer.stop();
	SWCommunication::GetInstance()->WriteJog2DownStop();
}

void AdjustMoverDlgView::OnJog2BtnUpReleased()
{
	qDebug() << "OnJog2BtnUpReleased\n";
	m_timer.stop();
	SWCommunication::GetInstance()->WriteJog2UpStop();
}

void AdjustMoverDlgView::OnJog2BtnDownReleased()
{
	qDebug() << "OnJog2BtnDownReleased\n";
	m_timer.stop();
	SWCommunication::GetInstance()->WriteJog2DownStop();
}

void AdjustMoverDlgView::OnJog3BtnUpReleased()
{
	qDebug() << "OnJog3BtnUpReleased\n";
	m_timer.stop();
	SWCommunication::GetInstance()->WriteJog3UpStop();
}

void AdjustMoverDlgView::OnJog3BtnDownReleased()
{
	qDebug() << "OnJog3BtnDownReleased\n";
	m_timer.stop();
	SWCommunication::GetInstance()->WriteJog3DownStop();
}