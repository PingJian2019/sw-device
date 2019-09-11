#include "WaveFormSetupDlgView.h"

WaveFormSetupDlgView::WaveFormSetupDlgView(QWidget * parent, ReceiveDataManage * data)
	: QDialog(parent)
	, m_receiveData(data)
	, m_sineWaveSetupView(this,data)
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

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(OnSetBtnClicked()));
	connect(&m_sineWaveSetupView, SIGNAL(SigCompleteSetParas()), this, SLOT(OnCompleteSetParas()));
}

void WaveFormSetupDlgView::OnSetBtnClicked()
{
	m_sineWaveSetupView.SetModelParas();
	ui.okButton->setEnabled(false);
}

void WaveFormSetupDlgView::OnCompleteSetParas()
{
	ui.okButton->setEnabled(true);
	QString TCountValue = m_sineWaveSetupView.GetCountString();
	emit SigUpdateTotalCountValue(TCountValue);
}