// DualViewMDI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DualViewMDI.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "DVMDoc.h"
#include "DVMView2.h"
#include "DVMView1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDVMApp

BEGIN_MESSAGE_MAP(CDVMApp, CWinApp)
	//{{AFX_MSG_MAP(CDVMApp)
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
// CDVMApp construction

CDVMApp::CDVMApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDVMApp object

CDVMApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDVMApp initialization

BOOL CDVMApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

// We store two separate doc templates so that the MFC framework won't get 
// confused as to which type of doc/view combo to create with.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DUALVITYPE,
		RUNTIME_CLASS(CDVMDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDVMView1));
	AddDocTemplate(pDocTemplate);
// Store this template so that we can refer to it.
	m_pMDTMain = pDocTemplate ;

// Now create and store the second template.
	pDocTemplate = new CMultiDocTemplate(
		IDR_DUALVITYPE,
		RUNTIME_CLASS(CDVMDoc),		// Same document.
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDVMView2));	// Second view.
// Note that we do not add this second doc template to the app - if we did, it 
// would have two to choose from and would not know which to use when creating 
// a new document - so it would ask the user. Aaaarrrggghhh!!!

// However, we must now explicitly delete this doc template in ExitInstance(), 
// or it will be a memory leak.
	m_pMDTSecond = pDocTemplate ;

// The second view is created when the document first gets initialised, which 
// is CDocument::OnNewDocument() - as both views share the same document, this 
// only gets called once per pair of child frames.

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
void CDVMApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDVMApp commands

CMultiDocTemplate * CDVMApp::GetDocTemplate(UINT uTemplate)
{
	CMultiDocTemplate	*pDocTemplate = NULL ;	// In case the index is bad.

	switch (uTemplate)
	{
// Definitions of template indexes are in this class' header file.
		case DOCTEMPLATE_MAINVIEW :
			pDocTemplate = m_pMDTMain ;
			break ;

		case DOCTEMPLATE_SECONDVIEW :
			pDocTemplate = m_pMDTSecond ;
			break ;
	}

	return pDocTemplate ;
}

int CDVMApp::ExitInstance() 
{
	delete m_pMDTSecond ;	// As it wasn't added to the app, it will not get 
							// automatically deleted when the app ends as the 
							// original will.
	
	return CWinApp::ExitInstance();
}
