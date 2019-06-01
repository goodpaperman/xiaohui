#if !defined(AFX_PUSHPINSHEET_H__DFC5AFD3_6507_11D1_BE51_000000000000__INCLUDED_)
#define AFX_PUSHPINSHEET_H__DFC5AFD3_6507_11D1_BE51_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


class CPushPinSheetApp : public CWinApp
{
public:
	CPushPinSheetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPushPinSheetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPushPinSheetApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUSHPINSHEET_H__DFC5AFD3_6507_11D1_BE51_000000000000__INCLUDED_)
