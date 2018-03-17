#pragma once
#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 247

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class SerialPort
{
private:

public:
	HANDLE handler;
	COMSTAT status;
	DWORD errors;
	bool connected;
	SerialPort(char *portName);
	~SerialPort();

	int readSerialPort(char *buffer, unsigned int buf_size);
	bool writeSerialPort(char *buffer, unsigned int buf_size);
	bool isConnected();
};

#endif // SERIALPORT_H

