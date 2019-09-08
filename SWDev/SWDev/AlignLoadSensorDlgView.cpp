#include "AlignLoadSensorDlgView.h"
#include "SWCommunication.h"

AligLoadSensorDlgView::AligLoadSensorDlgView(QWidget * parent, ReceiveDataManage * data)
	: QDialog(parent)
	, m_receiveData(data)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(320, 240);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);

	CreateConnection();
}

void AligLoadSensorDlgView::CreateConnection()
{
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(OnCalibrationBtnClicked()));
	connect(m_receiveData, SIGNAL(SigRecDMSection1(int, QString)), this, SLOT(OnRecClaibrationValue(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecLoadSensorCalibration(int, QString)), this, SLOT(OnRecSetCalibrationValue(int, QString)));

}

void AligLoadSensorDlgView::OnCalibrationBtnClicked()
{
	QString kvalue = ui.m_kValueLineEdit->text();
	QString bvalue = ui.m_bValueLineEdit->text();

	kvalue = QString::number(kvalue.toFloat() * 100);
	bvalue = QString::number(bvalue.toFloat() * 100);

	SWCommunication::GetInstance()->WriteLoadSensorAlign(kvalue.toStdString(), bvalue.toStdString());

	ui.okButton->setEnabled(false);
}

void AligLoadSensorDlgView::OnRecSetCalibrationValue(int type, QString data)
{
	ui.okButton->setEnabled(true);
}

void AligLoadSensorDlgView::OnRecClaibrationValue(int type, QString data)
{
	QStringList stringList = data.split(" ");
	int len = stringList.length();

	if (len < 2)
	{
		return;
	}

	QString kvalue = stringList[0];

	float iKvalue = kvalue.toFloat();
	iKvalue = iKvalue / 100;
	kvalue = QString::number(iKvalue);

	ui.m_kValueLineEdit->setText(kvalue);

	QString bvalue = stringList[1];
	float iBvalue = bvalue.toFloat();
	iBvalue = iBvalue / 100;
	bvalue = QString::number(iBvalue);
	ui.m_bValueLineEdit->setText(bvalue);
}