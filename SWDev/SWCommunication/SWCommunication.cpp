#include "SWCommunication.h"

SWCommunication * SWCommunication::m_instance = NULL;

SWCommunication::SWCommunication()
	: m_communication(NULL)
	, m_receiveData(NULL)
{
	memset(m_buffer, 0, 1024);

	unsigned char rdheader[3] = { 0x52,0x44,0x20 };
	memcpy(m_rdheader, rdheader, 3);
	m_rdheadrLen = 3;

	unsigned char rdsheader[4] = { 0x52,0x44,0x53,0x20 };
	memcpy(m_rdsHeader, rdsheader, 4);
	m_rdsHeaderLen = 4;

	unsigned char wdheader[4] = "WR ";
	memcpy(m_wdheader, wdheader, 3);
	m_wdheaderLen = 3;

	unsigned char wdsheader[5] = "WRS ";
	memcpy(m_wdsheader, wdsheader, 4);
	m_wdsheaderLen = 4;

}

SWCommunication::~SWCommunication()
{
}

SWCommunication * SWCommunication::GetInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new SWCommunication();
	}

	return m_instance;
}

bool SWCommunication::InitializeCommunication(QString portStr, QString baudRateStr)
{
	m_communication = new SerialCommunication(portStr, baudRateStr);
	bool result = false;

	if (m_communication->SetupCommunication())
	{
		//start downlink thread
		std::thread th(std::bind(&SWCommunication::downlinkFun, this));
		th.detach();

		//start uplink thread
		std::thread th1(std::bind(&SWCommunication::UplinkFun, this));
		th1.detach();
		result = true;
	}
	else
	{

	}

	return result;
}

void SWCommunication::SendDownlinnkMessage(const DownlinkMessage & message)
{
	m_downlinkList.AddDownLinkMessage(message);
}

void SWCommunication::downlinkFun()
{
	while (1)
	{
		DownlinkMessage message;
		m_downlinkList.GetNextMessage(message);

		bool result = false;
		if (m_communication)
		{
			result = m_communication->DownlinkMessage(message.m_downlinkData, message.m_downlinkDataLen);
		}

		if (result)
		{
			std::unique_lock<std::mutex> lock(m_waitResmutex);
			m_waitResConVar.wait(lock);
			if (m_receiveData)
			{
				m_receiveData->ReceiveData(message.m_messType, m_buffer, m_bufferLen);
			}
		}

		//std::chrono::milliseconds timespan(100);
		//std::this_thread::sleep_for(timespan);
	}
}

void SWCommunication::SetIReceiveData(IReceiveData * iReceiveData)
{
	m_receiveData = iReceiveData;
}

void SWCommunication::UplinkFun()
{
	while (1)
	{
		unsigned char buffer[1024] = { 0 };
		int bufferLen = 0;

		m_communication->UplinkMessage(buffer, 1024, bufferLen);
		if (bufferLen > 0)
		{
			std::unique_lock<std::mutex> lock(m_waitResmutex);
			memset(m_buffer, 0, 1024);
			memcpy(m_buffer, buffer, bufferLen);
			m_bufferLen = bufferLen;
			m_waitResConVar.notify_one();
		}

		//std::chrono::milliseconds timespan(100);
		//std::this_thread::sleep_for(timespan);
	}
}

void SWCommunication::StartCommunication()
{
	DownlinkMessage message;
	message.m_messType = MESS_START_COM_T;
	message.m_downlinkDataLen = 3;
	unsigned char command[3] = { 0x43,0x52,0x0D };
	memcpy(message.m_downlinkData, command, 3);
	SendDownlinnkMessage(message);
}

void SWCommunication::StopCommnuication()
{
	DownlinkMessage message;
	message.m_messType = MESS_STOP_COM_T;
	message.m_downlinkDataLen = 3;
	unsigned char command[3] = { 0x43,0x51,0x0D };
	memcpy(message.m_downlinkData, command, 3);
	SendDownlinnkMessage(message);

}

void SWCommunication::ClearCPUError()
{
	DownlinkMessage message;
	message.m_messType = MESS_CLEAR_ERROR_T;
	message.m_downlinkDataLen = 3;
	unsigned char command[3] = { 0x45,0x52,0x0D };
	memcpy(message.m_downlinkData, command, 3);
	SendDownlinnkMessage(message);

}


void SWCommunication::ConvertIntToStr(int iValue, char * buff, int & buffLen)
{
	char tempBuf[16] = { 0 };
	sprintf(tempBuf, "%d", iValue);
	strcpy(buff, tempBuf);
	buffLen = strlen(tempBuf);
}

void SWCommunication::RDMRData(int MR)
{
	DownlinkMessage message;
	int index = 0;
	memcpy(message.m_downlinkData + index, m_rdheader, m_rdheadrLen);
	index += m_rdheadrLen;
	unsigned char softType[] = { 'M','R' };
	memcpy(message.m_downlinkData + index, softType, 2);
	index += 2;


	char strMR[16] = { 0 };
	int MRlen = 0;
	ConvertIntToStr(MR, strMR, MRlen);
	memcpy(message.m_downlinkData + index, strMR, MRlen);
	index += MRlen;

	unsigned char dataformat[] = { '.','U' };
	int dataformatLen = sizeof(dataformat);
	memcpy(message.m_downlinkData + index, dataformat, dataformatLen);
	index += dataformatLen;

	unsigned char enddata[] = { 0x0D };
	memcpy(message.m_downlinkData + index, enddata, 1);
	index += 1;

	message.m_downlinkDataLen = index + 1;

	SendDownlinnkMessage(message);

}

