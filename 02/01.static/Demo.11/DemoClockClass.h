// DemoClockClass.h : main header file for the DEMOCLOCKCLASS application
//

#if !defined(AFX_DEMOCLOCKCLASS_H__7217CB64_979D_11D3_A77C_00105AA7390A__INCLUDED_)
#define AFX_DEMOCLOCKCLASS_H__7217CB64_979D_11D3_A77C_00105AA7390A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoClockClassApp:
// See DemoClockClass.cpp for the implementation of this class
//

class CDemoClockClassApp : public CWinApp
{
public:
	CDemoClockClassApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoClockClassApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemoClockClassApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOCLOCKCLASS_H__7217CB64_979D_11D3_A77C_00105AA7390A__INCLUDED_)
