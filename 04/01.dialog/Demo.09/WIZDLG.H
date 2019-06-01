// WizDlg.h : main header file for the WIZDLG application
//

#if !defined(AFX_WIZDLG_H__5C87DCC4_0E81_11D2_8427_0000B43382FE__INCLUDED_)
#define AFX_WIZDLG_H__5C87DCC4_0E81_11D2_8427_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWizDlgApp:
// See WizDlg.cpp for the implementation of this class
//

class CWizDlgApp : public CWinApp
{
public:
	CWizDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWizDlgApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZDLG_H__5C87DCC4_0E81_11D2_8427_0000B43382FE__INCLUDED_)
