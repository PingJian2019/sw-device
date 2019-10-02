#pragma once

#include "common_type.h"

#include <list>
#include <mutex>

class DownlinkMessageList
{
public:
	DownlinkMessageList();

	void QuitMessageList();

	void AddDownLinkMessage(const DownlinkMessage & message);
	void GetNextMessage(DownlinkMessage & message);

private:
	std::list<DownlinkMessage>	m_downlistList;

	std::mutex					m_mutex;
	std::condition_variable		m_condVar;
};