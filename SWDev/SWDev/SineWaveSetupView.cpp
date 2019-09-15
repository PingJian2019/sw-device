#include "SineWaveSetupView.h"
#include "SWCommunication.h"
#include <QDebug>

SineWaveSetupView::SineWaveSetupView(QWidget * parent, ReceiveDataManage * data)
	:QWidget(parent)
	, m_receiveData(data)
	, m_currentModel(0)
{
	ui.setupUi(this);

	CreateConnection();
}

void SineWaveSetupView::CreateConnection()
{
	connect(ui.m_modelCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnModelComboxIndexChanged(int)));
	connect(ui.m_pidRunBtn, SIGNAL(clicked()), this, SLOT(OnPidRunBtnClicked()));


	connect(m_receiveData, SIGNAL(SigRecDMSection1(int, QString)), this, SLOT(OnRecLoadModelParas(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecDMSection2(int, QString)), this, SLOT(OnRecDispModelParas(int, QString)));

	connect(m_receiveData, SIGNAL(SigRecModelChange(int, QString)), this, SLOT(OnRecModelChange(int, QString)));

	connect(m_receiveData, SIGNAL(SigDispModelLimits(int, QString)), this, SLOT(OnRecSetDispModeLimits(int, QString)));
	connect(m_receiveData, SIGNAL(SigLoadModelLimits(int, QString)), this, SLOT(OnRecSetLoadModeLimits(int, QString)));
	connect(m_receiveData, SIGNAL(SigDispModeFreqCount(int, QString)), this, SLOT(OnRecSetDispModeFreqCount(int, QString)));
	connect(m_receiveData, SIGNAL(SigLoadModeFreqCount(int, QString)), this, SLOT(OnRecSetLoadModeFreqCount(int, QString)));

	connect(m_receiveData, SIGNAL(SigPIDRun(int, QString)), this, SLOT(OnRecPidRun(int, QString)));
	connect(m_receiveData, SIGNAL(SigPIDRestore(int, QString)), this, SLOT(OnRecPidRestore(int, QString)));
	connect(m_receiveData, SIGNAL(SigMR5002503(int, QString)), this, SLOT(OnRecPidResult(int, QString)));
	connect(m_receiveData, SIGNAL(SigRecMR300to303(int, QString)), this, SLOT(OnRecCurrentModel(int, QString)));
	connect(m_receiveData, SIGNAL(SigRTLoadAndDispValue(int, QString)), this, SLOT(OnRecCurrentCount(int, QString)));

	
}

void SineWaveSetupView::OnRecCurrentCount(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() == 6)
	{
		if (m_currentModel == MODE_DISP)
		{
			QString strCount = stringList[5];
			int iCount = strCount.toInt();
			strCount = QString::number(iCount);
			ui.m_currentCountLineEdit->setText(strCount);
		}
		else if (m_currentModel == MODE_LOAD)
		{
			QString strCount = stringList[2];
			int iCount = strCount.toInt();
			strCount = QString::number(iCount);
			ui.m_currentCountLineEdit->setText(strCount);
		}
		else
		{ }
	}

}

void SineWaveSetupView::OnRecSetDispModeLimits(int type, QString data)
{
	m_isRecDispLimit = true;
	if (data == "OK\r\n")
	{
		m_dispLowLimit = GetLevel1String();
		m_dispUpLimit = GetLevel2String();
	}

	if (m_isRecDispLimit && m_isRecDispFreqCount)
	{
		emit SigCompleteSetParas();
	}
}

void SineWaveSetupView::OnRecSetLoadModeLimits(int type, QString data)
{
	m_isRecLoadLimit = true;
	if (data == "OK\r\n")
	{
		m_loadLowLimit = GetLevel1String();
		m_loadUpLimit = GetLevel2String();
	}

	if (m_isRecLoadLimit && m_isRecLoadFreqCount)
	{
		emit SigCompleteSetParas();
	}
}

void SineWaveSetupView::OnRecSetDispModeFreqCount(int type, QString data)
{
	m_isRecDispFreqCount = true;

	if (data == "OK\r\n")
	{
		m_dispFreqency = GetFreqencyString();
		m_dispCount = GetCountString();
	}

	if (m_isRecDispLimit && m_isRecDispFreqCount)
	{
		emit SigCompleteSetParas();
	}
}

void SineWaveSetupView::OnRecSetLoadModeFreqCount(int type, QString data)
{
	m_isRecLoadFreqCount = true;

	if (data == "OK\r\n")
	{
		m_loadFreqency = GetFreqencyString();
		m_loadCount = GetCountString();
	}

	if (m_isRecLoadLimit && m_isRecLoadFreqCount)
	{
		emit SigCompleteSetParas();
	}

}

QString SineWaveSetupView::GetLevel1String()
{
	QString strValue = ui.m_level1LineEdit->text();
	float fValue = strValue.toFloat() * 100;

	return QString::number(fValue);
}

QString SineWaveSetupView::GetLevel2String()
{
	QString strValue = ui.m_level2LineEdit->text();
	float fValue = strValue.toFloat() * 100;

	return QString::number(fValue);
}

QString SineWaveSetupView::GetFreqencyString()
{
	QString strValue = ui.m_frequencyLineEdit->text();
	float fValue = strValue.toFloat() * 100;

	return QString::number(fValue);
}

QString SineWaveSetupView::GetCountString()
{
	QString strValue = ui.m_countLineEdit->text();
	float fValue = strValue.toFloat();

	return QString::number(fValue);
}

