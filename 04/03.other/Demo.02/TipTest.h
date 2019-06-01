// TipTest.h : main header file for the TIPTEST application
//

#if !defined(AFX_TIPTEST_H__90D7DC02_EF5E_4E6B_9B67_8BFD34E8187F__INCLUDED_)
#define AFX_TIPTEST_H__90D7DC02_EF5E_4E6B_9B67_8BFD34E8187F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTipTestApp:
// See TipTest.cpp for the implementation of this class
//

class CTipTestApp : public CWinApp
{
public:
	CTipTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTipTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPTEST_H__90D7DC02_EF5E_4E6B_9B67_8BFD34E8187F__INCLUDED_)
