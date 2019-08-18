#pragma once

#include "ui_AdjustMoverDlg.h"

class AdjustMoverDlgView : public QDialog
{
public:
	AdjustMoverDlgView(QWidget * parent = nullptr);

private:
	void InitTable();
	void InitTableData();

private:
	Ui::AdjustMoverDlg ui;
};