#include "DownlinkMessageList.h"
#include <QDebug>

DownlinkMessageList::DownlinkMessageList()
{

}

void DownlinkMessageList::AddDownLinkMessage(const DownlinkMessage & message)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	// Now, add the message into the list. 
	// For messages with priority 1~3, search from head to tail

	int messageSize = m_downlistList.size();
	qDebug() << "messageSize: " << messageSize << "endl";
	std::list<DownlinkMessage>::iterator i = m_downlistList.begin();
	while ((i != m_downlistList.end()) && (*i).m_priority <= message.m_priority)
		i++;

	if (i == m_downlistList.begin())
	{
		//prepend(message);
		m_downlistList.push_front(message);
	}
	else if (i == m_downlistList.end())
	{
		//append(message);
		m_downlistList.push_back(message);
	}
	else
	{
		m_downlistList.insert(i, message);
	}
#if 0
	if ((message.m_priority >= PRIORITY_ONE) && (message.m_priority <= PRIORITY_THREE))
	{
		// For messages with priority 1~3, search from head to tail
		std::list<DownlinkMessage>::iterator i = m_downlistList.begin();
		while ((i != m_downlistList.end()) && (*i).m_priority <= message.m_priority)
			i++;

		if (i == m_downlistList.begin())
		{
			//prepend(message);
			m_downlistList.push_front(message);
		}
		else if (i == m_downlistList.end())
		{
			//append(message);
			m_downlistList.push_back(message);
		}
		else
		{
			m_downlistList.insert(i, message);
		}
	}
	else
	{
		// For messages with priority 4 and higher, search from tail to head
		std::list<DownlinkMessage>::iterator i = m_downlistList.end();
		i--;
		while ((i != m_downlistList.begin()) && (*i).m_priority > message.m_priority)
			i--;

		if (i == m_downlistList.end())
		{
			//append(message);
			m_downlistList.push_back(message);
		}
		else if (i == m_downlistList.begin())
		{
			//prepend(message);
			m_downlistList.push_front(message);
		}
		else
		{
			m_downlistList.insert(i, message);
		}
	}
	//m_downlistList.push_back(message);

#endif
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
	
	std::unique_lock<std::mutex> lock(m_mutex);
	message = *m_downlistList.begin();
	m_downlistList.pop_front();
	
}