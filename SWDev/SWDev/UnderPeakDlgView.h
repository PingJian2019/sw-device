#pragma once
#include "ui_UnderPeakDlg.h"

class UnderPeakDlgView : public QDialog
{
public:
	UnderPeakDlgView(QWidget * parent = nullptr);

private:
	void InitTable();
	void InitTableData();

private:
	Ui::UnderPeakDlg ui;
};