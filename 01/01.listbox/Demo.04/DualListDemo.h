// DualListDemo.h : main header file for the DUALLISTDEMO application
//
// MFC generated code: no changes necessary

#if !defined(AFX_DUALLISTDEMO_H__E6FFDCD4_DF3B_11D3_8664_0050DA15E05C__INCLUDED_)
#define AFX_DUALLISTDEMO_H__E6FFDCD4_DF3B_11D3_8664_0050DA15E05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoApp:
// See DualListDemo.cpp for the implementation of this class
//

class CDualListDemoApp : public CWinApp
{
public:
	CDualListDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDualListDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDualListDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUALLISTDEMO_H__E6FFDCD4_DF3B_11D3_8664_0050DA15E05C__INCLUDED_)
