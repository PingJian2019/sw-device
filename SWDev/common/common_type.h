#ifndef _COMMON_TYPE_H
#define _COMMON_TYPE_H

#include <iostream>

enum MessageType
{
	MESS_START_COM_T = 0,
	MESS_STOP_COM_T,
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
	unsigned char m_downlinkData[128];
	DownlinkMessage()
	{
		m_downlinkDataLen = 0;
		memset(m_downlinkData, 0, 128);
	}
};

#endif