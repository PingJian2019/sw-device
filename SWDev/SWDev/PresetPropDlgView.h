#pragma once

#include "ui_PresetPropDlg.h"
#include "common_type.h"
#include "ReceiveDataManage.h"

class PresetPropDlgView : public QDialog
{
	Q_OBJECT
public:
	PresetPropDlgView(QWidget * parent = nullptr, ReceiveDataManage * data = NULL);

private:
	void CreateConnection();

signals:
	void SigNotifyPreSetDispValue(QString value);
	void SigNotifyPreSetLoadValue(QString value);

private slots:
	void OnOkBtnClicked();
	void OnCancelBtnClicked();

	void OnRecDispPreValue(int type, QString data);
	void OnRecLoadPreValue(int type, QString data);

	void OnRecSetDispPreValue(int type, QString data);
	void OnRecSetLoadPreValue(int type, QString data);

private:
	Ui::PresetPropDlg ui;

	bool		m_isRecPreDisp;
	bool		m_isRecPreLoad;
	ReceiveDataManage * m_receiveData;
};