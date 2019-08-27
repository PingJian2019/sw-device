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
	MESS_WRITE_PID_RUN,
	MESS_WRITE_LOAD_CLEAR,
	MESS_WRITE_DISP_CLEAR,
	MESS_WRITE_JOG1_START,
	MESS_WRITE_JOG1_STOP,
	MESS_WRITE_JOG2_START,
	MESS_WRITE_JOG2_STOP,
	MESS_WRITE_JOG3_START,
	MESS_WRITE_JOG3_STOP,
	MESS_WRITE_PRELOAD_LOAD,
	MESS_WRITE_PREDISP_LOAD,
	MESS_WRITE_SWITCH_MODEL,
	MESS_WRITE_TEST_START_STOP,
	MESS_WRITE_SERIVCE_ON,
	MESS_CLEAR_ERROR_T,
};

enum RunMode
{
	MODE_DISP = 0,
	MODE_LOAD,
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