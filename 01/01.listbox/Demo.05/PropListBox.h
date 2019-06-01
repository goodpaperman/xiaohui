// PropListBox.h : main header file for the PROPLISTBOX application
//

#if !defined(AFX_PROPLISTBOX_H__B8AE5348_3892_11D4_BC48_00105AA2186F__INCLUDED_)
#define AFX_PROPLISTBOX_H__B8AE5348_3892_11D4_BC48_00105AA2186F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPropListBoxApp:
// See PropListBox.cpp for the implementation of this class
//

class CPropListBoxApp : public CWinApp
{
public:
	CPropListBoxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropListBoxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPropListBoxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPLISTBOX_H__B8AE5348_3892_11D4_BC48_00105AA2186F__INCLUDED_)
