// CustToolBarTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CustToolBarTest.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "CustToolBarTestDoc.h"
#include "CustToolBarTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestApp

BEGIN_MESSAGE_MAP(CCustToolBarTestApp, CWinApp)
	//{{AFX_MSG_MAP(CCustToolBarTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestApp construction

CCustToolBarTestApp::CCustToolBarTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCustToolBarTestApp object

CCustToolBarTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestApp initialization

BOOL CCustToolBarTestApp::InitInstance()
{
	AfxOleInit ();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("MY COMAPNY")); //_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_CUSTTOTYPE,
		RUNTIME_CLASS(CCustToolBarTestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCustToolBarTestView));
	AddDocTemplate(pDocTemplate);

	// Initialize customize managers:
	m_ContextMenuManager.AddMenu (_T("Test menu"), CG_IDR_POPUP_CUST_TOOL_BAR_TEST_VIEW);
	CString strEntry = REGISTRY_ROOT;
	strEntry += "Menus";
	m_ContextMenuManager.LoadState (strEntry);

	m_MouseManager.AddView (iIdTestView, "Test view", IDR_CUSTTOTYPE);
	CString strMouseEntry = REGISTRY_ROOT;
	strMouseEntry += "Mouse";
	m_MouseManager.LoadState (strMouseEntry);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	m_pMainWnd = pMainFrame;
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Load keyboard settings:
	CString strKbdEntry = REGISTRY_ROOT;
	strKbdEntry += "Keyboard";
	m_KeyboardManager.LoadState (strKbdEntry);

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCustToolBarTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestApp commands

int CCustToolBarTestApp::ExitInstance() 
{
	CString strMenuEntry = REGISTRY_ROOT;
	strMenuEntry += "Menus";
	m_ContextMenuManager.SaveState (strMenuEntry);
	
	CString strMouseEntry = REGISTRY_ROOT;
	strMouseEntry += "Mouse";
	m_MouseManager.SaveState (strMouseEntry);

	CString strKbdEntry = REGISTRY_ROOT;
	strKbdEntry += "Keyboard";
	m_KeyboardManager.SaveState (strKbdEntry);
    
	return CWinApp::ExitInstance();
}
//**********************************************************************************
BOOL CCustToolBarTestApp::ShowPopupMenu (UINT uiId, const CPoint& point, CWnd* pWnd)
{
	return m_ContextMenuManager.ShowPopupMenu (uiId,
				point.x, point.y, pWnd);
}
//**********************************************************************************
BOOL CCustToolBarTestApp::OnViewDoubleClick (int iViewId)
{
	UINT uiCmd = m_MouseManager.GetViewDblClickCommand (iViewId);
	if (uiCmd > 0)
	{
		AfxGetMainWnd ()->SendMessage (WM_COMMAND, uiCmd);
		return TRUE;
	}

	MessageBeep (-1);
	return FALSE;
}