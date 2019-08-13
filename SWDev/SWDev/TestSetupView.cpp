#include "TestSetupView.h"

TestSetupView::TestSetupView(QWidget * parent /* = NULL */)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	move(15, 50);
	setFixedSize(1100, 180);
	
	setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	ui.m_moverTable->horizontalHeader()->setStretchLastSection(true);

	for (int i = 0; i < 4; i++)
	{
		ui.m_moverTable->setColumnWidth(i, 73);
	}
}