// CColorStaticST_demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CColorStaticST_demo.h"
#include "CColorStaticST_demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCColorStaticST_demoApp

BEGIN_MESSAGE_MAP(CCColorStaticST_demoApp, CWinApp)
	//{{AFX_MSG_MAP(CCColorStaticST_demoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCColorStaticST_demoApp construction

CCColorStaticST_demoApp::CCColorStaticST_demoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCColorStaticST_demoApp object

CCColorStaticST_demoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCColorStaticST_demoApp initialization

BOOL CCColorStaticST_demoApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CCColorStaticST_demoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
