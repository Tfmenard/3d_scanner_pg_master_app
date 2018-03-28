#pragma once
#include "MotorCommand.h"

class MotorYCommand : public MotorCommand
{
public:
	bool isHoming = false;
public:
	MotorYCommand();
	~MotorYCommand();
	using MotorCommand::MotorCommand;

	void setMotorId();

	virtual bool execute();
};

