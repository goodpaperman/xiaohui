// SwitchTB.h : main header file for the SWITCHTB application
//

#if !defined(AFX_SWITCHTB_H__22E84077_DBB1_11D2_9145_0060082BE95D__INCLUDED_)
#define AFX_SWITCHTB_H__22E84077_DBB1_11D2_9145_0060082BE95D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBApp:
// See SwitchTB.cpp for the implementation of this class
//

BOOL IsWindow (CWnd *pWnd);

template <class T>
int FindInArray (const CArray<T,T> &array, const T &t)
{
	int n;

	for (n=0 ; n < array.GetSize () ; n++)
		if (t == array.GetAt (n))
			return (n);
	return (-1);
}

class CSwitchTBApp : public CWinApp
{
public:
	CSwitchTBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchTBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSwitchTBApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHTB_H__22E84077_DBB1_11D2_9145_0060082BE95D__INCLUDED_)
