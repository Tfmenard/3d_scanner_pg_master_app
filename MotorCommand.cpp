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
	this->_motor_id = this->motor_ids.X;
}
