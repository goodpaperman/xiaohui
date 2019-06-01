// BCGFrameImpl.cpp: implementation of the CBCGFrameImpl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "afxpriv.h"
#include <..\\src\\afximpl.h>
#include "BCGFrameImpl.h"
#include "BCGToolBar.h"
#include "BCGMenuBar.h"
#include "bcglocalres.h"
#include "bcgbarres.h"
#include "BCGPopupMenu.h"
#include "BCGToolbarMenuButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGFrameImpl::CBCGFrameImpl(CFrameWnd* pFrame) :
	m_pFrame (pFrame),
	m_pActivePopupMenu (NULL),
	m_uiUserToolbarFirst ((UINT)-1),
	m_uiUserToolbarLast ((UINT)-1),
	m_pMenuBar (NULL),
	m_hDefaultMenu (NULL),
	m_nIDDefaultResource (0)
{
	ASSERT_VALID (m_pFrame);
}
//**************************************************************************************
CBCGFrameImpl::~CBCGFrameImpl()
{
	//-----------------------------
	// Clear user-defined toolbars:
	//-----------------------------
	while (!m_listUserDefinedToolbars.IsEmpty ())
	{
		delete m_listUserDefinedToolbars.RemoveHead ();
	}
}
//**************************************************************************************
void CBCGFrameImpl::LoadUserToolbars ()
{
	ASSERT (!m_strControlBarRegEntry.IsEmpty ());

	for (UINT uiNewToolbarID = m_uiUserToolbarFirst;
		uiNewToolbarID <= m_uiUserToolbarLast;
		uiNewToolbarID ++)
	{
		CBCGToolBar* pNewToolbar = new CBCGToolBar;
		if (!pNewToolbar->Create (m_pFrame, 
			dwDefaultToolbarStyle,
			uiNewToolbarID))
		{
			TRACE0 ("Failed to create a new toolbar!\n");
			delete pNewToolbar;
			continue;
		}

		if (!pNewToolbar->LoadState (m_strControlBarRegEntry))
		{
			pNewToolbar->DestroyWindow ();
			delete pNewToolbar;
		}
		else
		{
			pNewToolbar->SetBarStyle (pNewToolbar->GetBarStyle () |
				CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
			pNewToolbar->EnableDocking (CBRS_ALIGN_ANY);

			m_pFrame->DockControlBar (pNewToolbar);
			m_listUserDefinedToolbars.AddTail (pNewToolbar);
		}
	}
}
//**********************************************************************************************
void CBCGFrameImpl::SaveUserToolbars ()
{
	ASSERT (!m_strControlBarRegEntry.IsEmpty ());

	for (POSITION pos = m_listUserDefinedToolbars.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolBar* pUserToolBar = 
			(CBCGToolBar*) m_listUserDefinedToolbars.GetNext (pos);
		ASSERT_VALID(pUserToolBar);

		pUserToolBar->SaveState (m_strControlBarRegEntry);
	}
}
//**********************************************************************************************
CBCGToolBar* CBCGFrameImpl::GetUserBarByIndex (int iIndex) const
{
	POSITION pos = m_listUserDefinedToolbars.FindIndex (iIndex);
	if (pos == NULL)
	{
		return NULL;
	}

	CBCGToolBar* pUserToolBar = 
		(CBCGToolBar*) m_listUserDefinedToolbars.GetAt (pos);
	ASSERT_VALID (pUserToolBar);

	return pUserToolBar;
}
//**********************************************************************************************
BOOL CBCGFrameImpl::IsUserDefinedToolbar (const CBCGToolBar* pToolBar) const
{
	ASSERT_VALID (pToolBar);

	UINT uiCtrlId = pToolBar->GetDlgCtrlID ();
	return	uiCtrlId >= m_uiUserToolbarFirst &&
			uiCtrlId <= m_uiUserToolbarLast;
}
//*******************************************************************************************
BOOL CBCGFrameImpl::IsDockStateValid (const CDockState& state)
{
	//----------------------------------------------------------------
	// This function helps to avoid GPF during CFrameWnd::LoadBarState
	// execution: when one of the previously saved toolbars is not
	// created, LoadBarState fails.
	//----------------------------------------------------------------

	for (int i = 0; i < state.m_arrBarInfo.GetSize (); i ++)
	{
		CControlBarInfo* pInfo = (CControlBarInfo*) state.m_arrBarInfo [i];
		ASSERT (pInfo != NULL);

		if (!pInfo->m_bFloating)
		{
			//---------------------------------------
			// Find the control bar with the same ID:
			//---------------------------------------
			if (m_pFrame->GetControlBar (pInfo->m_nBarID) == NULL)
			{
				TRACE (_T("CBCGFrameImpl::IsDockStateValid ControlBar %x is not valid!\n"), pInfo->m_nBarID);
				return FALSE;
			}
		}
	}

	return TRUE;
}
//**********************************************************************************
void CBCGFrameImpl::InitUserToobars (	LPCTSTR lpszRegEntry,
										UINT uiUserToolbarFirst, 
										UINT uiUserToolbarLast)
{
	ASSERT (lpszRegEntry != NULL);
	ASSERT (uiUserToolbarLast >= uiUserToolbarFirst);

	m_uiUserToolbarFirst = uiUserToolbarFirst;
	m_uiUserToolbarLast = uiUserToolbarLast;

	m_strControlBarRegEntry = lpszRegEntry;

	ASSERT (!m_strControlBarRegEntry.IsEmpty ());
}
//**************************************************************************************
const CBCGToolBar* CBCGFrameImpl::CreateNewToolBar (LPCTSTR lpszName)
{
	ASSERT (lpszName != NULL);

	if (m_uiUserToolbarFirst == (UINT)-1 ||
		m_uiUserToolbarLast == (UINT)-1)
	{
		TRACE (_T("User-defined toolbars IDs are none defined!\n"));
		return NULL;
	}

	int iMaxToolbars = m_uiUserToolbarLast - m_uiUserToolbarFirst + 1;
	if (m_listUserDefinedToolbars.GetCount () == iMaxToolbars)
	{
		CBCGLocalResource locaRes;

		CString strError;
		strError.Format (IDS_BCGBARRES_TOO_MANY_TOOLBARS_FMT, iMaxToolbars);

		AfxMessageBox (strError, MB_OK | MB_ICONASTERISK);
		return NULL;
	}

	//-----------------------
	// Find a new toolbar id:
	//-----------------------
	UINT uiNewToolbarID;

	for (uiNewToolbarID = m_uiUserToolbarFirst;
		uiNewToolbarID <= m_uiUserToolbarLast;
		uiNewToolbarID ++)
	{
		BOOL bUsed = FALSE;

		for (POSITION pos = m_listUserDefinedToolbars.GetHeadPosition (); 
			!bUsed && pos != NULL;)
		{
			CBCGToolBar* pUserToolBar = 
				(CBCGToolBar*) m_listUserDefinedToolbars.GetNext (pos);
			ASSERT_VALID(pUserToolBar);

			bUsed = (pUserToolBar->GetDlgCtrlID () == (int) uiNewToolbarID);
		}

		if (!bUsed)
		{
			break;
		}
	}

	if (uiNewToolbarID > m_uiUserToolbarLast)
	{
		TRACE0 ("Can't find non-used toolbar number!\n");
		return NULL;
	}

	CBCGToolBar* pNewToolbar = new CBCGToolBar;
	if (!pNewToolbar->Create (m_pFrame,
		dwDefaultToolbarStyle,
		uiNewToolbarID))
	{
		TRACE0 ("Failed to create a new toolbar!\n");
		delete pNewToolbar;
		return NULL;
	}

	pNewToolbar->SetWindowText (lpszName);

	pNewToolbar->SetBarStyle (pNewToolbar->GetBarStyle () |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	pNewToolbar->EnableDocking (CBRS_ALIGN_ANY);
	
	m_pFrame->FloatControlBar (pNewToolbar,
		CPoint (::GetSystemMetrics (SM_CXFULLSCREEN) / 2, 
				::GetSystemMetrics (SM_CYFULLSCREEN) / 2));
	m_pFrame->RecalcLayout ();

	m_listUserDefinedToolbars.AddTail (pNewToolbar);
	return pNewToolbar;
}
//**************************************************************************************
BOOL CBCGFrameImpl::DeleteToolBar (CBCGToolBar* pToolBar)
{
	ASSERT_VALID (pToolBar);

	POSITION pos = m_listUserDefinedToolbars.Find (pToolBar);
	if (pos == NULL)
	{
		return FALSE;
	}

	m_listUserDefinedToolbars.RemoveAt (pos);
	pToolBar->RemoveStateFromRegistry (m_strControlBarRegEntry);

	pToolBar->DestroyWindow ();
	delete pToolBar;

	m_pFrame->RecalcLayout ();
	return TRUE;
}
//*******************************************************************************************
void CBCGFrameImpl::SetMenuBar (CBCGMenuBar* pMenuBar)
{
	ASSERT_VALID (pMenuBar);
	ASSERT (m_pMenuBar == NULL);	// Method should be called once!

	m_pMenuBar = pMenuBar;

	m_hDefaultMenu=*m_pFrame->GetMenu();
	m_pMenuBar->CreateFromMenu (*m_pFrame->GetMenu(), TRUE /* Default menu */);
	m_pFrame->SetMenu (NULL);
	
	m_pMenuBar->SetDefaultMenuResId (m_nIDDefaultResource);
}
//*******************************************************************************************
BOOL CBCGFrameImpl::ProcessKeyboard (int nKey)
{
	if (m_pActivePopupMenu != NULL &&
		::IsWindow (m_pActivePopupMenu->m_hWnd))
	{
		m_pActivePopupMenu->SendMessage (WM_KEYDOWN, nKey);
		return TRUE;
	}

	return FALSE;
}
//*******************************************************************************************
BOOL CBCGFrameImpl::ProcessMouseClick (POINT pt)
{
	if (!CBCGToolBar::IsCustomizeMode () &&
		m_pActivePopupMenu != NULL &&
		::IsWindow (m_pActivePopupMenu->m_hWnd))
	{
		CRect rectMenu;
		m_pActivePopupMenu->GetWindowRect (rectMenu);

		if (!rectMenu.PtInRect (pt))
		{
			//--------------------------------------------
			// Maybe secondary click on the parent button?
			//--------------------------------------------
			CBCGToolbarMenuButton* pParentButton = 
				m_pActivePopupMenu->GetParentButton ();
			if (pParentButton != NULL)
			{
				CBCGPopupMenuBar* pWndParent = DYNAMIC_DOWNCAST (
					CBCGPopupMenuBar, pParentButton->GetParentWnd ());
				if (pWndParent != NULL)
				{
					CPoint ptClient = pt;
					pWndParent->ScreenToClient (&ptClient);

					if (pParentButton->m_rect.PtInRect (ptClient))
					{
						//-----------------------------
						// Secondary click, do nothing!
						//-----------------------------
						return TRUE;
					}
				}
			}

			m_pActivePopupMenu->SendMessage (WM_CLOSE);
			return TRUE;
		}
	}

	return FALSE;
}
//*******************************************************************************************
BOOL CBCGFrameImpl::ProcessMouseMove (POINT pt)
{
	if (!CBCGToolBar::IsCustomizeMode () &&
		m_pActivePopupMenu != NULL &&
		::IsWindow (m_pActivePopupMenu->m_hWnd))
	{
		CRect rectMenu;
		m_pActivePopupMenu->GetWindowRect (rectMenu);

		if (rectMenu.PtInRect (pt) ||
			m_pActivePopupMenu->GetMenuBar ()->FindDestBar (pt) != NULL)
		{
			return FALSE;	// Default processing
		}

		return TRUE;		// Active menu "capturing"
	}

	return FALSE;	// Default processing
}
//*******************************************************************************************
void CBCGFrameImpl::OnShowPopupMenu (CBCGPopupMenu* pMenuPopup, CFrameWnd* /*pWndFrame*/)
{
	m_pActivePopupMenu = pMenuPopup;
}

// Copyright (C) 1997,'98 by Joerg Koenig
// All rights reserved
//

/////////////////////////////////////////////////////////////////////////////
// helpers for docking 
/////////////////////////////////////////////////////////////////////////////


// We need our own version of a dock bar, because the original
// MFC implementation overlapps toolbars. CBCGToolBar don't want
// such a overlapping, because this makes it impossible to draw
// a real 3d border ...
class CBCGToolDockBar : public CDockBar {
	DECLARE_DYNAMIC(CBCGToolDockBar)

	public:
		// this is the one and only method of interest
		virtual CSize	CalcFixedLayout(BOOL bStretch, BOOL bHorz);
};

IMPLEMENT_DYNAMIC(CBCGToolDockBar, CDockBar);

CSize CBCGToolDockBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	ASSERT_VALID(this);

	CSize sizeFixed = CControlBar::CalcFixedLayout(bStretch, bHorz);

	// get max size
	CSize sizeMax;
	if (!m_rectLayout.IsRectEmpty())
		sizeMax = m_rectLayout.Size();
	else
	{
		CRect rectFrame;
		CFrameWnd* pFrame = GetParentFrame();
		pFrame->GetClientRect(&rectFrame);
		sizeMax = rectFrame.Size();
	}

	// prepare for layout
	AFX_SIZEPARENTPARAMS layout;
	layout.hDWP = m_bLayoutQuery ?
		NULL : ::BeginDeferWindowPos(m_arrBars.GetSize());
	int cxBorder = afxData.cxBorder2; 
	int cyBorder = afxData.cyBorder2;

	CPoint pt(-cxBorder, -cyBorder);
	int nWidth = 0;

	BOOL bWrapped = FALSE;
	BOOL bFirstBar = TRUE;

	// layout all the control bars
	for (int nPos = 0; nPos < m_arrBars.GetSize(); nPos++)
	{
		CControlBar* pBar = GetDockedControlBar(nPos);
		void* pVoid = m_arrBars[nPos];

		if (pBar != NULL)
		{
			if (pBar->IsKindOf (RUNTIME_CLASS(CBCGToolBar)))
			{
				cxBorder = cyBorder = 0;
			}
			else
			{
				cxBorder = afxData.cxBorder2;
				cyBorder = afxData.cyBorder2;
			}

			if (pBar->IsVisible())
			{
				// get ideal rect for bar
				DWORD dwMode = 0;
				if ((pBar->m_dwStyle & CBRS_SIZE_DYNAMIC) &&
					(pBar->m_dwStyle & CBRS_FLOATING))
					dwMode |= LM_HORZ | LM_MRUWIDTH;
				else if (pBar->m_dwStyle & CBRS_ORIENT_HORZ)
					dwMode |= LM_HORZ | LM_HORZDOCK;
				else
					dwMode |=  LM_VERTDOCK;

				CSize sizeBar = pBar->CalcDynamicLayout(-1, dwMode);
				BOOL bIsMenuBar = FALSE;

				if (pBar->IsKindOf (RUNTIME_CLASS(CBCGMenuBar)))
				{
					bIsMenuBar = TRUE;

					if (dwMode & LM_HORZDOCK)
					{
						sizeBar.cx = sizeMax.cx;
					}
					else if (dwMode & LM_VERTDOCK)
					{
						sizeBar.cy = sizeMax.cy;
					}
				}

				if (bFirstBar)
				{
					if (dwMode & LM_HORZDOCK)
					{
						pt.x = -cxBorder;
					}
					else if (dwMode & LM_VERTDOCK)
					{
						pt.y = -cyBorder;
					}
				}

				CRect rect(pt, sizeBar);

				// get current rect for bar
				CRect rectBar;
				pBar->GetWindowRect(&rectBar);
				ScreenToClient(&rectBar);

				BOOL bMenuIsCutted = FALSE;

				if (bHorz)
				{
					// Offset Calculated Rect out to Actual
					if (rectBar.left > rect.left && !m_bFloating)
						rect.OffsetRect(rectBar.left - rect.left, 0);

					// If ControlBar goes off the right, then right justify

					if (rect.right > sizeMax.cx && !m_bFloating)
					{
						int x = rect.Width() - cxBorder;
						x = max(sizeMax.cx - x, pt.x);
						rect.OffsetRect(x - rect.left, 0);

						if (bIsMenuBar)
						{
							bMenuIsCutted = TRUE;
						}
					}

					// If ControlBar has been wrapped, then left justify
					if (bWrapped)
					{
						bWrapped = FALSE;
						rect.OffsetRect(-(rect.left + cxBorder), 0);
					}
					// If ControlBar is completely invisible, then wrap it
					else if ((rect.left >= (sizeMax.cx - cxBorder) || bMenuIsCutted) &&
						(nPos > 0) && (m_arrBars[nPos - 1] != NULL))
					{
						m_arrBars.InsertAt(nPos, (CObject*)NULL);
						pBar = NULL; pVoid = NULL;
						bWrapped = TRUE;
					}
					if (!bWrapped)
					{
						if (rect != rectBar)
						{
							if (!m_bLayoutQuery &&
								!(pBar->m_dwStyle & CBRS_FLOATING))
							{
								pBar->m_pDockContext->m_rectMRUDockPos = rect;
							}

							AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
						}
						pt.x = rect.left + sizeBar.cx - cxBorder;
						nWidth = max(nWidth, sizeBar.cy);
					}
				}
				else
				{
					// Offset Calculated Rect out to Actual
					if (rectBar.top > rect.top && !m_bFloating)
						rect.OffsetRect(0, rectBar.top - rect.top);

					// If ControlBar goes off the bottom, then bottom justify
					if (rect.bottom > sizeMax.cy && !m_bFloating)
					{
						int y = rect.Height() - cyBorder;
						y = max(sizeMax.cy - y, pt.y);
						rect.OffsetRect(0, y - rect.top);

						if (bIsMenuBar)
						{
							bMenuIsCutted = TRUE;
						}
					}

					// If ControlBar has been wrapped, then top justify
					if (bWrapped)
					{
						bWrapped = FALSE;
						rect.OffsetRect(0, -(rect.top + cyBorder));
					}
					// If ControlBar is completely invisible, then wrap it
					else if ((rect.top >= (sizeMax.cy - cyBorder) || bIsMenuBar) &&
						(nPos > 0) && (m_arrBars[nPos - 1] != NULL))
					{
						m_arrBars.InsertAt(nPos, (CObject*)NULL);
						pBar = NULL; pVoid = NULL;
						bWrapped = TRUE;
					}

					if (!bWrapped)
					{
						if (rect != rectBar)
						{
							if (!m_bLayoutQuery &&
								!(pBar->m_dwStyle & CBRS_FLOATING))
							{
								pBar->m_pDockContext->m_rectMRUDockPos = rect;
							}
							AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
						}
						pt.y = rect.top + sizeBar.cy - cyBorder;
						nWidth = max(nWidth, sizeBar.cx);
					}
				}

				bFirstBar = FALSE;
			}

			if (!bWrapped)
			{
				// handle any delay/show hide for the bar
				pBar->RecalcDelayShow(&layout);
			}
		}

		if (pBar == NULL && pVoid == NULL && nWidth != 0)
		{
			// end of row because pBar == NULL
			if (bHorz)
			{
				pt.y += nWidth - cyBorder;
				sizeFixed.cx = max(sizeFixed.cx, pt.x);
				sizeFixed.cy = max(sizeFixed.cy, pt.y);
				pt.x = -cxBorder;
			}
			else
			{
				pt.x += nWidth - cxBorder;
				sizeFixed.cx = max(sizeFixed.cx, pt.x);
				sizeFixed.cy = max(sizeFixed.cy, pt.y);
				pt.y = -cyBorder;
			}
			nWidth = 0;
		}
	}
	if (!m_bLayoutQuery)
	{
		// move and resize all the windows at once!
		if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
			TRACE0("Warning: DeferWindowPos failed - low system resources.\n");
	}

	// adjust size for borders on the dock bar itself
	CRect rect;
	rect.SetRectEmpty();
	CalcInsideRect(rect, bHorz);

	if ((!bStretch || !bHorz) && sizeFixed.cx != 0)
		sizeFixed.cx += -rect.right + rect.left;
	if ((!bStretch || bHorz) && sizeFixed.cy != 0)
		sizeFixed.cy += -rect.bottom + rect.top;

	return sizeFixed;
}

// dwDockBarMap
const DWORD dwDockBarMap[4][2] =
{
	{ AFX_IDW_DOCKBAR_TOP,      CBRS_TOP    },
	{ AFX_IDW_DOCKBAR_BOTTOM,   CBRS_BOTTOM },
	{ AFX_IDW_DOCKBAR_LEFT,     CBRS_LEFT   },
	{ AFX_IDW_DOCKBAR_RIGHT,    CBRS_RIGHT  },
};


// Unfortunataly a simple rewrite of CFrameWnd's EnableDocking() is not possible,
// because we have not enough permissions to access some data in this class.
// That's why we call CFrameWnd::EnableDocking() first and exchange all occurencies
// of CDockBar objects with our own version of a dock bar.
void CBCGFrameImpl::FrameEnableDocking(CFrameWnd * pFrame, DWORD dwDockStyle) 
{
	ASSERT_VALID(pFrame);

	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
	ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

	pFrame->EnableDocking(dwDockStyle);

	for (int i = 0; i < 4; i++) {
		if (dwDockBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY) {
			CDockBar* pDock = (CDockBar*)pFrame->GetControlBar(dwDockBarMap[i][0]);
			
			// make sure the dock bar is of correct type
			if( pDock == 0 || ! pDock->IsKindOf(RUNTIME_CLASS(CBCGToolDockBar)) ) {
				BOOL bNeedDelete = ! pDock->m_bAutoDelete;
				pDock->m_pDockSite->RemoveControlBar(pDock);
				pDock->m_pDockSite = 0;	// avoid problems in destroying the dockbar
				pDock->DestroyWindow();
				if( bNeedDelete )
					delete pDock;
				pDock = 0;
			}

			if( pDock == 0 ) {
				pDock = new CBCGToolDockBar;
				if (!pDock->Create(pFrame,
					WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE |
						dwDockBarMap[i][1], dwDockBarMap[i][0])) {
					AfxThrowResourceException();
				}
			}
		}
	}
}
