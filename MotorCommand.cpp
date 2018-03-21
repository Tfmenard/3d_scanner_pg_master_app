#include "MotorCommand.h"



MotorCommand::MotorCommand()
{
}


MotorCommand::~MotorCommand()
{
	delete[] cmd_string;
}

void MotorCommand::setMotorId()
{
	//Default ID
	this->_motor_id = this->motor_ids.B;
}

void MotorCommand::setMotorId(char id)
{
	if (id == this->motor_ids.B)
	{
		this->_motor_id = this->motor_ids.B;
	}
	else if (id == this->motor_ids.X)
	{
		this->_motor_id = this->motor_ids.X;
	}
	else if (id == this->motor_ids.Y)
	{
		this->_motor_id = this->motor_ids.Y;
	}
	else if (id == this->motor_ids.S)
	{
		this->_motor_id = this->motor_ids.S;
	}
		
}

void MotorCommand::findCommandData(char (&buffer)[MAX_DATA_LENGTH], vector<string> &data_vector)
{
	int buffer_new_size = strlen(buffer);
	//char buffer_new[sizeof(*buffer)+1];
	//strcpy_s(buffer_new, *buffer);

	int buffer_size = strlen(buffer);

	//Convert buffer to string
	//string str(begin(buffer, buffer_size);

	//convert buffer string to stringstream to parse each line it contains
	std::stringstream  data;
	data << buffer;

	//String to store each line
	std::string line;

	//Sub data blocks
	string cmd_id;
	string device_id;
	string pos_data;

	//Parse each line in buffer data
	char delim = '}';
	while (std::getline(data, line, delim))
	{


		//convert line into string stream to parse each line 
		//and find the one that conatins ',' characters
		stringstream line_stream(line);

		//Variable to store index where the first ',' character found
		std::size_t found = 0;

		//String to store sub data block temporarily
		string tmp_data_string;

		//index to the first character of the sub data block being extracted
		int data_index = 0;

		//length of the sub data block being extracted
		int sub_data_length = found - data_index;

		//npos is returned by find_first_of when the input string does not contain the target string
		while (found != std::string::npos)
		{

			if (found == 0)
				found = line.find_first_of(',');
			else
				found = line.find_first_of(',', found + 1);

			cout << "found = " << found << endl;

			sub_data_length = found - data_index;

			//If this is true, no ',' character was found, so we are no looking at a line
			//containing COMMANDS or DONE signals
			if (sub_data_length < 0)
				break;
			cout << "sub_data_length = " << sub_data_length << endl;

			//Store sub data block in a string
			tmp_data_string = line.substr(data_index, sub_data_length);
			cout << "tmp_data_string " << tmp_data_string << endl;

			//Update sub data block index to be after the last found ',' char
			data_index = found + 1;

			cout << "data_index = " << data_index << endl;

			cout << endl;

			//Store data in vector. this way commands can have variable numbers of sub data blocks
			data_vector.push_back(tmp_data_string);

			if (data_vector.size() == 3)
			{
				break;
			}

		}

		//Filter DM commands
		if (data_vector.size() == 3)
		{
			if (data_vector[0] == "DMC")
			{
				break;
			}
		}
		data_vector.clear();


	}

}

void MotorCommand::findCommandData(char(&buffer)[MAX_DATA_LENGTH], string &cmd_id, int &position, int buffer_size)
{

	int buffer_new_size = strlen(buffer);
	int positionAsInt;


	//Parse each line in buffer data
	char startChar = '{';
	char endChar = '}';

	//Pointers to start and end of message
	int startMsgIndex = 0;
	int endMsgIndex = 0;

	//Offsets relative to start of message char
	int motor_id_offset = 5;
	int pos_offset = 7;

	bool foundStartChar = false;

	while (startMsgIndex < buffer_size && endMsgIndex < buffer_size)
	{

		//Find new start and end indexes
		for (int i = startMsgIndex; i<buffer_size; i++)
		{
			if (!foundStartChar)
			{
				if (buffer[i] == startChar)
				{
					startMsgIndex = i;
					foundStartChar = true;
					endMsgIndex = startMsgIndex + 10;
				}

			}
			else
			{
				break;
			}
		}

		//Make sure incomplete commands are not read
		if (startMsgIndex >= buffer_size || endMsgIndex >= buffer_size)
			break;


		//Filter DM commands
		if (buffer[startMsgIndex + 1] == 'E' && buffer[startMsgIndex + 2] == 'C' && buffer[startMsgIndex + 3] == 'D')
		{
			cmd_id = "ECD";
			uint8_t divider = buffer[startMsgIndex + pos_offset];
			uint8_t remainder = buffer[startMsgIndex + pos_offset + 1];
			int position = divider * (120) + remainder;
			//positionAsInt = (int)position;
			break;
		}

		//Update Start index to next chracter location
		startMsgIndex = endMsgIndex + 1;

		//reset boolean condition for loop above
		foundStartChar = false;


	}
}


