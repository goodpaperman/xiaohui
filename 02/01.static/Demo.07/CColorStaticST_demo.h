// CColorStaticST_demo.h : main header file for the CCOLORSTATICST_DEMO application
//

#if !defined(AFX_CCOLORSTATICST_DEMO_H__D2E6DD12_7FCF_11D2_A1E0_00805F8593B2__INCLUDED_)
#define AFX_CCOLORSTATICST_DEMO_H__D2E6DD12_7FCF_11D2_A1E0_00805F8593B2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCColorStaticST_demoApp:
// See CColorStaticST_demo.cpp for the implementation of this class
//

class CCColorStaticST_demoApp : public CWinApp
{
public:
	CCColorStaticST_demoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCColorStaticST_demoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCColorStaticST_demoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCOLORSTATICST_DEMO_H__D2E6DD12_7FCF_11D2_A1E0_00805F8593B2__INCLUDED_)
