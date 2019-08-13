#pragma once

#include "ui_TestSetup.h"

class TestSetupView : public QMainWindow
{
	Q_OBJECT
public:
	TestSetupView(QWidget * parent = NULL);

private:
	Ui::TestSetupForm ui;
};