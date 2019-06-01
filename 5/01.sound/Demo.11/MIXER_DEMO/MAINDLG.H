//=============================================================================
// Copyright Langis Pitre 1998
// You may do whatever you want with this code, as long as you include this
// copyright notice in your implementation files.
//
// If you wish to add new classes to this collection, feel free to do so.
// But please send me your code so that I can update the collection.
//
// Comments and bug reports: lpitre@sympatico.ca
//
//=============================================================================
#if !defined(AFX_MAINDLG_H__B42E1C11_349E_11D2_A1BB_000000000000__INCLUDED_)
#define AFX_MAINDLG_H__B42E1C11_349E_11D2_A1BB_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SpeakerDlg.h"
#include "WaveDlg.h"
#include "VoiceDlg.h"

//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//
// This class implements the main dialog. It is an empty dialog resource
// template. CMainDlg can display three child windows selectable from menu
// commands. When a new child window is selected, the main dialog resizes to
// fit the child.
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
class CMainDlg : public CDialog
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
{
public:
	CMainDlg(CWnd* pParent = NULL); 
	
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_MAIN_DIALOG };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	HICON       m_hIcon;
	
	CSpeakerDlg spDlg;  // the 3 child dialog boxes 
	CWaveDlg    wvDlg;
	CVoiceDlg   vcDlg;

	void SetCurrentDialog( int nId );

	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInfo();
	afx_msg void OnInfoDlg();
	//}}AFX_MSG
	afx_msg void OnChangeDialog(UINT nID);
	afx_msg void OnUpdateMenu(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__B42E1C11_349E_11D2_A1BB_000000000000__INCLUDED_)
