// AVCDemo.h : main header file for the AVCDEMO application
//

#if !defined(AFX_AVCDEMO_H__5E9B7CF4_5997_11D3_AE18_000000000000__INCLUDED_)
#define AFX_AVCDEMO_H__5E9B7CF4_5997_11D3_AE18_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAVCDemoApp:
// See AVCDemo.cpp for the implementation of this class
//

class CAVCDemoApp : public CWinApp
{
public:
	CAVCDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVCDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAVCDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVCDEMO_H__5E9B7CF4_5997_11D3_AE18_000000000000__INCLUDED_)
