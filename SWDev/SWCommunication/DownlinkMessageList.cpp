#include "DownlinkMessageList.h"

DownlinkMessageList::DownlinkMessageList()
{

}

void DownlinkMessageList::AddDownLinkMessage(const DownlinkMessage & message)
{
	//std::lock_guard<std::mutex> lock(m_mutex);
	std::unique_lock<std::mutex> lock(m_mutex);
	m_downlistList.push_back(message);
	m_condVar.notify_one();
}

void DownlinkMessageList::GetNextMessage(DownlinkMessage & message)
{
	if (m_downlistList.size() == 0)
	{
		//std::lock_guard<std::mutex> lock(m_mutex);
		std::unique_lock<std::mutex> lock(m_mutex);
		m_condVar.wait(lock);
		
	}
	
	message = *m_downlistList.begin();
	m_downlistList.pop_front();
	
}