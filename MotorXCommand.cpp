#include "MotorXCommand.h"



MotorXCommand::MotorXCommand()
{
}


MotorXCommand::~MotorXCommand()
{
	delete [] cmd_string;
}

void MotorXCommand::setMotorId()
{
	this->_motor_id = this->motor_ids.X;
}