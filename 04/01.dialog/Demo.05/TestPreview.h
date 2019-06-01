// TestPreview.h : main header file for the TESTPREVIEW application
//

#if !defined(AFX_TESTPREVIEW_H__D9C030C4_12DD_11D3_915F_FDE9AD318528__INCLUDED_)
#define AFX_TESTPREVIEW_H__D9C030C4_12DD_11D3_915F_FDE9AD318528__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewApp:
// See TestPreview.cpp for the implementation of this class
//

class CTestPreviewApp : public CWinApp
{
public:
	CTestPreviewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPreviewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestPreviewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPREVIEW_H__D9C030C4_12DD_11D3_915F_FDE9AD318528__INCLUDED_)
