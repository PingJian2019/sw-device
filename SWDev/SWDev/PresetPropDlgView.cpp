#include "PresetPropDlgView.h"

PresetPropDlgView::PresetPropDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(400, 385);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);
}