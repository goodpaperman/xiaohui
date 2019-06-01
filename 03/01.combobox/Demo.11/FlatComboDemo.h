// FlatComboDemo.h : main header file for the FLATCOMBODEMO application
//

#if !defined(AFX_FLATCOMBODEMO_H__E5237FC4_2921_11D3_8730_000000000000__INCLUDED_)
#define AFX_FLATCOMBODEMO_H__E5237FC4_2921_11D3_8730_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlatComboDemoApp:
// See FlatComboDemo.cpp for the implementation of this class
//

class CFlatComboDemoApp : public CWinApp
{
public:
	CFlatComboDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatComboDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFlatComboDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATCOMBODEMO_H__E5237FC4_2921_11D3_8730_000000000000__INCLUDED_)
