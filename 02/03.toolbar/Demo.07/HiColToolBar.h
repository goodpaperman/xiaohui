// HiColToolBar.h : main header file for the HICOLTOOLBAR application
//

#if !defined(AFX_HICOLTOOLBAR_H__16F54463_1B11_11D2_BD39_00A0C945A10E__INCLUDED_)
#define AFX_HICOLTOOLBAR_H__16F54463_1B11_11D2_BD39_00A0C945A10E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarApp:
// See HiColToolBar.cpp for the implementation of this class
//

class CHiColToolBarApp : public CWinApp
{
public:
	CHiColToolBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHiColToolBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHiColToolBarApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HICOLTOOLBAR_H__16F54463_1B11_11D2_BD39_00A0C945A10E__INCLUDED_)
