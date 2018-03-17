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
			
			vector<string> data_vector;
			bool atDestination = false;

			char *output_ptr[MAX_DATA_LENGTH];
			*output_ptr = output;

			//Poll encoder until motor reaches destination
			while (!atDestination)
			{

				//Overwrite RxBuffer
				arduino.readSerialPort(output, MAX_DATA_LENGTH);

				//Parse RxBuffer
				findCommandData(output_ptr, data_vector);

				//Filter Commands
				if (data_vector.size() == 3)
				{
					//Filter ECD commands
					if (data_vector[0] == "ECD")
					{
						//Convert String to int
						string positionString = data_vector[2];
						std::string::size_type sz;   // alias of size_t
						int position = std::stoi(positionString, &sz);

						//Check if within threshold
						if (position >  _target_position - 0.6 && position < _target_position + 0.6)
						{
							atDestination = true;
						}
					}
					
				}

			}

			//printing the output
			puts(output);
			//freeing c_string memory
			//delete[] command_string;
		}
		return true;
	}
};

