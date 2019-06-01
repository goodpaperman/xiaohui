// SeparatorDemo.h : main header file for the SEPARATORDEMO application
//

#if !defined(AFX_SEPARATORDEMO_H__D41D6FA4_6F88_11D2_9506_A0C64BC100C2__INCLUDED_)
#define AFX_SEPARATORDEMO_H__D41D6FA4_6F88_11D2_9506_A0C64BC100C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSeparatorDemoApp:
// See SeparatorDemo.cpp for the implementation of this class
//

class CSeparatorDemoApp : public CWinApp
{
public:
	CSeparatorDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeparatorDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSeparatorDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEPARATORDEMO_H__D41D6FA4_6F88_11D2_9506_A0C64BC100C2__INCLUDED_)
