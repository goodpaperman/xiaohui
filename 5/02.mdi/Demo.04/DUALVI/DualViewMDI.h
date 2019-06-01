// DualViewMDI.h : main header file for the DUALVIEWMDI application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDVMApp:
// See DualViewMDI.cpp for the implementation of this class
//

// Template indexes, for accessing the doc template for creating secondary 
// frames.
#define DOCTEMPLATE_MAINVIEW	1
#define DOCTEMPLATE_SECONDVIEW	2

class CDVMApp : public CWinApp
{
public:
	CMultiDocTemplate * GetDocTemplate(UINT uTemplate);
	CDVMApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDVMApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDVMApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMultiDocTemplate * m_pMDTSecond;
	CMultiDocTemplate * m_pMDTMain;
};


/////////////////////////////////////////////////////////////////////////////

extern CDVMApp	theApp ;
