#pragma once
#include "ui_TestSatusGroup.h"

class TestSatusGroupView : public QMainWindow
{
	Q_OBJECT
public:
	TestSatusGroupView(QWidget * parent = NULL);

private:
	Ui::TestStatusGroupForm ui;

};