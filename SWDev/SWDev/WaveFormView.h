#pragma once

#include "ui_WaveForm.h"
#include <QImage>
#include <QPainter>
#include <QTimer>

#define BUFFERSIZE		30

class WaveFormView : public QMainWindow
{
	Q_OBJECT
public:
	WaveFormView(QWidget * parent = NULL);

protected:
	virtual void paintEvent(QPaintEvent *event);

private slots:
	void OnTimerUpdate();

private:
	void Init();
	void Paint();
	void CreatData();

private:
	Ui::WaveForm ui;

	int				minvalue;
	int				maxvalue;
	int				minpos;
	int				maxpos;
	int				avevalue;

	int				index;

	int				buffer[BUFFERSIZE];

	QImage			image;
	QTimer			timer;

};