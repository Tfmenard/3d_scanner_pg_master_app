/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : CameraControlDlg.cpp                                            *
*                                                                             *
*   Description: This is the Sample code to show the usage of EDSDK.          *
*                                                                             *
*                                                                             *
*******************************************************************************
*                                                                             *
*   Written and developed by Camera Design Dept.53                            *
*   Copyright Canon Inc. 2006-2008 All Rights Reserved                        *
*                                                                             *
*******************************************************************************/

#include "stdafx.h"
#include <map>

#include "CameraControl.h"
#include "CameraControlDlg.h"
#include ".\CameraControldlg.h"

#include "EDSDK.h"
#include "EDSDKTypes.h"

#include "Shot.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_USER_DOWNLOAD_COMPLETE		WM_APP+1
#define WM_USER_PROGRESS_REPORT			WM_APP+2


// CCameraControlDlg 

CCameraControlDlg::CCameraControlDlg(CWnd* pParent )
	: CDialog(CCameraControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCameraControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_BUTTON19, _btnSend2Arduino);
	DDX_Control(pDX, IDC_EDIT2, _edit2);
	DDX_Control(pDX, IDC_EDIT3, _edit3);
	DDX_Control(pDX, IDC_EDIT4, _edit4);
	DDX_Control(pDX, IDC_BUTTON24, _btnMove2X);
	DDX_Control(pDX, IDC_BUTTON23, _btnAddRow);
	DDX_Control(pDX, IDC_BUTTON25, _startJob);
	DDX_Control(pDX, IDC_LIST2, _rowList);

	DDX_Control(pDX, IDC_EDIT_POS_Y_READONLY, _edit_pos_Y_readonly);
	DDX_Control(pDX, IDC_EDIT_POS_Y_SEND, _edit_pos_Y_send);

	DDX_Control(pDX, IDC_EDIT_POS_B_READONLY, _edit_pos_B_readonly);
	DDX_Control(pDX, IDC_EDIT_POS_B_SEND, _edit_pos_B_send);

	DDX_Control(pDX, IDC_EDIT_POS_S_READONLY, _edit_pos_S_readonly);
	DDX_Control(pDX, IDC_EDIT_POS_S_SEND, _edit_pos_S_send);


	_rowList.InsertColumn(0, "Number of shots");
	_rowList.SetColumnWidth(0, 60);

	_rowList.InsertColumn(1, "Tv");
	_rowList.SetColumnWidth(1, 80);

	_rowList.InsertColumn(2, "Av");
	_rowList.SetColumnWidth(2, 100);

	_rowList.InsertColumn(3, "ISO");
	_rowList.SetColumnWidth(3, 120);

	_rowList.InsertColumn(4, "X position");
	_rowList.SetColumnWidth(4, 140);

	_rowList.InsertColumn(5, "Y position");
	_rowList.SetColumnWidth(5, 160);

	_rowList.InsertColumn(6, "Tilt Angle");
	_rowList.SetColumnWidth(6, 180);

	
	//AddData(_rowList, 0, 0, "00");
	//AddData(_rowList, 0, 1, "01");
	//AddData(_rowList, 1, 0, "10");
	//AddData(_rowList, 1, 1, "11");
	_rowList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	DDX_Control(pDX, IDC_BUTTON1, _btnTakePicture);
	DDX_Control(pDX, IDC_PROGRESS1, _progress);
	DDX_Control(pDX, IDC_EDIT1, _edit);
	DDX_Control(pDX, IDC_PICT, _pictureBox);
	DDX_Control(pDX, IDC_COMBO1, _comboAEMode);
	DDX_Control(pDX, IDC_COMBO2, _comboTv);
	DDX_Control(pDX, IDC_COMBO3, _comboAv);
	DDX_Control(pDX, IDC_COMBO4, _comboIso);
	DDX_Control(pDX, IDC_COMBO5, _comboMeteringMode);
	DDX_Control(pDX, IDC_COMBO6, _comboExposureComp);
	DDX_Control(pDX, IDC_COMBO7, _comboImageQuality);
	DDX_Control(pDX, IDC_BUTTON2, _btnStartEVF);
	DDX_Control(pDX, IDC_BUTTON3, _btnEndEVF);
	DDX_Control(pDX, IDC_BUTTON4, _btnFocusNear3);
	DDX_Control(pDX, IDC_BUTTON5, _btnFocusNear2);
	DDX_Control(pDX, IDC_BUTTON6, _btnFocusNear1);
	DDX_Control(pDX, IDC_BUTTON7, _btnFocusFar1);
	DDX_Control(pDX, IDC_BUTTON8, _btnFocusFar2);
	DDX_Control(pDX, IDC_BUTTON9, _btnFocusFar3);
	DDX_Control(pDX, IDC_BUTTON10, _btnFocusUp);
	DDX_Control(pDX, IDC_BUTTON11, _btnFocusLeft);
	DDX_Control(pDX, IDC_BUTTON12, _btnFocusRight);
	DDX_Control(pDX, IDC_BUTTON13, _btnFocusDown);
	DDX_Control(pDX, IDC_BUTTON14, _btnZoomFit);
	DDX_Control(pDX, IDC_BUTTON15, _btnZoomZoom);
	DDX_Control(pDX, IDC_BUTTON16, _btnPressingHalfway);
	DDX_Control(pDX, IDC_BUTTON17, _btnPressingCompletely);
	DDX_Control(pDX, IDC_BUTTON18, _btnPressingOff);
	DDX_Control(pDX, IDC_BUTTON21, _btnEvfAfON);
	DDX_Control(pDX, IDC_BUTTON22, _btnEvfAfOFF);
	DDX_Control(pDX, IDC_COMBO8, _comboEvfAFMode);
}

