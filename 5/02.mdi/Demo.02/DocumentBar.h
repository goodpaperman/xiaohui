// DocumentBar.h : main header file for the DOCUMENTBAR application
//

#if !defined(AFX_DOCUMENTBAR_H__822331A8_F2C5_11D3_91A0_303D4FC10000__INCLUDED_)
#define AFX_DOCUMENTBAR_H__822331A8_F2C5_11D3_91A0_303D4FC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarApp:
// See DocumentBar.cpp for the implementation of this class
//

class CDocumentBarApp : public CWinApp
{
public:
	CDocumentBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocumentBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDocumentBarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCUMENTBAR_H__822331A8_F2C5_11D3_91A0_303D4FC10000__INCLUDED_)
