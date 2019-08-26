#include "WaveFormView.h"
#include <time.h>

#define IMAGEWIDTH 1000
#define IMAGEHEIGHT 350

#define IMAGELEFTPOS 30
#define IMAGETOPPOS 20

#define IMAGELEFMARGIN 60
#define IMAGERIGHTMARGIN 20
#define IMAGETOPMARGIN 50
#define IMGAGEBUTTOMMARGIN 50

#define DRAWAREAWIDH IMAGEWIDTH - IMAGELEFMARGIN - IMAGERIGHTMARGIN
#define DRAWAREAHEIGHT IMAGEHEIGHT - IMAGETOPMARGIN - IMGAGEBUTTOMMARGIN

#define COORDINATEORIGINX IMAGELEFMARGIN
#define COORDINATEORIGINY IMAGEHEIGHT - IMGAGEBUTTOMMARGIN

#define XCOUNT 5
#define YCOUNT 5
#define SCALELINELEN 4
#define SCALEVALUELEN 20

#define NUMPOINTTODRAW BUFFERSIZE


WaveFormView::WaveFormView(QWidget * parent /* = NULL */)
	: QMainWindow(parent)
	, maxvalue(0)
	, minvalue(1000)
	, maxpos(0)
	, minpos(0)
	, m_xScale(0.0f)
	, m_yScale(0.0f)
	, index(0)
	, m_lastDrawIndex(0)
	, maxvalue2(0)
	, minvalue2(1000)
{
	ui.setupUi(this);

	move(3, 325);
	setFixedSize(1040, 370);

	setWindowFlags((this->windowFlags()) & 
	 (~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));
	//setWindowFlags((this->windowFlags()) &
		//(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	Init();
}

void WaveFormView::Init()
{
	image = QImage(IMAGEWIDTH, IMAGEHEIGHT, QImage::Format_RGB32);  //画布的初始化大小设为600*500，使用32位颜色
	QColor backColor = qRgb(255, 255, 255);    //画布初始化背景色使用白色
	image.fill(backColor);

	memset(buffer, 0, 30);

	CreatData();

	m_width = DRAWAREAWIDH;
	m_height = DRAWAREAHEIGHT;
	m_originX = COORDINATEORIGINX;
	m_originY = COORDINATEORIGINY;

	m_xScale = (double)m_width / NUMPOINTTODRAW;
	m_yScale = (double)m_height * 0.4 / (maxvalue - minvalue);

	painter = new QPainter(&image);
	painter->setRenderHint(QPainter::Antialiasing, true);
	//painter->scale(double(DRAWAREAWIDH/NUMPOINTTODRAW), 1.0f);

	DrawCoorDinateSys();
	DrawXYScale();
	DrawGrad();

	connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimerUpdate()));
	timer.start(40);                  
}

void WaveFormView::OnTimerUpdate()
{
	index++;
	m_lastDrawIndex++;
	if (index == BUFFERSIZE)
	{
		index = 0;
		QColor backColor = qRgb(255, 255, 255);    //画布初始化背景色使用白色
		image.fill(backColor);

		DrawCoorDinateSys();
		DrawXYScale();
		DrawGrad();
	}

	if (m_lastDrawIndex == BUFFERSIZE)
	{
		m_lastDrawIndex = 0;
	}

	//Paint();
	if (index >= 1 && m_lastDrawIndex >= 1)
	{
		painter->save();
		QPen pen, penPoint;
		pen.setColor(Qt::blue);
		pen.setWidth(1);
		penPoint.setColor(Qt::green);
		penPoint.setWidth(1);

		painter->setPen(pen);
		painter->drawLine(m_originX + m_xScale * (index - 1), m_originY - buffer[m_lastDrawIndex - 1] * m_yScale,
			m_originX + m_xScale * (index), m_originY - buffer[m_lastDrawIndex] * m_yScale);

		painter->setPen(penPoint);
		painter->drawLine(m_originX + m_xScale * (index - 1), m_originY - buffer2[m_lastDrawIndex - 1] * m_yScale,
			m_originX + m_xScale * (index), m_originY - buffer2[m_lastDrawIndex] * m_yScale);


		painter->restore();
	}

	update();
}

