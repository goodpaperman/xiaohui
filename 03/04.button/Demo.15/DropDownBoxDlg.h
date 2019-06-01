// DropDownBoxDlg.h : main header file for the DROPDOWNBOXDLG application
//

#if !defined(AFX_DROPDOWNBOXDLG_H__58EB9225_27DF_11D3_B296_006097BEAB13__INCLUDED_)
#define AFX_DROPDOWNBOXDLG_H__58EB9225_27DF_11D3_B296_006097BEAB13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDropDownBoxDlgApp:
// See DropDownBoxDlg.cpp for the implementation of this class
//

class CDropDownBoxDlgApp : public CWinApp
{
public:
	CDropDownBoxDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropDownBoxDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDropDownBoxDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPDOWNBOXDLG_H__58EB9225_27DF_11D3_B296_006097BEAB13__INCLUDED_)
