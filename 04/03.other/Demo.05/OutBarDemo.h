// OutBarDemo.h : main header file for the OUTBARDEMO application
//

#if !defined(AFX_OUTBARDEMO_H__28FA2C94_11B7_11D2_8437_0000B43382FE__INCLUDED_)
#define AFX_OUTBARDEMO_H__28FA2C94_11B7_11D2_8437_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COutBarDemoApp:
// See OutBarDemo.cpp for the implementation of this class
//

class COutBarDemoApp : public CWinApp
{
public:
	COutBarDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutBarDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COutBarDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTBARDEMO_H__28FA2C94_11B7_11D2_8437_0000B43382FE__INCLUDED_)
