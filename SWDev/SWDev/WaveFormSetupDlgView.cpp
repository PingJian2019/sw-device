#include "WaveFormSetupDlgView.h"

WaveFormSetupDlgView::WaveFormSetupDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);
	move(200, 80);
	setFixedSize(800, 450);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);
}