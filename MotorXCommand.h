#pragma once
#include "MotorCommand.h"

class MotorXCommand : public MotorCommand
{
public:
	MotorXCommand();
	~MotorXCommand();
	using MotorCommand :: MotorCommand;

	void setMotorId();

	virtual bool execute()
	{
		char *command_string;
		command_string = buildCmdString(&cmd_stream, _target_position, _speed, &_motor_id);
		//Override
		SerialPort arduino(XW_arduino_port);

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

			char *command_string;
			command_string = buildCmdString(&cmd_stream, _target_position, _speed, &_motor_id);

			//Adding the delimiter
			//c_string[input_string.size()] = '\n';

			//Writing string to arduino
			arduino.writeSerialPort(command_string, MAX_DATA_LENGTH);
			//Getting reply from arduino
			arduino.readSerialPort(output, MAX_DATA_LENGTH);
			//printing the output
			puts(output);
			//freeing c_string memory
			//delete[] command_string;
		}
		return true;
	}
};

