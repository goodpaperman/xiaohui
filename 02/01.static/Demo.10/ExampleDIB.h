// ExampleDIB.h : main header file for the EXAMPLEDIB application
//

#if !defined(AFX_EXAMPLEDIB_H__A69F7E04_69CD_11D3_9AB9_0008C7728E19__INCLUDED_)
#define AFX_EXAMPLEDIB_H__A69F7E04_69CD_11D3_9AB9_0008C7728E19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExampleDIBApp:
// See ExampleDIB.cpp for the implementation of this class
//

class CExampleDIBApp : public CWinApp
{
public:
	CExampleDIBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleDIBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExampleDIBApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLEDIB_H__A69F7E04_69CD_11D3_9AB9_0008C7728E19__INCLUDED_)
