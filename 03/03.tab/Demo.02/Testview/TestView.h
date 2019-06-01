// TestView.h : main header file for the TESTVIEW application
//

#if !defined(AFX_TESTVIEW_H__7705EEA5_947B_4472_B655_E26F2345AC00__INCLUDED_)
#define AFX_TESTVIEW_H__7705EEA5_947B_4472_B655_E26F2345AC00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestViewApp:
// See TestView.cpp for the implementation of this class
//

class CTestViewApp : public CWinApp
{
public:
	CTestViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__7705EEA5_947B_4472_B655_E26F2345AC00__INCLUDED_)
