#pragma once

#include "swcommunication_global.h"
#include "i_communication.h"
#include "serial_communication.h"
#include "DownlinkMessageList.h"
#include "IReceiveData.h"

#include <thread>
#include <functional>
#include <chrono>
#include <mutex>

#include <vector>

class SWCOMMUNICATION_EXPORT SWCommunication
{
public:
	SWCommunication();
	~SWCommunication();

	static SWCommunication * GetInstance();

	void SetIReceiveData(IReceiveData * iReceiveData);

	void SendDownlinnkMessage(const DownlinkMessage & message);
	bool InitializeCommunication(QString portStr, QString baudRateStr);

	void StartCommunication();
	void StopCommnuication();
	void ClearCPUError();

	void RDMRData(int MR);
	void RDSMRData(int MRStart, int num);

	void RDDMData(int DR);
	void RDSDMData(int DRStart,int num);

	void WRMRData(int MR, char * data);
	void WRSMRData(int MR, std::vector<char *> dataList);

	void WRDMData(int DR, char * data);
	void WRSDMData(int DR, std::vector<char *> dataList);




private:
	void downlinkFun();
	void UplinkFun();

	void ConvertIntToStr(int iValue, char * buff, int & buffLen);


private:
	ICommunication	*			m_communication;
	DownlinkMessageList			m_downlinkList;

	std::mutex					m_waitResmutex;
	std::condition_variable		m_waitResConVar;

	unsigned char				m_buffer[1024];
	int							m_bufferLen;

	unsigned char				m_rdheader[3];
	int							m_rdheadrLen;

	unsigned char				m_rdsHeader[4];
	int							m_rdsHeaderLen;

	unsigned char				m_wdheader[3];
	int							m_wdheaderLen;

	unsigned char				m_wdsheader[4];
	int							m_wdsheaderLen;

	IReceiveData*				m_receiveData;

	static SWCommunication *	m_instance;
};
