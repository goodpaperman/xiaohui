// BCGPopupMenuBar.cpp : implementation file
//

#include "stdafx.h"
#include <afxpriv.h>

#pragma warning (disable : 4201)
	#include "mmsystem.h"
#pragma warning (default : 4201)

#include "BCGPopupMenuBar.h"
#include "BCGToolbarButton.h"
#include "BCGToolbarMenuButton.h"
#include "BCGPopupMenu.h"
#include "ImageHash.h"
#include "globals.h"
#include "BCGToolbarMenuButton.h"
#include "bcgbarres.h"
#include "bcglocalres.h"
#include "BCGMenuBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int iVertMargin = 1;
static const int iHorzMargin = 1;
static const int SEPARATOR_WIDTH = 8;
static const int iMinTabSpace = 10;
static const int iEmptyMenuWidth = 50;
static const int iEmptyMenuHeight = 20;

static const int uiPopupTimerEvent = 1;
static const int uiPopupTimerDelay = 500;

/////////////////////////////////////////////////////////////////////////////
// CBCGPopupMenuBar

IMPLEMENT_SERIAL(CBCGPopupMenuBar, CBCGToolBar, 1)

CBCGPopupMenuBar::CBCGPopupMenuBar() :
	m_uiDefaultMenuCmdId (0),
	m_pDelayedPopupMenuButton (NULL),
	m_bFirstClick (TRUE),
	m_iOffset (0)
{
	m_bMenuMode = TRUE;
}

CBCGPopupMenuBar::~CBCGPopupMenuBar()
{
}


BEGIN_MESSAGE_MAP(CBCGPopupMenuBar, CBCGToolBar)
	//{{AFX_MSG_MAP(CBCGPopupMenuBar)
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPopupMenuBar message handlers

