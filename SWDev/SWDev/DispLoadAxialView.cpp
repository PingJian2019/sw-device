#include"DispLoadAxialView.h"

DispLoadAxialView::DispLoadAxialView(QWidget * parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	move(1050, 250);
	setFixedSize(300, 180);

	setWindowFlags((this->windowFlags()) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));
}