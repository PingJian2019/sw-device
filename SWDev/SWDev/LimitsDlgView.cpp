#include "LimitsDlgView.h"

#include <QComboBox>

LimitsDlgView::LimitsDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	move(300, 80);
	setFixedSize(600, 300);
	/*setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint) &
		~Qt::WindowContextHelpButtonHint);*/

	setWindowFlags((this->windowFlags()) &
		~Qt::WindowContextHelpButtonHint);

	InitTable();
	InitTableData();
}

void LimitsDlgView::InitTable()
{
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);

	ui.tableWidget->setColumnCount(5);
	for (int i = 0; i < 5; i++)
	{
		ui.tableWidget->setColumnWidth(i, 110);

	}

	QStringList headerList;
	headerList << "Channel" << "Minimum" << "Maximum" << "Time" << "Action" << "Group";

	ui.tableWidget->setHorizontalHeaderLabels(headerList);
	
	ui.tableWidget->setRowCount(6);
	ui.tableWidget->verticalHeader()->setHidden(true);
	//ui.tableWidget->horizontalHeader()->setHidden(true);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	//ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ui.tableWidget->setShowGrid(false);
}

void LimitsDlgView::InitTableData()
{
	QTableWidgetItem * item = NULL;
	item = new QTableWidgetItem("Disp");
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	ui.tableWidget->setItem(0, 0, item);

	item = new QTableWidgetItem("Load");
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	ui.tableWidget->setItem(1, 0, item);

	item = new QTableWidgetItem("DirCmdA");
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	ui.tableWidget->setItem(2, 0, item);

	item = new QTableWidgetItem("Axial cmd");
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	ui.tableWidget->setItem(3, 0, item);

	item = new QTableWidgetItem("Axial error");
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	ui.tableWidget->setItem(4, 0, item);

	item = new QTableWidgetItem("Axial div");
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	ui.tableWidget->setItem(5, 0, item);

	//minimum
	QColor color(0, 0, 255);
	item = new QTableWidgetItem("-17.000");
	item->setTextColor(color);
	ui.tableWidget->setItem(0, 1, item);

	item = new QTableWidgetItem("-900.0");
	item->setTextColor(color);
	ui.tableWidget->setItem(1, 1, item);

	item = new QTableWidgetItem("-10.000");
	item->setTextColor(color);
	ui.tableWidget->setItem(2, 1, item);

	item = new QTableWidgetItem("-7500.0");
	item->setTextColor(color);
	ui.tableWidget->setItem(3, 1, item);

	item = new QTableWidgetItem("-108.0");
	item->setTextColor(color);
	ui.tableWidget->setItem(4, 1, item);

	item = new QTableWidgetItem("-100.0");
	item->setTextColor(color);
	ui.tableWidget->setItem(5, 1, item);

	//maximum
	item = new QTableWidgetItem("20.000");
	item->setTextColor(color);
	ui.tableWidget->setItem(0, 2, item);

	item = new QTableWidgetItem("1000.0");
	item->setTextColor(color);
	ui.tableWidget->setItem(1, 2, item);

	item = new QTableWidgetItem("10.000");
	item->setTextColor(color);
	ui.tableWidget->setItem(2, 2, item);

	item = new QTableWidgetItem("7500.0");
	item->setTextColor(color);
	ui.tableWidget->setItem(3, 2, item);

	item = new QTableWidgetItem("108.0");
	item->setTextColor(color);
	ui.tableWidget->setItem(4, 2, item);

	item = new QTableWidgetItem("100.0");
	item->setTextColor(color);
	ui.tableWidget->setItem(5, 2, item);

	//time
	item = new QTableWidgetItem("0.0002");
	item->setTextColor(color);
	ui.tableWidget->setItem(0, 3, item);

	item = new QTableWidgetItem("0.0002");
	item->setTextColor(color);
	ui.tableWidget->setItem(1, 3, item);

	item = new QTableWidgetItem("0.0002");
	item->setTextColor(color);
	ui.tableWidget->setItem(2, 3, item);

	item = new QTableWidgetItem("0.0002");
	item->setTextColor(color);
	ui.tableWidget->setItem(3, 3, item);

	item = new QTableWidgetItem("0.0002");
	item->setTextColor(color);
	ui.tableWidget->setItem(4, 3, item);

	item = new QTableWidgetItem("0.0002");
	item->setTextColor(color);
	ui.tableWidget->setItem(5, 3, item);

	//action
	QStringList strList;
	strList << "Controlled Stop" << "Undefined";
	QComboBox * comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(0, 4, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(1, 4, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(2, 4, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(3, 4, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(4, 4, comBox);


	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(5, 4, comBox);

}