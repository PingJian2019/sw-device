#include "TestSetupView.h"

#include <QMouseEvent>
#include "SWCommunication.h"

TestSetupView::TestSetupView(QWidget * parent, ReceiveDataManage * receiveData)
	: QMainWindow(parent)
	, m_testGroupView(this, receiveData)
	, m_waveFormView(this, receiveData)
	, m_peakValleyView(this, receiveData)
	, m_dispLoadAxialView(this, receiveData)
	, m_limitsDlgView(this, receiveData)
	, m_adjustMoverDlgView(this,receiveData)
	, m_presetPropDlgView(this, receiveData)
	, m_waveFormSetupDlgView(this,receiveData)
	, m_waveFormCompenDlgView(this,receiveData)
	, m_standardDataSetupDlgView(this)
	, m_alignLoadSensorDlgView(this, receiveData)
	, m_alarmInfoView(this,receiveData)
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
	connect(ui.actionTestAlarmInfo, SIGNAL(triggered()), this, SLOT(OnTestAlarmInfoAction()));


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
	connect(&m_waveFormSetupDlgView, SIGNAL(SigUpdateTotalCountValue(QString)), &m_testGroupView, SLOT(OnUpdateTotalCountValue(QString)));

	connect(&m_presetPropDlgView, SIGNAL(SigNotifyPreSetDispValue(QString)), this, SLOT(OnRecSetPreDispValue(QString)));
	connect(&m_presetPropDlgView, SIGNAL(SigNotifyPreSetLoadValue(QString)), this, SLOT(OnRecSetPreLoadVlaue(QString)));

	connect(m_receiveData, SIGNAL(SigRecDMSection1(int, QString)), this, SLOT(OnRecPreLoadValue(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecDMSection2(int, QString)), this, SLOT(OnRecPreDispValue(int, QString)));


	connect(m_receiveData, SIGNAL(SigStartStop(int, QString)), this, SLOT(OnRecStartStop(int, QString)));
	connect(m_receiveData, SIGNAL(SigServerOnOff(int, QString)), this, SLOT(OnServerOnOff(int, QString)));

	connect(m_receiveData, SIGNAL(SigRecMR300to303(int, QString)), this, SLOT(OnRecStatus(int, QString)));


}

void TestSetupView::OnRecSetPreDispValue(QString data)
{
	QString showDispValue = "PreSet Disp:" + data + "mm";
	ui.m_presetOneBtn->setText(showDispValue);
}

void TestSetupView::OnRecSetPreLoadVlaue(QString data)
{
	QString showloadValue = "PreSet Load:" + data + "N";
	ui.m_presetTwoBtn->setText(showloadValue);
}

void TestSetupView::OnRecPreDispValue(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 8)
	{
		return;
	}

	QString preDisValue = QString::number(stringList[7].toInt());
	QString showDispValue = "PreSet Disp:" + preDisValue + "mm";
	ui.m_presetOneBtn->setText(showDispValue);
}

void TestSetupView::OnRecPreLoadValue(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 10)
	{
		return;
	}

	QString preloadValue = QString::number(stringList[9].toInt());
	QString showloadValue = "PreSet Load:" + preloadValue + "N";
	ui.m_presetTwoBtn->setText(showloadValue);
}

void TestSetupView::OnRecStatus(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() == 4)
	{
		QString runState = stringList[1];
		if (runState == "1")
		{
			ui.m_startBtn->setText("Stop");
		}
		else
		{
			ui.m_startBtn->setText("Start");
		}

		QString serviceState = stringList[3];
		if (serviceState == "1")
		{
			ui.m_serverBtn->setText("Server Off");
		}
		else
		{
			ui.m_serverBtn->setText("Server On");
		}

	}
	else
	{
		SWCommunication::GetInstance()->ReadMR500to503();
	}
}

void TestSetupView::OnRecStartStop(int type, QString data)
{
	if (data == "OK")
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
	if (data == "OK")
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
	m_alarmInfoView.show();
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
	SWCommunication::GetInstance()->WritePreDispLoad();
	//m_presetPropDlgView.exec();
}

void TestSetupView::OnPresetTwoBtnClicked()
{
	SWCommunication::GetInstance()->WritePreLoadLoad();
	//m_presetPropDlgView.exec();
}

void TestSetupView::OnWaveFormSetupBtnClicked()
{
	m_waveFormSetupDlgView.exec();
}

void TestSetupView::OnStartStopBtnClicked()
{
	ui.m_startBtn->setEnabled(false);
	QString text = ui.m_startBtn->text();
	if (text == "Start")
	{
		SWCommunication::GetInstance()->WriteTestStart();

	}
	else
	{
		SWCommunication::GetInstance()->WriteTestStop();
	}
}

void TestSetupView::OnServerBtnClicked()
{
	ui.m_serverBtn->setEnabled(false);
	QString text = ui.m_serverBtn->text();
	if (text == "Server On")
	{
		SWCommunication::GetInstance()->WriteServiceOn();
	}
	else
	{
		SWCommunication::GetInstance()->WriteServiceOff();
	}
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

void TestSetupView::OnTestAlarmInfoAction()
{
	m_alarmInfoView.show();
}