// AutoCompletion.h : main header file for the AUTOCOMPLETION application
//

#if !defined(AFX_AUTOCOMPLETION_H__A2F51704_7F18_11D2_9B7D_006097F7F4CE__INCLUDED_)
#define AFX_AUTOCOMPLETION_H__A2F51704_7F18_11D2_9B7D_006097F7F4CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAutoCompletionApp:
// See AutoCompletion.cpp for the implementation of this class
//

class CAutoCompletionApp : public CWinApp
{
public:
	CAutoCompletionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoCompletionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAutoCompletionApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOCOMPLETION_H__A2F51704_7F18_11D2_9B7D_006097F7F4CE__INCLUDED_)