void WaveFormView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(IMAGELEFTPOS, IMAGETOPPOS, image);
}

void WaveFormView::DrawCoorDinateSys()
{
	painter->save();

	QPen penDegree;
	penDegree.setColor(Qt::black);
	penDegree.setWidth(2);
	painter->setPen(penDegree);
	
	painter->drawLine(m_originX, m_originY, m_originX + m_width, m_originY);
	painter->drawLine(m_originX, m_originY, m_originX, m_originY - m_height);

	painter->restore();
}

void WaveFormView::DrawXYScale()
{
	painter->save();

	QPen penDegree;
	penDegree.setColor(Qt::black);
	penDegree.setWidth(2);
	painter->setPen(penDegree);

	//draw origin
	painter->drawText(m_originX, m_originY + 20, QString::number(0));


	//draw x scale
	for (int i = 0; i < XCOUNT; i++)
	{
		painter->drawText(m_originX + (i + 0.97) * m_width / XCOUNT,
			m_originY + SCALEVALUELEN, QString::number(i + 1));
	}

	//draw y scale
	for (int i = 0; i < YCOUNT; i++)
	{
		painter->drawText(m_originX - SCALEVALUELEN, m_originY - (i + 0.85) * m_height / YCOUNT,
			QString::number(i + 1));
	}

	painter->restore();
}

void WaveFormView::DrawGrad()
{
	//x coordinate

	//draw origin
	//painter->drawText(m_originX, m_originY + 20, QString::number(0));
	painter->save();

	QPen penDegree;
	penDegree.setColor(Qt::black);
	penDegree.setWidth(2);
	painter->setPen(penDegree);

	QPen penGrad;
	penGrad.setColor(Qt::black);
	penGrad.setWidth(1);
	penGrad.setStyle(Qt::DotLine);

	
	//draw x
	for (int i = 0; i < XCOUNT; i++)
	{
		painter->setPen(penDegree);
		painter->drawLine(m_originX + (i + 1) * m_width / XCOUNT, m_originY, m_originX + (i + 1) * m_width / XCOUNT, m_originY + SCALELINELEN);
		//painter->drawText(m_originX + (i + 0.97) * m_width / XCOUNT,
			//m_originY + SCALEVALUELEN, QString::number(i + 1));

		painter->setPen(penGrad);
		painter->drawLine(m_originX + (i + 1) * m_width / XCOUNT, m_originY - m_height, m_originX + (i + 1) * m_width / XCOUNT, m_originY);
	}

	//draw y
	for (int i = 0; i < YCOUNT; i++)
	{
		painter->setPen(penDegree);
		painter->drawLine(m_originX, m_originY - (i + 1) * m_height / YCOUNT,
			m_originX - SCALELINELEN, m_originY - (i + 1) * m_height / YCOUNT);
		//painter->drawText(m_originX - SCALEVALUELEN, m_originY - (i + 0.85) * m_height / YCOUNT,
			//QString::number(i + 1));

		painter->setPen(penGrad);
		painter->drawLine(m_originX, m_originY - (i + 1) * m_height / YCOUNT,
			m_originX + m_width, m_originY - (i + 1) * m_height / YCOUNT);
	}
	painter->restore();
}

