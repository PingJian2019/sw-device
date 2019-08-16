#pragma once

#include"ui_PeakValley.h"

class PeakValleyView : public QMainWindow
{
	Q_OBJECT
public:
	PeakValleyView(QWidget * parent = NULL);

private:
	void InitTableWidget();

private:
	Ui::PeakValleyForm ui;
};