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
#include <string>

#include <vector>

#include <QObject>

class SWCOMMUNICATION_EXPORT SWCommunication : public QObject
{
	Q_OBJECT
public:
	SWCommunication();
	~SWCommunication();

	static SWCommunication * GetInstance();
	void ReleaseInstance();

	void SetIReceiveData(IReceiveData * iReceiveData);
	void StartReadRealData();

	void SendDownlinnkMessage(const DownlinkMessage & message);
	bool InitializeCommunication(QString portStr, QString baudRateStr);

	void StartCommunication();
	void StopCommnuication();
	void ClearCPUError();

	void ReadDM0to18();
	void ReadMR500to503();
	void ReadAlarmInfo();

	void ReadLoadPeakValley();
	void ReadDispPeakValley();

	void ReadDMSection1();
	void ReadDMSection2();
	void ReadDMSection3();

	void ReadMR300to303();
	

	void WritePIDRun();
	void WritePIDRestore();

	void WriteLoadClear0();
	void WriteDispClear0();

	void WriteJog1UpStart();
	void WriteJog1UpStop();

	void WriteJog1DownStart();
	void WriteJog1DownStop();

	void WriteJog2UpStart();
	void WriteJog2UpStop();

	void WriteJog2DownStart();
	void WriteJog2DownStop();

	void WriteJog3UpStart();
	void WriteJog3UpStop();

	void WriteJog3DownStart();
	void WriteJog3DownStop();

	void WritePreLoadLoad();
	void WritePreDispLoad();

	void WriteSwitchModel();
	void WriteTestStart();
	void WriteTestStop();

	void WriteClearError();
	void WriteRestoreError();
	void WriteServiceOn();
	void WriteServiceOff();

	void WriteDispAlarmLimits(std::string uplimit, std::string lowlimit);
	void WriteLoadAlarmLimits(std::string uplimit, std::string lowlimit);

	void WriteDispLimits(std::string uplimit, std::string lowlimit);
	void WriteLoadLimits(std::string uplimit, std::string lowlimit);

	void WritePreDispParas(std::string dispValue, std::string speedValue);
	void WritePreLoadParas(std::string loadValue, std::string speedValue);

	void WriteDispFreqAndCount(std::string freq, std::string count);
	void WriteLoadFreqAndCount(std::string freq, std::string count);

	void WriteWaveCompensation(std::string comp, std::string inputFilter);

	void WriteJog1Speed(std::string speed);
	void WriteJog2Speed(std::string speed);
	void WriteJog3Speed(std::string speed);

	void WriteLoadSensorAlign(std::string kValue, std::string bValue);

private:
	void downlinkFun();
	void UplinkFun();
	void readRealDataFun();

	void ConvertIntToStr(int iValue, char * buff, int & buffLen);

	void Stop();


private:
	ICommunication	*			m_communication;
	DownlinkMessageList			m_downlinkList;

	std::mutex					m_waitResmutex;
	std::condition_variable		m_waitResConVar;

	unsigned char				m_buffer[1024];
	int							m_bufferLen;

	IReceiveData*				m_receiveData;
	std::string					m_strReceiveMessage;

	bool						m_isStop;
	std::thread					m_downLinkThread;
	std::thread					m_upLinkThread;
	std::thread					m_addmessageThread;

	static SWCommunication *	m_instance;
};
