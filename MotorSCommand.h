#pragma once
#include "MotorCommand.h"

class MotorSCommand : public MotorCommand
{
public:
	MotorSCommand();
	~MotorSCommand();
	using MotorCommand::MotorCommand;

	void setMotorId();

	virtual bool execute();
};

