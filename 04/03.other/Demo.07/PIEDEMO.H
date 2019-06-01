// PieDemo.h : main header file for the PIEDEMO application
//

#if !defined(AFX_PIEDEMO_H__C0A9AE24_30C2_11D2_813C_F042F77F7401__INCLUDED_)
#define AFX_PIEDEMO_H__C0A9AE24_30C2_11D2_813C_F042F77F7401__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPieDemoApp:
// See PieDemo.cpp for the implementation of this class
//

class CPieDemoApp : public CWinApp
{
public:
	CPieDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPieDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPieDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIEDEMO_H__C0A9AE24_30C2_11D2_813C_F042F77F7401__INCLUDED_)
