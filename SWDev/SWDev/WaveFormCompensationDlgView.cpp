#include "WaveFormCompensationDlgView.h"

WaveFormCompensationDlgView::WaveFormCompensationDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(500, 300);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);
}

void WaveFormCompensationDlgView::InitTable()
{

}

void WaveFormCompensationDlgView::InitTableData()
{

}