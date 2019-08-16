#include"PeakValleyView.h"

PeakValleyView::PeakValleyView(QWidget * parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	move(1107, 50);
	setFixedSize(240, 150);

	setWindowFlags((this->windowFlags()) &
	(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	InitTableWidget();
}

void PeakValleyView::InitTableWidget()
{
	ui.m_tableWidget->horizontalHeader()->setStretchLastSection(true);

	for (int i = 0; i < 4; i++)
	{
		ui.m_tableWidget->setColumnWidth(i, 60);
	}
}