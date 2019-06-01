// MySphereButton.h : main header file for the MYSPHEREBUTTON application
//

#if !defined(AFX_MYSPHEREBUTTON_H__44648A94_9ABA_11D2_9E44_0020182F735A__INCLUDED_)
#define AFX_MYSPHEREBUTTON_H__44648A94_9ABA_11D2_9E44_0020182F735A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMySphereButtonApp:
// See MySphereButton.cpp for the implementation of this class
//

class CMySphereButtonApp : public CWinApp
{
public:
	CMySphereButtonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySphereButtonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMySphereButtonApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPHEREBUTTON_H__44648A94_9ABA_11D2_9E44_0020182F735A__INCLUDED_)
