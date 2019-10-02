#include "WaveFormCompensationDlgView.h"

#include "SWCommunication.h"

WaveFormCompensationDlgView::WaveFormCompensationDlgView(QWidget * parent,ReceiveDataManage * data)
	: QDialog(parent)
	, m_receiveData(data)
{
	ui.setupUi(this);

	move(300, 80);
	setFixedSize(500, 300);
	setWindowFlags((this->windowFlags()) & ~Qt::WindowContextHelpButtonHint);

	CreateConnection();
}

void WaveFormCompensationDlgView::CreateConnection()
{
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(OnSetBtnClicked()));
	connect(m_receiveData, SIGNAL(SigWaveFormComp(int, QString)), this, SLOT(OnRecWaveCompensation(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecDMSection3(int, QString)), this, SLOT(OnRecReadWaveCompensation(int, QString)));

}

void WaveFormCompensationDlgView::OnSetBtnClicked()
{
	ui.okButton->setEnabled(false);

	QString strfilterComp = ui.m_filterCompLineEdit->text();
	float ffilterComp = strfilterComp.toFloat();
	strfilterComp = QString::number(ffilterComp);


	QString strinputfilter = ui.m_inputFilterLineEdit->text();
	float finputfilter = strfilterComp.toFloat() * 100;
	strinputfilter = QString::number(finputfilter);

	SWCommunication::GetInstance()->WriteWaveCompensation(strfilterComp.toStdString(), strinputfilter.toStdString());
}

void WaveFormCompensationDlgView::OnRecWaveCompensation(int type, QString data)
{
	if (data == "OK")
	{
	}

	ui.okButton->setEnabled(true);
}

void WaveFormCompensationDlgView::OnRecReadWaveCompensation(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 3)
	{
		SWCommunication::GetInstance()->ReadDMSection3();
	}
	else
	{
		QString strFilterComp = stringList[1];
		float fFilterComp = strFilterComp.toFloat();
		strFilterComp = QString::number(fFilterComp);
		ui.m_filterCompLineEdit->setText(strFilterComp);

		QString strInputFilter = stringList[2];
		float fInputFilter = strInputFilter.toFloat() / 100;
		strInputFilter = QString::number(fInputFilter);

		ui.m_inputFilterLineEdit->setText(strInputFilter);
	}
}