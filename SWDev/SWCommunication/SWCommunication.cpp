#include "SWCommunication.h"

SWCommunication * SWCommunication::m_instance = NULL;

SWCommunication::SWCommunication()
	: m_communication(NULL)
	, m_receiveData(NULL)
	, m_strReceiveMessage("")
	, m_isStop(false)
{
	memset(m_buffer, 0, 1024);
}

SWCommunication::~SWCommunication()
{
	m_isStop = true;
	m_waitResConVar.notify_one();
	m_downlinkList.QuitMessageList();

	m_addmessageThread.join();
	m_upLinkThread.join();
	m_downLinkThread.join();

	if (m_communication)
	{
		delete m_communication;
		m_communication = NULL;
	}
}

void SWCommunication::ReleaseInstance()
{
	if (m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

void SWCommunication::Stop()
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

void SWCommunication::StartReadRealData()
{
	std::thread th(std::bind(&SWCommunication::readRealDataFun, this));
	//th.detach();
	m_addmessageThread = std::move(th);
}

bool SWCommunication::InitializeCommunication(QString portStr, QString baudRateStr)
{
	m_communication = new SerialCommunication(portStr, baudRateStr);
	bool result = false;

	if (m_communication->SetupCommunication())
	{
		//start downlink thread
		std::thread th(std::bind(&SWCommunication::downlinkFun, this));
		//th.detach();
		m_downLinkThread = std::move(th);

		//start uplink thread
		std::thread th1(std::bind(&SWCommunication::UplinkFun, this));
		//th1.detach();
		m_upLinkThread = std::move(th1);
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
	while (!m_isStop)
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
			std::chrono::milliseconds timespan(2000);
			m_waitResConVar.wait_for(lock, timespan);
			if (m_receiveData)
			{
				//m_receiveData->ReceiveData(message.m_messType, m_buffer, m_bufferLen);
				m_receiveData->ReceiveData(message.m_messType, m_strReceiveMessage);
				m_strReceiveMessage = "";
			}
		}

		//std::chrono::milliseconds timespan(100);
		//std::this_thread::sleep_for(timespan);
	}
}

void SWCommunication::readRealDataFun()
{
	while (!m_isStop)
	{
		static int count = 0;
		//read load and disp
		ReadDM0to18();

		count++;
		if (count == 60)
		{
			ReadAlarmInfo();
			count = 0;
		}

		//read peak and valley
		//ReadLoadPeakValley();

		//ReadDispPeakValley();

		if (m_isStop)return;

		std::chrono::milliseconds timespan(50);
		std::this_thread::sleep_for(timespan);
	}
}

void SWCommunication::SetIReceiveData(IReceiveData * iReceiveData)
{
	m_receiveData = iReceiveData;
}

void SWCommunication::UplinkFun()
{
	while (!m_isStop)
	{
		unsigned char buffer[1024] = { 0 };
		int bufferLen = 0;

		m_communication->UplinkMessage(buffer, 1024, bufferLen);
		if (bufferLen > 0)
		{
			std::unique_lock<std::mutex> lock(m_waitResmutex);
			m_strReceiveMessage = (char*)buffer;
			//memset(m_buffer, 0, 1024);
			////memcpy(m_buffer, buffer, bufferLen);
			//m_bufferLen = bufferLen;
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

	char * cmd = "CR\r";
	int cmdLen = strlen(cmd);

	unsigned char command[3] = { 0x43,0x52,0x0D };

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::StopCommnuication()
{
	DownlinkMessage message;
	message.m_messType = MESS_STOP_COM_T;

	char * cmd = "CQ\r";
	int cmdLen = strlen(cmd);

	//unsigned char command[3] = { 0x43,0x51,0x0D };

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::ReadDM0to18()
{
	DownlinkMessage message;
	message.m_messType = MESS_READ_DM_0TO18;
	message.m_priority = PRIORITY_THREE;


	char * cmd = "RDS DM0.L 10\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::ReadMR500to503()
{
	DownlinkMessage message;
	message.m_messType = MESS_READ_MR_500T0503;
	message.m_priority = PRIORITY_THREE;

	char * cmd = "RDS MR500 4\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::ReadAlarmInfo()
{
	DownlinkMessage message;
	message.m_messType = MESS_READ_ALARM_INFO;
	message.m_priority = PRIORITY_THREE;

	char * cmd = "RDS MR600 5\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::ReadDispPeakValley()
{
	DownlinkMessage message;
	message.m_messType = MESS_READ_DISP_PEAK_VALLEY;
	message.m_priority = PRIORITY_THREE;

	char * cmd = "RDS DM168.L 2\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::ReadLoadPeakValley()
{
	DownlinkMessage message;
	message.m_messType = MESS_READ_LOAD_PEAK_VALLEY;
	message.m_priority = PRIORITY_THREE;

	char * cmd = "RDS DM122.L 2\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::ReadDMSection1()
{
	DownlinkMessage message;
	message.m_messType = MESS_READ_DMSECTION1;
	//message.m_priority = PRIORITY_THREE;

	char * cmd = "RDS DM100.L 13\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::ReadDMSection2()
{
	DownlinkMessage message;
	message.m_messType = MESS_READ_DMSECTION2;
	//message.m_priority = PRIORITY_THREE;

	char * cmd = "RDS DM150.L 13\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::ReadDMSection3()
{
	DownlinkMessage message;
	message.m_messType = MESS_READ_DMSECTION3;
	//message.m_priority = PRIORITY_THREE;

	char * cmd = "RDS DM200.L 3\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::ReadMR300to303()
{
	DownlinkMessage message;
	message.m_messType = MESS_READ_MR_300TO303;
	//message.m_priority = PRIORITY_THREE;

	char * cmd = "RDS MR300 4\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WritePIDRun()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_PID_RUN;

	char * cmd = "WR MR0 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WritePIDRestore()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRTIE_PID_RESTORE;

	char * cmd = "WR MR0 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteLoadClear0()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_LOAD_CLEAR;

	char * cmd = "WR MR3 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteDispClear0()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_DISP_CLEAR;

	char * cmd = "WR MR200 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog1UpStart()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG1_UP_START;

	char * cmd = "WR MR201 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog1UpStop()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG1_UP_STOP;

	char * cmd = "WR MR201 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog1DownStart()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG1_DOWN_START;

	char * cmd = "WR MR202 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog1DownStop()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG1_DOWN_STOP;

	char * cmd = "WR MR202 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog2UpStart()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG2_UP_START;

	char * cmd = "WR MR203 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog2UpStop()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG2_UP_STOP;

	char * cmd = "WR MR203 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog2DownStart()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG2_DOWN_START;

	char * cmd = "WR MR204 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog2DownStop()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG2_DOWN_STOP;

	char * cmd = "WR MR204 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog3UpStart()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG3_UP_START;

	char * cmd = "WR MR205 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog3UpStop()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG3_UP_STOP;

	char * cmd = "WR MR205 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog3DownStart()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG3_DOWN_START;

	char * cmd = "WR MR206 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog3DownStop()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG3_DOWN_STOP;

	char * cmd = "WR MR206 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WritePreLoadLoad()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_PRELOAD_LOAD;

	char * cmd = "WR MR207 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WritePreDispLoad()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_PREDISP_LOAD;

	char * cmd = "WR MR208 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteSwitchModel()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_SWITCH_MODEL;

	char * cmd = "WR MR300 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteTestStart()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_TEST_START;

	char * cmd = "WR MR301 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteTestStop()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_TEST_STOP;

	char * cmd = "WR MR301 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteClearError()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_CLEAR_ERROR;

	char * cmd = "WR MR302 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteRestoreError()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_RESTORE_ERROR;

	char * cmd = "WR MR302 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}



void SWCommunication::WriteServiceOn()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_SERIVCE_ON;

	char * cmd = "WR MR303 1\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteServiceOff()
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_SERIVCE_OFF;

	char * cmd = "WR MR303 0\r";
	int cmdLen = strlen(cmd);

	message.m_downlinkDataLen = cmdLen;
	memcpy(message.m_downlinkData, cmd, cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteDispAlarmLimits(std::string uplimit, std::string lowlimit)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_DISP_ALARM_LIMITS;

	std::string cmd;
	cmd = "WRS DM110.L 2 ";
	cmd += uplimit;
	cmd += " ";
	cmd += lowlimit;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteLoadAlarmLimits(std::string uplimit, std::string lowlimit)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_LOAD_ALARM_LIMITS;

	std::string cmd;
	cmd = "WRS DM154.L 2 ";
	cmd += uplimit;
	cmd += " ";
	cmd += lowlimit;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteDispLimits(std::string uplimit, std::string lowlimit)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_DISP_LIMITS;

	std::string cmd;
	cmd = "WRS DM150.L 2 ";
	cmd += uplimit;
	cmd += " ";
	cmd += lowlimit;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteLoadLimits(std::string uplimit, std::string lowlimit)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_LOAD_LIMITS;

	std::string cmd;
	cmd = "WRS DM106.L 2 ";
	cmd += uplimit;
	cmd += " ";
	cmd += lowlimit;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WritePreDispParas(std::string dispValue, std::string speedValue)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_PREDISP_PARAS;

	std::string cmd;
	cmd = "WRS DM164.L 2 ";
	cmd += dispValue;
	cmd += " ";
	cmd += speedValue;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WritePreLoadParas(std::string loadValue, std::string speedValue)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_PRELOAD_PARAS;

	std::string cmd;
	cmd = "WRS DM118.L 2 ";
	cmd += loadValue;
	cmd += " ";
	cmd += speedValue;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteDispFreqAndCount(std::string freq, std::string count)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_DISP_FREQ_COUNT;

	std::string cmd;
	cmd = "WRS DM158.L 2 ";
	cmd += freq;
	cmd += " ";
	cmd += count;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteLoadFreqAndCount(std::string freq, std::string count)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_LOAD_FREQ_COUNT;

	std::string cmd;
	cmd = "WRS DM114.L 2 ";
	cmd += freq;
	cmd += " ";
	cmd += count;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteWaveCompensation(std::string comp, std::string inputFilter)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_WAVEFORM_COMPENSATION;

	std::string cmd;
	cmd = "WRS DM202.L 2 ";
	cmd += comp;
	cmd += " ";
	cmd += inputFilter;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog1Speed(std::string speed)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG1_SPEED;

	std::string cmd;
	cmd = "WRS DM162.L 1 ";
	cmd += speed;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog2Speed(std::string speed)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG2_SPEED;

	std::string cmd;
	cmd = "WRS DM172.L 1 ";
	cmd += speed;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteJog3Speed(std::string speed)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_JOG3_SPEED;

	std::string cmd;
	cmd = "WRS DM174.L 1 ";
	cmd += speed;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
	SendDownlinnkMessage(message);
}

void SWCommunication::WriteLoadSensorAlign(std::string kValue, std::string bValue)
{
	DownlinkMessage message;
	message.m_messType = MESS_WRITE_LOADSENSOR_ALIGN;

	std::string cmd;
	cmd = "WRS DM100.L 2 ";
	cmd += kValue;
	cmd += " ";
	cmd += bValue;
	cmd += "\r";

	int cmdLen = cmd.length();
	message.m_downlinkDataLen = cmdLen;

	memcpy(message.m_downlinkData, cmd.c_str(), cmdLen);
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