boolean MotorCommand::findCommandData(byte(&buffer)[MAX_DATA_LENGTH], string &cmd_id, int &position, int buffer_size)
{

	//Parse each line in buffer data
	char startChar = '{';
	char endChar = '}';

	//Pointers to start and end of message
	int startMsgIndex = 0;
	int endMsgIndex = 10;

	//Offsets relative to start of message char
	int motor_id_offset = 5;
	int pos_offset = 7;


	//Filter DM commands
	if (buffer[1] == 'E' && buffer[2] == 'C' && buffer[3] == 'D')
	{
		cmd_id = "ECD";
		uint8_t divider = buffer[startMsgIndex + pos_offset];
		uint8_t remainder = buffer[startMsgIndex + pos_offset + 1];
		position = divider * (120) + remainder;
		
		return true;
	}
	return false;
	
}

void MotorCommand::readFeedbackStream(char (&buffer)[MAX_DATA_LENGTH], SerialPort &arduino)
{
	vector<string> data_vector;
	bool atDestination = false;

	//char *output_ptr[MAX_DATA_LENGTH];
	//*output_ptr = output;

	//Poll encoder until motor reaches destination
	while (!atDestination)
	{

		//Overwrite RxBuffer
		int bytesRead = arduino.readSerialPort(output, MAX_DATA_LENGTH);
		int position;
		string cmd_id;
		//Parse RxBuffer
		findCommandData(output, cmd_id, position, MAX_DATA_LENGTH);

		
		//Filter ECD commands
		if (cmd_id == "ECD")
		{
			//int position = ((uint16_t)posHead << 8) | posTail;
			//Check if within threshold
			if (position >  _target_position - 2 && position < _target_position + 2)
			{
				atDestination = true;
			}
		}

	}


}

void MotorCommand::readFeedbackStream(byte(&buffer)[MAX_DATA_LENGTH], SerialPort &arduino)
{
	vector<string> data_vector;
	bool atDestination = false;

	//Poll encoder until motor reaches destination
	while (!atDestination)
	{

		//Overwrite RxBuffer
		int bytesRead = arduino.readSerialPort(buffer, MAX_DATA_LENGTH);
		int position;
		string cmd_id;

		if (arduino.readSerialPort(buffer, MAX_DATA_LENGTH))
		{
			//Parse RxBuffer
			if (findCommandData(buffer, cmd_id, position, MAX_DATA_LENGTH))
			{
				//Filter ECD commands
				if (cmd_id == "ECD")
				{
					//int position = ((uint16_t)posHead << 8) | posTail;
					//Check if within threshold
					if (position >  _target_position - 2 && position < _target_position + 2)
					{
						atDestination = true;
					}
				}
			}
		}

	}
}

char* MotorCommand::buildCmdString(stringstream *cmd_stream_ptr, char *cmd_id, int position, int speed, char *motor_id_ptr, char *resp_id)
{
	memset(cmd_string, 0, sizeof(cmd_string));
	cmd_stream.str(std::string());
	cmd_stream.clear();

	//Build command as stringstream
	*cmd_stream_ptr << *cmd_id;
	*cmd_stream_ptr << ",";
	*cmd_stream_ptr << *motor_id_ptr;
	*cmd_stream_ptr << ",";
	*cmd_stream_ptr << *resp_id;
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
