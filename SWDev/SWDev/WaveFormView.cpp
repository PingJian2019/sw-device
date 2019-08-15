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
	image = QImage(1000, 350, QImage::Format_RGB32);  //�����ĳ�ʼ����С��Ϊ600*500��ʹ��32λ��ɫ
	QColor backColor = qRgb(255, 255, 255);    //������ʼ������ɫʹ�ð�ɫ
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
		QColor backColor = qRgb(255, 255, 255);    //������ʼ������ɫʹ�ð�ɫ
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
	painter.setRenderHint(QPainter::Antialiasing, true);//���÷����ģʽ���ÿ�һ��
	int pointx = 40, pointy = 320;//ȷ��������������꣬���ﶨ��(35,280)
	int width = 960 - pointx, height = 280;//ȷ���������ȸ��߶� ���Ķ��廭��Ϊ600X300��������˶�����
										   //���������� ������ԭ��(35��280)
	//painter.drawRect(5, 5, 600 - 10, 300 - 10);//��Χ�ľ��Σ���(5,5)�𣬵�(590,290)��������Χ����5�ļ�϶��
	painter.drawLine(pointx, pointy, width + pointx, pointy);//������x���Ϊwidth
	painter.drawLine(pointx, pointy - height, pointx, pointy);//������y�߶�Ϊheight

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
		//����y���ǵ��ŵģ�����y������Ҫpointy-a[i]*ky ����kyΪ����ϵ��
		painter.setPen(pen);//��ɫ����������
		painter.drawLine(pointx + xscale*i, pointy - buffer[i] * yscale, pointx + xscale*(i + 1), pointy - buffer[i + 1] * yscale);
		painter.setPen(penPoint);//��ɫ�ıʣ����ڱ�Ǹ�����
		painter.drawPoint(pointx + xscale*i, pointy - buffer[i] * yscale);
	}

	//painter.drawPoint(pointx + xscale*(30 - 1), pointy - buffer[30 - 1] * yscale);//�������һ����

	QPen penDegree;
	penDegree.setColor(Qt::black);
	penDegree.setWidth(2);
	painter.setPen(penDegree);

	QPen penGrad;
	penGrad.setColor(Qt::black);
	penGrad.setWidth(1);
	penGrad.setStyle(Qt::DotLine);

	//����x��̶���

	//��Զ��
	painter.drawText(pointx,pointy + 20, QString::number(0));
	for (int i = 0; i < 10; i++)//�ֳ�10��
	{
		//ѡȡ���ʵ����꣬����һ�γ���Ϊ4��ֱ�ߣ����ڱ�ʾ�̶�
		painter.setPen(penDegree);
		painter.drawLine(pointx + (i + 1)*width / 10, pointy, pointx + (i + 1)*width / 10, pointy + 4);
		painter.drawText(pointx + (i + 0.97)*width / 10,
			pointy + 20, QString::number((int)((i + 1)*((double)30 / 10))));

		painter.setPen(penGrad);
		painter.drawLine(pointx + (i + 1)*width / 10, pointy - height, pointx + (i + 1)*width / 10, pointy);

	}

	//y��̶���
	double _maStep = (double)maxvalue / 10;//y��̶ȼ����������ֵ����ʾ
	for (int i = 0; i < 10; i++)
	{
		//��Ҫ����ȷ��һ��λ�ã�Ȼ��һ���̶̵�ֱ�߱�ʾ�̶ȡ�
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
	//������������ֵ����Сֵ��ƽ����
	int n = 30;//nΪ���ݸ���
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
	avevalue = sum / n;//ƽ����
}