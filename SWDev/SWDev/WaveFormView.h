#pragma once

#include "ui_WaveForm.h"

class WaveFormView : public QMainWindow
{
	Q_OBJECT
public:
	WaveFormView(QWidget * parent = NULL);

private:
	Ui::WaveForm ui;
};