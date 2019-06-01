// TLView.h : main header file for the TLVIEW application
//

#if !defined(AFX_TLVIEW_H__3C29E709_4823_11D2_980D_004095E0DEFA__INCLUDED_)
#define AFX_TLVIEW_H__3C29E709_4823_11D2_980D_004095E0DEFA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTLViewApp:
// See TLView.cpp for the implementation of this class
//

class CTLViewApp : public CWinApp
{
public:
	CTLViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTLViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTLViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TLVIEW_H__3C29E709_4823_11D2_980D_004095E0DEFA__INCLUDED_)
