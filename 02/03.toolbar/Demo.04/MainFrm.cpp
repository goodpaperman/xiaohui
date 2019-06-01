// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ToolBarExample.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BAR_ONE, OnBarOne)
	ON_BN_CLICKED(IDC_BAR_TWO, OnBarTwo)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};



/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

    // Create a dialog bar
	m_dlgBar1.Create( this, IDD_DIALOGBAR1, CBRS_TOP , IDD_DIALOGBAR1 );
	m_dlgBar1.SetWindowText( "Notepad Wizard Version 1.0" );
	m_dlgBar1.EnableDocking( CBRS_ALIGN_ANY );
	// Dock the control bar
    // Remove the two back slashs to use DockControlBar  
	// DockControlBar( &m_dlgBar1 );
	
    
	// Create a dialog bar
	m_dlgBar2.Create( this, IDD_DIALOGBAR2, CBRS_BOTTOM , IDD_DIALOGBAR2 );
	m_dlgBar2.SetWindowText( "Notepad Wizard Version 1.0" );
	m_dlgBar2.EnableDocking( CBRS_ALIGN_ANY );
	// Dock the control bar
    // Remove the two back slashs to use DockControlBar  
	// DockControlBar( &m_dlgBar2 );

	
	// Create a Floating ToolBar
	m_wndToolBar1.Create( this );
	m_wndToolBar1.SetWindowText( "Floating Toolbar" );
    m_wndToolBar1.LoadToolBar( IDR_TOOLBAR1 );
    
	// Enable docking even though the toolbar will float.
	m_wndToolBar1.EnableDocking( CBRS_ALIGN_ANY );
    
	// Calculate the location of the Floating toolbar.
	CRect  rc;
	GetClientRect( &rc );
	ClientToScreen( &rc );
    FloatControlBar(&m_wndToolBar1, rc.TopLeft() );  
    UINT nOldStyle = m_wndToolBar1.GetBarStyle();
	m_wndToolBar1.SetBarStyle(nOldStyle | CBRS_TOOLTIPS | CBRS_FLYBY);

    // Create a Floating Dialog Box.
	// To produce a Shareware screen or Freeware Screen.
	m_dlgBar3.Create( this, IDD_DIALOGBAR3, CBRS_TOP , IDD_DIALOGBAR3 );
	m_dlgBar3.SetWindowText( "Toolbar Example" );
	
	// Enable docking even though the toolbar will float.
	m_dlgBar3.EnableDocking( CBRS_ALIGN_ANY );

	// Calculate the location of the Floating toolbar.
	GetClientRect( &rc );
	ClientToScreen( &rc );
    FloatControlBar(&m_dlgBar3, rc.TopLeft() );  
	

	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG

void CMainFrame::OnBarOne()
{
	AfxMessageBox( "Toolbar Example Message Box one" );
}

void CMainFrame::OnBarTwo()
{
	AfxMessageBox( "Toolbar Example Message Box two" );
}

void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
