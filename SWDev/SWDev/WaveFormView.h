#pragma once

#include "ui_WaveForm.h"
#include <QImage>
#include <QPainter>
#include <QTimer>

#define BUFFERSIZE		100

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


	void DrawCoorDinateSys();
	void DrawXYScale();
	void DrawGrad();

private:
	Ui::WaveForm ui;

	int				minvalue;
	int				maxvalue;
	int				minpos;
	int				maxpos;
	int				avevalue;

	int				minvalue2;
	int				maxvalue2;
	int				minpos2;
	int				maxpos2;
	int				avevalue2;

	int				m_originX;
	int				m_originY;
	int				m_width;
	int				m_height;

	int				index;
	int				m_lastDrawIndex;

	float           m_xScale;
	float			m_yScale;

	int				buffer[BUFFERSIZE];
	int				buffer2[BUFFERSIZE];

	QImage			image;
	QTimer			timer;

	QPainter*       painter;

};