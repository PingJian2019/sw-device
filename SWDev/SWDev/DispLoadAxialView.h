#pragma once
#include"ui_DispLoadAxial.h"

class DispLoadAxialView : public QMainWindow
{
	Q_OBJECT
public:
	DispLoadAxialView(QWidget * parent = NULL);

private:
	Ui::DispLoadAxialForm ui;
};