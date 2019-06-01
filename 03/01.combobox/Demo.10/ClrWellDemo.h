// ClrWellDemo.h : main header file for the CLRWELLDEMO application
//

#if !defined(AFX_CLRWELLDEMO_H__D13C6687_9EED_11D2_8DF1_00104B2A8A87__INCLUDED_)
#define AFX_CLRWELLDEMO_H__D13C6687_9EED_11D2_8DF1_00104B2A8A87__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClrWellDemoApp:
// See ClrWellDemo.cpp for the implementation of this class
//

class CClrWellDemoApp : public CWinApp
{
public:
	CClrWellDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClrWellDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClrWellDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLRWELLDEMO_H__D13C6687_9EED_11D2_8DF1_00104B2A8A87__INCLUDED_)
