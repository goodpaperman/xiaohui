#include "stdafx.h"
#include "PushPinSheet.h"
#include "pushpinsheetdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CPushPinSheetApp, CWinApp)
	//{{AFX_MSG_MAP(CPushPinSheetApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CPushPinSheetApp::CPushPinSheetApp()
{
}

CPushPinSheetApp theApp;

BOOL CPushPinSheetApp::InitInstance()
{
	Enable3dControls();

	CPushPinSheetDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	return FALSE;
}

