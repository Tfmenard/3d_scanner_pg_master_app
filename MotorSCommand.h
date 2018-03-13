#pragma once
#include "MotorCommand.h"

class MotorSCommand : public MotorCommand
{
public:
	MotorSCommand();
	~MotorSCommand();
	using MotorCommand::MotorCommand;

	void setMotorId();

	virtual bool execute()
	{
		//char *command_string;
		//command_string = buildCmdString(&cmd_stream, _target_position, _speed, &_motor_id);
		//Override
		SerialPort arduino(XS_arduino_port);

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

			int command_string_length = strlen(command_string);
			//Writing string to arduino
			arduino.writeSerialPort(command_string, MAX_DATA_LENGTH);
			//Getting reply from arduino
			arduino.readSerialPort(output, MAX_DATA_LENGTH);

			//Attempt at delayed I/O
			/*char *output_buffer_ptr = output;
			vector<string> data_vector;
			while (data_vector.size() != 3)
			{
			findCommandData(output, data_vector, arduino);
			arduino.readSerialPort(output, MAX_DATA_LENGTH);
			}*/

			//printing the output
			puts(output);
			//freeing c_string memory
			//delete[] command_string;
		}
		return true;
	}
};

