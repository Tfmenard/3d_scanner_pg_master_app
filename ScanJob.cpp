#include "ScanJob.h"



ScanJob::ScanJob()
{
}


ScanJob::~ScanJob()
{
}

void ScanJob::addRow(vector<Shot> shots)
{
	this->rows.push_back( shots );
}

void ScanJob::addRow
(
	int numOfShots, DWORD_PTR _TvData, DWORD_PTR _AvData, DWORD_PTR _IsoData,
	int _motorXPos, int _motorYPos, int _servoTiltAngle,
	ActionListener* listener
)
{
	vector<Shot> row;
	for (int i = 0; i < numOfShots; i++)
	{
		double motorBAngle = i * (360 / numOfShots);
		Shot *newShot = new Shot(_TvData, _AvData, _IsoData, _motorXPos, _motorYPos, motorBAngle, _servoTiltAngle, listener);

		row.push_back(*newShot);
		
	}

	this->addRow(row);
}

void ScanJob::startJob()
{
	vector< vector<Shot> >::iterator rowIterator = rows.begin();

	vector<Shot>::iterator shotIterator;

	while (rowIterator != rows.end())
	{
		shotIterator = (rowIterator)->begin();

		while (shotIterator != rowIterator->end())
		{
			(shotIterator++)->sendCommands();
		}

		rowIterator++;
	}
}
