// JumpyText.h : main header file for the JUMPYTEXT application
//

#if !defined(AFX_JUMPYTEXT_H__E1E3B9A7_5E9C_11D3_A785_0000214D19D7__INCLUDED_)
#define AFX_JUMPYTEXT_H__E1E3B9A7_5E9C_11D3_A785_0000214D19D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJumpyTextApp:
// See JumpyText.cpp for the implementation of this class
//

class CJumpyTextApp : public CWinApp
{
public:
	CJumpyTextApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJumpyTextApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJumpyTextApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUMPYTEXT_H__E1E3B9A7_5E9C_11D3_A785_0000214D19D7__INCLUDED_)
