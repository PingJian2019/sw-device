#include"DispLoadAxialView.h"

DispLoadAxialView::DispLoadAxialView(QWidget * parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	move(1135, 350);
	setFixedSize(200, 250);

	setWindowFlags((this->windowFlags()) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));
}