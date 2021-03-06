#include "AdjustMoverDlgView.h"

#include "SWCommunication.h"

#include <QDebug>

AdjustMoverDlgView::AdjustMoverDlgView(QWidget * parent,ReceiveDataManage * receiveData)
	: QDialog(parent)
	, m_receiveData(receiveData)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(430, 410);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);

	CreateConnection();
}

void AdjustMoverDlgView::CreateConnection()
{
	connect(ui.m_homeBtn, SIGNAL(clicked()), this, SLOT(OnHomeBtnClicked()));
	connect(ui.m_speedJog1Btn, SIGNAL(clicked()), this, SLOT(OnJog1SpeedBtnClicked()));
	connect(ui.m_speedJog2Btn, SIGNAL(clicked()), this, SLOT(OnJog2SpeedBtnClicked()));
	connect(ui.m_speedJog3Btn, SIGNAL(clicked()), this, SLOT(OnJog3SpeedBtnClicked()));


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

	connect(m_receiveData, SIGNAL(SigRTLoadAndDispValue(int, QString)), this, SLOT(OnRecCurrentPostion(int, QString)));

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

void AdjustMoverDlgView::OnRecCurrentPostion(int tyep, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() >=4 )
	{
		QString strPostion = stringList[3];
		float fPostion = strPostion.toFloat();
		fPostion = fPostion / 100;

		strPostion = QString::number(fPostion);
		ui.m_positionLabel->setText(strPostion);
	}
}

void AdjustMoverDlgView::OnRecReadJogSpeed(int type,QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 13)
	{
		SWCommunication::GetInstance()->ReadDMSection2();
	}
	else
	{
		QString jogSpeed1 = stringList[6];
		float fjogSpeed1 = jogSpeed1.toFloat();
		fjogSpeed1 = fjogSpeed1 / 100;
		jogSpeed1 = QString::number(fjogSpeed1);
		ui.m_speed1LineEdit->setText(jogSpeed1);

		QString jogSpeed2 = stringList[11];
		float fjogSpeed2 = jogSpeed2.toFloat();
		fjogSpeed2 = fjogSpeed2 / 100;
		jogSpeed2 = QString::number(fjogSpeed2);
		ui.m_speed2LineEdit->setText(jogSpeed2);

		QString jogSpeed3 = stringList[12];
		float fjogSpeed3 = jogSpeed3.toFloat();
		fjogSpeed3 = fjogSpeed3 / 100;
		jogSpeed3 = QString::number(fjogSpeed3);
		ui.m_speed3LineEdit->setText(jogSpeed3);
	}
}

void AdjustMoverDlgView::OnRecSetJogSpeed(int type, QString data)
{
	switch (type)
	{
	case MESS_WRITE_JOG1_SPEED:
		break;
	case MESS_WRITE_JOG2_SPEED:
		break;
	case MESS_WRITE_JOG3_SPEED:
		break;
	default:
		break;
	}

	if (data == "OK")
	{
	}

}

void AdjustMoverDlgView::OnRecSetHome(int type, QString data)
{
	if (data == "OK")
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

void AdjustMoverDlgView::OnJog1SpeedBtnClicked()
{
	QString jogSpeed = ui.m_speed1LineEdit->text();
	float fjogSpeed = jogSpeed.toFloat();
	fjogSpeed = fjogSpeed / 100;

	jogSpeed = QString::number(fjogSpeed);

	SWCommunication::GetInstance()->WriteJog1Speed(jogSpeed.toStdString());
}

void AdjustMoverDlgView::OnJog2SpeedBtnClicked()
{
	QString jogSpeed = ui.m_speed2LineEdit->text();
	float fjogSpeed = jogSpeed.toFloat();
	fjogSpeed = fjogSpeed / 100;

	jogSpeed = QString::number(fjogSpeed);

	SWCommunication::GetInstance()->WriteJog2Speed(jogSpeed.toStdString());
}

void AdjustMoverDlgView::OnJog3SpeedBtnClicked()
{
	QString jogSpeed = ui.m_speed3LineEdit->text();
	float fjogSpeed = jogSpeed.toFloat();
	fjogSpeed = fjogSpeed / 100;

	jogSpeed = QString::number(fjogSpeed);

	SWCommunication::GetInstance()->WriteJog3Speed(jogSpeed.toStdString());
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