#include "AdjustMoverDlgView.h"

AdjustMoverDlgView::AdjustMoverDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(380, 330);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);
}

void AdjustMoverDlgView::InitTable()
{

}

void AdjustMoverDlgView::InitTableData()
{

}