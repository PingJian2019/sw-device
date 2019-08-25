#include "WaveFormSetupDlgView.h"

WaveFormSetupDlgView::WaveFormSetupDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
	, m_sineWaveSetupView(this)
{
	ui.setupUi(this);
	move(200, 80);
	setFixedSize(800, 450);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);

	ui.stackedWidget->addWidget(&m_sineWaveSetupView);
	ui.stackedWidget->setCurrentWidget(&m_sineWaveSetupView);

	CreateConnection();
}

void WaveFormSetupDlgView::CreateConnection()
{
	connect(&m_sineWaveSetupView, SIGNAL(SigModelChanged(int)), this, SIGNAL(SigModelChanged(int)));
}