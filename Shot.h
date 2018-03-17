#pragma once

#include "EDSDK.h"
#include "CameraModel.h"
#include "Processor.h"

#include "ActionListener.h"
#include "ActionEvent.h"

#include "ActionSource.h"

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

class Shot: public ActionSource
{

public:
	DWORD_PTR TvData;
	LPCTSTR TvCommand = "set_Tv";

	DWORD_PTR AvData;
	LPCTSTR AvCommand = "set_Av";

	DWORD_PTR IsoData;
	LPCTSTR IsoCommand = "set_ISOSpeed";
	
	LPCTSTR TakePictureCommand = "TakePicture";

	int motorXPos;
	LPCTSTR MotorXCommand = "Move2X";

	//TODO: Add other motor commands
	int motorYPos;
	LPCTSTR MotorYCommand = "Move2Y";

	int motorBAngle;
	LPCTSTR MotorBCommand = "Move2B";

	int servoTitleAngle;
	LPCTSTR MotorSCommand = "Move2S";



public:
	Shot();
	~Shot();

	Shot(DWORD_PTR _TvData, DWORD_PTR _AvData, DWORD_PTR _IsoData,
		int _motorXPos, int _motorYPos, int _motorBAngle, int _servoTitleAngle);

	Shot(DWORD_PTR _TvData, DWORD_PTR _AvData, DWORD_PTR _IsoData, int _motorXPos, int _motorYPos, int _motorBAngle, int _servoTiltAngle, ActionListener* listener);

	void fireEventAv(DWORD_PTR *data);

	void sendCommands();

	void setupListener(ActionListener* listener);
};

