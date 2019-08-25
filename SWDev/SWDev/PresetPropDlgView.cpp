#include "PresetPropDlgView.h"

PresetPropDlgView::PresetPropDlgView(QWidget * parent /* = nullptr */)
	: QDialog(parent)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(400, 340);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);

	connect(ui.m_okBtn, SIGNAL(clicked()), this, SLOT(OnOkBtnClicked()));
	connect(ui.m_cancelBtn, SIGNAL(clicked()), this, SLOT(OnCancelBtnClicked()));

}

void PresetPropDlgView::OnOkBtnClicked()
{
	accept();
}

void PresetPropDlgView::OnCancelBtnClicked()
{
	reject();
}