#pragma once

#include "Command.h"
#include "CameraEvent.h"
#include "EDSDK.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include "SerialPort.h"

using namespace std;


class MotorCommand : public Command
{

	/*Portname must contain these backslashes, and remember to
	replace the following com port*/
	protected:

		//Default port for arduinos on Windows
		char *YB_arduino_port = "\\\\.\\COM11";
		char *XW_arduino_port = "\\\\.\\COM10";

		//List of possible motor ids
		struct id_enum
		{
			char X = 'X';
			char Y = 'Y';
			char B = 'B';
		}  motor_ids ;

		//Member variables used when building cmd strings
		char _motor_id;
		int _target_position;
		int _speed;

		//String for getting the output from arduino
		char output[MAX_DATA_LENGTH];

		//Pointer to cmd string sent to arduinos
		char *cmd_string;

		//String stream used to concatenate different types into one string
		stringstream cmd_stream;

	private:
		//Cmd identifier for DC motors
		char *cmd_identifier = "DC";


	public:
		MotorCommand(int position, int speed):_target_position(position), _speed(speed)
		{
			setMotorId();
			cmd_string = new char[sizeof(_target_position) + sizeof(_speed) + 2];

		}
		MotorCommand(int* position, int speed) :_target_position(*position), _speed(speed)
		{
			setMotorId();
			cmd_string = new char[sizeof(_target_position) + sizeof(_speed) + 2];

		}
	public:
		MotorCommand(void);
		~MotorCommand(void);

		void setMotorId();


		char* buildCmdString(stringstream *cmd_stream_ptr, int position, int speed, char *motor_id_ptr)
		{
			//Build command as stringstream
			*cmd_stream_ptr << *cmd_identifier;
			*cmd_stream_ptr << ",";
			*cmd_stream_ptr << *motor_id_ptr;
			*cmd_stream_ptr << ",";
			*cmd_stream_ptr << position;
			*cmd_stream_ptr << ",";
			*cmd_stream_ptr << speed;

			//Convert to stringstream to string
			string tmp_string = cmd_stream_ptr->str();

			//Initiate cmd_string member variable
			cmd_string = new char[tmp_string.length()];

			// Copying the contents of tmp_string to char array cmd_string
			strcpy(cmd_string, tmp_string.c_str());

			return cmd_string;
		}

};

