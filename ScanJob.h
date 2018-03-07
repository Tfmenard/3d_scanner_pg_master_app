#pragma once

#include "Shot.h"
class ScanJob
{
public:
	vector< vector<Shot> > rows;
public:
	ScanJob();
	~ScanJob();

	void addShot2Row(Shot shot, int rowIndex);
	void addRow(vector<Shot> shots);

	void addRow
	(
		int numOfShots, DWORD_PTR _TvData, DWORD_PTR _AvData, DWORD_PTR _IsoData,
		int _motorXPos, int _motorYPos, int _servoTiltAngle,
		ActionListener* listener
	);

	void startJob();

};

