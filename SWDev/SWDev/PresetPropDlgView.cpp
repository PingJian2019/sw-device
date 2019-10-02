#include "PresetPropDlgView.h"
#include "SWCommunication.h"

PresetPropDlgView::PresetPropDlgView(QWidget * parent, ReceiveDataManage * data)
	: QDialog(parent)
	, m_receiveData(data)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(400, 340);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);

	CreateConnection();
}

void PresetPropDlgView::CreateConnection()
{
	connect(ui.m_okBtn, SIGNAL(clicked()), this, SLOT(OnOkBtnClicked()));
	connect(ui.m_cancelBtn, SIGNAL(clicked()), this, SLOT(OnCancelBtnClicked()));

	connect(m_receiveData, SIGNAL(SigRecDMSection1(int, QString)), this, SLOT(OnRecLoadPreValue(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecDMSection2(int, QString)), this, SLOT(OnRecDispPreValue(int, QString)));

	connect(m_receiveData, SIGNAL(SigPreSetDispParas(int, QString)), this, SLOT(OnRecSetDispPreValue(int, QString)));
	connect(m_receiveData, SIGNAL(SigPreSetLoadParas(int, QString)), this, SLOT(OnRecSetLoadPreValue(int, QString)));
}


void PresetPropDlgView::OnRecSetDispPreValue(int type, QString data)
{
	if (data == "OK")
	{
		QString preDispValue = ui.m_preDispValueLineEdit->text();
		preDispValue = QString::number(preDispValue.toInt());
		emit SigNotifyPreSetDispValue(preDispValue);
	}

	m_isRecPreDisp = true;
	if (m_isRecPreDisp && m_isRecPreLoad)
	{
		ui.m_okBtn->setEnabled(true);
	}

}

void PresetPropDlgView::OnRecSetLoadPreValue(int type, QString data)
{
	if (data == "OK")
	{
		QString preLoadValue = ui.m_preLoadValueLineEdit->text();
		preLoadValue = QString::number(preLoadValue.toInt());
		emit SigNotifyPreSetLoadValue(preLoadValue);
	}

	m_isRecPreLoad = true;
	if (m_isRecPreDisp && m_isRecPreLoad)
	{
		ui.m_okBtn->setEnabled(true);
	}
}

void PresetPropDlgView::OnRecDispPreValue(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 9)
	{
		SWCommunication::GetInstance()->ReadDMSection2();
	}
	else
	{
		QString preDisValue = QString::number(stringList[7].toInt());
		QString preDisRate = QString::number(stringList[8].toInt());

		ui.m_preDispValueLineEdit->setText(preDisValue);
		ui.m_preDispRateLineEdit->setText(preDisRate);
	}
}

void PresetPropDlgView::OnRecLoadPreValue(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 11)
	{
		SWCommunication::GetInstance()->ReadDMSection1();
	}
	else
	{
		QString preloadValue = QString::number(stringList[9].toInt());
		QString preloadrate = QString::number(stringList[10].toInt());

		ui.m_preLoadValueLineEdit->setText(preloadValue);
		ui.m_preLoadRateLineEdit->setText(preloadrate);
	}
}

void PresetPropDlgView::OnOkBtnClicked()
{
	QString preDispValue = ui.m_preDispValueLineEdit->text();
	preDispValue = QString::number(preDispValue.toInt());

	QString preDispRate = ui.m_preDispRateLineEdit->text();
	preDispRate = QString::number(preDispRate.toInt());

	SWCommunication::GetInstance()->WritePreDispParas(preDispValue.toStdString(), preDispRate.toStdString());

	QString preLoadValue = ui.m_preLoadValueLineEdit->text();
	preLoadValue = QString::number(preLoadValue.toInt());

	QString preLoadRate = ui.m_preLoadRateLineEdit->text();
	preLoadRate = QString::number(preLoadRate.toInt());
	SWCommunication::GetInstance()->WritePreLoadParas(preLoadValue.toStdString(), preLoadRate.toStdString());

	m_isRecPreDisp = false;
	m_isRecPreLoad = false;

	ui.m_okBtn->setEnabled(false);
}

void PresetPropDlgView::OnCancelBtnClicked()
{
	accept();
}