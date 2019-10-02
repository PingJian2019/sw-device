#pragma once

#include "IReceiveData.h"
#include "common_type.h"
#include <QObject>

#include <map>
#include <QString>

class ReceiveDataManage : public QObject, public IReceiveData
{
	Q_OBJECT
public:
	ReceiveDataManage();
	~ReceiveDataManage();

public:
	virtual void ReceiveData(MessageType type, unsigned char * data, int dataLen);
	virtual void ReceiveData(MessageType type, std::string data);

signals:
	//start & stop com
	void SigRecStartCommunication(int type, QString data);
	void SigRecStopCommunication(int type, QString data);

	//alarm limit
	void SigRecDispAlarmLimits(int type, QString data);
	void SigRecLoadAlramLimits(int type, QString data);

	//all dm data
	void SigRecDMSection1(int type, QString data);
	void SigRecDMSection2(int type, QString data);
	void SigRecDMSection3(int type, QString data);

	void SigRecMR300to303(int type, QString data);

	//calibration
	void SigRecLoadSensorCalibration(int type, QString data);

	//model change
	void SigRecModelChange(int type, QString data);

	//limits
	void SigDispModelLimits(int type, QString data);
	void SigLoadModelLimits(int type, QString data);

	//frequency and count
	void SigDispModeFreqCount(int type, QString data);
	void SigLoadModeFreqCount(int type, QString data);

	//pid
	void SigPIDRun(int type, QString data);
	void SigPIDRestore(int type, QString data);
	void SigMR5002503(int type, QString data);

	//wave form compensation
	void SigWaveFormComp(int type, QString data);

	//start server
	void SigStartStop(int type, QString data);
	void SigServerOnOff(int type, QString data);

	//preset paras
	void SigPreSetDispParas(int type, QString data);
	void SigPreSetLoadParas(int type, QString data);

	//jog speed
	void SigSetJogSpeed(int type, QString data);

	//clear 0
	void SigClearDisp(int type, QString data);
	void SigClearLoad(int type, QString data);


	//jog move
	void SigJogMove(int type, QString data);

	//real time load and disp value
	void SigRTLoadAndDispValue(int type, QString data);

	//peak valley
	void SigDispPeakValley(int type, QString data);
	void SigLoadPeakValley(int type, QString data);

	//test alarm info
	void SigTestAlarmInfo(int type, QString data);

	//clear and restore error
	void SigClearError(int type, QString data);
	void SigRestoreError(int type, QString data);

private:
};
