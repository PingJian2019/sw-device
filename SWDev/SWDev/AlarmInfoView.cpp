#include "AlarmInfoView.h"
#include "SWCommunication.h"

AlarmInfoView::AlarmInfoView(QWidget * parent, ReceiveDataManage * receiveData)
	: QMainWindow(parent)
	, m_receiveData(receiveData)
{
	ui.setupUi(this);

	move(1050, 460);
	setFixedSize(300, 200);

	setWindowFlags((this->windowFlags()) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));
	CreateConnection();
	InitTable();
	InitData();
}

AlarmInfoView::~AlarmInfoView()
{

}

void AlarmInfoView::CreateConnection()
{
	connect(ui.m_clearBtn, SIGNAL(clicked()), this, SLOT(OnClearBtnClicked()));

	connect(m_receiveData, SIGNAL(SigTestAlarmInfo(int, QString)), this, SLOT(OnRecAlarmInfo(int, QString)));
	connect(m_receiveData, SIGNAL(SigClearError(int, QString)), this, SLOT(OnRecClearError(int, QString)));
	connect(m_receiveData, SIGNAL(SigRestoreError(int, QString)), this, SLOT(OnRecRestorError(int, QString)));

}

void AlarmInfoView::OnRecClearError(int type, QString data)
{
	if (data == "OK")
	{
		SWCommunication::GetInstance()->ReadAlarmInfo();
		SWCommunication::GetInstance()->WriteRestoreError();
	}

	ui.m_clearBtn->setEnabled(true);
}

void AlarmInfoView::OnRecRestorError(int type, QString data)
{
	if (data == "OK")
	{

	}
}

void AlarmInfoView::OnClearBtnClicked()
{
	ui.m_clearBtn->setEnabled(false);

	SWCommunication::GetInstance()->WriteClearError();

}

void AlarmInfoView::OnRecAlarmInfo(int type, QString data)
{
	QStringList stringList = data.split(" ");

	int len = stringList.length();
	if (len < 5)return;

	QString strAlarm;
	int iAlarm;
	QString strAlarmStatus = "Unknown";
	QTableWidgetItem * item;

	for (int i = 0; i < 5; i++)
	{
		strAlarm = stringList[i];
		iAlarm = strAlarm.toInt();
		item = ui.tableWidget->item(i, 1);
		if (iAlarm == 1) {
			strAlarmStatus = "Yes";
			item->setTextColor(QColor(255, 0, 0));
		}
		else {
			strAlarmStatus = "No";
			item->setTextColor(QColor(0, 0, 0));
		}
		item->setText(strAlarmStatus);
	}
}

void AlarmInfoView::InitTable()
{
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);

	ui.tableWidget->setColumnCount(2);
	for (int i = 0; i < 2; i++)
	{
		ui.tableWidget->setColumnWidth(i, 140);
	}

	ui.tableWidget->setRowCount(5);
	for (int i = 0; i < 5; i++)
	{
		ui.tableWidget->setRowHeight(i, 27);
	}

	QStringList headerList;
	headerList << tr("Alarm Type") << tr("Alarm Trigger");

	ui.tableWidget->setHorizontalHeaderLabels(headerList);
	ui.tableWidget->verticalHeader()->setHidden(true);
	ui.tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void AlarmInfoView::InitData()
{
	QColor color(0, 0, 255);
	QTableWidgetItem * item = NULL;

	item = new QTableWidgetItem("Control Axis");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(0, 0, item);

	item = new QTableWidgetItem("Axis Driver");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(1, 0, item);

	item = new QTableWidgetItem("Load Position");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(2, 0, item);

	item = new QTableWidgetItem("Position Load");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(3, 0, item);

	item = new QTableWidgetItem("PID");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(4, 0, item);


	item = new QTableWidgetItem("No");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(0, 1, item);

	item = new QTableWidgetItem("No");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(1, 1, item);

	item = new QTableWidgetItem("No");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(2, 1, item);

	item = new QTableWidgetItem("No");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(3, 1, item);

	item = new QTableWidgetItem("No");
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(4, 1, item);
}