#include "PeakValleyDataSetupDlgView.h"

PeakValleyDataSetupDlgView::PeakValleyDataSetupDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);
	move(400, 80);
	setFixedSize(320, 350);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);
}