#ifndef SERIAL_COMMUNICATION_H
#define SERIAL_COMMUNICATION_H

#include "i_communication.h"
#include "QextSerialPort/win_qextserialport.h"

class SerialCommunication : public ICommunication
{
public:
	SerialCommunication(const QString portName, const QString baudRate);
	~SerialCommunication();
	bool SetupCommunication();
	bool DownlinkMessage(const unsigned char * message, const int messageLen);
	bool UplinkMessage(unsigned char * dataBuffer, const int bufferSize, int & dataLen);
	void EndCommunication();
private:
	BaudRateType GetBaudRateTypeByStr(const QString baudRate);
private:
	Win_QextSerialPort m_serialPort;
	QString				m_baudRate;
};


#endif