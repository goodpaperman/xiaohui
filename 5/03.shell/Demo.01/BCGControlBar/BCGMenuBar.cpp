// BCGMenuBar.cpp : implementation file
//

#include "stdafx.h"
#include <afxpriv.h>
#include <..\\src\\afximpl.h>

#include "globals.h"
#include "BCGMenuBar.h"
#include "BCGToolbarButton.h"
#include "BCGToolbarMenuButton.h"
#include "BCGToolbarSystemMenuButton.h"
#include "BCGToolbarMenuButtonsButton.h"
#include "BCGPopupMenu.h"
#include "MenuHash.h"
#include "bcgbarres.h"
#include "bcglocalres.h"
#include "BCGMDIFrameWnd.h"
#include "BCGFrameWnd.h"
#include "BCGOleIPFrameWnd.h"
#include "BCGMultiDocTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CBCGMenuBar, CBCGToolBar, VERSIONABLE_SCHEMA | 1)

HHOOK CBCGMenuBar::m_hookMouseDrag = NULL;
CBCGMenuBar* CBCGMenuBar::m_pDraggedMenuBar = NULL;

/////////////////////////////////////////////////////////////////////////////
// CBCGMenuBar

CBCGMenuBar::CBCGMenuBar()
{
	m_bMaximizeMode = FALSE;
	m_bActualMaximizeMode = FALSE;
	m_hMenu = NULL;
	m_hDefaultMenu = NULL;
	m_hSysMenu = NULL;
	m_hSysIcon = NULL;
	m_uiDefMenuResId = 0;
	m_nSystemButtonsNum = 0;
	m_nSystemButtonsNumSaved = 0;
	m_bHaveButtons = FALSE;
}

CBCGMenuBar::~CBCGMenuBar()
{
	SetDragMode (FALSE);
	::DestroyMenu (m_hMenu);
}


BEGIN_MESSAGE_MAP(CBCGMenuBar, CBCGToolBar)
	//{{AFX_MSG_MAP(CBCGMenuBar)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBCGMenuBar message handlers

void CBCGMenuBar::CreateFromMenu (HMENU hMenu, BOOL bDefaultMenu)
{
	g_menuHash.SaveMenuBar (m_hMenu, this);

	BOOL bMaximizeMode = m_bMaximizeMode;
	m_bMaximizeMode = FALSE;

	m_hMenu = hMenu;
	if (bDefaultMenu)
	{
		m_hDefaultMenu = hMenu;
	}

	if (!g_menuHash.LoadMenuBar (hMenu, this))
	{
		CMenu* pMenu = CMenu::FromHandle (hMenu);
		if (pMenu == NULL)
		{
			return;
		}

		RemoveAllButtons ();

		int iCount = (int) pMenu->GetMenuItemCount ();
		for (int i = 0; i < iCount; i ++)
		{
			UINT uiID = pMenu->GetMenuItemID (i);
			
			CString strText;
			pMenu->GetMenuString (i, strText, MF_BYPOSITION);
			
			switch (uiID)
			{
			case -1:	// Pop-up menu
				{
					CMenu* pPopupMenu = pMenu->GetSubMenu (i);
					ASSERT (pPopupMenu != NULL);

					CBCGToolbarMenuButton button (
						0, pPopupMenu->GetSafeHmenu (), -1, strText);
					button.m_bText = TRUE;
					button.m_bImage = FALSE;

					InsertButton (button);
				}
				break;

			case 0:		// Separator
				InsertSeparator ();
				break;

			default:	// Regular command
				{
					CBCGToolbarButton button (uiID, -1, strText);
					button.m_bText = TRUE;
					button.m_bImage = FALSE;

					InsertButton (button);
				}
				break;
			}
		}
	}

	if (bMaximizeMode)
	{
		CMDIFrameWnd* pParentFrame = DYNAMIC_DOWNCAST (CMDIFrameWnd, m_pParentWnd);
		if (pParentFrame != NULL)
		{
			SetMaximizeMode (TRUE, pParentFrame->MDIGetActive ());
		}
	}

	if (GetSafeHwnd () != NULL)
	{
		AdjustLayout ();
	}
}
//***************************************************************************************

class CBCGMenuBarDockBar : public CDockBar
{
	friend CBCGMenuBar;
};

