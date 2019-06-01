// ListBoxExDemo.h : main header file for the LISTBOXEXDEMO application
//

#if !defined(AFX_LISTBOXEXDEMO_H__BF92D784_D35C_11D3_B5AC_A965B72AE035__INCLUDED_)
#define AFX_LISTBOXEXDEMO_H__BF92D784_D35C_11D3_B5AC_A965B72AE035__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListBoxExDemoApp:
// See ListBoxExDemo.cpp for the implementation of this class
//

class CListBoxExDemoApp : public CWinApp
{
public:
	CListBoxExDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxExDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListBoxExDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXEXDEMO_H__BF92D784_D35C_11D3_B5AC_A965B72AE035__INCLUDED_)
