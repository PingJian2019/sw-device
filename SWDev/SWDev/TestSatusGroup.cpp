#include "TestSatusGroup.h"

TestSatusGroupView::TestSatusGroupView(QWidget * parent /* = NULL */)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	move(15, 265);
	setFixedSize(1100, 80);

	/*setWindowFlags((this->windowFlags()) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));*/

	setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint));
}