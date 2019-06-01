// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CustomMoreWindows.h"
#include "windowdlg.h"
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
	ON_WM_CREATE()
	ON_WM_INITMENUPOPUP()
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
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
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

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
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
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
#define DEFAULT_NUMBER_OF_MDIS 9

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	int nCount = 0;
	CWnd * pWnd = GetWindow (GW_CHILD);
	ASSERT (pWnd);
	pWnd = pWnd->GetWindow (GW_CHILD);
	while (pWnd)
	{
		nCount++;
		pWnd = pWnd->GetWindow (GW_HWNDNEXT);
	}

	if ( nCount == 0 )
		return;

	if ( !bSysMenu )
	{
		int nLength = pPopupMenu->GetMenuItemCount();
		for ( int i = 0; i < nLength; i++ )
		{
			if ( pPopupMenu->GetMenuItemID( i ) == AFX_IDM_FIRST_MDICHILD )
			{
				if ( pPopupMenu->GetMenuItemID( nLength - 1 ) == 
					AFX_IDM_FIRST_MDICHILD + DEFAULT_NUMBER_OF_MDIS )
				{
					pPopupMenu->DeleteMenu( nLength - 1, MF_BYPOSITION );
				}

				pPopupMenu->AppendMenu(MF_ENABLED|MF_STRING,
					AFX_IDM_FIRST_MDICHILD + DEFAULT_NUMBER_OF_MDIS, 
					"&Windows..." );

				return;
			}
		}
	}
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( wParam == AFX_IDM_FIRST_MDICHILD + 9 )
	{
		CWindowDlg dlgWindowDlg;
		dlgWindowDlg.DoModal();

		return TRUE;
	}
	
	return CMDIFrameWnd::OnCommand(wParam, lParam);
}
