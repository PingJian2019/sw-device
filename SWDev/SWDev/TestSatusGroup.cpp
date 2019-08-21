#include "TestSatusGroup.h"

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

TestSatusGroupView::TestSatusGroupView(QWidget * parent /* = NULL */)
	: QMainWindow(parent)
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
	ui.tableWidget->setItem(0, COLUMNCHANNEL, new QTableWidgetItem("Load"));
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