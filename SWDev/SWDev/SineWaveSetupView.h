#pragma once

#include "ui_SineWaveSetup.h"
#include "common_type.h"
#include "ReceiveDataManage.h"


class SineWaveSetupView : public QWidget
{
	Q_OBJECT
public:
	SineWaveSetupView(QWidget * parent = nullptr,ReceiveDataManage * data = NULL);

public:
	void SetModelParas();
	QString GetCountString();

private:
	void CreateConnection();

	void UpdateParasToUI();

	QString GetLevel1String();
	QString GetLevel2String();
	QString GetFreqencyString();

private slots :
	void OnModelComboxIndexChanged(int index);
	void OnPidRunBtnClicked();
	//void OnOkBtnClicked();
	//void OnCancelBtnClicked();

	void OnRecLoadModelParas(int type, QString data);
	void OnRecDispModelParas(int type, QString data);

	void OnRecModelChange(int type, QString data);

	void OnRecSetDispModeLimits(int type, QString data);
	void OnRecSetLoadModeLimits(int type, QString data);

	void OnRecSetDispModeFreqCount(int type, QString data);
	void OnRecSetLoadModeFreqCount(int type, QString data);

	void OnRecPidRun(int type, QString data);
	void OnRecPidRestore(int type, QString data);
	void OnRecPidResult(int type, QString data);
	void OnRecCurrentModel(int type, QString data);

	void OnRecCurrentCount(int type, QString data);



signals:
	void SigModelChanged(int index);
	void SigCompleteSetParas();

private:
	Ui::SineWaveSetupForm ui;

	bool				m_isRecDispLimit;
	bool				m_isRecLoadLimit;
	bool				m_isRecDispFreqCount;
	bool				m_isRecLoadFreqCount;

	int					m_currentModel;
	int					m_tempModel;

	QString				m_dispUpLimit;
	QString				m_dispLowLimit;
	QString				m_dispCount;
	QString				m_dispFreqency;


	QString				m_loadUpLimit;
	QString				m_loadLowLimit;
	QString				m_loadCount;
	QString				m_loadFreqency;


	QString				m_CurrnentCount;


	ReceiveDataManage *	m_receiveData;
};