void SWCommunication::RDSMRData(int MRStart, int num)
{
	DownlinkMessage message;
	int index = 0;
	memcpy(message.m_downlinkData + index, m_rdsHeader, m_rdsHeaderLen);
	index += m_rdsHeaderLen;
	unsigned char softType[] = { 'M','R' };
	memcpy(message.m_downlinkData + index, softType, 2);
	index += 2;

	char strMRStart[16] = { 0 };
	int mrStartLen = 0;
	ConvertIntToStr(MRStart, strMRStart, mrStartLen);
	memcpy(message.m_downlinkData + index, strMRStart, mrStartLen);
	index += mrStartLen;

	unsigned char dataformat[] = { '.','U' };
	int dataformatLen = sizeof(dataformat);
	memcpy(message.m_downlinkData + index, dataformat, dataformatLen);
	index += dataformatLen;

	unsigned char spiltData[] = { 0x20 };
	memcpy(message.m_downlinkData + index, spiltData, 1);
	index += 1;

	char strnum[8] = { 0 };
	sprintf(strnum, "%d", num);
	int numlen = strlen(strnum);
	memcpy(message.m_downlinkData + index, strnum, numlen);
	index += numlen;

	unsigned char enddata[] = { 0x0D };
	memcpy(message.m_downlinkData + index, enddata, 1);

	message.m_downlinkDataLen = index + 1;

	SendDownlinnkMessage(message);
}

void SWCommunication::RDDMData(int DR)
{
	DownlinkMessage message;
	int index = 0;
	memcpy(message.m_downlinkData + index, m_rdheader, m_rdheadrLen);
	index += m_rdheadrLen;
	unsigned char softType[] = { 'D','M' };
	memcpy(message.m_downlinkData + index, softType, 2);
	index += 2;

	char strDR[16] = { 0 };
	int drLen = 0;
	ConvertIntToStr(DR, strDR, drLen);
	memcpy(message.m_downlinkData + index, strDR, drLen);
	index += drLen;

	unsigned char dataformat[] = { '.','U' };
	int dataformatLen = sizeof(dataformat);
	memcpy(message.m_downlinkData + index, dataformat, dataformatLen);
	index += dataformatLen;

	unsigned char enddata[] = { 0x0D };
	memcpy(message.m_downlinkData + index, enddata, 1);
	
	message.m_downlinkDataLen = index + 1;

	SendDownlinnkMessage(message);

}

void SWCommunication::RDSDMData(int DRStart, int num)
{
	DownlinkMessage message;
	int index = 0;
	memcpy(message.m_downlinkData + index, m_rdsHeader, m_rdsHeaderLen);
	index += m_rdsHeaderLen;
	unsigned char softType[] = { 'D','M' };
	memcpy(message.m_downlinkData + index, softType, 2);
	index += 2;

	char strDRStart[16] = { 0 };
	int drLen = 0;
	ConvertIntToStr(DRStart, strDRStart, drLen);
	memcpy(message.m_downlinkData + index, strDRStart, drLen);
	index += drLen;

	unsigned char dataformat[] = { '.','U' };
	int dataformatLen = sizeof(dataformat);
	memcpy(message.m_downlinkData + index, dataformat, dataformatLen);
	index += dataformatLen;

	unsigned char spiltData[] = { 0x20 };
	memcpy(message.m_downlinkData + index, spiltData, 1);
	index += 1;

	char strnum[8] = { 0 };
	sprintf(strnum, "%d", num);
	int numlen = strlen(strnum);
	memcpy(message.m_downlinkData + index, strnum, numlen);
	index += numlen;

	unsigned char enddata[] = { 0x0D };
	memcpy(message.m_downlinkData + index, enddata, 1);
	index += 1;

	message.m_downlinkDataLen = index + 1;

	SendDownlinnkMessage(message);
}

void SWCommunication::WRMRData(int MR, char * data)
{
	DownlinkMessage message;
	int index = 0;
	memcpy(message.m_downlinkData + index, m_wdheader, m_wdheaderLen);
	index += m_wdheaderLen;

	unsigned char softType[] = { 'M','R' };
	memcpy(message.m_downlinkData + index, softType, 2);
	index += 2;

	char strMR[16] = { 0 };
	int mrLen = 0;
	ConvertIntToStr(MR, strMR, mrLen);
	memcpy(message.m_downlinkData + index, strMR, mrLen);
	index += mrLen;

	unsigned char dataformat[] = { '.','U' };
	int dataformatLen = sizeof(dataformat);
	memcpy(message.m_downlinkData + index, dataformat, dataformatLen);
	index += dataformatLen;

	unsigned char spiltData[] = { 0x20 };
	memcpy(message.m_downlinkData + index, spiltData, 1);
	index += 1;

	int datalen = strlen(data);
	memcpy(message.m_downlinkData + index, data, datalen);
	index += datalen;

	unsigned char enddata[] = { 0x0D };
	memcpy(message.m_downlinkData + index, enddata, 1);
	index += 1;

	message.m_downlinkDataLen = index + 1;

	SendDownlinnkMessage(message);
}

