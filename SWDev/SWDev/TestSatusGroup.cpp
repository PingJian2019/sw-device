#include "TestSatusGroup.h"
#include "common_type.h"

#define COLUMNCHANNEL 0
#define COLUMNWAVEFORM 1
#define COLUMNDEF 2
#define COLUMNRCC 3
#define COLUMNTCC 4
#define COLUMNCOMP 5
#define COLUMNTD 6
#define COLUMNPV 7

#define MINWIDTH 30
#define MAXWIDTH 140

TestSatusGroupView::TestSatusGroupView(QWidget * parent, ReceiveDataManage * receiveData)
	: QMainWindow(parent)
	, m_receiveData(receiveData)
	, m_model(MODE_DISP)
{
	ui.setupUi(this);
	
	move(3, 238);
	setFixedSize(1040, 50);

	/*setWindowFlags((this->windowFlags()) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));*/

	setWindowFlags((this->windowFlags()) & (~Qt::WindowMaximizeButtonHint) 
		& (~Qt::WindowMinimizeButtonHint));

	InitTable();
	InitTableData();

	CreateConnection();
}

void TestSatusGroupView::CreateConnection()
{
	connect(m_receiveData, SIGNAL(SigRTLoadAndDispValue(int, QString)), this, SLOT(OnRecCurrentCount(int,QString)));
	connect(m_receiveData, SIGNAL(SigRecDMSection1(int, QString)), this, SLOT(OnRecLModelTotalCount(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecDMSection2(int, QString)), this, SLOT(OnRecDModelTotalCount(int, QString)));

	connect(m_receiveData, SIGNAL(SigRecDMSection1(int, QString)), this, SLOT(OnRecDispAlarmLimitis(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecDMSection2(int, QString)), this, SLOT(OnRecLoadAlarmLimitis(int, QString)));

}

void TestSatusGroupView::InitTable()
{
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	
	ui.tableWidget->setColumnWidth(COLUMNDEF, 220);
	ui.tableWidget->setColumnWidth(COLUMNRCC, 150);
	ui.tableWidget->setColumnWidth(COLUMNTCC, 150);

	ui.tableWidget->setRowCount(1);
	ui.tableWidget->verticalHeader()->setHidden(true);
	ui.tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TestSatusGroupView::InitTableData()
{
	QTableWidgetItem * item = NULL;
	ui.tableWidget->setItem(0, COLUMNCHANNEL, new QTableWidgetItem("D Model"));
	item = ui.tableWidget->item(0, COLUMNCHANNEL);
	item->setTextColor(QColor(0, 0, 255));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(0, COLUMNWAVEFORM, new QTableWidgetItem("Sine"));
	item = ui.tableWidget->item(0, COLUMNWAVEFORM);
	item->setTextColor(QColor(0, 0, 255));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	ui.tableWidget->setItem(0, COLUMNDEF, new QTableWidgetItem("-274,27.4N"));
	item = ui.tableWidget->item(0, COLUMNDEF);
	item->setTextColor(QColor(0, 0, 255));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	ui.tableWidget->setItem(0, COLUMNRCC, new QTableWidgetItem("100000"));
	item = ui.tableWidget->item(0, COLUMNRCC);
	item->setTextColor(QColor(0, 0, 255));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	ui.tableWidget->setItem(0, COLUMNTCC, new QTableWidgetItem("483098"));
	item = ui.tableWidget->item(0, COLUMNTCC);
	item->setTextColor(QColor(0, 0, 255));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	ui.tableWidget->setItem(0, COLUMNCOMP, new QTableWidgetItem("Amplitude"));
	item = ui.tableWidget->item(0, COLUMNCOMP);
	item->setTextColor(QColor(0, 0, 255));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	ui.tableWidget->setItem(0, COLUMNTD, new QTableWidgetItem("On"));
	item = ui.tableWidget->item(0, COLUMNTD);
	item->setTextColor(QColor(0, 0, 255));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	ui.tableWidget->setItem(0, COLUMNPV, new QTableWidgetItem("On"));
	item = ui.tableWidget->item(0, COLUMNPV);
	item->setTextColor(QColor(0, 0, 255));
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void TestSatusGroupView::OnModelChanged(int index)
{
	m_model = index;
	QTableWidgetItem * item = ui.tableWidget->item(0, COLUMNCHANNEL);
	if (index == MODE_DISP)
	{
		if (item)
		{
			item->setText("D Model");
		}
	}
	else if (index == MODE_LOAD)
	{
		if (item)
		{
			item->setText("L Model");
		}
	}
	else
	{

	}
}

void TestSatusGroupView::OnUpdateTotalCountValue(QString value)
{
	QTableWidgetItem * item = ui.tableWidget->item(0, COLUMNTCC);
	item->setText(value);
}

void TestSatusGroupView::OnRecCurrentCount(int type, QString data)
{
	QStringList stringList = data.split(" ");

	if (m_model == MODE_DISP)
	{
		if (stringList.length() >= 6)
		{
			QString strCount = stringList[5];
			QTableWidgetItem * item = ui.tableWidget->item(0, COLUMNRCC);
			item->setText(strCount);
		}
	}
	else if (m_model == MODE_LOAD)
	{
		if (stringList.length() >= 3)
		{
			QString strCount = stringList[2];
			QTableWidgetItem * item = ui.tableWidget->item(0, COLUMNRCC);
			item->setText(strCount);
		}
	}
	else{}

}

void TestSatusGroupView::OnRecDModelTotalCount(int type, QString data)
{
	if (m_model == MODE_DISP)
	{
		QStringList stringList = data.split(" ");
		if (stringList.length() >= 6)
		{
			QString strCount = stringList[5];
			QTableWidgetItem * item = ui.tableWidget->item(0, COLUMNTCC);
			item->setText(strCount);
		}
	}
}

void TestSatusGroupView::OnRecLModelTotalCount(int type, QString data)
{
	if (m_model == MODE_LOAD)
	{
		QStringList stringList = data.split(" ");
		if (stringList.length() >= 9)
		{
			QString strCount = stringList[8];
			QTableWidgetItem * item = ui.tableWidget->item(0, COLUMNTCC);
			item->setText(strCount);
		}
	}
}

void TestSatusGroupView::OnRecDispAlarmLimitis(int type, QString data)
{
	if (m_model == MODE_DISP)
	{
		QStringList stringList = data.split(" ");
		if (stringList.length() >= 7)
		{
			QString strUpLimits = stringList[5];
			QString strLowLimits = stringList[6];

			float fUpLimits = strUpLimits.toFloat();
			fUpLimits /= 100;
			float fLowLimits = strLowLimits.toFloat();
			fLowLimits /= 100;

			strUpLimits = QString::number(fUpLimits);
			strLowLimits = QString::number(fLowLimits);

			QString strFinal = strLowLimits + "," + strUpLimits;
			QTableWidgetItem * item = ui.tableWidget->item(0, COLUMNDEF);
			item->setText(strFinal);
		}
	}
}

void TestSatusGroupView::OnRecLoadAlarmLimitis(int type, QString data)
{
	if (m_model == MODE_LOAD)
	{
		QStringList stringList = data.split(" ");
		if (stringList.length() >= 4)
		{
			QString strUpLimits = stringList[2];
			QString strLowLimits = stringList[3];

			float fUpLimits = strUpLimits.toFloat();
			fUpLimits /= 100;
			float fLowLimits = strLowLimits.toFloat();
			fLowLimits /= 100;

			strUpLimits = QString::number(fUpLimits);
			strLowLimits = QString::number(fLowLimits);

			QString strFinal = strLowLimits + "," + strUpLimits;
			QTableWidgetItem * item = ui.tableWidget->item(0, COLUMNDEF);
			item->setText(strFinal);
		}
	}
}

void TestSatusGroupView::OnRecCompentation(int type, QString data)
{

}