BEGIN_MESSAGE_MAP(CCameraControlDlg, CDialog)
	ON_MESSAGE(WM_USER_DOWNLOAD_COMPLETE, OnDownloadComplete)
	ON_MESSAGE(WM_USER_PROGRESS_REPORT, OnProgressReport)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON24, &CCameraControlDlg::OnBnClickedButton24)
	ON_EN_CHANGE(IDC_EDIT2, &CCameraControlDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CCameraControlDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON23, &CCameraControlDlg::OnBnClickedButton23)
	ON_EN_CHANGE(IDC_EDIT4, &CCameraControlDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON25, &CCameraControlDlg::OnBnClickedButton25)
END_MESSAGE_MAP()


// CCameraControlDlg message handlers

BOOL CCameraControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	setupListener(_controller);
	setupObserver(getCameraModel());

	//Execute controller
	_controller->run();

	// A set value of the camera is acquired. 
	// The value to which the camera can be set is acquired. 
	
	return TRUE;   // return TRUE  unless you set the focus to a control
}


void CCameraControlDlg::setupListener(ActionListener* listener)
{
	addActionListener(listener);
	
	_comboAEMode.setActionCommand("set_AEMode");
	_comboAEMode.addActionListener(listener);
	_comboTv.setActionCommand("set_Tv");
	_comboTv.addActionListener(listener);
	_comboAv.setActionCommand("set_Av");
	_comboAv.addActionListener(listener);
	_comboIso.setActionCommand("set_ISOSpeed");
	_comboIso.addActionListener(listener);
	_comboMeteringMode.addActionListener(listener);
	_comboExposureComp.setActionCommand("set_ExposureCompensation");
	_comboExposureComp.addActionListener(listener);
	_comboImageQuality.setActionCommand("set_ImageQuality");
	_comboImageQuality.addActionListener(listener);
	_comboEvfAFMode.setActionCommand("set_EvfAFMode");
	_comboEvfAFMode.addActionListener(listener);

	_btnSend2Arduino.setActionCommand("Send2Arduino");
	_btnSend2Arduino.addActionListener(listener);


	//CActionButtons used only as ActionSource to trigger event from a CEdit component
	_btnMove2X.setActionCommand("Move2X");
	_btnMove2X.addActionListener(listener);

	_btnMove2Y.setActionCommand("Move2Y");
	_btnMove2Y.addActionListener(listener);

	_btnMove2B.setActionCommand("Move2B");
	_btnMove2B.addActionListener(listener);

	_btnMove2S.setActionCommand("Move2S");
	_btnMove2S.addActionListener(listener);


	//_btnAddRow.setActionCommand("AddRow");
	//_btnAddRow.addActionListener(listener);



	_btnTakePicture.setActionCommand("TakePicture");
	_btnTakePicture.addActionListener(listener);
	_btnStartEVF.setActionCommand("startEVF");
	_btnStartEVF.addActionListener(listener);
	_btnEndEVF.setActionCommand("endEVF");
	_btnEndEVF.addActionListener(listener);
	_btnFocusNear3.setActionCommand("focus_Near3");
	_btnFocusNear3.addActionListener(listener);
	_btnFocusNear2.setActionCommand("focus_Near2");
	_btnFocusNear2.addActionListener(listener);
	_btnFocusNear1.setActionCommand("focus_Near1");
	_btnFocusNear1.addActionListener(listener);
	_btnFocusFar3.setActionCommand("focus_Far3");
	_btnFocusFar3.addActionListener(listener);
	_btnFocusFar2.setActionCommand("focus_Far2");
	_btnFocusFar2.addActionListener(listener);
	_btnFocusFar1.setActionCommand("focus_Far1");
	_btnFocusFar1.addActionListener(listener);
	_btnFocusUp.setActionCommand("focus_Up");
	_btnFocusUp.addActionListener(listener);
	_btnFocusLeft.setActionCommand("focus_Left");
	_btnFocusLeft.addActionListener(listener);
	_btnFocusRight.setActionCommand("focus_Right");
	_btnFocusRight.addActionListener(listener);
	_btnFocusDown.setActionCommand("focus_Down");
	_btnFocusDown.addActionListener(listener);
	_btnZoomFit.setActionCommand("zoom_Fit");
	_btnZoomFit.addActionListener(listener);
	_btnZoomZoom.setActionCommand("zoom_Zoom");
	_btnZoomZoom.addActionListener(listener);
	_btnPressingHalfway.setActionCommand("pressingHalfway");
	_btnPressingHalfway.addActionListener(listener);
	_btnPressingCompletely.setActionCommand("pressingCompletely");
	_btnPressingCompletely.addActionListener(listener);
	_btnPressingOff.setActionCommand("pressingOff");
	_btnPressingOff.addActionListener(listener);
	_btnEvfAfON.setActionCommand("evfAFOn");
	_btnEvfAfON.addActionListener(listener);
	_btnEvfAfOFF.setActionCommand("evfAFOff");
	_btnEvfAfOFF.addActionListener(listener);

	_pictureBox.setActionCommand("downloadEVF");
	_pictureBox.addActionListener(listener);
}


