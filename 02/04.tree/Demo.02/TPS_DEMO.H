// TPS_Demo.h : main header file for the TPS_DEMO application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoApp:
// See TPS_Demo.cpp for the implementation of this class
//

class CTPS_DemoApp : public CWinApp
{
public:
	BOOL	gprf_bISee;
	BOOL	gprf_bDontLike;
	BOOL	gprf_bLikeBeer;
	int		gprf_nWhen;
public:
	CTPS_DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPS_DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTPS_DemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
