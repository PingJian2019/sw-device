#include"DispLoadAxialView.h"
#include"SWCommunication.h"

DispLoadAxialView::DispLoadAxialView(QWidget * parent, ReceiveDataManage * receiveData)
	: QMainWindow(parent)
	, m_receiveData(receiveData)
{
	ui.setupUi(this);

	move(1050, 235);
	setFixedSize(300, 180);

	setWindowFlags((this->windowFlags()) &
		(~Qt::WindowMaximizeButtonHint) & (~Qt::WindowMinimizeButtonHint));

	CreateConnection();
}

void DispLoadAxialView::CreateConnection()
{
	connect(ui.m_resetDispBtn, SIGNAL(clicked()), this, SLOT(OnResetDispBtnClicked()));
	connect(ui.m_resetLoadBtn, SIGNAL(clicked()), this, SLOT(OnResetLoadBtnClicked()));

	connect(m_receiveData, SIGNAL(SigRTLoadAndDispValue(int, QString)), this, SLOT(OnRecRTDispAndLoadValue(int, QString)));

	connect(m_receiveData, SIGNAL(SigClearDisp(int, QString)), this, SLOT(OnRecClearDisp(int, QString)));
	connect(m_receiveData, SIGNAL(SigClearLoad(int, QString)), this, SLOT(OnRecClearLoad(int, QString)));

}

void DispLoadAxialView::OnRecClearDisp(int type, QString data)
{
	ui.m_resetDispBtn->setEnabled(true);

	if (data == "OK")
	{

	}
}

void DispLoadAxialView::OnRecClearLoad(int type, QString data)
{
	ui.m_resetLoadBtn->setEnabled(true);

	if (data == "OK")
	{

	}

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

void DispLoadAxialView::OnResetDispBtnClicked()
{
	SWCommunication::GetInstance()->WriteDispClear0();
	ui.m_resetDispBtn->setEnabled(false);
}

void DispLoadAxialView::OnResetLoadBtnClicked()
{
	SWCommunication::GetInstance()->WriteLoadClear0();

	ui.m_resetLoadBtn->setEnabled(false);
}