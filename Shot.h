#pragma once

#include "EDSDK.h"
#include "CameraModel.h"
#include "Processor.h"

#include "ActionListener.h"
#include "ActionEvent.h"

#include "OpenSessionCommand.h"
#include "CloseSessionCommand.h"
#include "SaveSettingCommand.h"
#include "TakePictureCommand.h"
#include "DownloadCommand.h"
#include "GetPropertyCommand.h"
#include "GetPropertyDescCommand.h"
#include "SetPropertyCommand.h"
#include "SetCapacityCommand.h"
#include "NotifyCommand.h"

#include "StartEvfCommand.h"
#include "EndEvfCommand.h"
#include "DownloadEvfCommand.h"
#include "DriveLensCommand.h"
#include "PressShutterButtonCommand.h"
#include "GetPropertyCommand.h"
#include "DoEvfAFCommand.h"

#include "StartSerial2ArduinoCommand.h"
#include "MotorXCommand.h"

class Shot
{

public:
	DWORD_PTR TvData;
	LPCTSTR TvCommand = "set_Tv";

	DWORD_PTR AvData;
	LPCTSTR AvCommand = "set_Av";

	DWORD_PTR IsoData;
	LPCTSTR IsoCommand = "set_ISOSpeed";
	

	int motorXPos;
	int motorYPos;
	int motorBAngle;
	int servoTitleAngle;


public:
	Shot();
	~Shot();

	Shot(DWORD_PTR _TvData, DWORD_PTR _AvData, DWORD_PTR _IsoData,
		int _motorXPos, int _motorYPos, int _motorBAngle, int _servoTitleAngle);
};

