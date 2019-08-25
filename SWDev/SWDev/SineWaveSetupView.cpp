#include "SineWaveSetupView.h"

SineWaveSetupView::SineWaveSetupView(QWidget * parent /* = nullptr */)
	:QWidget(parent)
{
	ui.setupUi(this);

	CreateConnection();
}

void SineWaveSetupView::CreateConnection()
{
	connect(ui.m_modelCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnModelComboxIndexChanged(int)));
}


void SineWaveSetupView::OnModelComboxIndexChanged(int index)
{
	emit SigModelChanged(index);
	int a = 0;
}