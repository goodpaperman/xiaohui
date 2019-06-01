// TestBedSmartEdit.h : main header file for the TESTBEDSMARTEDIT application
//

#if !defined(AFX_TESTBEDSMARTEDIT_H__0B514386_CADB_11D3_BD1E_0060520365FB__INCLUDED_)
#define AFX_TESTBEDSMARTEDIT_H__0B514386_CADB_11D3_BD1E_0060520365FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestBedSmartEditApp:
// See TestBedSmartEdit.cpp for the implementation of this class
//

class CTestBedSmartEditApp : public CWinApp
{
public:
	CTestBedSmartEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBedSmartEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestBedSmartEditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBEDSMARTEDIT_H__0B514386_CADB_11D3_BD1E_0060520365FB__INCLUDED_)
