#include "ReceiveDataManage.h"

ReceiveDataManage::ReceiveDataManage()
{
}

ReceiveDataManage::~ReceiveDataManage()
{

}

void ReceiveDataManage::ReceiveData(MessageType type, unsigned char * data, int dataLen)
{
	int a = 0;
}

void ReceiveDataManage::ReceiveData(MessageType type, std::string data)
{
	QString strData(data.c_str());
	strData = strData.trimmed();

	switch (type)
	{
		//start stop dev
	case MESS_START_COM_T:
		emit SigRecStartCommunication(type, strData);
		break;
	case MESS_STOP_COM_T:
		emit SigRecStopCommunication(type, strData);
		break;
		
		//alarm limits
	case MESS_WRITE_DISP_ALARM_LIMITS:
		emit SigRecDispAlarmLimits(type, strData);
		break;
	case MESS_WRITE_LOAD_ALARM_LIMITS:
		emit SigRecLoadAlramLimits(type, strData);
		break;
	
		//read DM
	case MESS_READ_DMSECTION1:
		emit SigRecDMSection1(type, strData);
		break;
	case MESS_READ_DMSECTION2:
		emit SigRecDMSection2(type, strData);
		break;
	case MESS_READ_DMSECTION3:
		emit SigRecDMSection3(type, strData);
		break;

		//read MR
	case MESS_READ_MR_300TO303:
		emit SigRecMR300to303(type, strData);
		break;

		//calibration
	case MESS_WRITE_LOADSENSOR_ALIGN:
		emit SigRecLoadSensorCalibration(type, strData);
		break;

		//model change
	case MESS_WRITE_SWITCH_MODEL:
		emit SigRecModelChange(type, strData);
		break;

		//limits
	case MESS_WRITE_DISP_LIMITS:
		emit SigDispModelLimits(type, strData);
		break;
	case MESS_WRITE_LOAD_LIMITS:
		emit SigLoadModelLimits(type, strData);
		break;

		//frequency and count
	case MESS_WRITE_DISP_FREQ_COUNT:
		emit SigDispModeFreqCount(type, strData);
		break;
	case MESS_WRITE_LOAD_FREQ_COUNT:
		emit SigLoadModeFreqCount(type, strData);
		break;

		//pid
	case MESS_WRITE_PID_RUN:
		emit SigPIDRun(type, strData);
		break;
	case MESS_WRTIE_PID_RESTORE:
		emit SigPIDRestore(type, strData);
		break;

		//MR 5002503
	case MESS_READ_MR_500T0503:
		emit SigMR5002503(type, strData);
		break;

		//wave form compensation
	case MESS_WRITE_WAVEFORM_COMPENSATION:
		emit SigWaveFormComp(type, strData);
		break;

		//start server 
	case MESS_WRITE_TEST_START:
	case MESS_WRITE_TEST_STOP:
		emit SigStartStop(type, strData);
		break;
	case MESS_WRITE_SERIVCE_ON:
	case MESS_WRITE_SERIVCE_OFF:
		emit SigServerOnOff(type, strData);
		break;

		//preset paras
	case MESS_WRITE_PREDISP_PARAS:
		emit SigPreSetDispParas(type, strData);
		break;
	case MESS_WRITE_PRELOAD_PARAS:
		emit SigPreSetLoadParas(type, strData);
		break;	

		//jog speed
	case MESS_WRITE_JOG1_SPEED:
	case MESS_WRITE_JOG2_SPEED:
	case MESS_WRITE_JOG3_SPEED:
		emit SigSetJogSpeed(type, strData);
		break;

		//clear 0
	case MESS_WRITE_DISP_CLEAR:
		emit SigClearDisp(type, strData);
		break;
	case MESS_WRITE_LOAD_CLEAR:
		emit SigClearLoad(type, strData);
		break;

		//jog move
	case MESS_WRITE_JOG1_UP_START:
	case MESS_WRITE_JOG1_UP_STOP:
	case MESS_WRITE_JOG1_DOWN_START:
	case MESS_WRITE_JOG1_DOWN_STOP:
	case MESS_WRITE_JOG2_UP_START:
	case MESS_WRITE_JOG2_UP_STOP:
	case MESS_WRITE_JOG2_DOWN_START:
	case MESS_WRITE_JOG2_DOWN_STOP:
	case MESS_WRITE_JOG3_UP_START:
	case MESS_WRITE_JOG3_UP_STOP:
	case MESS_WRITE_JOG3_DOWN_START:
	case MESS_WRITE_JOG3_DOWN_STOP:
		emit SigJogMove(type, strData);
		break;

		//real time load and disp
	case MESS_READ_DM_0TO18:
		emit SigRTLoadAndDispValue(type, strData);
		break;

		//peak valley
	case MESS_READ_DISP_PEAK_VALLEY:
		emit SigDispPeakValley(type, strData);
		break;
	case MESS_READ_LOAD_PEAK_VALLEY:
		emit SigLoadPeakValley(type, strData);
		break;

		//test alarm info
	case MESS_READ_ALARM_INFO:
		emit SigTestAlarmInfo(type, strData);
		break;

		//clear and restore error
	case MESS_WRITE_CLEAR_ERROR:
		emit SigClearError(type, strData);
		break;
	case MESS_WRITE_RESTORE_ERROR:
		emit SigRestoreError(type, strData);
		break;
	}
}