#include"DispLoadAxialView.h"

DispLoadAxialView::DispLoadAxialView(QWidget * parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	move(1107, 250);
	setFixedSize(240, 180);

	setWindowFlags((this->windowFlags()) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));
}