// TabDialogDemo.h : main header file for the TABDIALOGDEMO application
//

#if !defined(AFX_TABDIALOGDEMO_H__02A8BC76_DA1A_11D3_83D4_00105ABE120C__INCLUDED_)
#define AFX_TABDIALOGDEMO_H__02A8BC76_DA1A_11D3_83D4_00105ABE120C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTabDialogDemoApp:
// See TabDialogDemo.cpp for the implementation of this class
//

class CTabDialogDemoApp : public CWinApp
{
public:
	CTabDialogDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDialogDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTabDialogDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDIALOGDEMO_H__02A8BC76_DA1A_11D3_83D4_00105ABE120C__INCLUDED_)
