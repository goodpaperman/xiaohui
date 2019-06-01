// WFDemo.h : main header file for the WFDEMO application
//

#if !defined(AFX_WFDEMO_H__284419A5_4050_11D4_AE95_00A024E8EE6B__INCLUDED_)
#define AFX_WFDEMO_H__284419A5_4050_11D4_AE95_00A024E8EE6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWFDemoApp:
// See WFDemo.cpp for the implementation of this class
//

class CWFDemoApp : public CWinApp
{
public:
	CWFDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWFDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWFDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WFDEMO_H__284419A5_4050_11D4_AE95_00A024E8EE6B__INCLUDED_)
