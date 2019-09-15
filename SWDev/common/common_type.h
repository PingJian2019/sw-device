#ifndef _COMMON_TYPE_H
#define _COMMON_TYPE_H

#include <iostream>

enum MessPriority
{
	//priority value of thread: 1 is highest
	PRIORITY_ONE = 1,
	PRIORITY_TWO = 2,
	PRIORITY_THREE = 3,
	PRIORITY_FOUR = 4,
	PRIORITY_FIVE = 5,
};

enum MessageType
{
	MESS_START_COM_T = 0,
	MESS_STOP_COM_T,
	MESS_READ_DM_0TO10,
	MESS_READ_MR_500T0503,
	MESS_READ_ALARM_INFO,
	MESS_READ_DISP_PEAK_VALLEY,
	MESS_READ_LOAD_PEAK_VALLEY,
	MESS_READ_DMSECTION1,
	MESS_READ_DMSECTION2,
	MESS_READ_DMSECTION3,
	MESS_READ_MR_300TO303,
	MESS_WRITE_PID_RUN,
	MESS_WRTIE_PID_RESTORE,
	MESS_WRITE_LOAD_CLEAR,
	MESS_WRITE_DISP_CLEAR,
	MESS_WRITE_JOG1_UP_START,
	MESS_WRITE_JOG1_UP_STOP,
	MESS_WRITE_JOG1_DOWN_START,
	MESS_WRITE_JOG1_DOWN_STOP,
	MESS_WRITE_JOG2_UP_START,
	MESS_WRITE_JOG2_UP_STOP,
	MESS_WRITE_JOG2_DOWN_START,
	MESS_WRITE_JOG2_DOWN_STOP,
	MESS_WRITE_JOG3_UP_START,
	MESS_WRITE_JOG3_UP_STOP,
	MESS_WRITE_JOG3_DOWN_START,
	MESS_WRITE_JOG3_DOWN_STOP,
	MESS_WRITE_PRELOAD_LOAD,
	MESS_WRITE_PREDISP_LOAD,
	MESS_WRITE_SWITCH_MODEL,
	MESS_WRITE_TEST_START,
	MESS_WRITE_TEST_STOP,
	MESS_WRITE_SERIVCE_ON,
	MESS_WRITE_SERIVCE_OFF,
	MESS_WRITE_DISP_ALARM_LIMITS,
	MESS_WRITE_LOAD_ALARM_LIMITS,
	MESS_WRITE_DISP_LIMITS,
	MESS_WRITE_LOAD_LIMITS,
	MESS_WRITE_PREDISP_PARAS,
	MESS_WRITE_PRELOAD_PARAS,
	MESS_WRITE_DISP_FREQ_COUNT,
	MESS_WRITE_LOAD_FREQ_COUNT,
	MESS_WRITE_WAVEFORM_COMPENSATION,
	MESS_WRITE_JOG_SPEED,
	MESS_WRITE_LOADSENSOR_ALIGN,


	MESS_CLEAR_ERROR_T,
};

enum RunMode
{
	MODE_LOAD = 0,
	MODE_DISP = 1,
};

struct DownlinkMessage
{
	MessageType m_messType;
	int m_downlinkDataLen;
	int m_priority;
	unsigned char m_downlinkData[128];
	DownlinkMessage()
	{
		m_downlinkDataLen = 0;
		m_priority = PRIORITY_TWO;
		memset(m_downlinkData, 0, 128);
	}
};

#endif