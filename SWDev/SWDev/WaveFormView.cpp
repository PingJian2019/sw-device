#include "WaveFormView.h"

WaveFormView::WaveFormView(QWidget * parent /* = NULL */)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	move(15, 290);
	setFixedSize(1100, 400);

	setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint));
	//setWindowFlags((this->windowFlags()) &
		//(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));
}