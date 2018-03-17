#include "Shot.h"



Shot::Shot()
{
}


Shot::~Shot()
{
}

Shot::Shot(DWORD_PTR _TvData, DWORD_PTR _AvData, DWORD_PTR _IsoData,
	int _motorXPos, int _motorYPos, int _motorBAngle, int _servoTitleAngle)

:TvData(_TvData), AvData(_AvData), IsoData(_IsoData),
motorXPos(_motorXPos), motorYPos(_motorYPos), motorBAngle(_motorBAngle), servoTitleAngle(_servoTitleAngle)
{}

Shot::Shot(DWORD_PTR _TvData, DWORD_PTR _AvData, DWORD_PTR _IsoData,
	int _motorXPos, int _motorYPos, int _motorBAngle, int _servoTiltAngle, ActionListener* listener)

	: TvData(_TvData), AvData(_AvData), IsoData(_IsoData),
	motorXPos(_motorXPos), motorYPos(_motorYPos), motorBAngle(_motorBAngle), servoTitleAngle(_servoTiltAngle)
{
	setupListener(listener);
}

void Shot::fireEventAv(DWORD_PTR *data)
{
	fireEvent(AvCommand, data);
}

void Shot::setupListener(ActionListener* listener)
{
	addActionListener(listener);
}

void Shot::sendCommands()
{
	//Set Tv
	fireEvent(TvCommand, &TvData);

	//Set Av
	fireEvent(AvCommand, &AvData);

	//Set ISO
	fireEvent(IsoCommand, &IsoData);

	//Set Y position
	fireEvent(MotorYCommand, &motorYPos);

	//Set X position
	//fireEvent(MotorXCommand, &motorXPos);

	//Set S position
	//fireEvent(MotorSCommand, &servoTitleAngle);

	//Set B position
	fireEvent(MotorBCommand, &motorBAngle);


	fireEvent(TakePictureCommand);

	Sleep(2000);
	
}