void SineWaveSetupView::SetModelParas()
{
	m_isRecDispLimit = false;
	m_isRecLoadLimit = false;
	m_isRecDispFreqCount = false;
	m_isRecLoadFreqCount = false;

	QString dispLowValue = GetLevel1String();
	QString dispUpValue = GetLevel2String();

	QString dispFreqValue = GetFreqencyString();
	QString dispCountValue = GetCountString();

	if (m_currentModel == 1)
	{
		SWCommunication::GetInstance()->WriteDispLimits(dispUpValue.toStdString(), dispLowValue.toStdString());

		SWCommunication::GetInstance()->WriteDispFreqAndCount(dispFreqValue.toStdString(), dispCountValue.toStdString());
	}
	else if(m_currentModel == 0)
	{
		SWCommunication::GetInstance()->WriteLoadLimits(dispUpValue.toStdString(), dispLowValue.toStdString());

		SWCommunication::GetInstance()->WriteLoadFreqAndCount(dispFreqValue.toStdString(), dispCountValue.toStdString());
	}
	else
	{
	}
}

void SineWaveSetupView::OnRecModelChange(int type, QString data)
{
	if (data == "OK\r\n")
	{
		m_currentModel = m_tempModel;
		UpdateParasToUI();
		emit SigModelChanged(m_currentModel);
	}
	else
	{
		disconnect(ui.m_modelCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnModelComboxIndexChanged(int)));
		ui.m_modelCombox->setCurrentIndex(m_currentModel);
		connect(ui.m_modelCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnModelComboxIndexChanged(int)));
	}
}


void SineWaveSetupView::OnModelComboxIndexChanged(int index)
{
	m_tempModel = index;
	SWCommunication::GetInstance()->WriteSwitchModel();
}

void SineWaveSetupView::UpdateParasToUI()
{
	if (m_currentModel == 1)
	{
		ui.m_level1LineEdit->setText(m_dispLowLimit);
		ui.m_level2LineEdit->setText(m_dispUpLimit);
		ui.m_frequencyLineEdit->setText(m_dispFreqency);
		ui.m_countLineEdit->setText(m_dispCount);
	}
	else
	{
		ui.m_level1LineEdit->setText(m_loadLowLimit);
		ui.m_level2LineEdit->setText(m_loadUpLimit);
		ui.m_frequencyLineEdit->setText(m_loadFreqency);
		ui.m_countLineEdit->setText(m_loadCount);
	}
}

void SineWaveSetupView::OnRecDispModelParas(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 6)
	{
		return;
	}

	float dispUpLimit = stringList[0].toFloat() / 100;
	m_dispUpLimit = QString::number(dispUpLimit);

	float displowLimit = stringList[1].toFloat() / 100;
	m_dispLowLimit = QString::number(displowLimit);

	float dispfreqency = stringList[4].toFloat() / 100;
	m_dispFreqency = QString::number(dispfreqency);

	int idispCount = stringList[5].toInt();
	m_dispCount = QString::number(idispCount);

	UpdateParasToUI();

}

void SineWaveSetupView::OnRecLoadModelParas(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() < 9)
	{
		return;
	}

	float floadUpLimit = stringList[3].toFloat() / 100;
	m_loadUpLimit = QString::number(floadUpLimit);

	float floadlowLimit = stringList[4].toFloat() / 100;
	m_loadLowLimit = QString::number(floadlowLimit);

	float floadfreqency = stringList[7].toFloat() / 100;
	m_loadFreqency = QString::number(floadfreqency);

	int iloadCount = stringList[8].toInt();
	m_loadCount = QString::number(iloadCount);

	UpdateParasToUI();
}

void SineWaveSetupView::OnPidRunBtnClicked()
{
	ui.m_pidRunBtn->setEnabled(false);
	SWCommunication::GetInstance()->WritePIDRun();
}

void SineWaveSetupView::OnRecPidRun(int type, QString data)
{
	if (data == "OK\r\n")
	{
		SWCommunication::GetInstance()->WritePIDRestore();
		SWCommunication::GetInstance()->ReadMR500to503();
	}

	ui.m_pidRunBtn->setEnabled(true);
}

void SineWaveSetupView::OnRecPidRestore(int type, QString data)
{
	if (data == "OK\r\n")
	{
		//SWCommunication::GetInstance()->ReadMR500to503();
	}
	else
	{

	}
}

void SineWaveSetupView::OnRecCurrentModel(int type, QString data)
{
	QStringList stringlist = data.split(" ");
	if (stringlist.length() >= 1)
	{
		QString strMode = stringlist[0];
		m_currentModel = strMode.toInt();

		disconnect(ui.m_modelCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnModelComboxIndexChanged(int)));
		ui.m_modelCombox->setCurrentIndex(m_currentModel);
		connect(ui.m_modelCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnModelComboxIndexChanged(int)));

		//ui.m_modelCombox->setCurrentIndex(m_currentModel);
		emit SigModelChanged(m_currentModel);
	}
	else
	{
		SWCommunication::GetInstance()->ReadMR300to303();
	}
}

void SineWaveSetupView::OnRecPidResult(int type, QString data)
{
	QStringList stringList = data.split(" ");
	if (stringList.length() == 4)
	{
		QString pidstatussuc = stringList[2];
		QString pidstatusfail = stringList[3];

		if (pidstatussuc == "0" && pidstatusfail == "0")
		{
			SWCommunication::GetInstance()->ReadMR500to503();
		}
		else if (pidstatussuc == "1")
		{
			qDebug() << "PID Run Succeed\n";
		}
		else
		{
			qDebug() << "PID Run failed\n";

		}
	}
	else
	{
		SWCommunication::GetInstance()->ReadMR500to503();
	}
}