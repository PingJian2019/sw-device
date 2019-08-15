#pragma once

#include"ui_PeakValley.h"

class PeakValleyView : public QMainWindow
{
	Q_OBJECT
public:
	PeakValleyView(QWidget * parent = NULL);

private:
	Ui::PeakValleyForm ui;
};