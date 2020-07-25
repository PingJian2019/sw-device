#include "Log.h"
#include "Directory.h"
#include <QString>


Log::Log()
	: m_isStop(false)
	, m_currentNum(0)
{
	CreateFile();
}

Log::~Log()
{
	m_fstreamIn.flush();
	m_fstreamIn.close();
}

int Log::StartLog()
{
	std::thread th(std::bind(&Log::LogFun, this));
	m_logThread = std::move(th);

	return 0;
}

void Log::Stop()
{
	m_isStop = true;
	m_condVar.notify_one();
	m_logThread.join();
}

int Log::LogString(std::string strLog)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_pendingStrList.push_back(strLog);

	m_condVar.notify_one();

	return 0;
}

std::string Log::GetString()
{
	if (m_pendingStrList.size() == 0)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_condVar.wait(lock);
	}

	if (m_pendingStrList.size() == 0)return"";

	std::unique_lock<std::mutex> lock(m_mutex);
	std::string strLog = *m_pendingStrList.begin();
	m_pendingStrList.pop_front();
	return strLog;
}

void Log::LogFun()
{
	while (!m_isStop)
	{
		std::string strLog = GetString();
		if (strLog !="")
		{
			WriteFile(strLog);
		}
	}
}

int Log::CreateFile()
{
	if (m_fstreamIn.is_open())
	{
		m_fstreamIn.flush();
		m_fstreamIn.close();
		m_fstreamIn.clear();
	}

	QString strfileName = Directory::GetLatestFileName();
	m_fstreamIn.open(strfileName.toStdString().c_str(), std::fstream::app | std::fstream::out);
	
	if (m_fstreamIn.is_open())
	{
		m_fstreamIn << LOGHEADER;
		return 0;
	}
	else
	{
		return -1;
	}
}

int Log::WriteFile(std::string strLog)
{
	if (m_fstreamIn.is_open())
	{
		char chNum[8] = { 0 };
		sprintf_s(chNum, sizeof(chNum), "%d", m_currentNum);

		std::string strNum = chNum + std::string(",");
		m_fstreamIn << strNum;
		m_fstreamIn << strLog;
		m_currentNum++;
	}

	if (m_currentNum > MAXNUM)
	{
		m_currentNum = 0;
		CreateFile();
	}

	return 0;
}