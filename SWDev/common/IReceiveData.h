#pragma once

#include "common_type.h"
#include <string>

class IReceiveData
{
public:
	virtual void ReceiveData(MessageType type, unsigned char * data, int dataLen) = 0;
	virtual void ReceiveData(MessageType type, std::string data) = 0;
};