#include "MotorSCommand.h"



MotorSCommand::MotorSCommand()
{
}


MotorSCommand::~MotorSCommand()
{
}


bool MotorSCommand::execute()
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
		byte byte_buffer[MAX_DATA_LENGTH];

		int command_string_length = strlen(command_string);
		//Writing string to arduino
		arduino.writeSerialPort(command_string, MAX_DATA_LENGTH);

		//Getting reply from arduino
		arduino.readSerialPort(byte_buffer, MAX_DATA_LENGTH);

		//This function will only return when the position status feedback stream returns a value within
		//acceptale threshold
		readFeedbackStream(byte_buffer, arduino);

		//Stop stream command
		char *feedback_receive_id = "R";
		char *cmd_header_id = "M";
		char *command_string_stop_stream = buildCmdString(&cmd_stream, cmd_header_id, _target_position, _speed, &_motor_id, feedback_receive_id);
		arduino.writeSerialPort(command_string_stop_stream, MAX_DATA_LENGTH);

		//printing the output
		puts(output);
		//freeing c_string memory
		//delete[] command_string;
	}
	return true;
}