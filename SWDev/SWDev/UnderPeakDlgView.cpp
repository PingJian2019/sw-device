#include "UnderPeakDlgView.h"

#include <QComboBox>

UnderPeakDlgView::UnderPeakDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(800, 300);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);

	InitTable();
	InitTableData();
}

void UnderPeakDlgView::InitTable()
{
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);

	ui.tableWidget->setColumnCount(7);
	for (int i = 0; i < 4; i++)
	{
		ui.tableWidget->setColumnWidth(i, 100);
	}

	ui.tableWidget->setColumnWidth(5, 145);
	ui.tableWidget->setColumnWidth(6, 145);


	QStringList headerList;
	headerList << "Channel" << "Last Peak" << "Last Valley" << "Delta" << "Number" << "Action" << "Activate";

	ui.tableWidget->setHorizontalHeaderLabels(headerList);

	ui.tableWidget->setRowCount(6);
	ui.tableWidget->verticalHeader()->setHidden(true);
	//ui.tableWidget->horizontalHeader()->setHidden(true);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	//ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ui.tableWidget->setShowGrid(false);
}

void UnderPeakDlgView::InitTableData()
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

	//last peak
	QColor color(0, 0, 255);
	item = new QTableWidgetItem("-11.620");
	//item->setTextColor(color);
	ui.tableWidget->setItem(0, 1, item);

	item = new QTableWidgetItem("-28.4");
	//item->setTextColor(color);
	ui.tableWidget->setItem(1, 1, item);

	item = new QTableWidgetItem("0.000");
	//item->setTextColor(color);
	ui.tableWidget->setItem(2, 1, item);

	item = new QTableWidgetItem("16.0");
	//item->setTextColor(color);
	ui.tableWidget->setItem(3, 1, item);

	item = new QTableWidgetItem("Inactive");
	//item->setTextColor(color);
	ui.tableWidget->setItem(4, 1, item);

	item = new QTableWidgetItem("Inactive");
	//item->setTextColor(color);
	ui.tableWidget->setItem(5, 1, item);

	//last Valley
	item = new QTableWidgetItem("-12.230");
	//item->setTextColor(color);
	ui.tableWidget->setItem(0, 2, item);

	item = new QTableWidgetItem("-273.1");
	//item->setTextColor(color);
	ui.tableWidget->setItem(1, 2, item);

	item = new QTableWidgetItem("0.000");
	//item->setTextColor(color);
	ui.tableWidget->setItem(2, 2, item);

	item = new QTableWidgetItem("-317.9");
	//item->setTextColor(color);
	ui.tableWidget->setItem(3, 2, item);

	item = new QTableWidgetItem("Inactive");
	//item->setTextColor(color);
	ui.tableWidget->setItem(4, 2, item);

	item = new QTableWidgetItem("Inactive");
	//item->setTextColor(color);
	ui.tableWidget->setItem(5, 2, item);

	//delta
	item = new QTableWidgetItem("1.25");
	item->setTextColor(color);
	ui.tableWidget->setItem(0, 3, item);

	item = new QTableWidgetItem("62.5");
	item->setTextColor(color);
	ui.tableWidget->setItem(1, 3, item);

	item = new QTableWidgetItem("0.5");
	item->setTextColor(color);
	ui.tableWidget->setItem(2, 3, item);

	item = new QTableWidgetItem("375");
	item->setTextColor(color);
	ui.tableWidget->setItem(3, 3, item);

	item = new QTableWidgetItem("0");
	item->setTextColor(color);
	ui.tableWidget->setItem(4, 3, item);

	item = new QTableWidgetItem("0");
	item->setTextColor(color);
	ui.tableWidget->setItem(5, 3, item);

	//number
	item = new QTableWidgetItem("0");
	item->setTextColor(color);
	ui.tableWidget->setItem(0, 4, item);

	item = new QTableWidgetItem("0");
	item->setTextColor(color);
	ui.tableWidget->setItem(1, 4, item);

	item = new QTableWidgetItem("0");
	item->setTextColor(color);
	ui.tableWidget->setItem(2, 4, item);

	item = new QTableWidgetItem("0");
	item->setTextColor(color);
	ui.tableWidget->setItem(3, 4, item);

	item = new QTableWidgetItem("0");
	item->setTextColor(color);
	ui.tableWidget->setItem(4, 4, item);

	item = new QTableWidgetItem("0");
	item->setTextColor(color);
	ui.tableWidget->setItem(5, 4, item);

	//action
	QStringList strList;
	strList  << "Undefined" << "Controlled Stop";
	QComboBox * comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(0, 5, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(1, 5, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(2, 5, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(3, 5, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(4, 5, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList);
	ui.tableWidget->setCellWidget(5, 5, comBox);

	//Activate
	QStringList strList1;
	strList1 << "Inactivate" << "Activate";
	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList1);
	ui.tableWidget->setCellWidget(0, 6, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList1);
	ui.tableWidget->setCellWidget(1, 6, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList1);
	ui.tableWidget->setCellWidget(2, 6, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList1);
	ui.tableWidget->setCellWidget(3, 6, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList1);
	ui.tableWidget->setCellWidget(4, 6, comBox);

	comBox = new QComboBox(ui.tableWidget);
	comBox->addItems(strList1);
	ui.tableWidget->setCellWidget(5, 6, comBox);
}