// TestWizard.h : main header file for the TESTWIZARD application
//

#if !defined(AFX_TESTWIZARD_H__D4575997_172F_4BAC_98F5_ABAEB433D976__INCLUDED_)
#define AFX_TESTWIZARD_H__D4575997_172F_4BAC_98F5_ABAEB433D976__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestWizardApp:
// See TestWizard.cpp for the implementation of this class
//

class CTestWizardApp : public CWinApp
{
public:
	CTestWizardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestWizardApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestWizardApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTWIZARD_H__D4575997_172F_4BAC_98F5_ABAEB433D976__INCLUDED_)
