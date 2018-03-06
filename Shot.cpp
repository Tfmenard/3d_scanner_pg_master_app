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