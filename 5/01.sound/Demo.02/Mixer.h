// Mixer.h : main header file for the MIXER application
//

#if !defined(AFX_MIXER_H__EE4AE93E_082D_4A52_8C8E_1B569BFAE00A__INCLUDED_)
#define AFX_MIXER_H__EE4AE93E_082D_4A52_8C8E_1B569BFAE00A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMixerApp:
// See Mixer.cpp for the implementation of this class
//

class CMixerApp : public CWinApp
{
public:
	CMixerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMixerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMixerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIXER_H__EE4AE93E_082D_4A52_8C8E_1B569BFAE00A__INCLUDED_)
