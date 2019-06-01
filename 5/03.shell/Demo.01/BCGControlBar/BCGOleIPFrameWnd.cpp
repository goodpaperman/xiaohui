// BCGOleIPFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"
#include "bcgcontrolbar.h"
#include "BCGOleIPFrameWnd.h"
#include "BCGMenuBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGOleIPFrameWnd

IMPLEMENT_DYNCREATE(CBCGOleIPFrameWnd, COleIPFrameWnd)

#pragma warning (disable : 4355)

CBCGOleIPFrameWnd::CBCGOleIPFrameWnd() :
	m_Impl (this),
	m_bContextHelp (FALSE)
{
}

#pragma warning (default : 4355)

CBCGOleIPFrameWnd::~CBCGOleIPFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CBCGOleIPFrameWnd, COleIPFrameWnd)
	//{{AFX_MSG_MAP(CBCGOleIPFrameWnd)
	ON_WM_MENUCHAR()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_CREATETOOLBAR, OnToolbarCreateNew)
	ON_REGISTERED_MESSAGE(BCGM_DELETETOOLBAR, OnToolbarDelete)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBCGOleIPFrameWnd message handlers

LRESULT CBCGOleIPFrameWnd::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	if (m_Impl.m_pMenuBar != NULL && m_Impl.m_pMenuBar->TranslateChar (nChar))
	{
		return MAKELPARAM (MNC_EXECUTE, -1);
	}
		
	return CFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
}
//*******************************************************************************************
afx_msg LRESULT CBCGOleIPFrameWnd::OnSetMenu (WPARAM wp, LPARAM lp)
{
	OnSetMenu ((HMENU) wp);
	return DefWindowProc (WM_MDISETMENU, NULL, lp);
}
//*******************************************************************************************
void CBCGOleIPFrameWnd::OnSetMenu (HMENU hmenu)
{
	if (m_Impl.m_pMenuBar != NULL)
	{
		m_Impl.m_pMenuBar->CreateFromMenu 
			(hmenu == NULL ? m_Impl.m_hDefaultMenu : hmenu);
	}
}
//*******************************************************************************************
BOOL CBCGOleIPFrameWnd::PreTranslateMessage(MSG* pMsg) 
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		if (m_Impl.ProcessKeyboard ((int) pMsg->wParam))
		{
			return TRUE;
		}
		break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
		{
			CPoint pt (LOWORD(pMsg->lParam), HIWORD(pMsg->lParam));
			CWnd* pWnd = CWnd::FromHandlePermanent(pMsg->hwnd);

			if (pWnd != NULL)
			{
				pWnd->ClientToScreen (&pt);
			}

			if (m_Impl.ProcessMouseClick (pt))
			{
				return TRUE;
			}

			if (pMsg->message == WM_RBUTTONUP &&
				!CBCGToolBar::IsCustomizeMode ())
			{
				//---------------------------------------
				// Activate the control bar context menu:
				//---------------------------------------
				CWnd* pWnd = CWnd::FromHandlePermanent(pMsg->hwnd);
				CDockBar* pBar = DYNAMIC_DOWNCAST(CDockBar, pWnd);

				if (pBar != NULL)
				{
					CPoint pt;

					pt.x = LOWORD(pMsg->lParam);
					pt.y = HIWORD(pMsg->lParam);
					pBar->ClientToScreen(&pt);

					SendMessage (BCGM_TOOLBARMENU,
								(WPARAM) GetSafeHwnd (),
								MAKELPARAM (pt.x, pt.y));
				}
			}
		}
		break;

	case WM_NCLBUTTONDOWN:
	case WM_NCLBUTTONUP:
	case WM_NCRBUTTONDOWN:
	case WM_NCRBUTTONUP:
	case WM_NCMBUTTONDOWN:
	case WM_NCMBUTTONUP:
		if (m_Impl.ProcessMouseClick (CPoint (LOWORD(pMsg->lParam), HIWORD(pMsg->lParam))))
		{
			return TRUE;
		}
		break;

	case WM_MOUSEMOVE:
		{
			CPoint pt (LOWORD(pMsg->lParam), HIWORD(pMsg->lParam));
			CWnd* pWnd = CWnd::FromHandlePermanent(pMsg->hwnd);

			if (pWnd != NULL)
			{
				pWnd->ClientToScreen (&pt);
			}

			if (m_Impl.ProcessMouseMove (pt))
			{
				return TRUE;
			}
		}
	}

	return CFrameWnd::PreTranslateMessage(pMsg);
}
//*******************************************************************************************
void CBCGOleIPFrameWnd::OnShowPopupMenu (CBCGPopupMenu* pMenuPopup)
{
	m_Impl.OnShowPopupMenu (pMenuPopup, this);
}
//*******************************************************************************************
void CBCGOleIPFrameWnd::OnClosePopupMenu (CBCGPopupMenu* pMenuPopup)
{
	if (m_Impl.m_pActivePopupMenu == pMenuPopup)
	{
		m_Impl.m_pActivePopupMenu = NULL;
	}
}
//*******************************************************************************************
BOOL CBCGOleIPFrameWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (HIWORD (wParam) == 1)
	{
		//---------------------------
		// Simmulate ESC keystroke...
		//---------------------------
		if (m_Impl.ProcessKeyboard (VK_ESCAPE))
		{
			return TRUE;
		}
	}

	if (!CBCGToolBar::IsCustomizeMode ())
	{
		return CFrameWnd::OnCommand(wParam, lParam);
	}

	MessageBeep ((UINT) -1);
	return FALSE;
}
//******************************************************************
BOOL CBCGOleIPFrameWnd::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	m_Impl.m_nIDDefaultResource = nIDResource;
	return CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}
//***************************************************************************************
void CBCGOleIPFrameWnd::WinHelp(DWORD dwData, UINT nCmd) 
{
	if (dwData > 0 || !m_bContextHelp)
	{
		CFrameWnd::WinHelp(dwData, nCmd);
	}
	else
	{
		OnContextHelp ();
	}
}
//***************************************************************************************
void CBCGOleIPFrameWnd::OnContextHelp ()
{
	m_bContextHelp = TRUE;

	if (!m_bHelpMode && CanEnterHelpMode())
	{
		CBCGToolBar::SetHelpMode ();
	}

	CFrameWnd::OnContextHelp ();

	if (!m_bHelpMode)
	{
		CBCGToolBar::SetHelpMode (FALSE);
	}

	m_bContextHelp = FALSE;
}
//****************************************************************************************
void CBCGOleIPFrameWnd::EnableDocking (DWORD dwDockStyle)
{
	m_Impl.FrameEnableDocking (this, dwDockStyle);
}
//*******************************************************************************************
LRESULT CBCGOleIPFrameWnd::OnToolbarCreateNew(WPARAM,LPARAM lp)
{
	ASSERT (lp != NULL);
	return (LRESULT) m_Impl.CreateNewToolBar ((LPCTSTR) lp);
}
//***************************************************************************************
LRESULT CBCGOleIPFrameWnd::OnToolbarDelete(WPARAM,LPARAM lp)
{
	CBCGToolBar* pToolbar = (CBCGToolBar*) lp;
	ASSERT_VALID (pToolbar);

	return (LRESULT) m_Impl.DeleteToolBar (pToolbar);
}
