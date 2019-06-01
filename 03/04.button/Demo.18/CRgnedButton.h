// CRgnedButton.h : main header file for the CRGNEDBUTTON application
//

#if !defined(AFX_CRGNEDBUTTON_H__A60F9869_1365_11D3_A817_0090271A0C11__INCLUDED_)
#define AFX_CRGNEDBUTTON_H__A60F9869_1365_11D3_A817_0090271A0C11__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCRgnedButtonApp:
// See CRgnedButton.cpp for the implementation of this class
//

class CCRgnedButtonApp : public CWinApp
{
public:
	CCRgnedButtonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCRgnedButtonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCRgnedButtonApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRGNEDBUTTON_H__A60F9869_1365_11D3_A817_0090271A0C11__INCLUDED_)
