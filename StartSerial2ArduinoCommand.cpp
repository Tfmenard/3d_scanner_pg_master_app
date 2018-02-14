#include "Command.h"
#include "CameraEvent.h"
#include "EDSDK.h"
#include "StartSerial2ArduinoCommand.h"
#include "SerialPort.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;
// Execute command	
bool execute()

	SerialPort arduino = new SerialPort(port_name);

	if (arduino.isConnected())
	{
		cout << "Connection Established" << endl;
	}
	else
	{
		cout << "ERROR, check port name";
	}

	while (arduino.isConnected()) 
	{
		cout << "Write something: \n";
		std::string input_string;
		//Getting input
		getline(cin, input_string);
		//Creating a c string
		char *c_string = new char[input_string.size() + 1];
		//copying the std::string to c string
		std::copy(input_string.begin(), input_string.end(), c_string);
		//Adding the delimiter
		c_string[input_string.size()] = '\n';
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
