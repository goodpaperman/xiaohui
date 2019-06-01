// ColorLBTest.h : main header file for the COLORLBTEST application
//

#if !defined(AFX_COLORLBTEST_H__766FAF67_5731_11D3_90AF_0020AFBC499D__INCLUDED_)
#define AFX_COLORLBTEST_H__766FAF67_5731_11D3_90AF_0020AFBC499D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CColorLBTestApp:
// See ColorLBTest.cpp for the implementation of this class
//

class CColorLBTestApp : public CWinApp
{
public:
	CColorLBTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorLBTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CColorLBTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLBTEST_H__766FAF67_5731_11D3_90AF_0020AFBC499D__INCLUDED_)
