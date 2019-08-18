#include"PeakValleyView.h"

PeakValleyView::PeakValleyView(QWidget * parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	move(1107, 50);
	setFixedSize(240, 130);

	setWindowFlags((this->windowFlags()) &
	(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	InitTable();
	InitTableData();
}

void PeakValleyView::InitTable()
{
	ui.m_tableWidget->horizontalHeader()->setStretchLastSection(true);

	/*for (int i = 0; i < 4; i++)
	{
		ui.m_tableWidget->setColumnWidth(i, 60);
	}*/
	ui.m_tableWidget->setColumnWidth(0, 90);
	ui.m_tableWidget->setColumnWidth(1, 50);
	ui.m_tableWidget->setColumnWidth(2, 50);
	ui.m_tableWidget->setColumnWidth(3, 50);


	ui.m_tableWidget->setRowCount(3);
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
	ui.m_tableWidget->setItem(0, 0, item);
	item = new QTableWidgetItem("-11.620");
	ui.m_tableWidget->setItem(0, 1, item);
	item = new QTableWidgetItem("-12.226");
	ui.m_tableWidget->setItem(0, 2, item);
	item = new QTableWidgetItem("mm");
	ui.m_tableWidget->setItem(0, 3, item);


	item = new QTableWidgetItem("Load");
	ui.m_tableWidget->setItem(1, 0, item);
	item = new QTableWidgetItem("-11.620");
	ui.m_tableWidget->setItem(1, 1, item);
	item = new QTableWidgetItem("-12.226");
	ui.m_tableWidget->setItem(1, 2, item);
	item = new QTableWidgetItem("N");
	ui.m_tableWidget->setItem(1, 3, item);


	item = new QTableWidgetItem("Axial cmd");
	ui.m_tableWidget->setItem(2, 0, item);
	item = new QTableWidgetItem("-11.620");
	ui.m_tableWidget->setItem(2, 1, item);
	item = new QTableWidgetItem("-12.226");
	ui.m_tableWidget->setItem(2, 2, item);
	item = new QTableWidgetItem("N");
	ui.m_tableWidget->setItem(2, 3, item);
}