CSize CBCGMenuBar::CalcDynamicLayout (int nLength, DWORD dwMode)
{
	return CalcLayout(dwMode, nLength);
}
//**********************************************************************************
CSize CBCGMenuBar::CalcLayout(DWORD dwMode, int nLength)
{
	OnChangeHot (-1);

	//------------------------------------------
	// Is menu bar have the buttons with images?
	//------------------------------------------
	m_bHaveButtons = FALSE;

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		if (!pButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarMenuButtonsButton)) &&
			!pButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarSystemMenuButton)) &&
			pButton->m_bImage && pButton->IsDrawImage ())
		{
			m_bHaveButtons = TRUE;
			break;
		}
	}

	if (m_pDockContext != NULL &&
		m_pDockContext->m_bDragging)
	{
		SetDragMode (TRUE);
	}

	if ((dwMode == (LM_HORZ | LM_MRUWIDTH)) ||
		(m_pDockContext != NULL && !m_pDockContext->m_bDragging &&
		IsFloating ()))
	{
		return CBCGToolBar::CalcLayout (dwMode, nLength);
	}

	BOOL bVert = (dwMode & LM_VERTDOCK) || ((dwMode & LM_HORZ) == 0);

	CRect rect; rect.SetRectEmpty ();
	
	if (m_pDockBar != NULL)
	{
		rect = ((CBCGMenuBarDockBar*) m_pDockBar)->m_rectLayout;
	}

	if (rect.IsRectEmpty ())
	{
		CWnd* pFrame = GetOwner ();
		pFrame->GetClientRect(&rect);
	}

	CSize size;

	CRect rectClient;
	rectClient.SetRectEmpty();
	CalcInsideRect (rectClient, (dwMode & LM_HORZ));

	if (!bVert)
	{
		WrapToolBar (rect.Width ());

		//-------------------------------------
		// Calculate size again after wrapping:
		//-------------------------------------
		size = CalcSize (FALSE);
		size.cx = rect.Width () - rectClient.Width() / 2;
		size.cy -= rectClient.Height();
	}
	else
	{
		//-------------------------------------
		// Calculate size again after wrapping:
		//-------------------------------------
		size = CalcSize (TRUE);

		size.cy = rect.Height () - rectClient.Height() / 2;
		size.cx -= rectClient.Width();
	}

	//--------------------------------------------------
	// Something may changed, rebuild acceleration keys:
	//--------------------------------------------------
	RebuildAccelerationKeys ();
	
	return size;
}
//***************************************************************************************
void CBCGMenuBar::SetMaximizeMode (BOOL bMax, CWnd* pWnd)
{
	if (m_bMaximizeMode == bMax ||
		(bMax && IsCustomizeMode ()))
	{
		return;
	}

	if (bMax)
	{
		if (pWnd == NULL)
		{
			bMax = FALSE;
		}
		else
		{
            // get the sys menu.
			m_hSysMenu = pWnd->GetSystemMenu (FALSE)->GetSafeHmenu ();

            // If we have a system menu, then add a system menu button.
            if (m_hSysMenu != NULL)
            {
				m_hSysIcon = pWnd->GetIcon (FALSE);
				if (m_hSysIcon == NULL)
				{
					m_hSysIcon = (HICON) GetClassLong (*pWnd, GCL_HICONSM);
				}

                CBCGToolbarSystemMenuButton button (m_hSysMenu, m_hSysIcon);
                InsertButton (button, 0);
            }

            LONG style = ::GetWindowLong(*pWnd, GWL_STYLE);

            // Assume no buttons.
            m_nSystemButtonsNum = 0;

            // Add a minimize box if required.
            if (style & WS_MINIMIZEBOX)
            {
			    InsertButton (CBCGToolbarMenuButtonsButton (SC_MINIMIZE));
                m_nSystemButtonsNum++;
            }

            // Add a restore box if required.
            if (style & WS_MAXIMIZEBOX)
            {
    			InsertButton (CBCGToolbarMenuButtonsButton (SC_RESTORE));
                m_nSystemButtonsNum++;
            }

            // Add a close box if required.
            if (m_hSysMenu != NULL)
            {
			    InsertButton (CBCGToolbarMenuButtonsButton (SC_CLOSE));
                m_nSystemButtonsNum++;
            }
		}
	}
	else
	{
        // Remove first button if a system menu was added.
        if (m_hSysMenu != NULL)
        {
		    RemoveButton (0);
        }

		for (int i = 0; i < m_nSystemButtonsNum; i ++)
		{
			CBCGToolbarMenuButtonsButton* pButton = 
				(CBCGToolbarMenuButtonsButton*) m_Buttons.RemoveTail ();
			ASSERT_KINDOF (CBCGToolbarMenuButtonsButton, pButton);
			delete pButton;
		}
        // Now we habe no system buttons on the menu.
        m_nSystemButtonsNum = 0;
	}

	m_bMaximizeMode = bMax;
	AdjustLayout ();
}
//***************************************************************************************
void CBCGMenuBar::RestoreMaximizeMode ()
{
	if (m_bMaximizeMode)
	{
		return;
	}

	CBCGToolbarSystemMenuButton button (m_hSysMenu, m_hSysIcon);
	InsertButton (button, 0);
	
	InsertButton (CBCGToolbarMenuButtonsButton (SC_MINIMIZE));
	InsertButton (CBCGToolbarMenuButtonsButton (SC_RESTORE));
	InsertButton (CBCGToolbarMenuButtonsButton (SC_CLOSE));

	m_bMaximizeMode = TRUE;
	m_nSystemButtonsNum = m_nSystemButtonsNumSaved;

	GetParentFrame ()->RecalcLayout ();

	Invalidate ();
	UpdateWindow ();
}
//***************************************************************************************
void CBCGMenuBar::AdjustLocations ()
{
	CBCGToolBar::AdjustLocations ();

	if (!m_bMaximizeMode)
	{
		Invalidate ();
		UpdateWindow ();
		return;
	}

	CRect rectClient;
	GetClientRect (&rectClient);
	
	BOOL bHorz = m_dwStyle & CBRS_ORIENT_HORZ ? TRUE : FALSE;

	int iButtonWidth = ::GetSystemMetrics (SM_CXSIZE);
	int iButtonHeight = ::GetSystemMetrics (SM_CYSIZE);

	POSITION pos = m_Buttons.GetTailPosition ();
	CRect rect = rectClient;
	
	rectClient.SetRectEmpty ();
	CalcInsideRect (rectClient, bHorz);

	if (!bHorz)
	{
		rect.bottom += rectClient.Height ();
	}

	CClientDC dc (this);

	for (int i = 0; i < m_nSystemButtonsNum; i ++)
	{
		ASSERT (pos != NULL);

		CBCGToolbarMenuButtonsButton* pButton = 
			(CBCGToolbarMenuButtonsButton*) m_Buttons.GetPrev (pos);
		ASSERT_KINDOF (CBCGToolbarMenuButtonsButton, pButton);

		if (i == 0)
		{
			rect.left = rect.right - iButtonWidth;
			rect.top = rect.bottom - iButtonHeight;

			dc.DrawFrameControl (rect, DFC_CAPTION, DFCS_ADJUSTRECT);

			iButtonWidth = rect.Width ();
			iButtonHeight = rect.Height ();
		}

		pButton->m_rect = rect;

		if (bHorz)
		{
			rect.OffsetRect (-iButtonWidth - 1, 0);
		}
		else
		{
			rect.OffsetRect (0, -iButtonHeight - 1);
		}
	}

	Invalidate ();
	UpdateWindow ();
}
//***************************************************************************************
BOOL CBCGMenuBar::OnSendCommand (const CBCGToolbarButton* pButton)
{
	CBCGToolbarMenuButtonsButton* pSysButton =
		DYNAMIC_DOWNCAST (CBCGToolbarMenuButtonsButton, pButton);
	if (pSysButton == NULL)
	{
		return FALSE;
	}

	if (pSysButton->m_uiSystemCommand != SC_CLOSE &&
		pSysButton->m_uiSystemCommand != SC_MINIMIZE &&
		pSysButton->m_uiSystemCommand != SC_RESTORE)
	{
		ASSERT (FALSE);
		return TRUE;
	}

	CMDIFrameWnd* pParentFrame = 
		DYNAMIC_DOWNCAST (CMDIFrameWnd, m_pParentWnd);

	if (pParentFrame == NULL)
	{
		MessageBeep ((UINT) -1);
		return TRUE;
	}
		
	CMDIChildWnd* pChild = pParentFrame->MDIGetActive ();
	ASSERT_VALID (pChild);

	pChild->SendMessage (WM_SYSCOMMAND, pSysButton->m_uiSystemCommand);
	return TRUE;
}
//*************************************************************************************
int CBCGMenuBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	ASSERT_VALID(this);

	int nHit = ((CBCGMenuBar*)this)->HitTest(point);
	if (nHit != -1)
	{
		CBCGToolbarButton* pButton = GetButton (nHit);
		if (pButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarMenuButton)))
		{
			//-----------------------------------	
			// Don't show tooltips on menu items!
			//-----------------------------------
			return -1;
		}
	}

	return CBCGToolBar::OnToolHitTest (point, pTI);
}
//*************************************************************************************
int CBCGMenuBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	//------------------------------------
	// Attach menubar to the parent frame:
	//------------------------------------

	//----------------------
	// First, try MDI frame:
	//----------------------
	CBCGMDIFrameWnd* pWndParentMDIFrame = 
		DYNAMIC_DOWNCAST (CBCGMDIFrameWnd, m_pParentWnd);
	if (pWndParentMDIFrame != NULL)
	{
		pWndParentMDIFrame->m_Impl.SetMenuBar (this);
	}
	else
	{
		CBCGFrameWnd* pWndParentFrame = 
			DYNAMIC_DOWNCAST (CBCGFrameWnd, m_pParentWnd);
		if (pWndParentFrame != NULL)
		{
			pWndParentFrame->m_Impl.SetMenuBar (this);
		}
		else
		{
			CBCGOleIPFrameWnd* pOleFrame = 
				DYNAMIC_DOWNCAST (CBCGOleIPFrameWnd, AfxGetMainWnd ());
			if (pOleFrame != NULL)
			{
				pOleFrame->m_Impl.SetMenuBar (this);
			}
		}
	}

	//----------------------------
	// Set default menu bar title:
	//----------------------------
	CBCGLocalResource locaRes;

	CString strTitle;
	strTitle.LoadString (IDS_BCGBARRES_MENU_BAR_TITLE);
		
	SetWindowText (strTitle);

	//-------------------------------------------------------------
	// Force the menu bar to be hiden whren the in-place editing is
	// is activated (server application shows its own menu):
	//-------------------------------------------------------------
	SetBarStyle (GetBarStyle() | CBRS_HIDE_INPLACE);
	return 0;
}
//*************************************************************************************
BOOL CBCGMenuBar::LoadState (LPCTSTR lpszProfileName, int nIndex)
{
	ASSERT (m_hDefaultMenu != NULL);

	//------------------------------------------------------------
	// Save current maximize mode (system buttons are not saved!):
	//------------------------------------------------------------
	BOOL bMaximizeMode = m_bMaximizeMode;
	SetMaximizeMode (FALSE);

	CDocManager* pDocManager = AfxGetApp ()->m_pDocManager;
	if (pDocManager != NULL)
	{
		//---------------------------------------
		// Walk all templates in the application:
		//---------------------------------------
		for (POSITION pos = pDocManager->GetFirstDocTemplatePosition (); pos != NULL;)
		{
			CBCGMultiDocTemplate* pTemplate = 
				(CBCGMultiDocTemplate*) pDocManager->GetNextDocTemplate (pos);
			ASSERT_VALID (pTemplate);
			ASSERT_KINDOF (CDocTemplate, pTemplate);

			//-----------------------------------------------------
			// We are interessing CMultiDocTemplate objects with
			// the sahred menu only....
			//-----------------------------------------------------
			if (!pTemplate->IsKindOf (RUNTIME_CLASS (CMultiDocTemplate)) ||
				pTemplate->m_hMenuShared == NULL)
			{
				continue;
			}

			UINT uiMenuResId = pTemplate->GetResId ();
			ASSERT (uiMenuResId != 0);

			//---------------------------------------------------------------
			// Load menubar from registry and associate it with the
			// template shared menu:
			//---------------------------------------------------------------
			if (CBCGToolBar::LoadState (lpszProfileName, nIndex, uiMenuResId))
			{
				g_menuHash.SaveMenuBar (pTemplate->m_hMenuShared, this);
			}
		}
	}

	//----------------------
	// Load defualt menubar:
	//----------------------
	if (CBCGToolBar::LoadState (lpszProfileName, nIndex, 0))
	{
		g_menuHash.SaveMenuBar (m_hDefaultMenu, this);
	}

	//----------------------
	// Restore current menu:
	//----------------------
	if (bMaximizeMode)
	{
		RestoreMaximizeMode ();
	}

	if (m_hMenu != NULL && g_menuHash.LoadMenuBar (m_hMenu, this))
	{
		GetParentFrame ()->RecalcLayout ();
		Invalidate ();
		UpdateWindow ();
	}

	return TRUE;
}
//*************************************************************************************
BOOL CBCGMenuBar::SaveState (LPCTSTR lpszProfileName, int nIndex)
{
	ASSERT (m_hDefaultMenu != NULL);

	g_menuHash.SaveMenuBar (m_hMenu, this);

	//------------------------------------------------------------
	// Save current maximize mode (system buttons are not saved!):
	//------------------------------------------------------------
	BOOL bMaximizeMode = m_bMaximizeMode;
	SetMaximizeMode (FALSE);

	CDocManager* pDocManager = AfxGetApp ()->m_pDocManager;
	if (pDocManager != NULL)
	{
		//---------------------------------------
		// Walk all templates in the application:
		//---------------------------------------
		for (POSITION pos = pDocManager->GetFirstDocTemplatePosition (); pos != NULL;)
		{
			CBCGMultiDocTemplate* pTemplate = 
				(CBCGMultiDocTemplate*) pDocManager->GetNextDocTemplate (pos);
			ASSERT_VALID (pTemplate);
			ASSERT_KINDOF (CDocTemplate, pTemplate);

			//-----------------------------------------------------
			// We are interessing CMultiDocTemplate objects with
			// the sahred menu only....
			//-----------------------------------------------------
			if (!pTemplate->IsKindOf (RUNTIME_CLASS (CMultiDocTemplate)) ||
				pTemplate->m_hMenuShared == NULL)
			{
				continue;
			}

			UINT uiMenuResId = pTemplate->GetResId ();
			ASSERT (uiMenuResId != 0);

			//----------------------------------------------------------
			// Load menubar associated with the template shared menu and
			// save it in the registry:
			//----------------------------------------------------------
			if (g_menuHash.LoadMenuBar (pTemplate->m_hMenuShared, this))
			{
				CBCGToolBar::SaveState (lpszProfileName, nIndex, uiMenuResId);
			}
		}
	}

	//-------------------
	// Save default menu:
	//-------------------
	if (g_menuHash.LoadMenuBar (m_hDefaultMenu, this))
	{
		CBCGToolBar::SaveState (lpszProfileName, nIndex, 0);
	}

	//----------------------
	// Restore current menu:
	//----------------------
	if (m_hMenu != NULL && g_menuHash.LoadMenuBar (m_hMenu, this))
	{
		GetParentFrame ()->RecalcLayout ();
		Invalidate ();
		UpdateWindow ();
	}

	if (bMaximizeMode)
	{
		RestoreMaximizeMode ();
	}

	return TRUE;
}
//*****************************************************************************************
void CBCGMenuBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int iHit = HitTest (point);

	//--------------------------------------------------------
	// Disable control bar dragging if any menues are dropped!
	//--------------------------------------------------------
	if (iHit < 0 &&	// Click outside of buttons
		GetDroppedDownMenu () != NULL)
	{
//		Do nothing
	}
	else
	{		
		CBCGToolBar::OnLButtonDown(nFlags, point);
	}
}
//****************************************************************************************
BOOL CBCGMenuBar::TranslateChar (UINT nChar)
{
	UINT nUpperChar = toupper (nChar);

	CBCGToolbarButton* pButton;
	if (!m_AcellKeys.Lookup (nUpperChar, pButton))
	{
		return FALSE;
	}

	return DropDownMenu (pButton);
}
//****************************************************************************************
void CBCGMenuBar::OnCustomizeMode (BOOL bSet)
{
	if (bSet)
	{
		m_bActualMaximizeMode = m_bMaximizeMode;
		m_nSystemButtonsNumSaved = m_nSystemButtonsNum;
		SetMaximizeMode (FALSE);
	}
	else
	{
		if (m_bActualMaximizeMode)
		{
			RestoreMaximizeMode ();
		}
	}

	CBCGToolBar::OnCustomizeMode (bSet);
}
//****************************************************************************************
BOOL CBCGMenuBar::RestoreOriginalstate ()
{
	ASSERT (m_hMenu != NULL);
	HMENU hMenuCurr = m_hMenu;
	g_menuHash.SaveMenuBar (m_hMenu, this);

	BOOL bCurrMenuIsRestored = FALSE;

	//------------------------------------------------------------
	// Save current maximize mode (system buttons are not saved!):
	//------------------------------------------------------------
	BOOL bMaximizeMode = m_bMaximizeMode;
	SetMaximizeMode (FALSE);

	CDocManager* pDocManager = AfxGetApp ()->m_pDocManager;
	if (pDocManager != NULL)
	{
		//---------------------------------------
		// Walk all templates in the application:
		//---------------------------------------
		for (POSITION pos = pDocManager->GetFirstDocTemplatePosition (); pos != NULL;)
		{
			CBCGMultiDocTemplate* pTemplate = 
				(CBCGMultiDocTemplate*) pDocManager->GetNextDocTemplate (pos);
			ASSERT_VALID (pTemplate);
			ASSERT_KINDOF (CDocTemplate, pTemplate);

			//-----------------------------------------------------
			// We are interessing CMultiDocTemplate objects with
			// the shared menu only....
			//-----------------------------------------------------
			if (!pTemplate->IsKindOf (RUNTIME_CLASS (CMultiDocTemplate)) ||
				pTemplate->m_hMenuShared == NULL)
			{
				continue;
			}

			UINT uiMenuResId = pTemplate->GetResId ();
			ASSERT (uiMenuResId != 0);

			//-------------------------------------
			// Restore original menu from resource:
			//-------------------------------------
			HINSTANCE hInst = AfxFindResourceHandle (
				MAKEINTRESOURCE (uiMenuResId), RT_MENU);

			BOOL bCurr = (hMenuCurr == pTemplate->m_hMenuShared);
			pTemplate->m_hMenuShared = ::LoadMenu (hInst, MAKEINTRESOURCE (uiMenuResId));

			CreateFromMenu (pTemplate->m_hMenuShared, FALSE);
			g_menuHash.SaveMenuBar (pTemplate->m_hMenuShared, this);

			if (bCurr)
			{
				hMenuCurr = pTemplate->m_hMenuShared;
				bCurrMenuIsRestored = TRUE;
			}
		}
	}

	//----------------------
	// Load defualt menubar:
	//----------------------
	if (m_uiDefMenuResId != 0)
	{
		HINSTANCE hInst = AfxFindResourceHandle (
			MAKEINTRESOURCE (m_uiDefMenuResId), RT_MENU);

		m_hDefaultMenu = ::LoadMenu (hInst, MAKEINTRESOURCE (m_uiDefMenuResId));

		CreateFromMenu (m_hDefaultMenu, TRUE);
		g_menuHash.SaveMenuBar (m_hDefaultMenu, this);

		if (!bCurrMenuIsRestored)
		{
			hMenuCurr = m_hDefaultMenu;
		}
	}

	//----------------------
	// Restore current menu:
	//----------------------
	if (bMaximizeMode)
	{
		RestoreMaximizeMode ();
	}

	if (g_menuHash.LoadMenuBar (hMenuCurr, this))
	{
		m_hMenu = hMenuCurr;
		GetParentFrame ()->RecalcLayout ();
		Invalidate ();
		UpdateWindow ();
	}

	return TRUE;
}
//********************************************************************************************
void CBCGMenuBar::SetDefaultMenuResId (UINT uiResId)
{
	m_uiDefMenuResId = uiResId;
}
//******************************************************************
BOOL CBCGMenuBar::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		//-----------------------------------------------------------
		// Fisrt, try to move keyboard control to the drop-down menu:
		//-----------------------------------------------------------
		CBCGToolbarMenuButton* pMenuButon = GetDroppedDownMenu ();
		if (pMenuButon != NULL)
		{
			return CControlBar::PreTranslateMessage(pMsg);
		}

		int iTotalItems = GetCount ();
		if (m_bMaximizeMode)
		{
			iTotalItems -= m_nSystemButtonsNum;
		}

		if (m_iHighlighted >= 0 && m_iHighlighted < iTotalItems)
		{
			int iButton = m_iHighlighted;

			switch (pMsg->wParam)
			{
			case VK_ESCAPE:
				{
					Deactivate ();
/*					if (m_pParentWnd != NULL)
					{
						CMDIFrameWnd* pParentFrame = DYNAMIC_DOWNCAST (CMDIFrameWnd, m_pParentWnd);
						CMDIChildWnd* pChild;
						if (pParentFrame != NULL && 
							(pChild = pParentFrame->MDIGetActive ()) != NULL)
						{
							pChild->SetFocus ();	
						}
						else
						{
							GetOwner ()->SetFocus ();
						}
					}*/
					RestoreFocus ();
				}
				break;

			case VK_RIGHT:
				if (++ m_iHighlighted >= iTotalItems)
				{
					m_iHighlighted = 0;
				}

				InvalidateButton (iButton);
				InvalidateButton (m_iHighlighted);
				UpdateWindow ();
				break;

			case VK_LEFT:
				if (-- m_iHighlighted < 0)
				{
					m_iHighlighted = iTotalItems - 1;
				}

				InvalidateButton (iButton);
				InvalidateButton (m_iHighlighted);
				UpdateWindow ();
				break;

			case VK_DOWN:
			case VK_RETURN:
				DropDownMenu (GetButton (m_iHighlighted));
				return TRUE;

			default:
				if (TranslateChar ((int) pMsg->wParam))
				{
					return TRUE;
				}
			}
		}
	}

	return CControlBar::PreTranslateMessage(pMsg);
}
//**************************************************************************************
void CBCGMenuBar::OnKillFocus(CWnd* pNewWnd) 
{
	CBCGToolBar::OnKillFocus(pNewWnd);

	if (!IsCustomizeMode ())
	{
		CBCGPopupMenu* pMenu = DYNAMIC_DOWNCAST	(CBCGPopupMenu, pNewWnd);
		if (pMenu == NULL || pMenu->GetParentToolBar () != this)
		{
			Deactivate ();
		}
	}
}
//**************************************************************************************
void CBCGMenuBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGToolBar::OnSetFocus(pOldWnd);
	GetOwner()->SendMessage (WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);

	if (m_iHighlighted < 0 && GetCount () > 0)
	{
		m_iHighlighted = 0;
		InvalidateButton (0);
	}
}
//**************************************************************************************
BOOL CBCGMenuBar::Create(CWnd* pParentWnd,
			DWORD dwStyle,
			UINT nID)
{
	m_pParentWnd = pParentWnd;
	return CBCGToolBar::Create (pParentWnd, dwStyle, nID);
}
//***************************************************************************************
LRESULT CALLBACK CBCGMenuBar::BCGMenuBarMouseProc (int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT* lpMS = (MOUSEHOOKSTRUCT*) lParam;
	ASSERT (lpMS != NULL);

	if (wParam == WM_LBUTTONUP || wParam == WM_NCLBUTTONUP)
	{
		if (m_pDraggedMenuBar != NULL &&
			m_pDraggedMenuBar->m_pDockContext != NULL &&
			m_pDraggedMenuBar->m_pDockContext->m_bDragging)
		{
			//------------------------------------------------------------------------
			// End of dragging. Don't allow the menubar to be docked on the right side
			// of any control bars!
			//------------------------------------------------------------------------
			m_pDraggedMenuBar->m_pDockContext->m_rectDragVert.top = 0;
			m_pDraggedMenuBar->m_pDockContext->m_rectDragHorz.left = 0;

			m_pDraggedMenuBar->SetDragMode (FALSE);
		}
	}

	return CallNextHookEx (m_hookMouseDrag, nCode, wParam, lParam);
}
//************************************************************************************************
void CBCGMenuBar::SetDragMode (BOOL bOn)
{
	if (bOn)
	{
		if (m_hookMouseDrag == NULL)	// Not installed yet, set it now!
		{
			m_hookMouseDrag = ::SetWindowsHookEx (WH_MOUSE, BCGMenuBarMouseProc, 
				0, GetCurrentThreadId ());
			if (m_hookMouseDrag == NULL)
			{
				TRACE (_T("CBCGMenuBar: Can't set mouse hook!\n"));
				return;
			}
		}

		m_pDraggedMenuBar = this;
	}
	else
	{
		 if (m_hookMouseDrag != NULL)
		 {
			::UnhookWindowsHookEx (m_hookMouseDrag);
			m_hookMouseDrag = NULL;
		}

		m_pDraggedMenuBar = NULL;
	}
}
//************************************************************************************************
void CBCGMenuBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos)
{
	CBCGToolBar::OnWindowPosChanged(lpwndpos);
	SetDragMode (FALSE);
}
//*****************************************************************************************
CSize CBCGMenuBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	if (m_Buttons.IsEmpty ())
	{
		return m_sizeButton;
	}

	DWORD dwMode = bStretch ? LM_STRETCH : 0;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout (dwMode);
}
//*****************************************************************************************
BOOL CBCGMenuBar::OnSetDefaultButtonText (CBCGToolbarButton* pButton)
{
	ASSERT_VALID (pButton);

	CString strText;
	if (FindMenuItemText (m_hMenu, pButton->m_nID, strText))
	{
		pButton->m_strText = strText;
		return TRUE;
	}

	return CBCGToolBar::OnSetDefaultButtonText (pButton);
}
//****************************************************************************************
BOOL CBCGMenuBar::FindMenuItemText (HMENU hMenu, const UINT nItemID, CString& strOutText)
{
	if (hMenu == NULL || nItemID == 0 || nItemID == (UINT) -1)
	{
		return FALSE;
	}

	CMenu* pMenu = CMenu::FromHandle (hMenu);
	if (pMenu == NULL)
	{
		return FALSE;
	}

	int iCount = (int) pMenu->GetMenuItemCount ();
	for (int i = 0; i < iCount; i ++)
	{
		UINT uiID = pMenu->GetMenuItemID (i);
		if (uiID == nItemID)	// Found!
		{
			pMenu->GetMenuString (i, strOutText, MF_BYPOSITION);
			return TRUE;
		}
		else if (uiID == -1)	// Pop-up menu
		{
			CMenu* pPopupMenu = pMenu->GetSubMenu (i);
			ASSERT (pPopupMenu != NULL);

			if (FindMenuItemText (pPopupMenu->GetSafeHmenu (), nItemID, strOutText))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}
//*****************************************************************************************
BOOL CBCGMenuBar::PrevMenu ()
{
	int iHot;
	CBCGToolbarMenuButton* pCurrPopupMenu = GetDroppedDownMenu (&iHot);
	if (pCurrPopupMenu == NULL)
	{
		return FALSE;
	}

	int iTotalItems = GetCount ();
	if (m_bMaximizeMode)
	{
		iTotalItems -= m_nSystemButtonsNum;
	}

	if ( --iHot < 0)
	{
		iHot = iTotalItems - 1;
	}

	OnChangeHot (iHot);

	//-----------------------
	// Select the first item:
	//-----------------------
	if (m_iHot >= 0)
	{
		CBCGToolbarMenuButton* pMenuButton =
			DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, GetButton (m_iHot));
		if (pMenuButton != NULL && pMenuButton->m_pPopupMenu != NULL)
		{
			pMenuButton->m_pPopupMenu->SendMessage (WM_KEYDOWN, VK_HOME);
		}
	}

	return TRUE;
}
//*****************************************************************************************
BOOL CBCGMenuBar::NextMenu ()
{
	int iHot;
	CBCGToolbarMenuButton* pCurrPopupMenu = GetDroppedDownMenu (&iHot);
	if (pCurrPopupMenu == NULL)
	{
		return FALSE;
	}

	int iTotalItems = GetCount ();
	if (m_bMaximizeMode)
	{
		iTotalItems -= m_nSystemButtonsNum;
	}

	if (++ iHot >= iTotalItems)
	{
		iHot = 0;
	}

	OnChangeHot (iHot);

	//-----------------------
	// Select the first item:
	//-----------------------
	if (m_iHot >= 0)
	{
		CBCGToolbarMenuButton* pMenuButton =
			DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, GetButton (m_iHot));
		if (pMenuButton != NULL && pMenuButton->m_pPopupMenu != NULL)
		{
			pMenuButton->m_pPopupMenu->SendMessage (WM_KEYDOWN, VK_HOME);
		}
	}

	return TRUE;
}
//******************************************************************************************
int CBCGMenuBar::FindDropIndex (const CPoint point, CRect& rectDrag) const
{
	int iIndex = CBCGToolBar::FindDropIndex (point, rectDrag);
	if (m_bMaximizeMode && iIndex >= 0)
	{
		//--------------------------------------
		// Maybe drag left from the system icon?
		//--------------------------------------
		if (iIndex == 0)
		{
			return -1;
		}

		//-----------------------------------------
		// Maybe drag right of the system buttons?
		//-----------------------------------------
		if (iIndex > GetCount () - m_nSystemButtonsNum)
		{
			iIndex = GetCount () - m_nSystemButtonsNum;
		}
	}

	return iIndex;
}

