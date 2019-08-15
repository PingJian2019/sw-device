#include"PeakValleyView.h"

PeakValleyView::PeakValleyView(QWidget * parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	move(1135, 50);
	setFixedSize(200, 250);

	setWindowFlags((this->windowFlags()) &
	(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));
}