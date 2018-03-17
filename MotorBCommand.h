#pragma once
#include "MotorCommand.h"

class MotorBCommand : public MotorCommand
{
public:
	MotorBCommand();
	~MotorBCommand();
	using MotorCommand::MotorCommand;

	void setMotorId();

	virtual bool execute()
	{
		//char *command_string;
		//command_string = buildCmdString(&cmd_stream, _target_position, _speed, &_motor_id);
		//Override
		SerialPort arduino(YB_arduino_port);

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

			char *output_ptr[MAX_DATA_LENGTH];
			*output_ptr = output;

			readFeedbackStream(output_ptr, arduino);


			//printing the output
			puts(output);
			//freeing c_string memory
			//delete[] command_string;
		}
		return true;
	}
};

