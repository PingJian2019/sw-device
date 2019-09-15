#pragma once

#include "ui_AdjustMoverDlg.h"
#include "ReceiveDataManage.h"
#include "common_type.h"

#include <QTimer>

#define TIMEFREQ	100

class AdjustMoverDlgView : public QDialog
{
	Q_OBJECT
public:
	AdjustMoverDlgView(QWidget * parent = nullptr, ReceiveDataManage * receiveData = NULL);

public:
	enum JOGFlag
	{
		JOG1UP = 0,
		JOG1DOWN,
		JOG2UP,
		JOG2DOWN,
		JOG3UP,
		JOG3DOWN,
	};

private slots:
	void OnHomeBtnClicked();
	void OnJog1SpeedBtnClicked();
	void OnJog2SpeedBtnClicked();
	void OnJog3SpeedBtnClicked();

	void OnJog1BtnUpClicked();
	void OnJog1BtnDownClicked();
	void OnJog2BtnUpClicked();
	void OnJog2BtnDownClicked();
	void OnJog3BtnUpClicked();
	void OnJog3BtnDownClicked();

	void OnJog1BtnUpPressed();
	void OnJog1BtnDownPressed();
	void OnJog2BtnUpPressed();
	void OnJog2BtnDownPressed();
	void OnJog3BtnUpPressed();
	void OnJog3BtnDownPressed();

	void OnJog1BtnUpReleased();
	void OnJog1BtnDownReleased();
	void OnJog2BtnUpReleased();
	void OnJog2BtnDownReleased();
	void OnJog3BtnUpReleased();
	void OnJog3BtnDownReleased();

	void OnTimeOut();

	void OnRecReadJogSpeed(int type, QString data);
	void OnRecSetJogSpeed(int type, QString data);
	void OnRecSetHome(int type, QString data);

	void OnRecJogMove(int type, QString data);

	void OnRecCurrentPostion(int tyep, QString data);


signals:

private:
	void CreateConnection();

private:
	Ui::AdjustMoverDlg ui;

	int							m_jogFlag;

	ReceiveDataManage *			m_receiveData;

	QTimer						m_timer;
};