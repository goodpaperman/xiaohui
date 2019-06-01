// BCGPopupMenu.cpp : implementation file
//

#include "stdafx.h"

#pragma warning (disable : 4201)
	#include "mmsystem.h"
	#pragma comment(lib,"winmm.lib") 
	#pragma message("Automatically linking with winmm.lib") 
#pragma warning (default : 4201)

#include "BCGPopupMenu.h"
#include "globals.h"
#include "BCGToolbarMenuButton.h"
#include "BCGMDIFrameWnd.h"
#include "BCGFrameWnd.h"
#include "BCGOleIPFrameWnd.h"
#include "BCGMenuBar.h"
#include "menupage.h"
#include "MenuHash.h"
#include "bcglocalres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPopupMenu

static const int iBorderSize = 2;
static const int iAnimTimerId = 1;
static const int iAnimTimerDuration = 30;
static const int iScrollTimerId = 2;
static const int iScrollTimerDuration = 80;
static const int iImgIdArowDown = 0;
static const int iImgIdArowDownDisabled = 1;
static const int iImgIdArowUp = 16;
static const int iImgIdArowUpDisabled = 17;
static const COLORREF clrTransparent = RGB (255, 0, 255);
static const int iImageWidth = 9;

CString	CBCGPopupMenu::m_strClassName;
CBCGPopupMenu::ANIMATION_TYPE CBCGPopupMenu::m_AnimationType = NO_ANIMATION;
CImageList CBCGPopupMenu::m_MenuImages;

IMPLEMENT_SERIAL(CBCGPopupMenu, CMiniFrameWnd, VERSIONABLE_SCHEMA | 1)

CBCGPopupMenu::CBCGPopupMenu() :
	m_pMenuCustomizationPage (NULL)
{
	Initialize ();
}
//****************************************************************************************
CBCGPopupMenu::CBCGPopupMenu(CMenuPage* pCustPage, LPCTSTR lpszTitle) :
	m_pMenuCustomizationPage (pCustPage),
	m_strCaption (lpszTitle)
{
	Initialize ();
}
//****************************************************************************************
void CBCGPopupMenu::Initialize ()
{
	m_hMenu = NULL;
	m_x = m_y = 0;
	m_pParentBtn = NULL;
	m_bAutoDestroyParent = TRUE;
	m_bAutoDestroy = TRUE;
	m_FinalSize = CSize (0, 0);
	m_bIsAnimate = FALSE;
	m_bScrollable = FALSE;

	m_rectScrollUp.SetRectEmpty ();
	m_rectScrollDn.SetRectEmpty ();

	m_iScrollMode = 0;
}
//****************************************************************************************
CBCGPopupMenu::~CBCGPopupMenu()
{
	if (m_bAutoDestroy)
	{
		::DestroyMenu (m_hMenu);
	}
}

BEGIN_MESSAGE_MAP(CBCGPopupMenu, CMiniFrameWnd)
	//{{AFX_MSG_MAP(CBCGPopupMenu)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEACTIVATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_ACTIVATEAPP()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPopupMenu message handlers

