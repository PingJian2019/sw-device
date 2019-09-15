#pragma once

#include "ui_WaveForm.h"
#include <QImage>
#include <QPainter>
#include <QTimer>

#include "common_type.h"
#include "ReceiveDataManage.h"

#define BUFFERSIZE		100

class WaveFormView : public QMainWindow
{
	Q_OBJECT
public:
	WaveFormView(QWidget * parent = NULL, ReceiveDataManage * receiveData = NULL);

protected:
	virtual void paintEvent(QPaintEvent *event);

signals:
	void SigUpdateArea();

private slots:
	void OnTimerUpdate();

	void OnRecWaveData(int type, QString data);

	void OnUpdateDrawArea();

private:
	void CreateConnection();
	void Init();
	void Paint();
	void CreatData();

	void DrawCoorDinateSys();
	void DrawXYScale();
	void DrawGrad();

	void DrawWaveArea();

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



	float			m_loadMaxValue;
	float			m_loadMinValue;

	float			m_dispMaxValue;
	float			m_dispMinValue;

	float           m_dispBuffer[200];
	float           m_loadBuffer[200];

	int				m_lastdrawchannelIndex;
	int				m_currentdrawchannelIndex;

	int             m_currentChannelIndex;

	int				m_olddrawIndex;
	int				m_newdrawIndex;

	int				buffer[BUFFERSIZE];
	int				buffer2[BUFFERSIZE];

	ReceiveDataManage *		m_receiveData;

	QImage			image;
	QTimer			timer;

	QPainter*       painter;

};