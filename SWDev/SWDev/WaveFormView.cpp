#include "WaveFormView.h"
#include <time.h>

WaveFormView::WaveFormView(QWidget * parent /* = NULL */)
	: QMainWindow(parent)
	, maxvalue(0)
	, minvalue(1000)
	, maxpos(0)
	, minpos(0)
	, index(0)
{
	ui.setupUi(this);

	move(15, 290);
	setFixedSize(1100, 400);

	setWindowFlags((this->windowFlags()) & (~Qt::WindowCloseButtonHint));
	//setWindowFlags((this->windowFlags()) &
		//(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	Init();
}

void WaveFormView::Init()
{
	image = QImage(1000, 350, QImage::Format_RGB32);  //画布的初始化大小设为600*500，使用32位颜色
	QColor backColor = qRgb(255, 255, 255);    //画布初始化背景色使用白色
	image.fill(backColor);

	memset(buffer, 0, 30);

	CreatData();

	connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimerUpdate()));
	timer.start(40);                  
}

void WaveFormView::OnTimerUpdate()
{
	index++;
	if (index == 30)
	{
		index = 0;
		QColor backColor = qRgb(255, 255, 255);    //画布初始化背景色使用白色
		image.fill(backColor);
	}
	Paint();

	update();
}

void WaveFormView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(60, 40, image);
}

void WaveFormView::Paint()
{
	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点
	int pointx = 40, pointy = 320;//确定坐标轴起点坐标，这里定义(35,280)
	int width = 960 - pointx, height = 280;//确定坐标轴宽度跟高度 上文定义画布为600X300，宽高依此而定。
										   //绘制坐标轴 坐标轴原点(35，280)
	//painter.drawRect(5, 5, 600 - 10, 300 - 10);//外围的矩形，从(5,5)起，到(590,290)结束，周围留了5的间隙。
	painter.drawLine(pointx, pointy, width + pointx, pointy);//坐标轴x宽度为width
	painter.drawLine(pointx, pointy - height, pointx, pointy);//坐标轴y高度为height

	//CreatData();

	double xscale = (double)width / (30 - 1);
	//double yscale = (double)height / maxvalue;
	double yscale = (double)height * 0.4 / (maxvalue - minvalue);


	QPen pen, penPoint;
	pen.setColor(Qt::black);
	pen.setWidth(2);
	penPoint.setColor(Qt::blue);
	penPoint.setWidth(5);

	for (int i = 0; i < index; i++)
	{
		//由于y轴是倒着的，所以y轴坐标要pointy-a[i]*ky 其中ky为比例系数
		painter.setPen(pen);//黑色笔用于连线
		painter.drawLine(pointx + xscale*i, pointy - buffer[i] * yscale, pointx + xscale*(i + 1), pointy - buffer[i + 1] * yscale);
		painter.setPen(penPoint);//蓝色的笔，用于标记各个点
		painter.drawPoint(pointx + xscale*i, pointy - buffer[i] * yscale);
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
}

void WaveFormView::CreatData()
{
	srand(time(NULL));
	//获得数据中最大值和最小值、平均数
	int n = 30;//n为数据个数
	double sum = 0;
	double ave = 0;
	for (int i = 0; i < n; i++)
		buffer[i] = rand() % 40 + 20;
	int maxpos = 0, minpos = 0;
	for (int i = 0; i < n; i++)
	{
		sum += buffer[i];
		if (buffer[i] > maxvalue) {
			maxvalue = buffer[i];
			maxpos = i;
		}
		if (buffer[i] < minvalue) {
			minvalue = buffer[i];
			minpos = i;
		}
	}
	avevalue = sum / n;//平均数
}