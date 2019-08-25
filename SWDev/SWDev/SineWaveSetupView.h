#pragma once

#include "ui_SineWaveSetup.h"
#include "common_type.h"

class SineWaveSetupView : public QWidget
{
	Q_OBJECT
public:
	SineWaveSetupView(QWidget * parent = nullptr);

private:
	void CreateConnection();

private slots :
	void OnModelComboxIndexChanged(int index);
	//void OnOkBtnClicked();
	//void OnCancelBtnClicked();

signals:
	void SigModelChanged(int index);

private:
	Ui::SineWaveSetupForm ui;
};