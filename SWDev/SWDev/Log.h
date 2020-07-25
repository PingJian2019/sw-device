#pragma once

#include "Directory.h"

#include <list>
#include <string>
#include <mutex>
#include <thread>
#include <functional>

#include <fstream>

#define MAXNUM 5000
#define LOGHEADER "NO.,Time(Sec),Position,Load,Peak(pos),Valley(pos),Peak(load),Valley(load)\n";

class Log
{
public:
	Log();
	~Log();

	int StartLog();
	void Stop();
	int LogString(std::string strLog);

private:
	std::string GetString();
	int WriteFile(std::string strLog);

	int CreateFile();


	void LogFun();

private:
	std::list<std::string>		m_pendingStrList;

	std::mutex					m_mutex;
	std::condition_variable		m_condVar;

	std::thread					m_logThread;

	std::fstream				m_fstreamIn;

	int							m_currentNum;

	bool						m_isStop;
};
