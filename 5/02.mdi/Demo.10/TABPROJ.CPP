// TabProj.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TabProj.h"

#include "MainFrm.h"
#include "TabFrame.h"
#include "TabProjDoc.h"
#include "TabProjView.h"
#include "Family.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// group 1  
static  char* p1[] =  {"ALEX",
						"BILL",
						"PAUL",
						"JAMES",
						"DADDY"};

static CRuntimeClass* v1[] =  {RUNTIME_CLASS(CAlex),
						RUNTIME_CLASS(CBill),
						RUNTIME_CLASS(CPaul),
						RUNTIME_CLASS(CJames),
						RUNTIME_CLASS(CDaddy)
						};

// group 2
static  char* p2[] =  {"PROMPT 1 GROUP2"};
static CRuntimeClass* v2[] =  {RUNTIME_CLASS(CTabProjView)};
// group 3 

static  char* p3[] =  {"PROMPT  VIEW 1 GROUP3",
                        "PROMPT  VIEW 2 GROUP3",
                        "PROMPT  VIEW 3 GROUP3",
                        "PROMPT  VIEW 4 GROUP3",
                        "PROMPT  VIEW 5 GROUP3",
                        "PROMPT  VIEW 6 GROUP3",
                        "PROMPT  VIEW 7 GROUP3",
                        "PROMPT  VIEW 8 GROUP3",
                        "PROMPT  VIEW 9 GROUP3",
                        "PROMPT  VIEW 10 GROUP3",
                        "PROMPT  VIEW 11 GROUP3",
                        "PROMPT  VIEW 12 GROUP3",
                        "PROMPT  VIEW 13 GROUP3",
                        "PROMPT  VIEW 14 GROUP3"
                        };

static CRuntimeClass* v3[] =  {RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView),
                                RUNTIME_CLASS(CTabProjView)
                         };

// group 4 

static  char* p4[] =  {"PROMPT VIEW 1 GROUP 4",
                        "PROMPT VIEW 2 GROUP 4",
                        "PROMPT VIEW 3 GROUP 4",
                        "PROMPT VIEW 4 GROUP 4",
                        "PROMPT VIEW 5 GROUP 4"
                        };
static CRuntimeClass* v4[] = {RUNTIME_CLASS(CTabProjView),
                              RUNTIME_CLASS(CTabProjView),
                              RUNTIME_CLASS(CTabProjView),
                              RUNTIME_CLASS(CTabProjView),
                              RUNTIME_CLASS(CTabProjView)
};
// GROUP OF  tabs (NUMERO VIEW, PROMPT ,OGGETTI VIEW)
static    SELECTOR_VIEWS enumgroup[] = { {5,p1,v1, "FAMILY GROUP"}, // 1 GROUP 
											{1,p2,v2, "NAME GROUP2"}, // 2
											{14,p3,v3, "NAME GROUP3"},	// 3 
											{5,p4,v4, "NAME GROUP4"}	// 4
										};  
													 
static GROUP_SELECTOR_LIST g1[] = {	4,  // NUMERO SELETTORI
                                    0, // initial group
									TRUE,  // TABSTYLE = FALSE BUTTON = TRUE
 								 	FALSE,   // BOTTOM POSITION
									enumgroup // GROUP LIST
									};             


/////////////////////////////////////////////////////////////////////////////
// CTabProjApp

BEGIN_MESSAGE_MAP(CTabProjApp, CWinApp)
	//{{AFX_MSG_MAP(CTabProjApp)
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
// CTabProjApp construction

CTabProjApp::CTabProjApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTabProjApp object

CTabProjApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTabProjApp initialization

BOOL CTabProjApp::InitInstance()
{
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
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_TABPROTYPE,
		RUNTIME_CLASS(CTabProjDoc),
		RUNTIME_CLASS(CTabFrame), // custom MDI child frame
		RUNTIME_CLASS(CTabProjView)); //default view
	AddDocTemplate(pDocTemplate);
//
// config CTabFrame
//
     CTabFrame::SetSelector(g1);
   //CTabFrame::SetTabContext(UINT idsel,UINT idnosel) 
   //CTabFrame::SetTabReserved(160,50);

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
void CTabProjApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTabProjApp message handlers

