// BCGMDIFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"
#include "BCGMDIFrameWnd.h"
#include "BCGToolbar.h"
#include "BCGMenuBar.h"
#include "BCGPopupMenu.h"
#include "BCGToolbarMenuButton.h"
#include "bcglocalres.h"
#include "bcgbarres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGMDIFrameWnd

IMPLEMENT_DYNCREATE(CBCGMDIFrameWnd, CMDIFrameWnd)

#pragma warning (disable : 4355)

CBCGMDIFrameWnd::CBCGMDIFrameWnd() :
	m_Impl (this),
	m_hmenuWindow (NULL),
	m_bContextHelp (FALSE)
{
}

#pragma warning (default : 4355)

CBCGMDIFrameWnd::~CBCGMDIFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CBCGMDIFrameWnd, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CBCGMDIFrameWnd)
	ON_WM_MENUCHAR()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_CREATETOOLBAR, OnToolbarCreateNew)
	ON_REGISTERED_MESSAGE(BCGM_DELETETOOLBAR, OnToolbarDelete)
	ON_COMMAND( ID_CONTEXT_HELP, OnContextHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGMDIFrameWnd message handlers

void CBCGMDIFrameWnd::OnSetMenu (HMENU hmenu)
{
	if (m_Impl.m_pMenuBar != NULL)
	{
		m_Impl.m_pMenuBar->CreateFromMenu (hmenu == NULL ? m_Impl.m_hDefaultMenu : hmenu);
	}
}
//*******************************************************************************************
BOOL CBCGMDIFrameWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!CMDIFrameWnd::OnCreateClient(lpcs, pContext))
	{
		return FALSE;
	}

	m_wndClientArea.SubclassWindow (m_hWndMDIClient);
	return TRUE;
}
//*******************************************************************************************
LRESULT CBCGMDIFrameWnd::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	if (m_Impl.m_pMenuBar != NULL && m_Impl.m_pMenuBar->TranslateChar (nChar))
	{
		return MAKELPARAM (MNC_EXECUTE, -1);
	}
		
	return CMDIFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
}
//*******************************************************************************************
void CBCGMDIFrameWnd::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CMDIFrameWnd::OnWindowPosChanged(lpwndpos);
	
	if (m_Impl.m_pMenuBar != NULL)
	{
		BOOL bMaximized;
		CMDIChildWnd* pChild = MDIGetActive (&bMaximized);

		if (pChild == NULL || !bMaximized)
		{
			m_Impl.m_pMenuBar->SetMaximizeMode (FALSE);
		}
		else
		{
			m_Impl.m_pMenuBar->SetMaximizeMode (TRUE, pChild);
		}
	}
}
//*******************************************************************************************
BOOL CBCGMDIFrameWnd::PreTranslateMessage(MSG* pMsg) 
{
	switch (pMsg->message)
	{
	case WM_SYSKEYDOWN:
		if (m_Impl.m_pActivePopupMenu != NULL &&
			::IsWindow (m_Impl.m_pActivePopupMenu->m_hWnd))
		{
			m_Impl.m_pActivePopupMenu->SendMessage (WM_CLOSE);
			return TRUE;
		}
		break;

	case WM_SYSKEYUP:
		if (m_Impl.m_pMenuBar != NULL)
		{
			if (m_Impl.m_pMenuBar == GetFocus ())
			{
				SetFocus ();
			}
			else
			{
				m_Impl.m_pMenuBar->SetFocus ();
			}
			return TRUE;
		}
		break;

	case WM_KEYDOWN:
		//-----------------------------------------
		// Pass keyboard action to the active menu:
		//-----------------------------------------
		if (m_Impl.ProcessKeyboard ((int) pMsg->wParam))
		{
			return TRUE;
		}
		break;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
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

	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}
//*******************************************************************************************
BOOL CBCGMDIFrameWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
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
		return CMDIFrameWnd::OnCommand(wParam, lParam);
	}

	MessageBeep ((UINT) -1);
	return FALSE;
}
//*******************************************************************************************
HMENU CBCGMDIFrameWnd::GetWindowMenuPopup (HMENU hMenuBar)
{
	m_hmenuWindow = CMDIFrameWnd::GetWindowMenuPopup (hMenuBar);
	return m_hmenuWindow;
}
//********************************************************************************************
BOOL CBCGMDIFrameWnd::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	m_Impl.m_nIDDefaultResource = nIDResource;
	
	return CMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}
