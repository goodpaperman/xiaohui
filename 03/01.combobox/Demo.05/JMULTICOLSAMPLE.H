// JMultiColSample.h : main header file for the JMULTICOLSAMPLE application
//

#if !defined(AFX_JMULTICOLSAMPLE_H__2AF0C2A8_09E9_11D2_B3DF_00104B307E8C__INCLUDED_)
#define AFX_JMULTICOLSAMPLE_H__2AF0C2A8_09E9_11D2_B3DF_00104B307E8C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJMultiColSampleApp:
// See JMultiColSample.cpp for the implementation of this class
//

class CJMultiColSampleApp : public CWinApp
{
public:
	CJMultiColSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMultiColSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJMultiColSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JMULTICOLSAMPLE_H__2AF0C2A8_09E9_11D2_B3DF_00104B307E8C__INCLUDED_)
