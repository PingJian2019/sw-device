#include "TestSatusGroup.h"

#define COLUMNMOVE 0
#define COLUMNCHANNEL 1
#define COLUMNWAVEFORM 2
#define COLUMNDEF 3
#define COLUMNCS 4
#define COLUMNCC 5
#define COLUMNRCC 6
#define COLUMNTCC 7
#define COLUMNCOMP 8
#define COLUMNTD 9
#define COLUMNPV 10
#define COLUMNLC 11

#define MINWIDTH 30
#define MAXWIDTH 140

TestSatusGroupView::TestSatusGroupView(QWidget * parent /* = NULL */)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	move(3, 265);
	setFixedSize(1100, 55);

	/*setWindowFlags((this->windowFlags()) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));*/

	setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint));

	InitTable();
	InitTableData();
}

void TestSatusGroupView::InitTable()
{
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	int iwidth = (1100 - MINWIDTH * 3 - MAXWIDTH - 20) / 8;
	for (int i = 0; i < 9; i++)
	{
		ui.tableWidget->setColumnWidth(i, iwidth);
	}

	ui.tableWidget->setColumnWidth(COLUMNCS, MAXWIDTH);

	ui.tableWidget->setColumnWidth(COLUMNTD, MINWIDTH);
	ui.tableWidget->setColumnWidth(COLUMNPV, MINWIDTH);
	ui.tableWidget->setColumnWidth(COLUMNLC, MINWIDTH);

	ui.tableWidget->setRowCount(1);
	ui.tableWidget->verticalHeader()->setHidden(true);
	ui.tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TestSatusGroupView::InitTableData()
{
	QTableWidgetItem * item = NULL;
	ui.tableWidget->setItem(0, COLUMNMOVE, new QTableWidgetItem("Axial"));
	item = ui.tableWidget->item(0, COLUMNMOVE);
	item->setTextColor(QColor(0,0,255));
	ui.tableWidget->setItem(0, COLUMNCHANNEL, new QTableWidgetItem("Load"));
	item = ui.tableWidget->item(0, COLUMNCHANNEL);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNWAVEFORM, new QTableWidgetItem("Sine"));
	item = ui.tableWidget->item(0, COLUMNWAVEFORM);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNDEF, new QTableWidgetItem("-274,27.4N"));
	item = ui.tableWidget->item(0, COLUMNDEF);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNCS, new QTableWidgetItem("N/A"));
	item = ui.tableWidget->item(0, COLUMNCS);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNCC, new QTableWidgetItem("483098"));
	item = ui.tableWidget->item(0, COLUMNCC);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNRCC, new QTableWidgetItem("100000"));
	item = ui.tableWidget->item(0, COLUMNRCC);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNTCC, new QTableWidgetItem("483098"));
	item = ui.tableWidget->item(0, COLUMNTCC);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNCOMP, new QTableWidgetItem("Amplitude"));
	item = ui.tableWidget->item(0, COLUMNCOMP);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNTD, new QTableWidgetItem("On"));
	item = ui.tableWidget->item(0, COLUMNTD);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNPV, new QTableWidgetItem("On"));
	item = ui.tableWidget->item(0, COLUMNPV);
	item->setTextColor(QColor(0, 0, 255));
	ui.tableWidget->setItem(0, COLUMNLC, new QTableWidgetItem("On"));
	item = ui.tableWidget->item(0, COLUMNLC);
	item->setTextColor(QColor(0, 0, 255));
}