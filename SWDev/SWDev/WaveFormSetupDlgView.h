#pragma once
#include "ui_WaveFormSetupDlg.h"

#include "SineWaveSetupView.h"

class WaveFormSetupDlgView : public QDialog
{
	Q_OBJECT
public:
	WaveFormSetupDlgView(QWidget * parent = nullptr);


private:
	void CreateConnection();

private slots:

signals:
	void SigModelChanged(int index);


private:
	SineWaveSetupView m_sineWaveSetupView;



private:
	Ui::WaveFormSetupDlg ui;
};