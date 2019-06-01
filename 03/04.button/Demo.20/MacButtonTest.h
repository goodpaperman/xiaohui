// MacButtonTest.h : main header file for the MACBUTTONTEST application
//

#if !defined(AFX_MACBUTTONTEST_H__994F45CB_C9CC_11D3_910F_0020AFBC499D__INCLUDED_)
#define AFX_MACBUTTONTEST_H__994F45CB_C9CC_11D3_910F_0020AFBC499D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMacButtonTestApp:
// See MacButtonTest.cpp for the implementation of this class
//

class CMacButtonTestApp : public CWinApp
{
public:
	CMacButtonTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMacButtonTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMacButtonTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACBUTTONTEST_H__994F45CB_C9CC_11D3_910F_0020AFBC499D__INCLUDED_)
