// GreyEditTest.h : main header file for the GREYEDITTEST application
//

#if !defined(AFX_GREYEDITTEST_H__CB8BEE73_AC6B_4A23_8255_1CC97A16D6C3__INCLUDED_)
#define AFX_GREYEDITTEST_H__CB8BEE73_AC6B_4A23_8255_1CC97A16D6C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGreyEditTestApp:
// See GreyEditTest.cpp for the implementation of this class
//

class CGreyEditTestApp : public CWinApp
{
public:
	CGreyEditTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGreyEditTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGreyEditTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GREYEDITTEST_H__CB8BEE73_AC6B_4A23_8255_1CC97A16D6C3__INCLUDED_)
