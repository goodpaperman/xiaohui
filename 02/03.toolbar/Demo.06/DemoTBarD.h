// DemoTBarD.h : main header file for the DEMOTBARD application
//

#if !defined(AFX_DEMOTBARD_H__DA7A8A04_9921_11D2_ABA4_B4FFFFC00000__INCLUDED_)
#define AFX_DEMOTBARD_H__DA7A8A04_9921_11D2_ABA4_B4FFFFC00000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDApp:
// See DemoTBarD.cpp for the implementation of this class
//

class CDemoTBarDApp : public CWinApp
{
public:
	CDemoTBarDApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoTBarDApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDemoTBarDApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOTBARD_H__DA7A8A04_9921_11D2_ABA4_B4FFFFC00000__INCLUDED_)