//*******************************************************************************************
void CBCGMDIFrameWnd::OnShowPopupMenu (CBCGPopupMenu* pMenuPopup)
{
	m_Impl.OnShowPopupMenu (pMenuPopup, this);

	if (CBCGToolBar::IsCustomizeMode () || m_hmenuWindow == NULL ||
		pMenuPopup == NULL)
	{
		return;
	}

	//-----------------------------------------------------------
	// Check the popup menu for the "Windows..." menu maching...:
	//-----------------------------------------------------------
	HMENU hMenuPop = pMenuPopup->GetMenu ();
	ASSERT (hMenuPop != NULL);
	BOOL bIsWindowMenu = FALSE;

	int iItemMax = ::GetMenuItemCount (hMenuPop);
	for (int iItemPop = 0; !bIsWindowMenu && iItemPop < iItemMax; iItemPop ++)
	{
		UINT nID = ::GetMenuItemID( hMenuPop, iItemPop);
		bIsWindowMenu =  (nID >= AFX_IDM_WINDOW_FIRST && nID <= AFX_IDM_WINDOW_LAST);
	}

	if (!bIsWindowMenu)
	{
		return;
	}

	CMenu* pMenu = CMenu::FromHandle (m_hmenuWindow);
	if (pMenu == NULL)
	{
		return;
	}

	int iCount = (int) pMenu->GetMenuItemCount ();
	BOOL bIsFirstWindowItem = TRUE;

	for (int i = 0; i < iCount; i ++)
	{
		UINT uiCmd = pMenu->GetMenuItemID (i);
		if (uiCmd < AFX_IDM_FIRST_MDICHILD)
		{
			continue;
		}

		if (bIsFirstWindowItem)
		{
			pMenuPopup->InsertSeparator ();
			bIsFirstWindowItem = FALSE;
		}

		CString strText;
		pMenu->GetMenuString (i, strText, MF_BYPOSITION);

		CBCGToolbarMenuButton button (uiCmd, NULL /* No submenus - assume */, -1, strText);

		UINT uiState = pMenu->GetMenuState (i, MF_BYPOSITION);
		if (uiState & MF_CHECKED)
		{
			button.m_nStyle |= TBBS_CHECKED;
		}

		pMenuPopup->InsertItem (button);
	}
}
//**********************************************************************************
void CBCGMDIFrameWnd::OnClosePopupMenu (CBCGPopupMenu* pMenuPopup)
{
	if (m_Impl.m_pActivePopupMenu == pMenuPopup)
	{
		m_Impl.m_pActivePopupMenu = NULL;
	}
}
//*******************************************************************************************
LRESULT CBCGMDIFrameWnd::OnToolbarCreateNew(WPARAM,LPARAM lp)
{
	ASSERT (lp != NULL);
	return (LRESULT) m_Impl.CreateNewToolBar ((LPCTSTR) lp);
}
//***************************************************************************************
LRESULT CBCGMDIFrameWnd::OnToolbarDelete(WPARAM,LPARAM lp)
{
	CBCGToolBar* pToolbar = (CBCGToolBar*) lp;
	ASSERT_VALID (pToolbar);

	return (LRESULT) m_Impl.DeleteToolBar (pToolbar);
}
//***************************************************************************************
void CBCGMDIFrameWnd::WinHelp(DWORD dwData, UINT nCmd) 
{
	if (dwData > 0 || !m_bContextHelp)
	{
		CMDIFrameWnd::WinHelp(dwData, nCmd);
	}
	else
	{
		OnContextHelp ();
	}
}
//***************************************************************************************
void CBCGMDIFrameWnd::OnContextHelp ()
{
	m_bContextHelp = TRUE;

	if (!m_bHelpMode && CanEnterHelpMode())
	{
		CBCGToolBar::SetHelpMode ();
	}

	CMDIFrameWnd::OnContextHelp ();

	if (!m_bHelpMode)
	{
		CBCGToolBar::SetHelpMode (FALSE);
	}

	m_bContextHelp = FALSE;
}
//****************************************************************************************
void CBCGMDIFrameWnd::EnableDocking (DWORD dwDockStyle)
{
	m_Impl.FrameEnableDocking (this, dwDockStyle);
}
