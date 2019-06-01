// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DemoTBarE.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_BACK, OnBack)
	ON_COMMAND(ID_FORWARD, OnForward)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_HOME, OnHome)
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
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);

	if (!m_hotToolBar.Create(this) ||
		!m_hotToolBar.LoadToolBar(IDR_HOTBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_hotToolBar.ModifyStyle(0, TBSTYLE_FLAT);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Set up hot bar image lists.
	CImageList	imageList;
	CBitmap		bitmap;

	// Create and set the normal toolbar image list.
	bitmap.LoadBitmap(IDB_TOOLBAR_COLD);
	imageList.Create(21, 20, ILC_COLORDDB|ILC_MASK, 13, 1);
	imageList.Add(&bitmap, RGB(255,0,255));
	m_hotToolBar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)imageList.m_hImageList);
	imageList.Detach();
	bitmap.Detach();

	// Create and set the hot toolbar image list.
	bitmap.LoadBitmap(IDB_TOOLBAR_HOT);
	imageList.Create(21, 20, ILC_COLORDDB|ILC_MASK, 13, 1);
	imageList.Add(&bitmap, RGB(255,0,255));
	m_hotToolBar.SendMessage(TB_SETHOTIMAGELIST, 0, (LPARAM)imageList.m_hImageList);
	imageList.Detach();
	bitmap.Detach();

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_hotToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_hotToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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


void CMainFrame::OnBack() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnForward() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnStop() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnRefresh() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnHome() 
{
	// TODO: Add your command handler code here
	
}
