#include "TestSetupView.h"

TestSetupView::TestSetupView(QWidget * parent /* = NULL */)
	: QMainWindow(parent)
	, m_testGroupView(this)
	, m_waveFormView(this)
	, m_peakValleyView(this)
	, m_dispLoadAxialView(this)
	, m_limitsDlgView(this)
	, m_underPeakDlgView(this)
	, m_adjustMoverDlgView(this)
	, m_presetPropDlgView(this)
	, m_waveFormSetupDlgView(this)
{
	ui.setupUi(this);

	move(3, 50);
	setFixedSize(1100, 180);
	
	setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));


	InitView();
	InitMoverTable();
	InitMoverTableData();
	CreateConnection();
}

void TestSetupView::CreateConnection()
{
	connect(ui.actionPeak_Valley, SIGNAL(triggered()), this, SLOT(OnPeakValleyAction()));
	connect(ui.actionDispLoad, SIGNAL(triggered()), this, SLOT(OnDispLoadAction()));
	connect(ui.m_limitsBtn, SIGNAL(clicked()), this, SLOT(OnLimitsBtnClicked()));
	connect(ui.m_underPeakBtn, SIGNAL(clicked()), this, SLOT(OnUndePeakBtnClicked()));
	connect(ui.m_adjustMoverBtn, SIGNAL(clicked()), this, SLOT(OnAdjustMoverBtnClicked()));

	connect(ui.m_presetOneBtn, SIGNAL(clicked()), this, SLOT(OnPresetOneBtnClicked()));
	connect(ui.m_presetTwoBtn, SIGNAL(clicked()), this, SLOT(OnPresetTwoBtnClicked()));
	connect(ui.m_waveFormSetupBtn, SIGNAL(clicked()), this, SLOT(OnWaveFormSetupBtnClicked()));
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

	ui.m_moverTable->setRowCount(1);
	ui.m_moverTable->verticalHeader()->setHidden(true);
	ui.m_moverTable->setSelectionMode(QAbstractItemView::NoSelection);
	ui.m_moverTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TestSetupView::InitMoverTableData()
{
	QColor color(0, 0, 255);
	QTableWidgetItem * item = NULL;

	item = new QTableWidgetItem("Axial");
	item->setTextColor(color);
	ui.m_moverTable->setItem(0, 0, item);

	item = new QTableWidgetItem("Load");
	item->setTextColor(color);
	ui.m_moverTable->setItem(0, 1, item);

	item = new QTableWidgetItem("On");
	item->setTextColor(color);
	ui.m_moverTable->setItem(0, 2, item);

	item = new QTableWidgetItem("Running");
	item->setTextColor(color);
	ui.m_moverTable->setItem(0, 3, item);
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

void TestSetupView::OnLimitsBtnClicked()
{
	m_limitsDlgView.exec();
}

void TestSetupView::OnUndePeakBtnClicked()
{
	m_underPeakDlgView.exec();
}

void TestSetupView::OnAdjustMoverBtnClicked()
{
	m_adjustMoverDlgView.exec();
}

void TestSetupView::OnPresetOneBtnClicked()
{
	m_presetPropDlgView.exec();
}

void TestSetupView::OnPresetTwoBtnClicked()
{
	m_presetPropDlgView.exec();
}

void TestSetupView::OnWaveFormSetupBtnClicked()
{
	m_waveFormSetupDlgView.exec();
}