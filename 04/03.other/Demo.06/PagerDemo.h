// PagerDemo.h : main header file for the PAGERDEMO application
//

#if !defined(AFX_PAGERDEMO_H__F07F0308_61EC_11D2_9582_0040053E0F5B__INCLUDED_)
#define AFX_PAGERDEMO_H__F07F0308_61EC_11D2_9582_0040053E0F5B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPagerDemoApp:
// See PagerDemo.cpp for the implementation of this class
//

class CPagerDemoApp : public CWinApp
{
public:
	CPagerDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPagerDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPagerDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGERDEMO_H__F07F0308_61EC_11D2_9582_0040053E0F5B__INCLUDED_)
