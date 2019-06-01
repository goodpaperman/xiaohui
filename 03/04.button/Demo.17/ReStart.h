// ReStart.h : main header file for the RESTART application
//

#if !defined(AFX_RESTART_H__4A734418_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)
#define AFX_RESTART_H__4A734418_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CReStartApp:
// See ReStart.cpp for the implementation of this class
//

class CReStartApp : public CWinApp
{
public:
	CReStartApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReStartApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CReStartApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESTART_H__4A734418_EB5C_11D3_B07D_0050DAB826FF__INCLUDED_)
