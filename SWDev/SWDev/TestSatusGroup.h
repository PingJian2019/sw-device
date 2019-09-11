#pragma once
#include "ui_TestSatusGroup.h"
#include "common_type.h"
#include "ReceiveDataManage.h"


class TestSatusGroupView : public QMainWindow
{
	Q_OBJECT
public:
	TestSatusGroupView(QWidget * parent = NULL, ReceiveDataManage * receiveData = NULL);

private:
	void InitTable();
	void InitTableData();

	void CreateConnection();

private slots:
	void OnModelChanged(int index);
	void OnUpdateTotalCountValue(QString value);

	void OnRecCurrentCount(int type, QString data);
	void OnRecDModelTotalCount(int type, QString data);
	void OnRecLModelTotalCount(int type, QString data);
	void OnRecDispAlarmLimitis(int type, QString data);
	void OnRecLoadAlarmLimitis(int type, QString data);
	void OnRecCompentation(int type, QString data);

private:
	Ui::TestStatusGroupForm ui;


	int						m_model;
	ReceiveDataManage *		m_receiveData;


};