BOOL CBCGPopupMenuBar::OnSendCommand (const CBCGToolbarButton* pButton)
{
	ASSERT_VALID (pButton);

	if ((pButton->m_nStyle & TBBS_DISABLED) != 0 ||
		pButton->m_nID < 0 || pButton->m_nID == (UINT)-1)
	{
		return FALSE;
	}

	CBCGToolbarMenuButton* pMenuButton = 
		DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pButton);
	if (pMenuButton != NULL && pMenuButton->m_pPopupMenu != NULL)
	{
		return FALSE;
	}

	//--------------------
	// Deactivate menubar:
	//--------------------
	CBCGPopupMenu* pParentMenu = DYNAMIC_DOWNCAST (CBCGPopupMenu, GetParent ());
	if (pParentMenu != NULL)
	{
		CBCGToolBar* pToolBar = pParentMenu->GetParentToolBar ();
		if (pToolBar != NULL)
		{
			pToolBar->Deactivate ();
		}
	}

	//----------------------------------
	// Play standard menu command sound!
	//----------------------------------
	PlaySound (_T("MenuCommand"), NULL, SND_ASYNC | SND_NODEFAULT);

	//----------------------------------
	// Send command to the parent frame:
	//----------------------------------
	CFrameWnd* pParentFrame = GetParentFrame ();
	ASSERT_VALID (pParentFrame);

	GetOwner()->PostMessage(WM_COMMAND, pButton->m_nID);
	pParentFrame->DestroyWindow ();

	return TRUE;
}
//***************************************************************
void CBCGPopupMenuBar::AdjustLocations ()
{
	if (GetSafeHwnd () == NULL ||
		!::IsWindow (m_hWnd))
	{
		return;
	}

	ASSERT_VALID(this);

	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	CClientDC dc (this);
	CFont* pOldFont = (CFont*) dc.SelectObject (&globalData.fontRegular);
	ASSERT (pOldFont != NULL);

	int y = rectClient.top + iVertMargin - m_iOffset * GetRowHeight ();

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		int iHeight;
		if (pButton->m_nStyle & TBBS_SEPARATOR)
		{
			iHeight = SEPARATOR_WIDTH;
		}
		else
		{
			iHeight = GetRowHeight ();
		}

		CRect rectButton;
		rectButton.left = rectClient.left;
		rectButton.right = rectClient.right;
		rectButton.top = y;
		rectButton.bottom = rectButton.top + iHeight;

		if (pButton->m_rect != rectButton)
		{
			pButton->m_rect = rectButton;
			pButton->OnMove ();
		}

		y += iHeight;
	}

	dc.SelectObject (pOldFont);

	//--------------------------------------------------
	// Something may changed, rebuild acceleration keys:
	//--------------------------------------------------
	RebuildAccelerationKeys ();
}
//***************************************************************************************
void CBCGPopupMenuBar::DrawSeparator (CDC* pDC, const CRect& rect, BOOL /*bHorz*/)
{
	CRect rectSeparator = rect;

	rectSeparator.top += rectSeparator.Height () / 2;
	rectSeparator.bottom = rectSeparator.top + 2;

	pDC->Draw3dRect (rectSeparator, globalData.clrBtnShadow,
									globalData.clrBtnHilite);
}
//***************************************************************************************
CSize CBCGPopupMenuBar::CalcSize ()
{
	CSize size (0, 0);

	CClientDC dc (this);
	CFont* pOldFont = (CFont*) dc.SelectObject (&globalData.fontRegular);
	ASSERT (pOldFont != NULL);

	if (m_Buttons.IsEmpty ())
	{
		size = CSize (iEmptyMenuWidth, iEmptyMenuHeight);
	}
	else
	{
		for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
			ASSERT (pButton != NULL);

			CSize sizeButton = pButton->OnCalculateSize (&dc, 
				GetMenuButtonSize (), TRUE);

			int iHeight;
			if (pButton->m_nStyle & TBBS_SEPARATOR)
			{
				iHeight = SEPARATOR_WIDTH;
			}
			else
			{
				iHeight = GetRowHeight ();

				if (pButton->IsDrawText () &&
					pButton->m_strText.Find (_T('\t')) > 0)
				{
					sizeButton.cx += iMinTabSpace;
				}

				size.cx = max (sizeButton.cx, size.cx);

			}

			size.cy += iHeight;
		}
	}

	size.cy += 2 * iVertMargin;
	size.cx += 2 * iHorzMargin;

	dc.SelectObject (pOldFont);
	return size;
}
//***************************************************************************************
void CBCGPopupMenuBar::OnNcPaint() 
{
	//--------------------------------------
	// Disable gripper and borders painting!
	//--------------------------------------
}
//***************************************************************************************
void CBCGPopupMenuBar::OnNcCalcSize(BOOL /*bCalcValidRects*/, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	//-----------------------------------------------
	// Don't leave space for the gripper and borders!
	//-----------------------------------------------
	lpncsp->rgrc [0].right -= iHorzMargin;
}
//***************************************************************************************
int CBCGPopupMenuBar::GetRowHeight () const
{
	return GetMenuButtonSize ().cy - 3;
}
//****************************************************************************************
void CBCGPopupMenuBar::DrawDragMarker (CDC* pDC)
{
	CPen* pOldPen = (CPen*) pDC->SelectObject (&m_penDrag);

	for (int i = 0; i < 2; i ++)
	{
		pDC->MoveTo (m_rectDrag.left, m_rectDrag.top + m_rectDrag.Height () / 2 + i - 1);
		pDC->LineTo (m_rectDrag.right, m_rectDrag.top + m_rectDrag.Height () / 2 + i - 1);

		pDC->MoveTo (m_rectDrag.left + i, m_rectDrag.top + i);
		pDC->LineTo (m_rectDrag.left + i, m_rectDrag.bottom - i);

		pDC->MoveTo (m_rectDrag.right - i - 1, m_rectDrag.top + i);
		pDC->LineTo (m_rectDrag.right - i - 1, m_rectDrag.bottom - i);
	}

	pDC->SelectObject (pOldPen);
}
//********************************************************************************
int CBCGPopupMenuBar::FindDropIndex (const CPoint p, CRect& rectDrag) const
{
	const int iCursorSize = 6;

	GetClientRect (&rectDrag);

	if (m_Buttons.IsEmpty ())
	{
		rectDrag.bottom = rectDrag.top + iCursorSize;
		return 0;
	}

	CPoint point = p;
	if (point.y < 0)
	{
		point.y = 0;
	}

	int iDragButton = -1;
	int iIndex = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; iIndex ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		CRect rect = pButton->m_rect;
		if (point.y < rect.top)
		{
			iDragButton = iIndex;
			rectDrag.top = rect.top;
			break;
		}
		else if (point.y <= rect.bottom)
		{
			rectDrag = rect;
			if (point.y - rect.top > rect.bottom - point.y)
			{
				iDragButton = iIndex + 1;
				rectDrag.top = rectDrag.bottom;
			}
			else
			{
				iDragButton = iIndex;
				rectDrag.top = rect.top;
			}
			break;
		}
	}

	if (iDragButton == -1)
	{
		rectDrag.top = rectDrag.bottom - iCursorSize;
		iDragButton = iIndex;
	}

	rectDrag.bottom = rectDrag.top + iCursorSize;
	rectDrag.OffsetRect (0, -iCursorSize / 2);

	return iDragButton;
}
//***************************************************************************************
CBCGToolbarButton* CBCGPopupMenuBar::CreateDroppedButton (COleDataObject* pDataObject)
{
	CBCGToolbarButton* pButton = CBCGToolbarButton::CreateFromOleData (pDataObject);
	ASSERT (pButton != NULL);

	CBCGToolbarMenuButton* pMenuButton = 
		DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pButton);

	if (pMenuButton == NULL)
	{
		pMenuButton = new CBCGToolbarMenuButton (
			pButton->m_nID, NULL, pButton->GetImage (), pButton->m_strText,
			pButton->m_bUserButton);
		ASSERT (pMenuButton != NULL);

		pMenuButton->m_bText = TRUE;
		pMenuButton->m_bImage = TRUE;

		//-----------------------------------------------------
		// Text may be undefined, bring it from the tooltip :-(
		//-----------------------------------------------------
		if (pMenuButton->m_strText.IsEmpty () && pMenuButton->m_nID != 0)
		{
			CString strMessage;
			int iOffset;
			if (strMessage.LoadString (pMenuButton->m_nID) &&
				(iOffset = strMessage.Find (_T('\n'))) != -1)
			{
				pMenuButton->m_strText = strMessage.Mid (iOffset + 1);
			}
		}

		delete pButton;
		
		if (pMenuButton->m_strText.IsEmpty ())
		{
			delete pMenuButton;
			return NULL;
		}
	}

	return pMenuButton;
}
//****************************************************************************************
BOOL CBCGPopupMenuBar::ImportFromMenu (HMENU hMenu)
{
	RemoveAllButtons ();

	if (hMenu == NULL)
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
		UINT uiCmd = pMenu->GetMenuItemID (i);
		UINT uiState = pMenu->GetMenuState (i, MF_BYPOSITION);

		HMENU hSubMenu = NULL;

		CString strText;
		pMenu->GetMenuString (i, strText, MF_BYPOSITION);

		switch (uiCmd)
		{
		case 0:
			InsertSeparator ();
			break;

		case -1:
			hSubMenu = pMenu->GetSubMenu (i)->GetSafeHmenu ();
			ASSERT (hSubMenu != NULL);

		default:
			{
				CBCGToolbarMenuButton item (uiCmd, hSubMenu,
											-1, strText);
				item.m_bText = TRUE;
				item.m_bImage = FALSE;

				if (g_ImageHash.Get (uiCmd, FALSE) == -1)
				{
					item.m_bUserButton = TRUE;
				}

				int iIndex = InsertButton (item);
				if (iIndex >= 0)
				{
					CBCGToolbarButton* pButton = GetButton (iIndex);
					ASSERT (pButton != NULL);

					pButton->m_bImage = (pButton->GetImage () >= 0);

					if ((uiState & MF_DISABLED) || (uiState & MF_GRAYED))
					{
						pButton->m_nStyle |= TBBS_DISABLED;
					}

					if (uiState & MF_CHECKED)
					{
						pButton->m_nStyle |= TBBS_CHECKED;
					}
				}
			}
		}
	}

	m_uiDefaultMenuCmdId = ::GetMenuDefaultItem (hMenu, FALSE, GMDI_USEDISABLED);
	return TRUE;
}
//****************************************************************************************
HMENU CBCGPopupMenuBar::ExportToMenu () const
{
	CMenu menu;
	menu.CreatePopupMenu ();

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		if (pButton->m_nStyle & TBBS_SEPARATOR)
		{
			menu.AppendMenu (MF_SEPARATOR);
			continue;
		}

		if (!pButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarMenuButton)))
		{
			continue;
		}

		CBCGToolbarMenuButton* pMenuButton = (CBCGToolbarMenuButton*) pButton;

		HMENU hPopupMenu = pMenuButton->CreateMenu ();
		if (hPopupMenu != NULL)
		{
			menu.AppendMenu (MF_STRING | MF_POPUP, (UINT) hPopupMenu, 
							pMenuButton->m_strText);

			//--------------------------------------------------------
			// This is incompatibility between Windows 95 and 
			// NT API! (IMHO). CMenu::AppendMenu with MF_POPUP flag 
			// COPIES sub-menu resource under the Win NT and 
			// MOVES sub-menu under Win 95!
			//--------------------------------------------------------
			if (globalData.bIsWindowsNT)
			{
				::DestroyMenu (hPopupMenu);
			}
		}
		else
		{
			menu.AppendMenu (MF_STRING, pMenuButton->m_nID, pMenuButton->m_strText);
		}
	}

	HMENU hMenu = menu.Detach ();

	::SetMenuDefaultItem (hMenu, m_uiDefaultMenuCmdId, FALSE);
	return hMenu;
}
//***************************************************************************************
void CBCGPopupMenuBar::OnChangeHot (int iHot)
{
	if (iHot == -1 && !CBCGToolBar::IsCustomizeMode ())
	{
		return;
	}

	CBCGToolbarMenuButton* pCurrPopupMenu = NULL;

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		CBCGToolbarMenuButton* pMenuButton =
			DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pButton);

		if (pMenuButton != NULL && pMenuButton->IsDroppedDown ())
		{
			pCurrPopupMenu = pMenuButton;
			break;
		}
	}

	CBCGToolbarMenuButton* pMenuButton = NULL;
	if (iHot >= 0)
	{
		CBCGToolbarButton* pButton = GetButton (iHot);
		ASSERT_VALID (pButton);

		pMenuButton = DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pButton);
	}

	if (pMenuButton != pCurrPopupMenu)
	{
		if (pCurrPopupMenu != NULL)
		{
			pCurrPopupMenu->OnCancelMode ();

			CBCGPopupMenu* pParentMenu = DYNAMIC_DOWNCAST (CBCGPopupMenu, GetParent ());
			if (pParentMenu != NULL)
			{
				CBCGPopupMenu::ActivatePopupMenu (pParentMenu);
			}
		}

		if (pMenuButton != NULL && 
			(pMenuButton->m_nID == (UINT) -1 || pMenuButton->m_bDrawDownArrow))
		{
			pMenuButton->OnClick (this);
		}
	}
}
//****************************************************************************************
void CBCGPopupMenuBar::OnDestroy() 
{
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		CBCGToolbarMenuButton* pMenuButton =
			DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pButton);

		if (pMenuButton != NULL && pMenuButton->IsDroppedDown ())
		{
			CBCGPopupMenu* pMenu = pMenuButton->m_pPopupMenu;
			if (pMenu != NULL && ::IsWindow (pMenu->m_hWnd))
			{
				pMenu->SaveState ();
				pMenu->PostMessage (WM_CLOSE);
			}
		}
	}

	CBCGToolBar::OnDestroy();
}
//****************************************************************************************
BOOL CBCGPopupMenuBar::OnKey(UINT nChar)
{
	BOOL bProcessed = FALSE;

	POSITION posSel = 
		(m_iHighlighted < 0) ? NULL : m_Buttons.FindIndex (m_iHighlighted);
	CBCGToolbarButton* pOldSelButton = 
		(posSel == NULL) ? NULL : (CBCGToolbarButton*) m_Buttons.GetAt (posSel);
	CBCGToolbarButton* pNewSelButton = pOldSelButton;
	int iNewHighlight = m_iHighlighted;

	switch (nChar)
	{
	case VK_RETURN:
		{
			bProcessed = TRUE;

			// Try to cascase a popup menu and, if failed 
			CBCGToolbarMenuButton* pMenuButton = DYNAMIC_DOWNCAST (CBCGToolbarMenuButton,
							pOldSelButton);
			if (pMenuButton != NULL &&
				!pMenuButton->OpenPopupMenu ())
			{
				GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
				OnSendCommand (pMenuButton);
			}
		}
		break;

	case VK_HOME:
		posSel = NULL;
		// Like "Before first"...

	case VK_DOWN:
		//-----------------------------
		// Find next "selecteble" item:
		//-----------------------------
		{
			bProcessed = TRUE;
			if (m_Buttons.IsEmpty ())
			{
				break;
			}

			POSITION pos = posSel;
			if (pos != NULL)
			{
				m_Buttons.GetNext (pos);
			}

			if (pos == NULL)
			{
				pos = m_Buttons.GetHeadPosition ();
				iNewHighlight = 0;
			}
			else
			{
				iNewHighlight ++;
			}

			POSITION posFound = NULL;
			while (pos != posSel)
			{
				posFound = pos;

				CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
				ASSERT_VALID (pButton);

				if ((pButton->m_nStyle & TBBS_SEPARATOR) == 0)
				{
					break;
				}

				iNewHighlight ++;
				if (pos == NULL)
				{
					pos = m_Buttons.GetHeadPosition ();
					iNewHighlight = 0;
				}
			}

			if (posFound != NULL)
			{
				pNewSelButton = (CBCGToolbarButton*) m_Buttons.GetAt (posFound);
			}
		}
		break;

	case VK_END:
		posSel = NULL;
		// Like "After last"....

	case VK_UP:
		//---------------------------------
		// Find previous "selecteble" item:
		//---------------------------------
		{
			bProcessed = TRUE;
			if (m_Buttons.IsEmpty ())
			{
				break;
			}

			POSITION pos = posSel;
			if (pos != NULL)
			{
				m_Buttons.GetPrev (pos);
			}
			if (pos == NULL)
			{
				pos = m_Buttons.GetTailPosition ();
				iNewHighlight = m_Buttons.GetCount () - 1;
			}
			else
			{
				iNewHighlight --;
			}

			POSITION posFound = NULL;
			while (pos != posSel)
			{
				posFound = pos;

				CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetPrev (pos);
				ASSERT_VALID (pButton);

				if ((pButton->m_nStyle & TBBS_SEPARATOR) == 0)
				{
					break;
				}

				iNewHighlight --;
				if (pos == NULL)
				{
					pos = m_Buttons.GetTailPosition ();
					iNewHighlight = m_Buttons.GetCount () - 1;
				}
			}

			if (posFound != NULL)
			{
				pNewSelButton = (CBCGToolbarButton*) m_Buttons.GetAt (posFound);
			}
		}
		break;

	default:
		// Process acceleration key:
		{
			UINT nUpperChar = toupper (nChar);

			CBCGToolbarButton* pButton;
			if (m_AcellKeys.Lookup (nUpperChar, pButton))
			{
				ASSERT_VALID (pButton);

				pNewSelButton = pButton;

				//-------------------
				// Find button index:
				//-------------------
				int iIndex = 0;
				for (POSITION pos = m_Buttons.GetHeadPosition ();
					pos != NULL; iIndex ++)
				{
					CBCGToolbarButton* pListButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
					ASSERT (pListButton != NULL);

					if (pListButton == pButton)
					{
						iNewHighlight = iIndex;
						break;
					}
				}
				
				CBCGToolbarMenuButton* pMenuButton =
					DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pButton);

				if (pMenuButton != NULL &&
					!pMenuButton->OpenPopupMenu ())
				{
					GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
					bProcessed = OnSendCommand (pMenuButton);
					if (bProcessed)
					{
						return TRUE;
					}
				}
			}
		}
	}

	if (pNewSelButton != pOldSelButton)
	{
		ASSERT_VALID (pNewSelButton);
		ASSERT (iNewHighlight >= 0 && iNewHighlight < m_Buttons.GetCount ());
		ASSERT (GetButton (iNewHighlight) == pNewSelButton);

		//------------------------------------
		// Fixed by Sven Ritter (SpeedProject)
		//------------------------------------
		if (IsCustomizeMode ())
		{
			m_iSelected = iNewHighlight;
		}
		// --- End ---

		m_iHighlighted = iNewHighlight;

		if (pOldSelButton != NULL)
		{
			InvalidateRect (pOldSelButton->m_rect);
		}

		InvalidateRect (pNewSelButton->m_rect);
		UpdateWindow ();

		if (pNewSelButton->m_nID != (UINT) -1)
		{
			ShowCommandMessageString (pNewSelButton->m_nID);
		}
	}

	return bProcessed;
}
//**************************************************************************************
void CBCGPopupMenuBar::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == uiPopupTimerEvent)
	{
		if (m_pDelayedPopupMenuButton != NULL)
		{
			ASSERT_VALID (m_pDelayedPopupMenuButton);

			if (m_iHighlighted >= 0 &&
				m_iHighlighted < m_Buttons.GetCount () &&
				GetButton (m_iHighlighted) == m_pDelayedPopupMenuButton)
			{
				m_pDelayedPopupMenuButton->OpenPopupMenu (this);
			}

			m_pDelayedPopupMenuButton = NULL;
		}

		KillTimer (uiPopupTimerEvent);
	}
		
	CBCGToolBar::OnTimer(nIDEvent);
}
//**************************************************************************************
void CBCGPopupMenuBar::StartPopupMenuTimer (CBCGToolbarMenuButton* pMenuButton)
{
	if (m_pDelayedPopupMenuButton != NULL)
	{
		KillTimer (uiPopupTimerEvent);
	}

	if ((m_pDelayedPopupMenuButton = pMenuButton) != NULL)
	{
		SetTimer (uiPopupTimerEvent, uiPopupTimerDelay, NULL);
	}
}
//**********************************************************************************
void CBCGPopupMenuBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bFirstClick = FALSE;

	CRect rectClient;
	GetClientRect (&rectClient);

	if (!IsCustomizeMode () && 
		!rectClient.PtInRect (point))
	{
		CBCGToolBar* pDestBar = FindDestBar (point);
		if (pDestBar != NULL)
		{
			CPoint ptDest = point;
			MapWindowPoints (pDestBar, &ptDest, 1);

			pDestBar->SendMessage (	WM_LBUTTONDOWN, 
									nFlags, 
									MAKELPARAM (ptDest.x, ptDest.y));
		}
	}

	CBCGToolBar::OnLButtonDown(nFlags, point);
}
//**********************************************************************************
void CBCGPopupMenuBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rectClient;
	GetClientRect (&rectClient);

	if (!m_bFirstClick &&
		!IsCustomizeMode () && 
		!rectClient.PtInRect (point))
	{
		CBCGToolBar* pDestBar = FindDestBar (point);
		if (pDestBar != NULL)
		{
			MapWindowPoints (pDestBar, &point, 1);
			pDestBar->SendMessage (	WM_LBUTTONUP, 
									nFlags, 
									MAKELPARAM (point.x, point.y));
		}

		CFrameWnd* pParentFrame = GetParentFrame ();
		ASSERT_VALID (pParentFrame);

		pParentFrame->DestroyWindow ();
		return;
	}

	if (!IsCustomizeMode () && m_iHighlighted >= 0)
	{
		m_iButtonCapture = m_iHighlighted;
	}

	m_bFirstClick = FALSE;
	CBCGToolBar::OnLButtonUp (nFlags, point);
}
//**********************************************************************************
BOOL CBCGPopupMenuBar::OnSetDefaultButtonText (CBCGToolbarButton* pButton)
{
	ASSERT_VALID (pButton);

	CBCGPopupMenu* pParentMenu = DYNAMIC_DOWNCAST (CBCGPopupMenu, GetParent ());
	if (pParentMenu != NULL)
	{
		CBCGToolBar* pToolBar = pParentMenu->GetParentToolBar ();
		if (pToolBar != NULL && pToolBar->OnSetDefaultButtonText (pButton))
		{
			return TRUE;
		}
	}

	return CBCGToolBar::OnSetDefaultButtonText (pButton);
}
//****************************************************************************************
BOOL CBCGPopupMenuBar::EnableContextMenuItems (CBCGToolbarButton* pButton, CMenu* pPopup)
{
	if (!CBCGToolBar::IsCustomizeMode ())
	{
		// Disable context menu
		return FALSE;
	}

	ASSERT_VALID (pButton);
	ASSERT_VALID (pPopup);

	pPopup->EnableMenuItem (ID_BCGBARRES_TOOLBAR_IMAGE, MF_GRAYED | MF_BYCOMMAND);
	pPopup->EnableMenuItem (ID_BCGBARRES_TOOLBAR_TEXT, MF_GRAYED | MF_BYCOMMAND);
	pPopup->EnableMenuItem (ID_BCGBARRES_TOOLBAR_IMAGE_AND_TEXT, MF_GRAYED | MF_BYCOMMAND);

	pButton->m_bText = TRUE;
	CBCGToolBar::EnableContextMenuItems (pButton, pPopup);

	return TRUE;
}
//****************************************************************************************
void CBCGPopupMenuBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rectClient;
	GetClientRect (&rectClient);

	if (IsCustomizeMode () ||
		rectClient.PtInRect (point))
	{
		CBCGToolBar::OnMouseMove(nFlags, point);
	}
	else
	{
		CBCGToolBar* pDestBar = FindDestBar (point);
		if (pDestBar != NULL)
		{
			MapWindowPoints (pDestBar, &point, 1);
			pDestBar->SendMessage (	WM_MOUSEMOVE, 
									nFlags, 
									MAKELPARAM (point.x, point.y));
		}
	}
}
//***************************************************************************************
CBCGToolBar* CBCGPopupMenuBar::FindDestBar (CPoint point)
{
	ScreenToClient (&point);

	CRect rectClient;

	CBCGPopupMenu* pPopupMenu = DYNAMIC_DOWNCAST (CBCGPopupMenu, GetParent ());
	ASSERT_VALID (pPopupMenu);

	CBCGPopupMenu* pLastPopupMenu = pPopupMenu;

	//-------------------------------
	// Go up trougth all popup menus:
	//-------------------------------
	while ((pPopupMenu = pPopupMenu->GetParentPopupMenu ()) != NULL)
	{
		CBCGPopupMenuBar* pPopupMenuBar = pPopupMenu->GetMenuBar ();
		ASSERT_VALID (pPopupMenuBar);

		pPopupMenuBar->GetClientRect (&rectClient);
		pPopupMenuBar->MapWindowPoints (this, &rectClient);

		if (rectClient.PtInRect (point))
		{
			return pPopupMenuBar;
		}

		pLastPopupMenu = pPopupMenu;
	}

	ASSERT_VALID (pLastPopupMenu);

	//--------------------
	// Try parent toolbar:
	//--------------------
	CBCGToolBar* pToolBar = pLastPopupMenu->GetParentToolBar ();
	if (pToolBar != NULL)
	{
		pToolBar->GetClientRect (&rectClient);
		pToolBar->MapWindowPoints (this, &rectClient);

		if (rectClient.PtInRect (point))
		{
			return pToolBar;
		}
	}

	return NULL;
}
//*********************************************************************************************
DROPEFFECT CBCGPopupMenuBar::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	//-----------------------------------------------
	// Disable MOVING menu item into one of submenus!
	//-----------------------------------------------
	if ((dwKeyState & MK_CONTROL) == 0)
	{
		CBCGPopupMenu* pParentMenu = DYNAMIC_DOWNCAST (CBCGPopupMenu, GetParent ());
		if (pParentMenu != NULL)
		{
			CBCGToolBar* pParentBar = pParentMenu->GetParentToolBar ();
			CBCGToolbarMenuButton* pParentButton = pParentMenu->GetParentButton ();

			if (pParentBar != NULL && pParentButton != NULL &&
				pParentBar->IsDragButton (pParentButton))
			{
				return DROPEFFECT_NONE;
			}
		}
	}

	return CBCGToolBar::OnDragOver(pDataObject, dwKeyState, point);
}
