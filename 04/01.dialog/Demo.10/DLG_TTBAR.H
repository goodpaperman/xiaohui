// dlg_ttbar.h : main header file for the DLG_TTBAR application
//

#if !defined(AFX_DLG_TTBAR_H__B7115764_5231_11D2_B126_0060082FF473__INCLUDED_)
#define AFX_DLG_TTBAR_H__B7115764_5231_11D2_B126_0060082FF473__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlg_ttbarApp:
// See dlg_ttbar.cpp for the implementation of this class
//

class CDlg_ttbarApp : public CWinApp
{
public:
	CDlg_ttbarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_ttbarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlg_ttbarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_TTBAR_H__B7115764_5231_11D2_B126_0060082FF473__INCLUDED_)
