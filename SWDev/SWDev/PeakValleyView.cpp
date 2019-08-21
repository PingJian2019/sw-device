#include"PeakValleyView.h"

PeakValleyView::PeakValleyView(QWidget * parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	move(1050, 48);
	setFixedSize(300, 130);

	setWindowFlags((this->windowFlags()) &
	(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	InitTable();
	InitTableData();
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