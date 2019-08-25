#pragma once

#include "ui_WaveFormCompensation.h"

class WaveFormCompensationDlgView : public QDialog
{
	Q_OBJECT
public:
	WaveFormCompensationDlgView(QWidget * parent = nullptr);

private:
	void InitTable();
	void InitTableData();

private:
	Ui::WaveFormCompensationDlg ui;
};