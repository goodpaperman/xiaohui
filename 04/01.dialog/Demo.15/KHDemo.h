// KHDemo.h : main header file for the KHDEMO application
//

#if !defined(AFX_KHDEMO_H__546F2503_6E43_11D2_B9A8_00104B138C8C__INCLUDED_)
#define AFX_KHDEMO_H__546F2503_6E43_11D2_B9A8_00104B138C8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKHDemoApp:
// See KHDemo.cpp for the implementation of this class
//

class CKHDemoApp : public CWinApp
{
public:
	CKHDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKHDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKHDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KHDEMO_H__546F2503_6E43_11D2_B9A8_00104B138C8C__INCLUDED_)