void SWCommunication::WRSMRData(int MR, std::vector<char *> dataList)
{
	DownlinkMessage message;
	int index = 0;
	memcpy(message.m_downlinkData + index, m_wdheader, m_wdheaderLen);
	index += m_wdheaderLen;

	unsigned char softType[] = { 'M','R' };
	memcpy(message.m_downlinkData + index, softType, 2);
	index += 2;

	char strMR[16] = { 0 };
	int mrLen = 0;
	ConvertIntToStr(MR, strMR, mrLen);
	memcpy(message.m_downlinkData + index, strMR, mrLen);
	index += mrLen;

	unsigned char dataformat[] = { '.','U' };
	int dataformatLen = sizeof(dataformat);
	memcpy(message.m_downlinkData + index, dataformat, dataformatLen);
	index += dataformatLen;

	unsigned char spiltData[] = { 0x20 };
	memcpy(message.m_downlinkData + index, spiltData, 1);
	index += 1;

	int num = dataList.size();
	if (num == 0)return;
	char strNum[16] = { 0 };
	int numLen = 0;
	ConvertIntToStr(num, strNum, numLen);
	memcpy(message.m_downlinkData + index, strNum, numLen);
	index += numLen;

	for each (char * var in dataList)
	{
		unsigned char spiltData[] = { 0x20 };
		memcpy(message.m_downlinkData + index, spiltData, 1);
		index += 1;

		int len = strlen(var);
		memcpy(message.m_downlinkData + index, var, len);
		index += len;
	}

	unsigned char enddata[] = { 0x0D };
	memcpy(message.m_downlinkData + index, enddata, 1);
	index += 1;

	message.m_downlinkDataLen = index + 1;

	SendDownlinnkMessage(message);
}

void SWCommunication::WRDMData(int DR, char * data)
{
	DownlinkMessage message;
	int index = 0;
	memcpy(message.m_downlinkData + index, m_wdheader, m_wdheaderLen);
	index += m_wdheaderLen;

	unsigned char softType[] = { 'D','R' };
	memcpy(message.m_downlinkData + index, softType, 2);
	index += 2;

	char strDR[16] = { 0 };
	int drLen = 0;
	ConvertIntToStr(DR, strDR, drLen);
	memcpy(message.m_downlinkData + index, strDR, drLen);
	index += drLen;

	unsigned char dataformat[] = { '.','U' };
	int dataformatLen = sizeof(dataformat);
	memcpy(message.m_downlinkData + index, dataformat, dataformatLen);
	index += dataformatLen;

	unsigned char spiltData[] = { 0x20 };
	memcpy(message.m_downlinkData + index, spiltData, 1);
	index += 1;

	int datalen = strlen(data);
	memcpy(message.m_downlinkData + index, data, datalen);
	index += datalen;

	unsigned char enddata[] = { 0x0D };
	memcpy(message.m_downlinkData + index, enddata, 1);
	index += 1;

	message.m_downlinkDataLen = index + 1;

	SendDownlinnkMessage(message);
}

void SWCommunication::WRSDMData(int DR, std::vector<char *> dataList)
{
	DownlinkMessage message;
	int index = 0;
	memcpy(message.m_downlinkData + index, m_wdheader, m_wdheaderLen);
	index += m_wdheaderLen;

	unsigned char softType[] = { 'M','R' };
	memcpy(message.m_downlinkData + index, softType, 2);
	index += 2;

	char strDR[16] = { 0 };
	int drLen = 0;
	ConvertIntToStr(DR, strDR, drLen);
	memcpy(message.m_downlinkData + index, strDR, drLen);
	index += drLen;

	unsigned char dataformat[] = { '.','U' };
	int dataformatLen = sizeof(dataformat);
	memcpy(message.m_downlinkData + index, dataformat, dataformatLen);
	index += dataformatLen;

	unsigned char spiltData[] = { 0x20 };
	memcpy(message.m_downlinkData + index, spiltData, 1);
	index += 1;

	int num = dataList.size();
	if (num == 0)return;
	char strNum[16] = { 0 };
	int numLen = 0;
	ConvertIntToStr(num, strNum, numLen);
	memcpy(message.m_downlinkData + index, strNum, numLen);
	index += numLen;

	for each (char * var in dataList)
	{
		unsigned char spiltData[] = { 0x20 };
		memcpy(message.m_downlinkData + index, spiltData, 1);
		index += 1;

		int len = strlen(var);
		memcpy(message.m_downlinkData + index, var, len);
		index += len;
	}

	unsigned char enddata[] = { 0x0D };
	memcpy(message.m_downlinkData + index, enddata, 1);
	index += 1;

	message.m_downlinkDataLen = index + 1;

	SendDownlinnkMessage(message);
}