void CCameraControlDlg::setupObserver(Observable* ob)
{
	ob->addObserver(static_cast<Observer*>(&_comboAEMode));
	ob->addObserver(static_cast<Observer*>(&_comboTv));
	ob->addObserver(static_cast<Observer*>(&_comboAv));
	ob->addObserver(static_cast<Observer*>(&_comboIso));
	ob->addObserver(static_cast<Observer*>(&_comboMeteringMode));
	ob->addObserver(static_cast<Observer*>(&_comboExposureComp));
	ob->addObserver(static_cast<Observer*>(&_comboImageQuality));
	ob->addObserver(static_cast<Observer*>(&_pictureBox));
	ob->addObserver(static_cast<Observer*>(&_comboEvfAFMode));
	ob->addObserver(static_cast<Observer*>(&_btnZoomZoom));

}

void CCameraControlDlg::OnClose()
{
	// TODO : The control notification handler code is added here or Predetermined processing is called. 
	fireEvent("closing");
	_btnSend2Arduino.EnableWindow(FALSE);
	_btnMove2X.EnableWindow(FALSE);
	_edit2.EnableWindow(FALSE);
	_edit3.EnableWindow(FALSE);

	_btnTakePicture.EnableWindow(FALSE);	
	_progress.EnableWindow(FALSE);
	_edit.EnableWindow(FALSE);
	_comboAEMode.EnableWindow(FALSE);
	_comboTv.EnableWindow(FALSE);
	_comboAv.EnableWindow(FALSE);
	_comboIso.EnableWindow(FALSE);	
	_comboImageQuality.EnableWindow(FALSE);	
	_btnPressingHalfway.EnableWindow(FALSE);	
	_btnPressingCompletely.EnableWindow(FALSE);	
	_btnPressingOff.EnableWindow(FALSE);	
	_comboEvfAFMode.EnableWindow(FALSE);	
	_btnEvfAfON.EnableWindow(FALSE);
	_btnEvfAfOFF.EnableWindow(FALSE);
	__super::OnClose();
}


