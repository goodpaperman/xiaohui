// snd.h : main header file for the SND application
//

#if !defined(AFX_SND_H__2AAD2285_7424_11D2_8045_540610C10374__INCLUDED_)
#define AFX_SND_H__2AAD2285_7424_11D2_8045_540610C10374__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSndApp:
// See snd.cpp for the implementation of this class
//

class CSndApp : public CWinApp
{
public:
	CSndApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSndApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSndApp)
	afx_msg void OnAppAbout();
	afx_msg void OnSoundOutStart();
	afx_msg void OnSoundInStop();
	afx_msg void OnSoundInStart();
	afx_msg void OnSoundOutStop();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SND_H__2AAD2285_7424_11D2_8045_540610C10374__INCLUDED_)
