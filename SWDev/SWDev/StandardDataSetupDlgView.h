#pragma once

#include "ui_StandardDataSetupDlg.h"

class StandardDataSetupDlgView : public QDialog
{
	Q_OBJECT
public:
	StandardDataSetupDlgView(QWidget * parent = nullptr);

private:
	void InitTable();
	void InitTableData();

private:
	Ui::StandardDataSetupDlg ui;
};