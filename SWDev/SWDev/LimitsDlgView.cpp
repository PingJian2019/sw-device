#include "LimitsDlgView.h"

#include <QComboBox>

LimitsDlgView::LimitsDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);
	
	move(300, 80);
	setFixedSize(600, 285);
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

	ui.tableWidget->setColumnCount(3);
	for (int i = 0; i < 3; i++)
	{
		ui.tableWidget->setColumnWidth(i, 190);
	}

	ui.tableWidget->setRowCount(4);
	for (int i = 0; i < 4; i++)
	{
		ui.tableWidget->setRowHeight(i, 50);
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
	item = new QTableWidgetItem(tr("Disp(D Model)"));
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(0, 0, item);

	item = new QTableWidgetItem(tr("Load(D Model)"));
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(1, 0, item);

	item = new QTableWidgetItem(tr("Disp(L Model)"));
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(2, 0, item);

	item = new QTableWidgetItem(tr("Load(L Model)"));
	item->setFlags(item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(3, 0, item);

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

	item = new QTableWidgetItem(tr("-10.000"));
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(2, 1, item);

	item = new QTableWidgetItem(tr("-7500.0"));
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(3, 1, item);


	//maximum
	item = new QTableWidgetItem(tr("20.000"));
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(0, 2, item);

	item = new QTableWidgetItem(tr("1000.0"));
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(1, 2, item);

	item = new QTableWidgetItem(tr("10.000"));
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(2, 2, item);

	item = new QTableWidgetItem("7500.0");
	item->setTextColor(color);
	item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.tableWidget->setItem(3, 2, item);
}