// BCGIEDemo.h : main header file for the BCGIEDEMO application
//

#if !defined(AFX_BCGIEDEMO_H__F83C8E0B_F33E_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_BCGIEDEMO_H__F83C8E0B_F33E_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define REGISTRY_ROOT	/*_T("CUSTOM STATE\\") */_T("SOFTWARE\\MY COMAPNY\\BCGIEDemo\\");

/////////////////////////////////////////////////////////////////////////////
// CBCGIEDemoApp:
// See BCGIEDemo.cpp for the implementation of this class
//

class CBCGIEDemoApp : public CWinApp
{
public:
	CBCGIEDemoApp();


	void LoadCustomState ();
	void SaveCustomState ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGIEDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGIEDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBCGKeyboardManager		m_KeyboardManager;
};


extern CBCGIEDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGIEDEMO_H__F83C8E0B_F33E_11D2_A713_0090274409AC__INCLUDED_)
