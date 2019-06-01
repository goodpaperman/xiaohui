// counter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "counter.h"
#include "counterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCounterApp

BEGIN_MESSAGE_MAP(CCounterApp, CWinApp)
	//{{AFX_MSG_MAP(CCounterApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCounterApp construction

CCounterApp::CCounterApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCounterApp object

CCounterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCounterApp initialization

BOOL CCounterApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    SetRegistryKey("Counter"); 

	CCounterDlg dlg;
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
