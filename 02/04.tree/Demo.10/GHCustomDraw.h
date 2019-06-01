// GHCustomDraw.h : main header file for the GHCUSTOMDRAW application
//

#if !defined(AFX_GHCUSTOMDRAW_H__B510B4A5_CA7C_11D2_80FF_00104B346232__INCLUDED_)
#define AFX_GHCUSTOMDRAW_H__B510B4A5_CA7C_11D2_80FF_00104B346232__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawApp:
// See GHCustomDraw.cpp for the implementation of this class
//

class CGHCustomDrawApp : public CWinApp
{
public:
	CGHCustomDrawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGHCustomDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGHCustomDrawApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GHCUSTOMDRAW_H__B510B4A5_CA7C_11D2_80FF_00104B346232__INCLUDED_)
