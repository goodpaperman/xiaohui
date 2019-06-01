// clearmine.h : main header file for the CLEARMINE application
//

#if !defined(AFX_CLEARMINE_H__BB20D5D4_19E6_11D5_86D8_0000F74D8D41__INCLUDED_)
#define AFX_CLEARMINE_H__BB20D5D4_19E6_11D5_86D8_0000F74D8D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClearmineApp:
// See clearmine.cpp for the implementation of this class
//

class CClearmineApp : public CWinApp
{
public:
	CClearmineApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClearmineApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CClearmineApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLEARMINE_H__BB20D5D4_19E6_11D5_86D8_0000F74D8D41__INCLUDED_)
