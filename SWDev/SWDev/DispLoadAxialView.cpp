#include"DispLoadAxialView.h"

DispLoadAxialView::DispLoadAxialView(QWidget * parent, ReceiveDataManage * receiveData)
	: QMainWindow(parent)
	, m_receiveData(receiveData)
{
	ui.setupUi(this);

	move(1050, 250);
	setFixedSize(300, 180);

	setWindowFlags((this->windowFlags()) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	CreateConnection();
}

void DispLoadAxialView::CreateConnection()
{
	connect(m_receiveData, SIGNAL(SigRTLoadAndDispValue(int, QString)), this, SLOT(OnRecRTDispAndLoadValue(int, QString)));
}

void DispLoadAxialView::OnRecRTDispAndLoadValue(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() >= 4)
	{
		QString strLoadValue = stringList[0];
		float fLoadValue = strLoadValue.toFloat();
		fLoadValue /= 100;
		strLoadValue = QString::number(fLoadValue);
		ui.m_loadValue->setText(strLoadValue);
		

		QString strDispValue = stringList[3];
		float fDispValue = strDispValue.toFloat();
		fDispValue /= 100;
		strDispValue = QString::number(fDispValue);
		ui.m_dispValue->setText(strDispValue);
	}
}