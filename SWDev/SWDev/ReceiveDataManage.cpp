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
	switch (type)
	{
		//start stop dev
	case MESS_START_COM_T:
		emit SigRecStartCommunication(type, data.c_str());
		break;
	case MESS_STOP_COM_T:
		emit SigRecStopCommunication(type, data.c_str());
		break;
		
		//alarm limits
	case MESS_WRITE_DISP_ALARM_LIMITS:
		emit SigRecDispAlarmLimits(type, data.c_str());
		break;
	case MESS_WRITE_LOAD_ALARM_LIMITS:
		emit SigRecLoadAlramLimits(type, data.c_str());
		break;
	
		//read DM
	case MESS_READ_DMSECTION1:
		emit SigRecDMSection1(type, data.c_str());
		break;
	case MESS_READ_DMSECTION2:
		emit SigRecDMSection2(type, data.c_str());
		break;
	case MESS_READ_DMSECTION3:
		emit SigRecDMSection3(type, data.c_str());
		break;

		//calibration
	case MESS_WRITE_LOADSENSOR_ALIGN:
		emit SigRecLoadSensorCalibration(type, data.c_str());
		break;

		//model change
	case MESS_WRITE_SWITCH_MODEL:
		emit SigRecModelChange(type, data.c_str());
		break;

		//limits
	case MESS_WRITE_DISP_LIMITS:
		emit SigDispModelLimits(type, data.c_str());
		break;
	case MESS_WRITE_LOAD_LIMITS:
		emit SigLoadModelLimits(type, data.c_str());
		break;

		//frequency and count
	case MESS_WRITE_DISP_FREQ_COUNT:
		emit SigDispModeFreqCount(type, data.c_str());
		break;
	case MESS_WRITE_LOAD_FREQ_COUNT:
		emit SigLoadModeFreqCount(type, data.c_str());
		break;

		//pid
	case MESS_WRITE_PID_RUN:
		emit SigPIDRun(type, data.c_str());
		break;

		//MR 5002503
	case MESS_READ_MR_500T0503:
		emit SigMR5002503(type, data.c_str());
		break;

		//wave form compensation
	case MESS_WRITE_WAVEFORM_COMPENSATION:
		emit SigWaveFormComp(type, data.c_str());
		break;

		//start server 
	case MESS_WRITE_TEST_START_STOP:
		emit SigStartStop(type, data.c_str());
		break;
	case MESS_WRITE_SERIVCE_ON:
		emit SigServerOnOff(type, data.c_str());
		break;

	}
	int b = 0;
}