void CCameraControlDlg::update(Observable* from, CameraEvent *e)
{
	std::string event = e->getEvent();

	//End of download of image
	if(event == "DownloadComplete")
	{
		//The update processing can be executed from another thread. 
		::PostMessage(this->m_hWnd, WM_USER_DOWNLOAD_COMPLETE, NULL, NULL);
	}

	//Progress of download of image
	if(event == "ProgressReport")
	{
		EdsInt32 percent = *static_cast<EdsInt32 *>(e->getArg());
		
		//The update processing can be executed from another thread. 
		::PostMessage(this->m_hWnd, WM_USER_PROGRESS_REPORT, percent, NULL);
	}

	//shutdown event
	if(event == "shutDown")
	{
		::PostMessage(this->m_hWnd, WM_CLOSE, 0, NULL);
	}

}


LRESULT CCameraControlDlg::OnDownloadComplete(WPARAM wParam, LPARAM lParam)
{
	//End of download of image
	_progress.SetPos(0);
	return 0;
}

LRESULT CCameraControlDlg::OnProgressReport(WPARAM wParam, LPARAM lParam)
{
	_progress.SetPos((int)wParam);
	return 0;
}



void CCameraControlDlg::OnBnClickedButton24()
{
	// TODO: Add your control notification handler code here

}


void CCameraControlDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCameraControlDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString text;
	_edit3.GetWindowText(text);

	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(text);
	_edit2.SetWindowTextA(text);

	//TODO:
	//If isValid update message
}


void CCameraControlDlg::OnOK()
{
	CString positionString;
	if (GetFocus() == &_edit3)
	{
		// TODO: Add your handling of the Return key here.
		TRACE0("Sending X command in calibration mode\n");
		//If ValidInput call Move2X
		CString text;
		_edit3.GetWindowText(text);
		
		// Convert a TCHAR string to a LPCSTR
		CT2CA pszConvertedAnsiString(text);
		// construct a std::string using the LPCSTR input
		std::string posDataString(pszConvertedAnsiString);

		std::string::size_type sz;   // alias of size_t
		int *posDataInt = new int;
		*posDataInt = std::stoi(posDataString, &sz);

		if (isValidMoveXInput(*posDataInt))
		{
			_btnMove2X.fireEvent(posDataInt);
		}
		delete posDataInt;
		// Call `return` to leave the dialog open.
		return;
	}

	else if (GetFocus() == &_edit_pos_Y_send)
	{
		TRACE0("Sending Y command in calibration mode\n");
		_edit_pos_Y_send.GetWindowText(positionString);
		int posDataInt = CString2Int(positionString);

		if (isValidMoveXInput(posDataInt))
		{

			_btnMove2Y.fireEvent(&posDataInt);
		}

		// Convert a TCHAR string to a LPCSTR
		CT2CA pszConvertedAnsiString(positionString);
		_edit_pos_Y_readonly.SetWindowTextA(positionString);
		

		return;
	}
	else if (GetFocus() == &_edit_pos_B_send)
	{
		_edit_pos_B_send.GetWindowText(positionString);
		int posDataInt = CString2Int(positionString);

		if (isValidMoveXInput(posDataInt))
		{
			_btnMove2B.fireEvent(&posDataInt);
		}

		// Convert a TCHAR string to a LPCSTR
		CT2CA pszConvertedAnsiString(positionString);
		_edit_pos_B_readonly.SetWindowTextA(positionString);

		return;
	}
	else if (GetFocus() == &_edit_pos_S_send)
	{
		_edit_pos_S_send.GetWindowText(positionString);
		int posDataInt = CString2Int(positionString);
		if (isValidMoveXInput(posDataInt))
		{
			_btnMove2S.fireEvent(&posDataInt);
		}

		// Convert a TCHAR string to a LPCSTR
		CT2CA pszConvertedAnsiString(positionString);
		_edit_pos_S_readonly.SetWindowTextA(positionString);

		return;
	}

	// Default behavior: Close the dialog.
	CDialog::OnOK();
}

bool CCameraControlDlg::isValidMoveXInput(int &data)
{
	return true;
}

void CCameraControlDlg::AddData(CListCtrl &ctrl, int row, int col, const char *str)

{

	LVITEM lv;

	lv.iItem = row;

	lv.iSubItem = col;

	lv.pszText = (LPSTR)str;

	lv.mask = LVIF_TEXT;
	//ctrl.InsertItem(&lv);
	if (col == 0)
	{
		ctrl.InsertItem(&lv);
	}
	else
	{
		ctrl.SetItem(&lv);
	}
}


