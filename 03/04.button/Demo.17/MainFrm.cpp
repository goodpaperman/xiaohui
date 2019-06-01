// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ReStart.h"

#include "MainFrm.h"
#include "ReStartView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT GfxSetSafeTimer(CWnd * pWnd, const UINT uiElapse)
{
	ASSERT(pWnd && pWnd->GetSafeHwnd());
	UINT iTimer = 1;
	while (iTimer < 10000)
	{
		UINT res = pWnd->SetTimer(1, uiElapse, NULL);
		if (res) return res;
		iTimer ++;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_INITMENU()
	ON_WM_INITMENUPOPUP()
	ON_WM_MENUCHAR()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_WM_ENTERMENULOOP()
	ON_WM_EXITMENULOOP()
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
	cSpawn.LoadToolBarResource(IDR_MAINFRAME);
	oldMenuBarRc.SetRect(0,0,0,0);
	bMenuLooping = false;
	uiTimerId = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, CRect(0,0,1200, 0)) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBarShowInputWave.Create(this, IDR_MAINFRAME_INPUT_WAVE, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndDlgBarShowOutputWave.Create(this, IDR_MAINFRAME_OUTPUT_WAVE, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndDlgBarShowWave.Create(this, IDR_MAINFRAME_WAVE, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBarShowInputWave) ||
		!m_wndReBar.AddBar(&m_wndDlgBarShowOutputWave) ||
		!m_wndReBar.AddBar(&m_wndDlgBarShowWave))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.x = cs.y = 100;
	cs.cx = 680;
	cs.cy = 600;
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


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	lpMMI->ptMinTrackSize.x = 680;
	lpMMI->ptMinTrackSize.y = 600;
	
	CMDIFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnEnterMenuLoop(BOOL bIsTrackPopupMenu)
{
	if (!(oldMenuBarRc.IsRectEmpty()))
	{
		CWindowDC dc(this);
		dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
		oldMenuBarRc.SetRect(0,0,0,0);
	}

	bMenuLooping = true;
}

void CMainFrame::OnExitMenuLoop(BOOL bIsTrackPopupMenu)
{
	bMenuLooping = false;
}

void CMainFrame::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (!cSpawn.DrawItem(lpDrawItemStruct))
		CFrameWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
	
	CMDIFrameWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if (!cSpawn.MeasureItem(lpMeasureItemStruct))
		CFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CMainFrame::OnInitMenu(CMenu* pMenu) 
{
	CFrameWnd::OnInitMenu(pMenu);
	cSpawn.RemapMenu(pMenu);	
}

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	cSpawn.RemapMenu(pPopupMenu);
}

LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	LRESULT lRes;
	if (!cSpawn.FindKeyboardShortcut(nChar, nFlags, pMenu, lRes)) 
		lRes = CFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
	return lRes;
}

UINT CMainFrame::OnNcHitTest(CPoint point) 
{
	UINT res = CFrameWnd::OnNcHitTest(point);
	if (!bMenuLooping && res == HTMENU)
	{
		CMenu * pMenu = GetMenu();
		ASSERT(pMenu);

		UINT mifp = MenuItemFromPoint(GetSafeHwnd(), pMenu->GetSafeHmenu(), point);
		if (mifp != (UINT) -1)
		{
			CRect rc, wrc;
			if (GetMenuItemRect(GetSafeHwnd(), pMenu->GetSafeHmenu(), mifp, &rc))
			{
				if (cSpawn.IsSpawnMenu(pMenu, mifp, true))
				{
					GetWindowRect(wrc);
					rc.top -= wrc.top;
					rc.bottom -= wrc.top;
					rc.left -= wrc.left;
					rc.right -= wrc.left;
					if (oldMenuBarRc != rc || oldMenuBarRc.IsRectEmpty())
					{
						CWindowDC dc(this);
						if (!(oldMenuBarRc.IsRectEmpty()))
						{
							dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
						}
						dc.Draw3dRect(rc,cSpawn.cr3dHilight, cSpawn.cr3dShadow);
						oldMenuBarRc = rc;
					}
				}
				else
				{
					if (!(oldMenuBarRc.IsRectEmpty()))
					{
						CWindowDC dc(this);
						dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
						oldMenuBarRc.SetRect(0,0,0,0);
					}
				}
			}
		}
	}
	else
	{
		if (!(oldMenuBarRc.IsRectEmpty()))
		{
			CWindowDC dc(this);
			dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
			oldMenuBarRc.SetRect(0,0,0,0);
		}
	}
	
	return res;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if (uiTimerId == nIDEvent && !bMenuLooping)
	{
		CPoint pt;
		GetCursorPos(&pt);
		LRESULT res = SendMessage(WM_NCHITTEST, 0, MAKELONG(pt.x, pt.y));
	}
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnDestroy() 
{
	if (uiTimerId) KillTimer(uiTimerId);
		CFrameWnd::OnDestroy();
}

void CMainFrame::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CMDIFrameWnd::OnWindowPosChanged(lpwndpos);
	
	CRect rect;
	GetWindowRect(rect);

	

	CReStartView* pView = (CReStartView*)GetActiveFrame()->GetActiveView();
	if(pView)
		if(pView->m_info != NULL)
			pView->m_info->MoveWindow(rect.right+2, rect.top, 100, 600, TRUE);
}