BOOL CBCGPopupMenu::Create (CWnd* pWndParent, int x, int y, HMENU hMenu, BOOL bLocked)
{
	ASSERT (pWndParent != NULL);

	// Play standard menu popup sound!
	PlaySound (_T("MenuPopup"), NULL, SND_ASYNC | SND_NODEFAULT);

	if (m_strClassName.IsEmpty ())
	{
		m_strClassName = ::AfxRegisterWndClass (
			CS_SAVEBITS,
			::LoadCursor(NULL, IDC_ARROW),
			(HBRUSH)(COLOR_BTNFACE + 1), NULL);
	}

	m_hMenu = hMenu;

	if (x == -1 && y == -1)	// Undefined position
	{
		if (pWndParent != NULL)
		{
			CRect rectParent;
			pWndParent->GetClientRect (&rectParent);
			pWndParent->ClientToScreen (&rectParent);

			m_x = rectParent.left + 5;
			m_y = rectParent.top + 5;
		}
		else
		{
			m_x = 0;
			m_y = 0;
		}
	}
	else
	{
		m_x = x;
		m_y = y;
	}

	DWORD dwStyle = WS_POPUP;
	if (m_pMenuCustomizationPage != NULL)
	{
		dwStyle |= (WS_CAPTION | WS_SYSMENU);
	}

	m_bIsAnimate = (m_AnimationType != NO_ANIMATION) && 
					!CBCGToolBar::IsCustomizeMode ();

	CRect rect (x, y, x, y);
	BOOL bCreated = CMiniFrameWnd::CreateEx (
				0,
				m_strClassName, m_strCaption,
				dwStyle, rect,
				pWndParent->GetOwner () == NULL ? 
					pWndParent : pWndParent->GetOwner ());
	if (!bCreated)
	{
		return FALSE;
	}

	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	pMenuBar->m_bLocked = bLocked;

	if (m_bIsAnimate)
	{
		pMenuBar->SetOffset (pMenuBar->m_Buttons.GetCount () - 1);

		m_AnimSize = m_FinalSize;
		m_AnimSize.cy = pMenuBar->GetRowHeight ();

		if (m_AnimationType == UNFOLD)
		{
			m_AnimSize.cx = pMenuBar->GetColumnWidth ();
		}

		SetWindowPos (NULL, -1, -1, m_AnimSize.cx, m_AnimSize.cy,
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

		SetTimer (iAnimTimerId, iAnimTimerDuration, NULL);
	}

	ShowWindow (SW_SHOWNOACTIVATE);
	
	pMenuBar->Invalidate ();
	pMenuBar->UpdateWindow ();

	return TRUE;
}
//****************************************************************************************

//-----------------------------------------------------
// My "classic " trick - how I can access to protected
// member m_pRecentFileList?
//-----------------------------------------------------
class CBCGApp : public CWinApp
{
	friend class CBCGPopupMenu;
};

int CBCGPopupMenu::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndMenuBar.Create (this))
	{
		TRACE(_T("Can't create popup menu bar\n"));
		return -1;
	}

	m_wndMenuBar.SetOwner (GetParent ());

	ASSERT (m_hMenu != NULL);
	if (m_pParentBtn != NULL || 
		!g_menuHash.LoadMenuBar (m_hMenu, &m_wndMenuBar))
	{
		//-------------------------------------------
		// Failed to restore, load the default state:
		//-------------------------------------------
		if (!m_wndMenuBar.ImportFromMenu (m_hMenu))
		{
			return -1;
		}
	}

	//----------------------------------------
	// Maybe, we should process the MRU files:
	//----------------------------------------
	CRecentFileList* pMRUFiles = 
		((CBCGApp*) AfxGetApp ())->m_pRecentFileList;

	if (pMRUFiles != NULL && !CBCGToolBar::IsCustomizeMode ())
	{
		int iMRUItemIndex = 0;
		BOOL bIsPrevSeparator = FALSE;

		for (POSITION pos = m_wndMenuBar.m_Buttons.GetHeadPosition (); 
			pos != NULL; iMRUItemIndex ++)
		{
			POSITION posSave = pos;

			CBCGToolbarButton* pButton = 
				(CBCGToolbarButton*) m_wndMenuBar.m_Buttons.GetNext (pos);
			ASSERT (pButton != NULL);

			if (pButton->m_nID == ID_FILE_MRU_FILE1)
			{
				//------------------------------
				// Remove dummy item ("Recent"):
				//------------------------------
				m_wndMenuBar.m_Buttons.RemoveAt (posSave);
				delete pButton;

				TCHAR szCurDir [_MAX_PATH];
				::GetCurrentDirectory (_MAX_PATH, szCurDir);

				int nCurDir = lstrlen (szCurDir);
				ASSERT (nCurDir >= 0);

				szCurDir [nCurDir] = _T('\\');
				szCurDir [++ nCurDir] = _T('\0');

				//---------------
				// Add MRU files:
				//---------------
				int iNumOfFiles = 0;	// Actual added to menu
				for (int i = 0; i < pMRUFiles->GetSize (); i ++)
				{
					CString strName;

					if (pMRUFiles->GetDisplayName (strName, i, 
						szCurDir, nCurDir))
					{
						//---------------------
						// Add shortcut number:
						//---------------------
						CString strItem;
						strItem.Format (_T("&%d %s"), ++iNumOfFiles, strName);

						m_wndMenuBar.InsertButton (
							CBCGToolbarMenuButton (
								ID_FILE_MRU_FILE1 + i, NULL,
								-1, strItem),
							iMRUItemIndex ++);
					}
				}

				//------------------------------------------------------
				// Usualy, the MRU group is "covered" by two seperators.
				// If MRU list is empty, remove redandant separator:
				//------------------------------------------------------
				if (iNumOfFiles == 0 &&	// No files were added
					bIsPrevSeparator &&	// Prev. button was separator
					pos != NULL)		// Not a last button
				{
					posSave = pos;

					pButton = (CBCGToolbarButton*) 
						m_wndMenuBar.m_Buttons.GetNext (pos);
					ASSERT (pButton != NULL);

					if (pButton->m_nStyle & TBBS_SEPARATOR)
					{
						//---------------------------------------
						// Next button also separator, remove it:
						//---------------------------------------
						m_wndMenuBar.m_Buttons.RemoveAt (posSave);
						delete pButton;
					}
				}

				break;
			}

			bIsPrevSeparator = (pButton->m_nStyle & TBBS_SEPARATOR);
		}
	}

	//-----------------------------------------------------------------------------
	// Maybe, main application frame should update the popup menu context before it
	// displayed (example - windows list):
	//-----------------------------------------------------------------------------
	ActivatePopupMenu (this);

	RecalcLayout ();
	return 0;
}
//****************************************************************************************
void CBCGPopupMenu::OnSize(UINT nType, int cx, int cy) 
{
	CMiniFrameWnd::OnSize(nType, cx, cy);
	
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	if (pMenuBar->GetSafeHwnd () == NULL)
	{
		return;
	}

	if (m_bScrollable)
	{
		pMenuBar->SetWindowPos (NULL, iBorderSize, 
					iBorderSize + pMenuBar->GetRowHeight (),
					cx - iBorderSize * 2, 
					cy - iBorderSize * 2 - 2 * pMenuBar->GetRowHeight (),
					SWP_NOZORDER | SWP_NOACTIVATE);
		
		m_rectScrollUp = CRect (iBorderSize, iBorderSize,
			cx - iBorderSize, iBorderSize + pMenuBar->GetRowHeight ());
		m_rectScrollDn = CRect (iBorderSize, cy - pMenuBar->GetRowHeight () - iBorderSize,
			cx - iBorderSize, cy - iBorderSize);
	}
	else
	{
		pMenuBar->SetWindowPos (NULL, iBorderSize, iBorderSize,
					cx - iBorderSize * 2, cy - iBorderSize * 2,
					SWP_NOZORDER | SWP_NOACTIVATE);

		m_rectScrollUp.SetRectEmpty ();
		m_rectScrollDn.SetRectEmpty ();
	}
}
//****************************************************************************************
void CBCGPopupMenu::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	dc.Draw3dRect (rectClient, 
					globalData.clrBtnLight, 
					globalData.clrBtnDkShadow);
	rectClient.DeflateRect (1, 1);
	dc.Draw3dRect (rectClient, 
					globalData.clrBtnHilite,
					globalData.clrBtnShadow);

	if (m_bScrollable)
	{
		if (m_MenuImages.GetSafeHandle () == NULL)
		{
			CBCGLocalResource locaRes;
			m_MenuImages.Create (IDB_BCGBARRES_MENU_IMAGES, iImageWidth, 0, clrTransparent);
		}

		IMAGEINFO imageInfo;
		m_MenuImages.GetImageInfo (0, &imageInfo);

		CRect rectImage = imageInfo.rcImage;

		dc.FillSolidRect (m_rectScrollUp, globalData.clrBtnFace);

		CPoint pointUpArrow (
			m_rectScrollUp.left + (m_rectScrollUp.Width () - rectImage.Width ()) / 2,
			m_rectScrollUp.top + (m_rectScrollUp.Height () - rectImage.Height ()) / 2);
		m_MenuImages.Draw (&dc, 
			IsScrollUpAvailable () ? iImgIdArowUp : iImgIdArowUpDisabled, 
			pointUpArrow, ILD_NORMAL);

		if (m_iScrollMode < 0)
		{
			dc.Draw3dRect (m_rectScrollUp, 
				globalData.clrBtnHilite,
				globalData.clrBtnShadow);
		}

		dc.FillSolidRect (m_rectScrollDn, globalData.clrBtnFace);

		CPoint pointDownArrow (
			m_rectScrollDn.left + (m_rectScrollDn.Width () - rectImage.Width ()) / 2,
			m_rectScrollDn.top + (m_rectScrollDn.Height () - rectImage.Height ()) / 2);
		m_MenuImages.Draw (&dc, 
			IsScrollDnAvailable () ? iImgIdArowDown : iImgIdArowDownDisabled, 
			pointDownArrow, ILD_NORMAL);

		if (m_iScrollMode > 0)
		{
			dc.Draw3dRect (m_rectScrollDn,
				globalData.clrBtnHilite,
				globalData.clrBtnShadow);
		}
	}
}
//****************************************************************************************
int CBCGPopupMenu::OnMouseActivate(CWnd* /*pDesktopWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
	return MA_NOACTIVATE;
}
//****************************************************************************************
void CBCGPopupMenu::RecalcLayout (BOOL /*bNotify*/) 
{
#ifdef _DEBUG
	if (m_pParentBtn != NULL)
	{
		ASSERT_VALID (m_pParentBtn);
		ASSERT (m_pParentBtn->m_pPopupMenu == this);
	}
#endif // _DEBUG

	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	if (!::IsWindow (m_hWnd) ||
		!::IsWindow (pMenuBar->m_hWnd))
	{
		return;
	}

	CRect rectScreen;
	::SystemParametersInfo (SPI_GETWORKAREA, 0, &rectScreen, 0);

	CSize size = pMenuBar->CalcSize ();
	size.cx += iBorderSize * 2;
	size.cy += iBorderSize * 2;

	if (m_pMenuCustomizationPage != NULL)
	{
		size.cy += ::GetSystemMetrics (SM_CYSMCAPTION);
		size.cy += 2 * ::GetSystemMetrics (SM_CYBORDER) + 5;
	}

	//---------------------------------------------
	// Adjust the menu position by the screen size:
	//---------------------------------------------
	if (m_x + size.cx > rectScreen.right)
	{
		//-----------------------------------------------------
		// Menu can't be overlapped with the parent popup menu!
		//-----------------------------------------------------
		CBCGPopupMenu* pParentMenu = GetParentPopupMenu ();
		CBCGMenuBar* pParentMenuBar = m_pParentBtn == NULL ? NULL :
			DYNAMIC_DOWNCAST (CBCGMenuBar, m_pParentBtn->m_pWndParent);

		if (pParentMenu != NULL)
		{
			CRect rectParent;
			pParentMenu->GetWindowRect (rectParent);

			m_x = rectParent.left - size.cx;
		}
		else if (pParentMenuBar != NULL && 
			(pParentMenuBar->m_dwStyle & CBRS_ORIENT_HORZ) == 0)
		{
			//------------------------------------------------
			// Parent menu bar is docked vertical, place menu 
			// in the left or right side of the parent frame:
			//------------------------------------------------
			CRect rectParent;
			pParentMenuBar->GetWindowRect (rectParent);

			m_x = rectParent.left - size.cx;
		}
		else
		{
			m_x = rectScreen.right - size.cx - 1;
		}

		if (m_x < rectScreen.left)
		{
			m_x = rectScreen.left;
		}
	}

	if (m_y + size.cy > rectScreen.bottom)
	{
		if (m_bScrollable)
		{
			size.cy = rectScreen.bottom - m_y;
		}
		else
		{
			m_y -= size.cy;

			if (m_pParentBtn != NULL)
			{
				m_y -= m_pParentBtn->m_rect.Height () + 4;
			}

			if (m_y < rectScreen.top)
			{
				m_y = rectScreen.top;
			}
		}

		if (m_y + size.cy > rectScreen.bottom)
		{
			EnableScrolling ();
		}
	}

	if (!m_bIsAnimate)
	{
		if (m_pMenuCustomizationPage != NULL)
		{
			SetWindowPos (NULL, -1, -1, size.cx, size.cy,
						SWP_NOMOVE | SWP_NOZORDER |
						SWP_NOACTIVATE);
		}
		else
		{
			SetWindowPos (NULL, m_x, m_y, size.cx, size.cy,
						SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}

	m_FinalSize = size;

	if (CBCGToolBar::IsCustomizeMode ())
	{
		pMenuBar->AdjustLocations ();
	}
}
//****************************************************************************************
void CBCGPopupMenu::OnDestroy() 
{
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	//---------------------------------------------------------
	// First, maybe we have a dragged menu item. Remove it now:
	//---------------------------------------------------------
	if (pMenuBar->m_pDragButton != NULL &&
		!pMenuBar->m_bIsDragCopy)
	{
		pMenuBar->RemoveButton (
			pMenuBar->ButtonToIndex (pMenuBar->m_pDragButton));
		pMenuBar->m_pDragButton = NULL;
	}

	if (m_pParentBtn != NULL)
	{
		ASSERT (m_pParentBtn->m_pPopupMenu == this);

		SaveState ();

		m_pParentBtn->m_pPopupMenu = NULL;
		m_pParentBtn->m_bClickedOnMenu = FALSE;

		if (m_bAutoDestroyParent && !CBCGToolBar::IsCustomizeMode ())
		{
			//-------------------------------------------
			// Automatically close the parent popup menu:
			//-------------------------------------------
			CBCGPopupMenu* pParentMenu = GetParentPopupMenu ();
			if (pParentMenu != NULL)
			{
				pParentMenu->SendMessage (WM_CLOSE);
				m_pParentBtn = NULL;
			}
		}
	}

	if (m_pMenuCustomizationPage != NULL)
	{
		m_pMenuCustomizationPage->CloseContextMenu (this);
	}
				
	//------------------------------------------------
	// Inform the main frame about the menu detsroyng:
	//------------------------------------------------
	CBCGMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGMDIFrameWnd, AfxGetMainWnd ());
	if (pMainFrame != NULL)
	{
		pMainFrame->OnClosePopupMenu (this);
	}
	else	// Maybe, SDI frame...
	{
		CBCGFrameWnd* pFrame = DYNAMIC_DOWNCAST (CBCGFrameWnd, AfxGetMainWnd ());
		if (pFrame != NULL)
		{
			pFrame->OnClosePopupMenu (this);
		}
		else	// Maybe, OLE frame...
		{
			CBCGOleIPFrameWnd* pOleFrame = 
				DYNAMIC_DOWNCAST (CBCGOleIPFrameWnd, AfxGetMainWnd ());
			if (pOleFrame != NULL)
			{
				pOleFrame->OnClosePopupMenu (this);
			}
		}
	}

	CMiniFrameWnd::OnDestroy();
}
//****************************************************************************************
void CBCGPopupMenu::PostNcDestroy() 
{
	if (m_pParentBtn != NULL)
	{
		m_pParentBtn->OnCancelMode ();
	}
		
	CMiniFrameWnd::PostNcDestroy();
}
//****************************************************************************************
void CBCGPopupMenu::SaveState ()
{
	if (!CBCGToolBar::IsCustomizeMode ())
	{
		return;
	}

	if (m_pParentBtn == NULL)
	{
		return;
	}

	ASSERT_VALID (m_pParentBtn);

	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	HMENU hmenu = pMenuBar->ExportToMenu ();
	ASSERT (hmenu != NULL);

	m_pParentBtn->CreateFromMenu (hmenu);
	::DestroyMenu (hmenu);

	CBCGPopupMenu* pParentMenu = GetParentPopupMenu ();
	if (pParentMenu != NULL)
	{
		pParentMenu->SaveState ();
	}
}
//****************************************************************************************
void CBCGPopupMenu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	ASSERT_VALID (this);

	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

#ifdef _DEBUG
	if (m_pParentBtn != NULL)
	{
		ASSERT_VALID (m_pParentBtn);
		ASSERT (m_pParentBtn->m_pPopupMenu == this);
	}
#endif // _DEBUG

	switch (nChar)
	{
	case VK_RIGHT:
		{
			//-------------------------------
			// Try to open next cascade menu:
			//-------------------------------
			CBCGToolbarMenuButton* pSelItem = GetSelItem ();
			if (pSelItem != NULL && pSelItem->OpenPopupMenu ())
			{
				if (pSelItem->m_pPopupMenu != NULL)
				{
					//--------------------------
					// Select a first menu item:
					//--------------------------
					pSelItem->m_pPopupMenu->OnKeyDown (VK_HOME, 0, 0);
				}
			}
			else
			{
				//------------------------------------------------------
				// No next menu, first try to go to the parent menu bar:
				//------------------------------------------------------
				CBCGToolBar* pToolBar = GetParentToolBar ();
				if (pToolBar != NULL && 
					!pToolBar->IsKindOf (RUNTIME_CLASS (CBCGPopupMenuBar)))
				{
					pToolBar->NextMenu ();
				}
				else
				{
					//------------------------------------------------------
					// Close the current menu and move control to the parent
					// popup menu:
					//------------------------------------------------------
					CBCGPopupMenu* pParenMenu = GetParentPopupMenu ();
					if (pParenMenu != NULL)
					{
						pParenMenu->SendMessage (WM_KEYDOWN, VK_RIGHT);
					}
				}
			}
		}
		break;
				
	case VK_LEFT:
		{
			CBCGToolBar* pToolBar = GetParentToolBar ();
			if (pToolBar != NULL)
			{
				pToolBar->PrevMenu ();
			}
			else if (m_pParentBtn != NULL && m_pParentBtn->IsDroppedDown ())		
			{
				CloseMenu ();
			}
		}
		break;

	case VK_DOWN:
	case VK_UP:
	case VK_HOME:
	case VK_END:
	case VK_RETURN:
		pMenuBar->OnKey (nChar);
		break;

	case VK_ESCAPE:
		CloseMenu (TRUE);
		break;

	default:
		if (!pMenuBar->OnKey (nChar))
		{
			CMiniFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
		}
	}

	if (m_bScrollable && pMenuBar->m_iSelected >= 0)
	{
		//---------------------------------------
		// Maybe, selected item is invisible now?
		//---------------------------------------
		
	}
}
//****************************************************************************************
CBCGPopupMenu* CBCGPopupMenu::GetParentPopupMenu () const
{
	if (m_pParentBtn == NULL)
	{
		return NULL;
	}

	CBCGPopupMenuBar* pParentBar = 
		DYNAMIC_DOWNCAST (CBCGPopupMenuBar, m_pParentBtn->m_pWndParent);
	if (pParentBar != NULL)
	{
		CBCGPopupMenu* pParentMenu =
			DYNAMIC_DOWNCAST (CBCGPopupMenu, pParentBar->GetParentFrame ());
		ASSERT_VALID (pParentMenu);

		return pParentMenu;
	}
	else
	{
		return NULL;
	}
}
//****************************************************************************************
CBCGToolBar* CBCGPopupMenu::GetParentToolBar () const
{
	if (m_pParentBtn == NULL)
	{
		return NULL;
	}

	CBCGToolBar* pParentBar = 
		DYNAMIC_DOWNCAST (CBCGToolBar, m_pParentBtn->m_pWndParent);
	return pParentBar;
}
//****************************************************************************************
CBCGToolbarMenuButton* CBCGPopupMenu::GetSelItem ()
{
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	return DYNAMIC_DOWNCAST (CBCGToolbarMenuButton,
							pMenuBar->GetHighlightedButton ());
}
//****************************************************************************************
void CBCGPopupMenu::CloseMenu (BOOL bSetFocusToBar)
{
	SaveState ();

	CBCGPopupMenu* pParentMenu = GetParentPopupMenu ();
	CBCGToolBar* pParentToolBar = GetParentToolBar ();

	if (pParentMenu != NULL)
	{
		m_bAutoDestroyParent = FALSE;
		ActivatePopupMenu (pParentMenu);
	}
	else if (pParentToolBar != NULL)
	{
		ActivatePopupMenu (NULL);

		if (bSetFocusToBar)
		{
			pParentToolBar->SetFocus ();
		}
	}
	else
	{
		ActivatePopupMenu (NULL);
	}

	SendMessage (WM_CLOSE);
}
//****************************************************************************************
int CBCGPopupMenu::InsertItem (const CBCGToolbarMenuButton& button, int iInsertAt)
{
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	return pMenuBar->InsertButton (button, iInsertAt);
}
//****************************************************************************************
int CBCGPopupMenu::InsertSeparator (int iInsertAt)
{
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	return pMenuBar->InsertSeparator (iInsertAt);
}
//****************************************************************************************
BOOL CBCGPopupMenu::RemoveItem (int iIndex)
{
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	return pMenuBar->RemoveButton (iIndex);
}
//****************************************************************************************
void CBCGPopupMenu::RemoveAllItems ()
{
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	pMenuBar->RemoveAllButtons ();
}
//****************************************************************************************
BOOL CBCGPopupMenu::OnEraseBkgnd(CDC* pDC) 
{
	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	rectClient.left = rectClient.right - 2 * iBorderSize;
	pDC->FillSolidRect (rectClient, globalData.clrBtnFace);
	return TRUE;
}
//****************************************************************************************
void CBCGPopupMenu::ActivatePopupMenu (CBCGPopupMenu* pPopupMenu)
{
	CBCGMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGMDIFrameWnd, AfxGetMainWnd ());
	if (pMainFrame != NULL)
	{
		pMainFrame->OnShowPopupMenu (pPopupMenu);
	}
	else	// Maybe, SDI frame...
	{
		CBCGFrameWnd* pFrame = DYNAMIC_DOWNCAST (CBCGFrameWnd, AfxGetMainWnd ());
		if (pFrame != NULL)
		{
			pFrame->OnShowPopupMenu (pPopupMenu);
		}
		else	// Maybe, OLE frame
		{
			CBCGOleIPFrameWnd* pOleFrame = 
				DYNAMIC_DOWNCAST (CBCGOleIPFrameWnd, AfxGetMainWnd ());
			if (pOleFrame != NULL)
			{
				pOleFrame->OnShowPopupMenu (pPopupMenu);
			}
		}
	}
}
//************************************************************************************
void CBCGPopupMenu::OnActivateApp(BOOL bActive, HTASK /*hTask*/) 
{
	if (!bActive && !CBCGToolBar::IsCustomizeMode ())
	{
		SendMessage (WM_CLOSE);
	}
}
//*************************************************************************************
void CBCGPopupMenu::OnTimer(UINT nIDEvent) 
{
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	switch (nIDEvent)
	{
	case iAnimTimerId:
		{
			m_AnimSize.cy += pMenuBar->GetRowHeight ();
			if (m_AnimationType == UNFOLD)
			{
				m_AnimSize.cx += pMenuBar->GetColumnWidth ();
			}

			if (m_AnimSize.cy >= m_FinalSize.cy ||
				(m_AnimationType == UNFOLD && m_AnimSize.cx >= m_FinalSize.cx))
			{
				m_bIsAnimate = FALSE;

				m_AnimSize.cx = m_FinalSize.cx;
				m_AnimSize.cy = m_FinalSize.cy;

				KillTimer (iAnimTimerId);
				pMenuBar->SetOffset (0);
			}
			else
			{
				pMenuBar->SetOffset (pMenuBar->GetOffset () - 1);
			}

			// Invalidate border:
			CRect rectClient;
			GetClientRect (rectClient);

			SetWindowPos (NULL, -1, -1, m_AnimSize.cx, m_AnimSize.cy,
						SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

			InvalidateRect (CRect (	CPoint (rectClient.left, rectClient.top),
									CSize (rectClient.Width (), iBorderSize)));
			InvalidateRect (CRect (	CPoint (rectClient.left, rectClient.top),
									CSize (iBorderSize, rectClient.Height ())));
			InvalidateRect (CRect (	CPoint (rectClient.right - iBorderSize, rectClient.top),
									CSize (iBorderSize, rectClient.Height ())));

			InvalidateRect (m_rectScrollUp);
		}
		break;

	case iScrollTimerId:
		{
			CPoint point;
			::GetCursorPos (&point);
			ScreenToClient (&point);

			int iOffset = pMenuBar->GetOffset ();

			if (m_rectScrollUp.PtInRect (point) && m_iScrollMode < 0 &&
				IsScrollUpAvailable ())	// Scroll Up
			{
				pMenuBar->SetOffset (iOffset - 1);
				pMenuBar->AdjustLayout ();
			}
			else if (m_rectScrollDn.PtInRect (point) && m_iScrollMode > 0 &&
				IsScrollDnAvailable ())	// Scroll Down
			{
				pMenuBar->SetOffset (iOffset + 1);
				pMenuBar->AdjustLayout ();
			}
			else
			{
				KillTimer (iScrollTimerId);
				m_iScrollMode = 0;
				InvalidateRect (m_rectScrollDn);
				InvalidateRect (m_rectScrollUp);
			}
		}
		break;
	}

	CMiniFrameWnd::OnTimer(nIDEvent);
}
//****************************************************************************************
void CBCGPopupMenu::OnMouseMove(UINT nFlags, CPoint point) 
{
	CMiniFrameWnd::OnMouseMove(nFlags, point);

	if (!m_bScrollable || m_iScrollMode != 0)
	{
		return;
	}
	
	if (m_rectScrollUp.PtInRect (point) && IsScrollUpAvailable ())
	{
		m_iScrollMode = -1;
		InvalidateRect (m_rectScrollUp);
	}
	else if (m_rectScrollDn.PtInRect (point) && IsScrollDnAvailable ())
	{
		m_iScrollMode = 1;
		InvalidateRect (m_rectScrollDn);
	}
	else
	{
		m_iScrollMode = 0;
	}

	if (m_iScrollMode != 0)
	{
		SetTimer (iScrollTimerId, iScrollTimerDuration, NULL);
	}
}
//****************************************************************************************
BOOL CBCGPopupMenu::IsScrollUpAvailable ()
{
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	return pMenuBar->GetOffset () > 0;
}
//****************************************************************************************
BOOL CBCGPopupMenu::IsScrollDnAvailable ()
{
	CBCGPopupMenuBar* pMenuBar = GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	if (pMenuBar->GetRowHeight () == 0)
	{
		return FALSE;
	}

	int iTotalRows = m_FinalSize.cy / pMenuBar->GetRowHeight () - 2;
	return (pMenuBar->GetOffset () < 
		pMenuBar->m_Buttons.GetCount () - iTotalRows);
}
//****************************************************************************************
void CBCGPopupMenu::CollapseSubmenus ()
{
	for (POSITION pos = m_wndMenuBar.m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = 
			(CBCGToolbarButton*) m_wndMenuBar.m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		pButton->OnCancelMode ();
	}
}