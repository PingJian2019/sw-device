#pragma once

#include "IReceiveData.h"

class ReceiveDataManage : public IReceiveData
{
public:
	ReceiveDataManage();
	~ReceiveDataManage();

public:
	virtual void ReceiveData(MessageType type, unsigned char * data, int dataLen);
};
