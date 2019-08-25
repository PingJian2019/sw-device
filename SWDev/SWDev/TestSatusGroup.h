#pragma once
#include "ui_TestSatusGroup.h"

class TestSatusGroupView : public QMainWindow
{
	Q_OBJECT
public:
	TestSatusGroupView(QWidget * parent = NULL);

private:
	void InitTable();
	void InitTableData();

private slots:
	void OnModelChanged(int index);

private:
	Ui::TestStatusGroupForm ui;

};