void CCameraControlDlg::AddRow()
{
	int num_of_rows = _rowList.GetItemCount();
	int new_row_num = 0;
	
	if (num_of_rows != 0)
	{
		new_row_num = num_of_rows;
	}


	//Num Of Shots Data
	CString numOfShotsText;
	_edit4.GetWindowText(numOfShotsText);
	
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(numOfShotsText);
	// construct a std::string using the LPCSTR input
	std::string numOfShotsString(pszConvertedAnsiString);

	std::string::size_type sz;   // alias of size_t
	int numOfShots = std::stoi(numOfShotsString, &sz);

	AddData(_rowList, new_row_num, 0, numOfShotsText);




	//Tv Data
	CString TvData;
	//Read current camera settings
	int currShutterSpeed = _comboTv.GetCurSel();
	if (currShutterSpeed != LB_ERR)
	{
		_comboTv.GetLBText(currShutterSpeed, TvData);
	}
	//Print row
	AddData(_rowList, new_row_num, 1, TvData);


	//Av Data
	CString AvData;
	//Read current camera settings
	int currApperture = _comboAv.GetCurSel();
	if (currApperture != LB_ERR)
	{
		_comboAv.GetLBText(currApperture, AvData);
	}
	//Print row
	AddData(_rowList, new_row_num, 2, AvData);


	//ISO Data
	CString IsoData;
	//Read current camera settings
	int currIso = _comboIso.GetCurSel();
	if (currIso != LB_ERR)
	{
		_comboIso.GetLBText(currIso, IsoData);
	}
	//Print row
	AddData(_rowList, new_row_num, 3, IsoData);


	//Get X position
	CString xPositionString;
	_edit2.GetWindowText(xPositionString);

	//Get Y position
	CString yPositionString;
	_edit_pos_Y_readonly.GetWindowText(yPositionString);

	//Get B position
	CString bPositionString;
	_edit_pos_B_readonly.GetWindowText(bPositionString);

	//Get S position
	CString sPositionString;
	_edit_pos_S_readonly.GetWindowText(sPositionString);

	//Print row info x
	AddData(_rowList, new_row_num, 4, xPositionString);

	//Print row info y
	AddData(_rowList, new_row_num, 5, yPositionString);

	//Print row info b
	AddData(_rowList, new_row_num, 6, bPositionString);

	//Print row info s
	AddData(_rowList, new_row_num, 7, sPositionString);


	int xPositionInt = CString2Int(xPositionString);
	int yPositionInt = CString2Int(yPositionString);
	int bPositionInt = CString2Int(bPositionString);
	int sPositionInt = CString2Int(sPositionString);

	Shot *newShot = new Shot(
		_comboTv.GetItemData(currShutterSpeed), 
		_comboAv.GetItemData(currApperture),
		_comboIso.GetItemData(currIso),
		xPositionInt,
		yPositionInt,
		bPositionInt,
		sPositionInt
	
	);

	//Add Row data Scan Job
	scanJob.addRow(
		numOfShots, 
		_comboTv.GetItemData(currShutterSpeed),
		_comboAv.GetItemData(currApperture),
		_comboIso.GetItemData(currIso),
		xPositionInt,
		yPositionInt,
		bPositionInt,
		_controller
	);
	
	//FireEvent test

	//newShot->setupListener(_controller);
	//DWORD_PTR AvData_DWORD = _comboAv.GetItemData(currApperture +1);
	//newShot->fireEventAv(&AvData_DWORD);
}


void CCameraControlDlg::OnBnClickedButton23()
{
	// TODO: Add your control notification handler code here
	AddRow();
}


char* CCameraControlDlg::Int2CharPtr(int integer)
{
	stringstream cmd_stream_ptr;
	//Build command as stringstream
	cmd_stream_ptr << integer;

	//Convert to stringstream to string
	string tmp_string = cmd_stream_ptr.str();

	//Initiate cmd_string member variable
	char *char_string = new char[tmp_string.length()];

	// Copying the contents of tmp_string to char array cmd_string
	strcpy(char_string, tmp_string.c_str());

	return char_string;
}

int CCameraControlDlg::CString2Int(CString &string)
{
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(string);
	// construct a std::string using the LPCSTR input
	std::string posDataString(pszConvertedAnsiString);

	std::string::size_type sz;   // alias of size_t
	int dataInt =  std::stoi(posDataString, &sz);

	return dataInt;
}

void CCameraControlDlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCameraControlDlg::OnBnClickedButton25()
{
	//Start scan job
	scanJob.startJob();
}
