// Mute.h : main header file for the MUTE application
//

#if !defined(AFX_MUTE_H__39694505_F4A0_11D1_9F80_006008984DF6__INCLUDED_)
#define AFX_MUTE_H__39694505_F4A0_11D1_9F80_006008984DF6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMuteApp:
// See Mute.cpp for the implementation of this class
//

class CMuteApp : public CWinApp
{
public:
	CMuteApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMuteApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMuteApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUTE_H__39694505_F4A0_11D1_9F80_006008984DF6__INCLUDED_)
