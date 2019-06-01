// myothello.h : main header file for the MYOTHELLO application
//

#if !defined(AFX_MYOTHELLO_H__47761D05_F48E_4DDD_B68C_23E74E4960D5__INCLUDED_)
#define AFX_MYOTHELLO_H__47761D05_F48E_4DDD_B68C_23E74E4960D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyothelloApp:
// See myothello.cpp for the implementation of this class
//

class CMyothelloApp : public CWinApp
{
public:
	CMyothelloApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyothelloApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyothelloApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYOTHELLO_H__47761D05_F48E_4DDD_B68C_23E74E4960D5__INCLUDED_)
