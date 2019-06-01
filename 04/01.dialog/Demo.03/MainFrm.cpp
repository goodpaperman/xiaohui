// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TwoPanes.h"

#include "MainFrm.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(IDM_SPLIT_COL, OnSplitCol)
	ON_COMMAND(IDM_SPLIT_ROW, OnSplitRow)
	ON_COMMAND(IDM_COMMAND_INPUT, OnCommandInput)
	ON_UPDATE_COMMAND_UI(IDM_COMMAND_INPUT, OnUpdateCommandInput)
	//}}AFX_MSG_MAP
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
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	CCreateContext context;
	context.m_pNewViewClass = RUNTIME_CLASS(CChildView);

	if (!m_wndSplitter.Create( this,
		2, 2,                 // TODO: adjust the number of rows, columns
		CSize( 100, 100 ),    // TODO: adjust the minimum pane size
		&context, WS_CHILD | WS_VISIBLE | SPLS_DYNAMIC_SPLIT))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
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
	if (!m_wndCommandInput.Create(this))
	{
		TRACE("Failed to create toolbox\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndCommandInput.SetBarStyle(m_wndCommandInput.GetBarStyle() | CBRS_SIZE_DYNAMIC);
	m_wndCommandInput.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar, AFX_IDW_DOCKBAR_TOP);
	DockControlBar(&m_wndCommandInput, AFX_IDW_DOCKBAR_BOTTOM);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd*)
{
	// forward focus to the view window
	m_wndSplitter.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndSplitter.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnSplitCol() 
{
	m_wndSplitter.SplitColumn();
}

void CMainFrame::OnSplitRow() 
{
	m_wndSplitter.SplitRow();
}

BOOL CMainFrame::DestroyWindow() 
{
	if(CFrameWnd::DestroyWindow())
	{
		WaitForSingleObject(g_hEventClosed, 5000);
		CloseHandle(g_hEventClosed);
		return TRUE;
	}
	return FALSE;
}

void CMainFrame::OnCommandInput() 
{
	BOOL bVisible = ((m_wndCommandInput.GetStyle() & WS_VISIBLE) != 0);
	ShowControlBar(&m_wndCommandInput, !bVisible, FALSE);
	RecalcLayout();
}

void CMainFrame::OnUpdateCommandInput(CCmdUI* pCmdUI) 
{
	BOOL bVisible = ((m_wndCommandInput.GetStyle() & WS_VISIBLE) != 0);
	pCmdUI->SetCheck(bVisible);
}