void WaveFormView::Paint()
{
	//DrawCoorDinateSys();
	//DrawXYScale();
#if 0
	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);
	int pointx = COORDINATEORIGINX, pointy = COORDINATEORIGINY;
	//int width = 960 - pointx, height = 280;//确定坐标轴宽度跟高度 上文定义画布为600X300，宽高依此而定。
										   //绘制坐标轴 坐标轴原点(35，280)

	int width = DRAWAREAWIDH;
	int height = DRAWAREAHEIGHT;
	//painter.drawRect(5, 5, 600 - 10, 300 - 10);//外围的矩形，从(5,5)起，到(590,290)结束，周围留了5的间隙。
	painter.drawLine(pointx, pointy, width + pointx, pointy);//坐标轴x宽度为width
	painter.drawLine(pointx, pointy - height, pointx, pointy);//坐标轴y高度为height

	//CreatData();

	double xscale = (double)width / (30 - 1);
	//double yscale = (double)height / maxvalue;
	double yscale = (double)height * 0.4 / (maxvalue - minvalue);


	QPen pen, penPoint;
	pen.setColor(Qt::black);
	pen.setWidth(1);
	penPoint.setColor(Qt::blue);
	penPoint.setWidth(3);

	for (int i = 0; i < index; i++)
	{
		//由于y轴是倒着的，所以y轴坐标要pointy-a[i]*ky 其中ky为比例系数
		painter.setPen(pen);//黑色笔用于连线
		painter.drawLine(pointx + xscale*i, pointy - buffer[i] * yscale, pointx + xscale*(i + 1), pointy - buffer[i + 1] * yscale);
		//painter.setPen(penPoint);//蓝色的笔，用于标记各个点
		//painter.drawPoint(pointx + xscale*i, pointy - buffer[i] * yscale);
	}

	//painter.drawPoint(pointx + xscale*(30 - 1), pointy - buffer[30 - 1] * yscale);//绘制最后一个点

	QPen penDegree;
	penDegree.setColor(Qt::black);
	penDegree.setWidth(2);
	painter.setPen(penDegree);

	QPen penGrad;
	penGrad.setColor(Qt::black);
	penGrad.setWidth(1);
	penGrad.setStyle(Qt::DotLine);

	//画上x轴刻度线

	//画远点
	painter.drawText(pointx,pointy + 20, QString::number(0));
	for (int i = 0; i < 10; i++)//分成10份
	{
		//选取合适的坐标，绘制一段长度为4的直线，用于表示刻度
		painter.setPen(penDegree);
		painter.drawLine(pointx + (i + 1)*width / 10, pointy, pointx + (i + 1)*width / 10, pointy + 4);
		painter.drawText(pointx + (i + 0.97)*width / 10,
			pointy + 20, QString::number((int)((i + 1)*((double)30 / 10))));

		painter.setPen(penGrad);
		painter.drawLine(pointx + (i + 1)*width / 10, pointy - height, pointx + (i + 1)*width / 10, pointy);

	}

	//y轴刻度线
	double _maStep = (double)maxvalue / 10;//y轴刻度间隔需根据最大值来表示
	for (int i = 0; i < 10; i++)
	{
		//主要就是确定一个位置，然后画一条短短的直线表示刻度。
		painter.setPen(penDegree);
		painter.drawLine(pointx, pointy - (i + 1)*height / 10,
			pointx - 4, pointy - (i + 1)*height / 10);
		painter.drawText(pointx - 20, pointy - (i + 0.85)*height / 10,
			QString::number((int)(_maStep*(i + 1))));

		painter.setPen(penGrad);
		painter.drawLine(pointx, pointy - (i + 1)*height / 10,
			pointx + width, pointy - (i + 1)*height / 10);
	}

#endif
}

void WaveFormView::CreatData()
{
	srand(time(NULL));

	int n = BUFFERSIZE;
	double sum = 0;
	double sum2 = 0;
	double ave = 0;
	for (int i = 0; i < n; i++)
	{
		buffer[i] = rand() % 40 + 20;
		buffer2[i] = rand() % 40 + 40;
	}

	int maxpos = 0, minpos = 0;
	int maxpos2 = 0, minpos2 = 0;
	for (int i = 0; i < n; i++)
	{
		sum += buffer[i];
		sum2 += buffer2[i];
		if (buffer[i] > maxvalue) {
			maxvalue = buffer[i];
			maxpos = i;
			maxvalue2 = buffer2[i];
		}
		if (buffer[i] < minvalue) {
			minvalue = buffer[i];
			minpos = i;
			minvalue2 = buffer2[i];
		}
	}
	avevalue = sum / n;
	avevalue2 = sum / n;
}