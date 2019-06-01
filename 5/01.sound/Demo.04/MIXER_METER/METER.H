// Meter.h : main header file for the METER application
//

#if !defined(AFX_METER_H__3A48D835_F4B7_11D1_9F80_006008984DF6__INCLUDED_)
#define AFX_METER_H__3A48D835_F4B7_11D1_9F80_006008984DF6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMeterApp:
// See Meter.cpp for the implementation of this class
//

class CMeterApp : public CWinApp
{
public:
	CMeterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMeterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METER_H__3A48D835_F4B7_11D1_9F80_006008984DF6__INCLUDED_)
