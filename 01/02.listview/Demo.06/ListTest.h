// ListTest.h : main header file for the LISTTEST application
//

#if !defined(AFX_LISTTEST_H__D0BD95E0_D338_4BFF_B4FF_7B62C1F6BB67__INCLUDED_)
#define AFX_LISTTEST_H__D0BD95E0_D338_4BFF_B4FF_7B62C1F6BB67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListTestApp:
// See ListTest.cpp for the implementation of this class
//

class CListTestApp : public CWinApp
{
public:
	CListTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTTEST_H__D0BD95E0_D338_4BFF_B4FF_7B62C1F6BB67__INCLUDED_)
