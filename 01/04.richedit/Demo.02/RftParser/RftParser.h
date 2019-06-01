// RftParser.h : main header file for the RFTPARSER application
//

#if !defined(AFX_RFTPARSER_H__6975176B_FFE6_449D_B22C_440C8097F6FB__INCLUDED_)
#define AFX_RFTPARSER_H__6975176B_FFE6_449D_B22C_440C8097F6FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRftParserApp:
// See RftParser.cpp for the implementation of this class
//

class CRftParserApp : public CWinApp
{
public:
	CRftParserApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRftParserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRftParserApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RFTPARSER_H__6975176B_FFE6_449D_B22C_440C8097F6FB__INCLUDED_)
