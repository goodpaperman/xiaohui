// Example.h : main header file for the EXAMPLE application
//

#if !defined(AFX_EXAMPLE_H__73B46E67_01FB_11D3_8647_00105AC69564__INCLUDED_)
#define AFX_EXAMPLE_H__73B46E67_01FB_11D3_8647_00105AC69564__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExampleApp:
// See Example.cpp for the implementation of this class
//

class CExampleApp : public CWinApp
{
public:
	CExampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE_H__73B46E67_01FB_11D3_8647_00105AC69564__INCLUDED_)
