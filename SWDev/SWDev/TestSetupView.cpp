#include "TestSetupView.h"

#include <QMouseEvent>
#include "SWCommunication.h"

TestSetupView::TestSetupView(QWidget * parent, ReceiveDataManage * receiveData)
	: QMainWindow(parent)
	, m_testGroupView(this)
	, m_waveFormView(this)
	, m_peakValleyView(this)
	, m_dispLoadAxialView(this)
	, m_limitsDlgView(this, receiveData)
	, m_underPeakDlgView(this)
	, m_adjustMoverDlgView(this)
	, m_presetPropDlgView(this)
	, m_waveFormSetupDlgView(this,receiveData)
	, m_waveFormCompenDlgView(this,receiveData)
	, m_standardDataSetupDlgView(this)
	, m_alignLoadSensorDlgView(this, receiveData)
	, m_receiveData(receiveData)
{
	ui.setupUi(this);

	move(3, 48);
	setFixedSize(1040, 155);
	
	setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	InitView();
	InitMoverTable();
	InitMoverTableData();
	CreateConnection();

	InitInstallEvent();
}

void TestSetupView::CreateConnection()
{
	connect(ui.actionPeak_Valley, SIGNAL(triggered()), this, SLOT(OnPeakValleyAction()));
	connect(ui.actionDispLoad, SIGNAL(triggered()), this, SLOT(OnDispLoadAction()));
	connect(ui.actionWaveForm, SIGNAL(triggered()), this, SLOT(OnWaveFormAction()));
	connect(ui.actionLimits, SIGNAL(triggered()), this, SLOT(OnLimitsAction()));
	connect(ui.actionStandardData, SIGNAL(triggered()), this, SLOT(OnStandardDataAction()));
	connect(ui.actionPeekValleyData, SIGNAL(triggered()), this, SLOT(OnPeakValleyDataAction()));
	connect(ui.ActionClaibration, SIGNAL(triggered()), this, SLOT(OnCalibrationAction()));

	connect(ui.m_limitsBtn, SIGNAL(clicked()), this, SLOT(OnLimitsBtnClicked()));
	connect(ui.m_adjustMoverBtn, SIGNAL(clicked()), this, SLOT(OnAdjustMoverBtnClicked()));

	connect(ui.m_presetOneBtn, SIGNAL(clicked()), this, SLOT(OnPresetOneBtnClicked()));
	connect(ui.m_presetTwoBtn, SIGNAL(clicked()), this, SLOT(OnPresetTwoBtnClicked()));
	connect(ui.m_waveFormSetupBtn, SIGNAL(clicked()), this, SLOT(OnWaveFormSetupBtnClicked()));

	connect(ui.m_startBtn, SIGNAL(clicked()), this, SLOT(OnStartStopBtnClicked()));
	connect(ui.m_serverBtn, SIGNAL(clicked()), this, SLOT(OnServerBtnClicked()));

	connect(ui.m_waveFormCompemBtn, SIGNAL(clicked()), this, SLOT(OnWaveFormCompenBtnClicked()));
	connect(ui.m_standardDataSetupBtn, SIGNAL(clicked()), this, SLOT(OnStandardDataSetupBtnClicked()));
	connect(ui.m_peakValleyDataSetupBtn, SIGNAL(clicked()), this, SLOT(OnPeakValleyDataSetupBtnClicked()));

	connect(&m_waveFormSetupDlgView, SIGNAL(SigModelChanged(int)), &m_testGroupView, SLOT(OnModelChanged(int)));

	connect(m_receiveData, SIGNAL(SigStartStop(int, QString)), this, SLOT(OnRecStartStop(int, QString)));
	connect(m_receiveData, SIGNAL(SigServerOnOff(int, QString)), this, SLOT(OnServerOnOff(int, QString)));

}

void TestSetupView::OnRecStartStop(int type, QString data)
{
	if (data == "OK\r\n")
	{
		QString strText = ui.m_startBtn->text();
		if (strText == "Start")
		{
			ui.m_startBtn->setText("Stop");
		}
		else if (strText == "Stop")
		{
			ui.m_startBtn->setText("Start");
		}
		else
		{
		}
	}

	ui.m_startBtn->setEnabled(true);
}

void TestSetupView::OnServerOnOff(int type, QString data)
{
	if (data == "OK\r\n")
	{
		QString strText = ui.m_serverBtn->text();
		if (strText == "Server On")
		{
			ui.m_serverBtn->setText("Server Off");
		}
		else if (strText == "Server Off")
		{
			ui.m_serverBtn->setText("Server On");
		}
		else
		{
		}
	}

	ui.m_serverBtn->setEnabled(true);
}

void TestSetupView::InitView()
{
	m_testGroupView.show();
	m_waveFormView.show();
	m_peakValleyView.show();
	m_dispLoadAxialView.show();
}

void TestSetupView::InitInstallEvent()
{
	ui.m_presetOneBtn->installEventFilter(this);
	ui.m_presetTwoBtn->installEventFilter(this);
}

bool TestSetupView::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == ui.m_presetOneBtn || watched == ui.m_presetTwoBtn)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent * mEvent = (QMouseEvent *)event;
			if (mEvent->button() == Qt::RightButton)
			{
				m_presetPropDlgView.exec();
				return true;
			}
		}
	}
	return QMainWindow::eventFilter(watched, event);
}

void TestSetupView::InitMoverTable()
{
	/*ui.m_moverTable->horizontalHeader()->setStretchLastSection(true);

	for (int i = 0; i < 4; i++)
	{
		ui.m_moverTable->setColumnWidth(i, 73);
	}

	ui.m_moverTable->setRowCount(1);
	ui.m_moverTable->verticalHeader()->setHidden(true);
	ui.m_moverTable->setSelectionMode(QAbstractItemView::NoSelection);
	ui.m_moverTable->setEditTriggers(QAbstractItemView::NoEditTriggers);*/
}

void TestSetupView::InitMoverTableData()
{
	/*QColor color(0, 0, 255);
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
	ui.m_moverTable->setItem(0, 3, item);*/
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

void TestSetupView::OnWaveFormAction()
{
	m_waveFormView.show();
}

void TestSetupView::OnLimitsAction()
{
	m_limitsDlgView.exec();
}

void TestSetupView::OnStandardDataAction()
{

}

void TestSetupView::OnPeakValleyDataAction()
{

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
	//m_presetPropDlgView.exec();
}

void TestSetupView::OnPresetTwoBtnClicked()
{
	//m_presetPropDlgView.exec();
}

void TestSetupView::OnWaveFormSetupBtnClicked()
{
	m_waveFormSetupDlgView.exec();
}

void TestSetupView::OnStartStopBtnClicked()
{
	ui.m_startBtn->setEnabled(false);
	SWCommunication::GetInstance()->WriteTestStartStop();

}

void TestSetupView::OnServerBtnClicked()
{
	ui.m_serverBtn->setEnabled(false);
	SWCommunication::GetInstance()->WriteServiceOn();
}

void TestSetupView::OnWaveFormCompenBtnClicked()
{
	m_waveFormCompenDlgView.exec();
}

void TestSetupView::OnStandardDataSetupBtnClicked()
{
	m_standardDataSetupDlgView.exec();
}

void TestSetupView::OnPeakValleyDataSetupBtnClicked()
{
	m_peakValleyDataSetupDlgView.exec();
}

void TestSetupView::OnCalibrationAction()
{
	m_alignLoadSensorDlgView.exec();
}