#pragma once

#include "ui_LimitsDlg.h"

class LimitsDlgView : public QDialog
{
public:
	LimitsDlgView(QWidget * parent = nullptr);

private:
	void InitTable();
	void InitTableData();

private:
	Ui::LimitsDlg ui;
};