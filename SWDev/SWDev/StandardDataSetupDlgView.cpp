#include "StandardDataSetupDlgView.h"

StandardDataSetupDlgView::StandardDataSetupDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);
	move(400, 80);
	setFixedSize(320, 350);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);
}

void StandardDataSetupDlgView::InitTableData()
{

}

void StandardDataSetupDlgView::InitTable()
{

}