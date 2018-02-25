#pragma once

#pragma once

#include "Command.h"
#include "CameraEvent.h"
#include "EDSDK.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SerialPort.h"

using namespace std;


class StartSerial2ArduinoCommand : public Command
{
	//String for getting the output from arduino
	char output[MAX_DATA_LENGTH];

	/*Portname must contain these backslashes, and remember to
	replace the following com port*/
	char *port = "\\\\.\\COM11";

	//String for incoming data
	//char incomingDataFromArduino[MAX_DATA_LENGTH];

public:
	StartSerial2ArduinoCommand(CameraModel *model) : Command(model) {}


	// Execute command	
	virtual bool execute()
	{
		SerialPort arduino(port);

		if (arduino.isConnected())
		{
			cout << "Connection Established" << endl;
		}
		else
		{
			cout << "ERROR, check port name";
		}

		if (arduino.isConnected())
		{
			cout << "Write something: \n";
			std::string input_string;
			//Getting input
			//getline(cin, input_string);

			//Creating a c string
			char *c_string = new char[input_string.size() + 1];
			//copying the std::string to c string
			//std::copy(input_string.begin(), input_string.end(), c_string);

			c_string = "ON\n";

			//Adding the delimiter
			//c_string[input_string.size()] = '\n';

			//Writing string to arduino
			arduino.writeSerialPort(c_string, MAX_DATA_LENGTH);
			//Getting reply from arduino
			arduino.readSerialPort(output, MAX_DATA_LENGTH);
			//printing the output
			puts(output);
			//freeing c_string memory
			delete[] c_string;
		}

		return true;
	}

};

