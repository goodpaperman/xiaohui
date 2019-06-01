// IconCombo.h : main header file for the ICONCOMBO application
//

#if !defined(AFX_ICONCOMBO_H__68AC5110_3600_4EB4_A31E_D688AC3F7218__INCLUDED_)
#define AFX_ICONCOMBO_H__68AC5110_3600_4EB4_A31E_D688AC3F7218__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIconComboApp:
// See IconCombo.cpp for the implementation of this class
//

class CIconComboApp : public CWinApp
{
public:
	CIconComboApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconComboApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIconComboApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONCOMBO_H__68AC5110_3600_4EB4_A31E_D688AC3F7218__INCLUDED_)
