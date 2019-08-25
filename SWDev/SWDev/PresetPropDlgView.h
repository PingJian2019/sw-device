#pragma once

#include "ui_PresetPropDlg.h"

class PresetPropDlgView : public QDialog
{
	Q_OBJECT
public:
	PresetPropDlgView(QWidget * parent = nullptr);

private:

private slots:
	void OnOkBtnClicked();
	void OnCancelBtnClicked();

private:
	Ui::PresetPropDlg ui;
};