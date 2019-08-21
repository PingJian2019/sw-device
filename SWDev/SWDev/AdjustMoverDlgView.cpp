#include "AdjustMoverDlgView.h"

AdjustMoverDlgView::AdjustMoverDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(400, 250);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);
}

void AdjustMoverDlgView::InitTable()
{

}

void AdjustMoverDlgView::InitTableData()
{

}