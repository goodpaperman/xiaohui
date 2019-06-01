// CustToolBarTest.h : main header file for the CUSTTOOLBARTEST application
//

#if !defined(AFX_CUSTTOOLBARTEST_H__761D39DC_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
#define AFX_CUSTTOOLBARTEST_H__761D39DC_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "BCGContextMenuManager.h"
#include "BCGMouseManager.h"
#include "BCGKeyboardManager.h"

#define REGISTRY_ROOT	_T("SOFTWARE\\MY COMAPNY\\CustToolbarTest\\")

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestApp:
// See CustToolBarTest.cpp for the implementation of this class
//
const int iIdTestView	= 1;
//const int iIdTest2View	= 2;

class CCustToolBarTestApp : public CWinApp
{
public:
	CCustToolBarTestApp();

// Operations
	BOOL ShowPopupMenu (UINT uiMenuResId, const CPoint& point, CWnd* pWnd);
	BOOL OnViewDoubleClick (int iViewId);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustToolBarTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCustToolBarTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//--------------------------------
	// Customizable features managers:
	//--------------------------------
	CBCGContextMenuManager	m_ContextMenuManager;
	CBCGMouseManager		m_MouseManager;
	CBCGKeyboardManager		m_KeyboardManager;
};

extern CCustToolBarTestApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTTOOLBARTEST_H__761D39DC_CFDF_11D1_A648_00A0C93A70EC__INCLUDED_)
