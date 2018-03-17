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

void MotorCommand::findCommandData(char *buffer[MAX_DATA_LENGTH], vector<string> &data_vector)
{
	int buffer_new_size = strlen(*buffer);
	//char buffer_new[sizeof(*buffer)+1];
	//strcpy_s(buffer_new, *buffer);

	int buffer_size = strlen(*buffer);

	//Convert buffer to string
	string str(*buffer, buffer_size);

	//convert buffer string to stringstream to parse each line it contains
	std::stringstream  data(str);

	//String to store each line
	std::string line;

	//Sub data blocks
	string cmd_id;
	string device_id;
	string pos_data;

	//Parse each line in buffer data
	while (std::getline(data, line, '\n'))
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
			if (data_vector[0] == "DM")
			{
				break;
			}
		}
		data_vector.clear();


	}

}

void MotorCommand::readFeedbackStream(char *output[MAX_DATA_LENGTH], SerialPort &arduino)
{
	vector<string> data_vector;
	bool atDestination = false;

	char *output_ptr[MAX_DATA_LENGTH];
	*output_ptr = *output;

	//Poll encoder until motor reaches destination
	while (!atDestination)
	{

		//Overwrite RxBuffer
		int bytesRead = arduino.readSerialPort(*output, MAX_DATA_LENGTH);

		//Parse RxBuffer
		findCommandData(output_ptr, data_vector);

		//Filter Commands
		if (data_vector.size() == 3)
		{
			//Filter ECD commands
			if (data_vector[0] == "DMC")
			{
				//Convert String to int
				string positionString = data_vector[2];
				std::string::size_type sz;   // alias of size_t
				int position = std::stoi(positionString, &sz);

				//Check if within threshold
				if (position >  _target_position - 2 && position < _target_position + 2)
				{
					atDestination = true;
				}
			}

		}

	}
}

char* MotorCommand::buildCmdString(stringstream *cmd_stream_ptr, char *cmd_id, int position, int speed, char *motor_id_ptr, char *resp_id)
{
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
