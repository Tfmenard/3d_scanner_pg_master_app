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
		char *YB_arduino_port = "\\\\.\\COM13";
		char *XS_arduino_port = "\\\\.\\COM15";


		//List of possible motor ids
		struct id_enum
		{
			char X = 'X';
			char Y = 'Y';
			char B = 'B';
			char S = 'S';
		}  motor_ids ;

		struct cmd_id_enum
		{
			char Encoder = 'E';
			
		}  cmd_ids;

		//Member variables used when building cmd strings
		char _motor_id;
		int _target_position;
		int _speed = 5;

		//String for getting the output from arduino
		char output[MAX_DATA_LENGTH];

		//String stream used to concatenate different types into one string
		stringstream cmd_stream;

	protected:
		//Cmd identifier for DC motors
		char *cmd_identifier = "M";
	
	public:
		//Pointer to cmd string sent to arduinos
		char *cmd_string;

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
		MotorCommand(int* position, char id) :_target_position(*position)
		{
			setMotorId(id);
			cmd_string = new char[sizeof(_target_position) + sizeof(_speed) + 2];

		}
	public:
		MotorCommand(void);
		~MotorCommand(void);

		void setMotorId();

		void setMotorId(char id);

		void findCommandData(char (&buffer)[MAX_DATA_LENGTH], vector<string> &data_vector);

		void findCommandData(char *buffer, vector<string> &data_vector, SerialPort &arduino);

		void findCommandData(char(&buffer)[MAX_DATA_LENGTH], string &cmd_id, int &position, int buffer_size);

		boolean findCommandData(byte(&buffer)[MAX_DATA_LENGTH], string &cmd_id, int &position, int buffer_size);
		boolean findCommandData(byte(&buffer)[MAX_DATA_LENGTH], string &cmd_id, int &position, int buffer_size, string trgt_cmd);

		void readFeedbackStream(char (&buffer)[MAX_DATA_LENGTH], SerialPort &arduino);
		void readFeedbackStream(byte(&buffer)[MAX_DATA_LENGTH], SerialPort &arduino);
		void readFeedbackStream(byte(&buffer)[MAX_DATA_LENGTH], SerialPort &arduino, string trgt_cmd);

		char* buildCmdString(stringstream *cmd_stream_ptr, char *cmd_id, int position, int speed, char *motor_id_ptr, char *resp_id);
		

		char* buildCmdString(stringstream *cmd_stream_ptr, int position, int speed, char *motor_id_ptr)
		{
			//Build command as stringstream
			*cmd_stream_ptr << *cmd_identifier;
			*cmd_stream_ptr << ",";
			*cmd_stream_ptr << *motor_id_ptr;
			*cmd_stream_ptr << ",";
			*cmd_stream_ptr << position;
			*cmd_stream_ptr << '\n';
			//*cmd_stream_ptr << ",";
			//*cmd_stream_ptr << speed;

			//Convert to stringstream to string
			string tmp_string = cmd_stream_ptr->str();

			std::string segment;
			std::vector<std::string> seglist;

			getline(*cmd_stream_ptr, tmp_string, '\0');
			seglist.push_back(tmp_string);


			//Initiate cmd_string member variable
			cmd_string = new char[tmp_string.length()];

			// Copying the contents of tmp_string to char array cmd_string
			strcpy(cmd_string, tmp_string.c_str());

			return cmd_string;
		}
};

