// GfxList.h : main header file for the GFXLIST application
//

#if !defined(AFX_GFXLIST_H__C8BADFC4_051E_11D2_83EF_0000B43382FE__INCLUDED_)
#define AFX_GFXLIST_H__C8BADFC4_051E_11D2_83EF_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGfxListApp:
// See GfxList.cpp for the implementation of this class
//

class CGfxListApp : public CWinApp
{
public:
	CGfxListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGfxListApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXLIST_H__C8BADFC4_051E_11D2_83EF_0000B43382FE__INCLUDED_)
