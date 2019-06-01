// dragdroptree.h : main header file for the DRAGDROPTREE application
//

#if !defined(AFX_DRAGDROPTREE_H__29F88945_897C_11D3_A59E_00A02411D21E__INCLUDED_)
#define AFX_DRAGDROPTREE_H__29F88945_897C_11D3_A59E_00A02411D21E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDragdroptreeApp:
// See dragdroptree.cpp for the implementation of this class
//

class CDragdroptreeApp : public CWinApp
{
public:
	CDragdroptreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragdroptreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDragdroptreeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGDROPTREE_H__29F88945_897C_11D3_A59E_00A02411D21E__INCLUDED_)
