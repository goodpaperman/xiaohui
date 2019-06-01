// TwoPanes.h : main header file for the TWOPANES application
//

#if !defined(AFX_TWOPANES_H__4CCAE7F7_B491_11D3_9CE3_E7C9978DB001__INCLUDED_)
#define AFX_TWOPANES_H__4CCAE7F7_B491_11D3_9CE3_E7C9978DB001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

extern const bool g_bIsWindows98orLater;

extern HANDLE g_hEventClosed;

/////////////////////////////////////////////////////////////////////////////
// CTwoPanesApp:
// See TwoPanes.cpp for the implementation of this class
//

class CTwoPanesApp : public CWinApp
{
public:
	CTwoPanesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTwoPanesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CTwoPanesApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TWOPANES_H__4CCAE7F7_B491_11D3_9CE3_E7C9978DB001__INCLUDED_)
