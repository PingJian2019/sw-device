#ifndef COMMUNICATION_BASE_H
#define COMMUNICATION_BASE_H


class ICommunication
{
public:
	virtual bool SetupCommunication() = 0;
	virtual bool DownlinkMessage(const unsigned char * message, const int messageLen) = 0;
	virtual bool UplinkMessage(unsigned char * dataBuffer, const int bufferSize, int & dataLen) = 0;
	virtual void EndCommunication() = 0;
};


#endif