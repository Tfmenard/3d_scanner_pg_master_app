/******************************************************************************
*                                                                             *
*   PROJECT : EOS Digital Software Development Kit EDSDK                      *
*      NAME : CameraControlDlg.h                                              *
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

#pragma once

#include <map>
#include "Observer.h"

#include "CameraController.h"



#include "AEMode.h"
#include "Tv.h"
#include "Av.h"
#include "Iso.h"
#include "MeteringMode.h"
#include "ExposureComp.h"
#include "ImageQuality.h"
#include "EVFPictureBox.h"
#include "EvfAFMode.h"

#include "ActionButton.h"
#include "EvfZoomButton.h"

#include "ActionListener.h"
#include "ActionEvent.h"

#include "RowDlg.h"
#include "ScanJob.h"


// CCameraControlDlg Dialog
class CCameraControlDlg : public CDialog, public ActionSource, public Observer
{
	
// Construction
private:
	void setupListener(ActionListener* listener);
	void setupObserver(Observable* ob);
	void changeEnableWindow();

public:
	CCameraControlDlg(CWnd* pParent = NULL);	// standard constructor
	void setCameraController(CameraController* controller){_controller = controller;}
	bool isValidMoveXInput(int &data);
	void AddData(CListCtrl &ctrl, int row, int col, const char *str);
	void AddRow();
	char* Int2CharPtr(int integer);
	int CString2Int(CString &string);


public:
	// Observer 
	virtual void update(Observable* from, CameraEvent *e);

	//Dialog data
	enum { IDD = IDD_CAMERACONTROL_DIALOG };
	
	CActionButton	_btnMove2X;
	CActionButton	_btnSend2Arduino;
	CButton	_btnAddRow;
	CActionButton	_btnPopulateNewRow;
	CButton	_startJob;

	ScanJob scanJob;

	CActionButton	_btnTakePicture;
	CActionButton	_btnStartEVF;
	CActionButton	_btnEndEVF;
	CActionButton	_btnFocusNear3;
	CActionButton	_btnFocusNear2;
	CActionButton	_btnFocusNear1;
	CActionButton	_btnFocusFar3;
	CActionButton	_btnFocusFar2;
	CActionButton	_btnFocusFar1;
	CActionButton	_btnFocusUp;
	CActionButton	_btnFocusDown;
	CActionButton	_btnFocusLeft;
	CActionButton	_btnFocusRight;
	CActionButton	_btnZoomFit;
	CEvfZoomButton	_btnZoomZoom;
	CProgressCtrl	_progress;
	CEdit			_edit;

	CEdit			_edit2;
	CEdit			_edit3;
	CEdit			_edit4;

	CListCtrl		_rowList;

	CEVFPictureBox	_pictureBox;
	CAEMode			_comboAEMode;
	CTv				_comboTv;
	CAv				_comboAv;
	CIso			_comboIso;
	CMeteringMode	_comboMeteringMode;
	CExposureComp	_comboExposureComp;
	CImageQuality	_comboImageQuality;
	CActionButton	_btnPressingHalfway;
	CActionButton	_btnPressingCompletely;
	CActionButton	_btnPressingOff;
	CEvfAFMode		_comboEvfAFMode;
	CActionButton	_btnEvfAfON;
	CActionButton	_btnEvfAfOFF;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnDownloadComplete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProgressReport(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnOK();

protected:
	CameraController* _controller;

	RowDlg* _rowDlg;

public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton25();
};
