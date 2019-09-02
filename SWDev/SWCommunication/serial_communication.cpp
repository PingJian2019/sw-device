#include <QIODevice>

#include "serial_communication.h"

SerialCommunication::SerialCommunication(const QString portName, const QString baudRate)
	: m_baudRate(baudRate)
{
	m_serialPort.setPortName(portName);
	m_serialPort.setQueryMode(QextSerialBase::Polling);
	/*m_serialPort.setBaudRate(GetBaudRateTypeByStr(baudRate));
	m_serialPort.setDataBits(DATA_8);
	m_serialPort.setParity(PAR_EVEN);
	m_serialPort.setStopBits(STOP_1);
	m_serialPort.setFlowControl(FLOW_OFF);*/
	m_serialPort.setTimeout(10);
}

SerialCommunication::~SerialCommunication()
{
	EndCommunication();
}

bool SerialCommunication::SetupCommunication()
{
	bool result = false;
 
	//Open the serial port
	result = m_serialPort.open(QIODevice::ReadWrite);
	if (result)
	{
		m_serialPort.setBaudRate(GetBaudRateTypeByStr(m_baudRate));
		m_serialPort.setDataBits(DATA_8);
		m_serialPort.setParity(PAR_EVEN);
		m_serialPort.setStopBits(STOP_1);
		m_serialPort.setFlowControl(FLOW_OFF);
	}

	return result;
}

bool SerialCommunication::DownlinkMessage(const unsigned char * message, const int messageLen)
{
	int returnCode = m_serialPort.write((const char *)message, messageLen);

	return returnCode != -1;
}

bool SerialCommunication::UplinkMessage(unsigned char * dataBuffer, const int bufferSize, int & dataLen)
{
	dataLen = m_serialPort.read((char *)dataBuffer, bufferSize);

	return dataLen != -1;
}

void SerialCommunication::EndCommunication()
{
	//Close the serial port
	m_serialPort.close();
}

BaudRateType SerialCommunication::GetBaudRateTypeByStr(const QString baudRate)
{
	BaudRateType type = BAUD57600;

	if(baudRate == "110")
		type = BAUD110;
	else if(baudRate == "300")
		type = BAUD300;
	else if(baudRate == "600")
		type = BAUD600;
	else if(baudRate == "1200")
		type = BAUD1200;
	else if(baudRate == "2400")
		type = BAUD2400;
	else if(baudRate == "4800")
		type = BAUD4800;
	else if(baudRate == "9600")
		type = BAUD9600;
	else if(baudRate == "14400")
		type = BAUD14400;
	else if(baudRate == "19200")
		type = BAUD19200;
	else if(baudRate == "38400")
		type = BAUD38400;
	else if(baudRate == "56000")
		type = BAUD56000;
	else if(baudRate == "57600")
		type = BAUD57600;
	else if(baudRate == "115200")
		type = BAUD115200;
	else if(baudRate == "128000")
		type = BAUD128000;
	else if(baudRate == "256000")
		type = BAUD256000;

	return type;
}