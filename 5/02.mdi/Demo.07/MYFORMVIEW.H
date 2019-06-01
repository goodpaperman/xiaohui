// MyFormView.h : main header file for the MYFORMVIEW application
//

#if !defined(AFX_MYFORMVIEW_H__F9BB0CC4_3D20_11D2_BC46_0060970A2B51__INCLUDED_)
#define AFX_MYFORMVIEW_H__F9BB0CC4_3D20_11D2_BC46_0060970A2B51__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyFormViewApp:
// See MyFormView.cpp for the implementation of this class
//

class CMyFormViewApp : public CWinApp
{
public:
	CMyFormViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFormViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyFormViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFORMVIEW_H__F9BB0CC4_3D20_11D2_BC46_0060970A2B51__INCLUDED_)
