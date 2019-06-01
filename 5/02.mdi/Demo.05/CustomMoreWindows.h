// CustomMoreWindows.h : main header file for the CUSTOMMOREWINDOWS application
//

#if !defined(AFX_CUSTOMMOREWINDOWS_H__1E39FFE8_EC51_11D3_91A0_20314FC10000__INCLUDED_)
#define AFX_CUSTOMMOREWINDOWS_H__1E39FFE8_EC51_11D3_91A0_20314FC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsApp:
// See CustomMoreWindows.cpp for the implementation of this class
//

class CCustomMoreWindowsApp : public CWinApp
{
public:
	CCustomMoreWindowsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomMoreWindowsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCustomMoreWindowsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMMOREWINDOWS_H__1E39FFE8_EC51_11D3_91A0_20314FC10000__INCLUDED_)
