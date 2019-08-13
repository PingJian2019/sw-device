#pragma once

#include "common_type.h"

class IReceiveData
{
public:
	virtual void ReceiveData(MessageType type, unsigned char * data, int dataLen) = 0;
};