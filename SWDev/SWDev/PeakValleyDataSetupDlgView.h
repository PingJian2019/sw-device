#pragma once

#include "ui_PeakValleyDataSetupDlg.h"

class PeakValleyDataSetupDlgView : public QDialog
{
	Q_OBJECT
public:
	PeakValleyDataSetupDlgView(QWidget * parent = nullptr);

private:
	//void InitTable();
	//void InitTableData();

private:
	Ui::PeakValleyDataSetupDlg ui;
};