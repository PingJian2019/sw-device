#include "LimitsDlgView.h"

#include <QComboBox>
#include "SWCommunication.h"

LimitsDlgView::LimitsDlgView(QWidget * parent, ReceiveDataManage * data)
	: QDialog(parent)
	, m_receiveData(data)
	, m_isRecDisp(false)
	, m_isRecLoad(false)
{
	ui.setupUi(this);
	
	move(300, 100);
	setFixedSize(600, 190);
	/*setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint) &
		~Qt::WindowContextHelpButtonHint);*/

	setWindowFlags((this->windowFlags()) &
		~Qt::WindowContextHelpButtonHint);

	InitTable();
	InitTableData();

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(OnOKBtnClicked()));
	connect(m_receiveData, SIGNAL(SigRecDispAlarmLimits(int, QString)), this, SLOT(OnRecSetDispAlarmLimitis(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecLoadAlramLimits(int, QString)), this, SLOT(OnRecSetLoadAlarmLimits(int, QString)));

	connect(m_receiveData, SIGNAL(SigRecDMSection1(int, QString)), this, SLOT(OnRecGetDispAlramLimitis(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecDMSection2(int, QString)), this, SLOT(OnRecGetLoadAlramLimitis(int, QString)));

}

void LimitsDlgView::InitTable()
{
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);

	ui.tableWidget->setColumnCount(3);
	for (int i = 0; i < 3; i++)
	{
		ui.tableWidget->setColumnWidth(i, 190);
	}

	ui.tableWidget->setRowCount(2);
	for (int i = 0; i < 2; i++)
	{
		ui.tableWidget->setRowHeight(i, 52);
	}

	QStringList headerList;
	headerList << tr("Channel") << tr("Minimum") << tr("Maximum");

	ui.tableWidget->setHorizontalHeaderLabels(headerList);
	ui.tableWidget->verticalHeader()->setHidden(true);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

void LimitsDlgView::InitTableData()
{
	QTableWidgetItem * item = NULL;
	item = new QTableWidgetItem(tr("Disp"));
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(0, 0, item);

	item = new QTableWidgetItem(tr("Load"));
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(1, 0, item);

	//minimum
	QColor color(0, 0, 255);
	item = new QTableWidgetItem(tr("-17.000"));
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(0, 1, item);

	item = new QTableWidgetItem(tr("-900.0"));
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(1, 1, item);

	//maximum
	item = new QTableWidgetItem(tr("20.000"));
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(0, 2, item);

	item = new QTableWidgetItem(tr("1000.0"));
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(1, 2, item);
}

void LimitsDlgView::OnOKBtnClicked()
{
	QString strDispAlarmMin = ui.tableWidget->item(0, 1)->text();
	QString strDispAlarmMax = ui.tableWidget->item(0, 2)->text();

	strDispAlarmMin = QString::number(strDispAlarmMin.toFloat() * 100);
	strDispAlarmMax = QString::number(strDispAlarmMax.toFloat() * 100);
	SWCommunication::GetInstance()->WriteDispAlarmLimits(strDispAlarmMax.toStdString(), strDispAlarmMin.toStdString());

	QString strLoadAlarmMin = ui.tableWidget->item(1, 1)->text();
	QString strLoadAlarmMax = ui.tableWidget->item(1, 2)->text();

	strLoadAlarmMin = QString::number(strLoadAlarmMin.toFloat() * 100);
	strLoadAlarmMax = QString::number(strLoadAlarmMax.toFloat() * 100);
	SWCommunication::GetInstance()->WriteLoadAlarmLimits(strLoadAlarmMax.toStdString(), strLoadAlarmMin.toStdString());

	m_isRecDisp = false;
	m_isRecLoad = false;
	ui.okButton->setEnabled(false);
}

void LimitsDlgView::OnRecSetDispAlarmLimitis(int type, QString data)
{
	m_isRecDisp = true;
	if (m_isRecDisp && m_isRecLoad)
	{
		ui.okButton->setEnabled(true);
	}
}

void LimitsDlgView::OnRecSetLoadAlarmLimits(int type, QString data)
{
	m_isRecLoad = true;
	if (m_isRecDisp && m_isRecLoad)
	{
		ui.okButton->setEnabled(true);
	}
}

void LimitsDlgView::OnRecGetDispAlramLimitis(int type, QString data)
{
	QStringList stringList = data.split(" ");

	if (stringList.length() < 7)
	{
		SWCommunication::GetInstance()->ReadDMSection1();
	}
	else
	{
		QString dispupAlarm = stringList[5];
		float idispupAlarm = dispupAlarm.toFloat();
		idispupAlarm = idispupAlarm / 100;
		dispupAlarm = QString::number(idispupAlarm);
		ui.tableWidget->item(0, 2)->setText(dispupAlarm);

		QString displowAlarm = stringList[6];
		float idisplowAlarm = displowAlarm.toFloat();
		idisplowAlarm = idisplowAlarm / 100;
		displowAlarm = QString::number(idisplowAlarm);
		ui.tableWidget->item(0, 1)->setText(displowAlarm);
	}
}

void LimitsDlgView::OnRecGetLoadAlramLimitis(int type, QString data)
{
	QStringList stringList = data.split(" ");

	if (stringList.length() < 4)
	{
		SWCommunication::GetInstance()->ReadDMSection2();
	}
	else
	{
		QString loadpupAlarm = stringList[2];
		float iloadupAlarm = loadpupAlarm.toFloat();
		iloadupAlarm = iloadupAlarm / 100;
		loadpupAlarm = QString::number(iloadupAlarm);
		ui.tableWidget->item(1, 2)->setText(loadpupAlarm);

		QString loadplowAlarm = stringList[3];
		float iloadlowAlarm = loadplowAlarm.toFloat();
		iloadlowAlarm = iloadlowAlarm / 100;
		loadplowAlarm = QString::number(iloadlowAlarm);
		ui.tableWidget->item(1, 1)->setText(loadplowAlarm);
	}
}