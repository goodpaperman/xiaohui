// counter.h : main header file for the COUNTER application
//

#if !defined(AFX_COUNTER_H__C012E026_AB9E_11D1_A717_AC9DD64C3607__INCLUDED_)
#define AFX_COUNTER_H__C012E026_AB9E_11D1_A717_AC9DD64C3607__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCounterApp:
// See counter.cpp for the implementation of this class
//

class CCounterApp : public CWinApp
{
public:
	CCounterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCounterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCounterApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTER_H__C012E026_AB9E_11D1_A717_AC9DD64C3607__INCLUDED_)
