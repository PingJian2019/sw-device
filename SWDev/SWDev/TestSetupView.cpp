#include "TestSetupView.h"

TestSetupView::TestSetupView(QWidget * parent /* = NULL */)
	: QMainWindow(parent)
	, m_testGroupView(this)
	, m_waveFormView(this)
	, m_peakValleyView(this)
	, m_dispLoadAxialView(this)
{
	ui.setupUi(this);

	move(15, 50);
	setFixedSize(1100, 180);
	
	setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	InitView();
	InitMoverTable();

	CreateConnection();
}

void TestSetupView::CreateConnection()
{
	connect(ui.actionPeak_Valley, SIGNAL(triggered()), this, SLOT(OnPeakValleyAction()));
	connect(ui.actionDispLoad, SIGNAL(triggered()), this, SLOT(OnDispLoadAction()));
}

void TestSetupView::InitView()
{
	m_testGroupView.show();
	m_waveFormView.show();
	m_peakValleyView.show();
	m_dispLoadAxialView.show();
}

void TestSetupView::InitMoverTable()
{
	ui.m_moverTable->horizontalHeader()->setStretchLastSection(true);

	for (int i = 0; i < 4; i++)
	{
		ui.m_moverTable->setColumnWidth(i, 73);
	}
}

void TestSetupView::OnPeakValleyAction()
{
	if (!m_peakValleyView.isVisible())
	{
		m_peakValleyView.show();
	}
}

void TestSetupView::OnDispLoadAction()
{
	if (!m_dispLoadAxialView.isVisible())
	{
		m_dispLoadAxialView.show();
	}
}