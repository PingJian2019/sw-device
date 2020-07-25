#include"PeakValleyView.h"

PeakValleyView::PeakValleyView(QWidget * parent, ReceiveDataManage * receiveData)
	: QMainWindow(parent)
	, m_receiveData(receiveData)
	, m_lastTimeStamp(0)
{
	ui.setupUi(this);

	move(1050, 48);
	setFixedSize(300, 130);

	setWindowFlags((this->windowFlags()) &
	(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	InitTable();
	InitTableData();

	CreateConnection();

	m_log.StartLog();
}

PeakValleyView::~PeakValleyView()
{
	m_log.Stop();
}


void PeakValleyView::CreateConnection()
{
	//connect(m_receiveData, SIGNAL(SigDispPeakValley(int, QString)), this, SLOT(OnRecDispPeakValley(int, QString)));
	//connect(m_receiveData, SIGNAL(SigLoadPeakValley(int, QString)), this, SLOT(OnRecLoadPeakValley(int, QString)));
	

	connect(m_receiveData, SIGNAL(SigRTLoadAndDispValue(int, QString)), this, SLOT(OnRecDispAndLoadPeakValley(int, QString)));

}

long long int PeakValleyView::GetCurrentTimeStamp()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	return currentTime.toMSecsSinceEpoch();
}

void PeakValleyView::OnRecDispAndLoadPeakValley(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 10)
	{
		return;
	}

	float difftime;

	long long int currentTimeStamp = GetCurrentTimeStamp();
	if (m_lastTimeStamp == 0)
	{
		difftime = 0;
		m_lastTimeStamp = currentTimeStamp;
	}
	else
	{
		difftime = (currentTimeStamp - m_lastTimeStamp) / 1000.0;
		m_lastTimeStamp = currentTimeStamp;
	}

	QString strLog;
	strLog = QString::number(difftime) + ",";

	QString strLoadValue = stringList[0];
	float fLoadVaue = strLoadValue.toFloat();
	fLoadVaue = fLoadVaue / 100;
	strLoadValue = QString::number(fLoadVaue);

	QString strDispVlaue = stringList[3];
	float fDispVlaue = strDispVlaue.toFloat();
	fDispVlaue = fDispVlaue / 100;
	strDispVlaue = QString::number(fDispVlaue);
	
	QString strLoadPeakValue = stringList[6];
	float fLoadPeakValue = strLoadPeakValue.toFloat();
	strLoadPeakValue = QString::number(fLoadPeakValue);

	QTableWidgetItem * item = ui.m_tableWidget->item(1, 1);
	item->setText(strLoadPeakValue);


	QString strLoadValleyValue = stringList[7];
	float fLoadValleyValue = strLoadValleyValue.toFloat();
	strLoadValleyValue = QString::number(fLoadValleyValue);

	item = ui.m_tableWidget->item(1, 2);
	item->setText(strLoadValleyValue);

	QString strDispPeakValue = stringList[8];
	float fDispPeakValue = strDispPeakValue.toFloat();
	strDispPeakValue = QString::number(fDispPeakValue);

	item = ui.m_tableWidget->item(0, 1);
	item->setText(strDispPeakValue);


	QString strDispValleyValue = stringList[9];
	float fDispValleyValue = strDispValleyValue.toFloat();
	strDispValleyValue = QString::number(fDispValleyValue);

	item = ui.m_tableWidget->item(1, 2);
	item->setText(strDispValleyValue);

	strLog += strDispVlaue;
	strLog += ",";
	strLog += strLoadValue;
	strLog += ",";
	strLog += strDispPeakValue;
	strLog += ",";
	strLog += strDispValleyValue;
	strLog += ",";
	strLog += strLoadPeakValue;
	strLog += ",";
	strLog += strLoadValleyValue;
	strLog += "\n";

	m_log.LogString(strLog.toStdString());

}

void PeakValleyView::OnRecDispPeakValley(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 2)
	{
		return;
	}

	QString strPeakValue = stringList[0];
	float fPeakValue = strPeakValue.toFloat();
	strPeakValue = QString::number(fPeakValue);

	QTableWidgetItem * item = ui.m_tableWidget->item(0, 1);
	item->setText(strPeakValue);


	QString strValleyValue = stringList[1];
	float fValleyValue = strValleyValue.toFloat();
	strValleyValue = QString::number(fValleyValue);

	item = ui.m_tableWidget->item(0, 2);
	item->setText(strValleyValue);
}

void PeakValleyView::OnRecLoadPeakValley(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 2)
	{
		return;
	}

	QString strPeakValue = stringList[0];
	float fPeakValue = strPeakValue.toFloat();
	strPeakValue = QString::number(fPeakValue);

	QTableWidgetItem * item = ui.m_tableWidget->item(1, 1);
	item->setText(strPeakValue);


	QString strValleyValue = stringList[1];
	float fValleyValue = strValleyValue.toFloat();
	strValleyValue = QString::number(fValleyValue);

	item = ui.m_tableWidget->item(1, 2);
	item->setText(strValleyValue);
}

void PeakValleyView::InitTable()
{
	ui.m_tableWidget->horizontalHeader()->setStretchLastSection(true);

	ui.m_tableWidget->setColumnWidth(0, 75);
	ui.m_tableWidget->setColumnWidth(1, 75);
	ui.m_tableWidget->setColumnWidth(2, 75);
	ui.m_tableWidget->setColumnWidth(3, 75);


	ui.m_tableWidget->setRowCount(2);
	ui.m_tableWidget->setRowHeight(0, 45);
	ui.m_tableWidget->setRowHeight(1, 45);

	ui.m_tableWidget->verticalHeader()->setHidden(true);
	ui.m_tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	ui.m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.m_tableWidget->setShowGrid(false);
}

void PeakValleyView::InitTableData()
{
	QColor color(0, 0, 255);
	QTableWidgetItem * item = NULL;

	item = new QTableWidgetItem("Disp");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_tableWidget->setItem(0, 0, item);

	item = new QTableWidgetItem("-11.620");
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_tableWidget->setItem(0, 1, item);

	item = new QTableWidgetItem("-12.226");
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_tableWidget->setItem(0, 2, item);

	item = new QTableWidgetItem("mm");
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_tableWidget->setItem(0, 3, item);

	item = new QTableWidgetItem("Load");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_tableWidget->setItem(1, 0, item);

	item = new QTableWidgetItem("-11.620");
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_tableWidget->setItem(1, 1, item);

	item = new QTableWidgetItem("-12.226");
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_tableWidget->setItem(1, 2, item);

	item = new QTableWidgetItem("N");
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.m_tableWidget->setItem(1, 3, item);
}