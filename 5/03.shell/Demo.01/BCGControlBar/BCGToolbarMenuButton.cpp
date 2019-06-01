// BCGToolbarMenuButton.cpp: implementation of the CBCGToolbarMenuButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <..\\src\\afximpl.h>
#include <afxpriv.h>

#include "bcgbarres.h"
#include "BCGToolbarMenuButton.h"
#include "BCGMenuBar.h"
#include "BCGPopupMenuBar.h"
#include "ImageHash.h"
#include "globals.h"
#include "bcglocalres.h"
#include "BCGKeyboardManager.h"

#include "BCGFrameWnd.h"
#include "BCGMDIFrameWnd.h"
#include "BCGOleIPFrameWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const int SEPARATOR_SIZE = 2;
static const COLORREF clrTransparent = RGB (255, 0, 255);
static const int iImageWidth = 9;
static const int TEXT_MARGIN = 3;

static const int iImgIdArowDown = 0;
static const int iImgIdArowDownDsbl = 1;
static const int iImgIdArowLeft = 2;
static const int iImgIdArowLeftDsbl = 3;
static const int iImgIdArowLeftWhite = 4;
static const int iImgIdArowLeftWhiteDsbl = 5;
static const int iImgIdCheck = 6;
static const int iImgIdCheckDsbl = 7;
static const int iImgIdMinimize = 8;
static const int iImgIdMinimizeDsbl = 9;
static const int iImgIdRestore = 10;
static const int iImgIdRestoreDsbl = 11;
static const int iImgIdClose = 12;
static const int iImgIdCloseDsbl = 13;
static const int iImgIdMaximize = 14;
static const int iImgIdMaximizeDsbl = 15;

CImageList CBCGToolbarMenuButton::m_Images;
CSize CBCGToolbarMenuButton::m_sizeImageArrow;

IMPLEMENT_SERIAL(CBCGToolbarMenuButton, CBCGToolbarButton, VERSIONABLE_SCHEMA | 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGToolbarMenuButton::CBCGToolbarMenuButton()
{
	m_nID = 0;
	m_bDrawDownArrow = FALSE;
	m_bText = FALSE;
	m_bImage = TRUE;
	m_bMenuMode = FALSE;
	m_pPopupMenu = NULL;
	m_pWndParent = NULL;
	m_bUserButton = FALSE;
	m_bDefault = FALSE;
	m_bClickedOnMenu = FALSE;
	m_bHorz = TRUE;
}
//*****************************************************************************************
CBCGToolbarMenuButton::CBCGToolbarMenuButton (UINT uiID, HMENU hMenu, 
								int iImage, LPCTSTR lpszText, BOOL bUserButton)
{
	m_nID = uiID;
	m_nStyle = TBBS_BUTTON;
	m_bUserButton = bUserButton;

	SetImage (iImage);
	m_strText = (lpszText == NULL) ? _T("") : lpszText;
	m_bDragFromCollection = FALSE;
	m_bText = FALSE;
	m_bImage = TRUE;
	m_bDrawDownArrow = FALSE;
	m_bMenuMode = FALSE;

	CreateFromMenu (hMenu);
	m_rect.SetRectEmpty ();

	m_pPopupMenu = NULL;
	m_pWndParent = NULL;

	m_bDefault = FALSE;

	m_bClickedOnMenu = FALSE;
	m_bHorz = TRUE;
}
//*****************************************************************************************
CBCGToolbarMenuButton::CBCGToolbarMenuButton (const CBCGToolbarMenuButton& src)
{
	m_nID = src.m_nID;
	m_nStyle = src.m_nStyle;
	m_bUserButton = src.m_bUserButton;

	SetImage (src.GetImage ());
	m_strText = src.m_strText;
	m_bDragFromCollection = FALSE;
	m_bText = src.m_bText;
	m_bImage = src.m_bImage;
	m_bDrawDownArrow = src.m_bDrawDownArrow;
	m_bMenuMode = src.m_bMenuMode;
	m_bDefault = src.m_bDefault;

	HMENU hmenu = src.CreateMenu ();
	ASSERT (hmenu != NULL);

	CreateFromMenu (hmenu);
	::DestroyMenu (hmenu);

	m_rect.SetRectEmpty ();

	m_pPopupMenu = NULL;
	m_pWndParent = NULL;

	m_bClickedOnMenu = FALSE;
	m_bHorz = TRUE;
}
//*****************************************************************************************
CBCGToolbarMenuButton::~CBCGToolbarMenuButton()
{
	if (m_pPopupMenu != NULL)
	{
		m_pPopupMenu->m_pParentBtn = NULL;
	}

	while (!m_listCommands.IsEmpty ())
	{
		delete m_listCommands.RemoveHead ();
	}
}

//////////////////////////////////////////////////////////////////////
// Overrides:

void CBCGToolbarMenuButton::CopyFrom (const CBCGToolbarButton& s)
{
	CBCGToolbarButton::CopyFrom (s);

	const CBCGToolbarMenuButton& src = (const CBCGToolbarMenuButton&) s;

	m_bDefault = src.m_bDefault;

	while (!m_listCommands.IsEmpty ())
	{
		delete m_listCommands.RemoveHead ();
	}

	for (POSITION pos = src.m_listCommands.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarMenuButton* pItem = (CBCGToolbarMenuButton*) src.m_listCommands.GetNext (pos);
		ASSERT (pItem != NULL);
		ASSERT_KINDOF (CBCGToolbarMenuButton, pItem);

		CRuntimeClass* pSrcClass = pItem->GetRuntimeClass ();
		ASSERT (pSrcClass != NULL);

		CBCGToolbarMenuButton* pNewItem = (CBCGToolbarMenuButton*) pSrcClass->CreateObject ();
		ASSERT (pNewItem != NULL);
		ASSERT_KINDOF (CBCGToolbarMenuButton, pNewItem);

		pNewItem->CopyFrom (*pItem);
		m_listCommands.AddTail (pNewItem);
	}

//	m_nID = 0;	?????
}
//*****************************************************************************************
void CBCGToolbarMenuButton::Serialize (CArchive& ar)
{
	CBCGToolbarButton::Serialize (ar);

	if (ar.IsLoading ())
	{
		while (!m_listCommands.IsEmpty ())
		{
			delete m_listCommands.RemoveHead ();
		}
	}

	m_listCommands.Serialize (ar);
}
//*****************************************************************************************
void CBCGToolbarMenuButton::OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
			BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight,
			BOOL bDrawBorder, BOOL bGrayDisabledButtons)
{
	if (m_bMenuMode)
	{
		DrawMenuItem (pDC, rect, pImages, bCustomizeMode, bHighlight);
		return;
	}

	//---------------
	// Interior grey:
	//---------------
	pDC->FillSolidRect (&rect, globalData.clrBtnFace);

	if (!bCustomizeMode && !bHighlight &&
		(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)))
	{
		CRect rectDither = rect;
		rectDither.InflateRect (-afxData.cxBorder2, -afxData.cyBorder2);

		CBCGToolBarImages::FillDitheredRect (pDC, rectDither);
	}

	CRect rectParent = rect;
	CRect rectArrow = rect;

	if (m_bDrawDownArrow)
	{
		if (bHorz)
		{
			rectParent.right -= m_sizeImageArrow.cx + SEPARATOR_SIZE;
			rectArrow.left = rectParent.right;
		}
		else
		{
			rectParent.bottom -= m_sizeImageArrow.cy + SEPARATOR_SIZE;
			rectArrow.top = rectParent.bottom;
		}
	}

	UINT uiStyle = m_nStyle;

	if (m_bClickedOnMenu && m_nID != 0 && m_nID != (UINT) -1)
	{
		m_nStyle &= ~TBBS_PRESSED;
	}
	else if (m_pPopupMenu != NULL)
	{
		m_nStyle |= TBBS_PRESSED;
	}

	CBCGToolbarButton::OnDraw (pDC, rectParent, pImages, bHorz, 
			bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

	if (m_bDrawDownArrow)
	{
		if (m_nStyle & (TBBS_PRESSED | TBBS_CHECKED))
		{
			rectArrow.OffsetRect (1, 1);
		}

		if ((bHighlight || (m_nStyle & TBBS_PRESSED) ||
			m_pPopupMenu != NULL) &&
			m_nID != 0 && m_nID != (UINT) -1)
		{
			//----------------
			// Draw separator:
			//----------------
			CRect rectSeparator = rectArrow;

			if (bHorz)
			{
				rectSeparator.right = rectSeparator.left + SEPARATOR_SIZE;
			}
			else
			{
				rectSeparator.bottom = rectSeparator.top + SEPARATOR_SIZE;
			}

			pDC->Draw3dRect (rectSeparator, ::GetSysColor (COLOR_3DSHADOW),
											::GetSysColor (COLOR_3DHILIGHT));
		}

		BOOL bDisabled = (bCustomizeMode && !IsEditable ()) ||
			(!bCustomizeMode && (m_nStyle & TBBS_DISABLED));

		ASSERT (m_Images.GetSafeHandle () != NULL);

		int iImage;
		if (bHorz)
		{
			iImage = (bDisabled) ? iImgIdArowDownDsbl : iImgIdArowDown;
		}
		else
		{
			iImage = (bDisabled) ? iImgIdArowLeftDsbl : iImgIdArowLeft;
		}

		if (m_pPopupMenu != NULL &&
			(m_nStyle & (TBBS_PRESSED | TBBS_CHECKED)) == 0)
		{
			rectArrow.OffsetRect (1, 1);
		}

		CPoint pointImage (
			rectArrow.left + (rectArrow.Width () - m_sizeImageArrow.cx) / 2,
			rectArrow.top + (rectArrow.Height () - m_sizeImageArrow.cy) / 2);

		m_Images.Draw (pDC, iImage, pointImage, ILD_NORMAL);
	}

	if (!bCustomizeMode)
	{
		if ((m_nStyle & (TBBS_PRESSED | TBBS_CHECKED)) ||
			m_pPopupMenu != NULL)
		{
			//-----------------------
			// Pressed in or checked:
			//-----------------------
			if (m_bClickedOnMenu && m_nID != 0 && m_nID != (UINT) -1)
			{
				pDC->Draw3dRect (&rectParent,
					globalData.clrBtnHilite,
					globalData.clrBtnShadow);

				rectArrow.right --;
				rectArrow.bottom --;

				pDC->Draw3dRect (&rectArrow,
					globalData.clrBtnShadow,
					globalData.clrBtnHilite);
			}
			else
			{
				pDC->Draw3dRect (&rect,
					globalData.clrBtnShadow,
					globalData.clrBtnHilite);
			}
		}
		else if (bHighlight && !(m_nStyle & TBBS_DISABLED) &&
			!(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)))
		{
			pDC->Draw3dRect (&rect, globalData.clrBtnHilite,
									globalData.clrBtnShadow);
		}
	}

	m_nStyle = uiStyle;
}
//*****************************************************************************************
SIZE CBCGToolbarMenuButton::OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz)
{
	m_bHorz = bHorz;

	int iArrowSize = 0;

	if (m_bDrawDownArrow || m_bMenuMode)
	{
		if (m_Images.GetSafeHandle () == NULL)
		{
			CBCGLocalResource locaRes;
			m_Images.Create (IDB_BCGBARRES_MENU_IMAGES, iImageWidth, 0, clrTransparent);

			IMAGEINFO imageInfo;
			m_Images.GetImageInfo (0, &imageInfo);

			CRect rectImage = imageInfo.rcImage;
			m_sizeImageArrow = rectImage.Size ();
		}

		iArrowSize = (bHorz) ? 
			m_sizeImageArrow.cx + SEPARATOR_SIZE - TEXT_MARGIN : 
			m_sizeImageArrow.cy + SEPARATOR_SIZE - TEXT_MARGIN;
	}

	//--------------------
	// Change accelerator:
	//--------------------
	if (g_pKeyboardManager != NULL &&
		m_bMenuMode &&
		(m_nID < 0xF000 || m_nID >= 0xF1F0))	// Not system.
	{
		//-----------------------------------
		// Remove standard aceleration label:
		//-----------------------------------
		int iTabOffset = m_strText.Find (_T('\t'));
		if (iTabOffset >= 0)
		{
			m_strText = m_strText.Left (iTabOffset);
		}

		//---------------------------------
		// Add an actual accelartion label:
		//---------------------------------
		CString strAccel;
		CFrameWnd* pParent = 
			DYNAMIC_DOWNCAST (CFrameWnd, AfxGetMainWnd ());

		if (pParent != NULL &&
			(CBCGKeyboardManager::FindDefaultAccelerator (
				m_nID, strAccel, pParent) ||
			CBCGKeyboardManager::FindDefaultAccelerator (
				m_nID, strAccel, pParent->GetActiveFrame ())))
		{
			m_strText += _T('\t');
			m_strText += strAccel;
		}
	}

	CSize size = CBCGToolbarButton::OnCalculateSize (pDC, sizeDefault, bHorz);
	if (bHorz)
	{	
		size.cx += iArrowSize;
	}
	else
	{
		size.cy += iArrowSize;
	}

	if (m_bMenuMode)
	{
		size.cx += sizeDefault.cx + 2 * TEXT_MARGIN;
	}

	return size;
}
//*****************************************************************************************
BOOL CBCGToolbarMenuButton::OnClick (CWnd* pWnd, BOOL bDelay)
{
	ASSERT_VALID (pWnd);
	
	m_bClickedOnMenu = FALSE;

	if (m_bDrawDownArrow && !bDelay && !m_bMenuMode)
	{
		if (m_nID == 0 || m_nID == (UINT) -1)
		{
			m_bClickedOnMenu = TRUE;
		}
		else
		{
			CPoint ptMouse;
			::GetCursorPos (&ptMouse);
			pWnd->ScreenToClient (&ptMouse);

			CRect rectArrow = m_rect;
			if (m_bHorz)
			{
				rectArrow.left = rectArrow.right - m_sizeImageArrow.cx - SEPARATOR_SIZE;
			}
			else
			{
				rectArrow.top = rectArrow.bottom - m_sizeImageArrow.cy - SEPARATOR_SIZE;
			}

			m_bClickedOnMenu = rectArrow.PtInRect (ptMouse);
			if (!m_bClickedOnMenu)
			{
				return FALSE;
			}
		}
	}

	if (!m_bClickedOnMenu && m_nID > 0 && m_nID != (UINT) -1 && !m_bDrawDownArrow)
	{
		return FALSE;
	}

	CBCGMenuBar* pMenuBar = DYNAMIC_DOWNCAST (CBCGMenuBar, m_pWndParent);

	if (m_pPopupMenu != NULL)
	{
		//-----------------------------------------------------
		// Second click to the popup menu item closes the menu:
		//-----------------------------------------------------		
		ASSERT_VALID(m_pPopupMenu);

		m_pPopupMenu->m_bAutoDestroyParent = FALSE;
		m_pPopupMenu->DestroyWindow ();
		m_pPopupMenu = NULL;

		if (pMenuBar != NULL)
		{
			pMenuBar->SetHot (NULL);
		}
	}
	else
	{
		CBCGPopupMenuBar* pParentMenu =
			DYNAMIC_DOWNCAST (CBCGPopupMenuBar, m_pWndParent);

		if (bDelay && pParentMenu != NULL && !CBCGToolBar::IsCustomizeMode ())
		{
			pParentMenu->StartPopupMenuTimer (this);
		}
		else
		{
			//------------------------------------
			// Fixed by Sven Ritter (SpeedProject)
			//------------------------------------
			if (pMenuBar != NULL)
			{
				CBCGToolbarMenuButton* pCurrPopupMenuButton = 
					pMenuBar->GetDroppedDownMenu();
				if (pCurrPopupMenuButton != NULL)
				{
					pCurrPopupMenuButton->OnCancelMode ();
				}
			}
			// ***  End *************************
			
			if (!OpenPopupMenu (pWnd))
			{
				return FALSE;
			}
		}

		if (pMenuBar != NULL)
		{
			pMenuBar->SetHot (this);
		}
	}

	if (m_pWndParent != NULL)
	{
		m_pWndParent->InvalidateRect (m_rect);
	}

	return TRUE;
}
//****************************************************************************************
void CBCGToolbarMenuButton::OnChangeParentWnd (CWnd* pWndParent)
{
	if (pWndParent != NULL)
	{
		if (pWndParent->IsKindOf (RUNTIME_CLASS (CBCGMenuBar)))
		{
			m_bDrawDownArrow = FALSE;
			m_bText = TRUE;
			m_bImage = FALSE;
		}
		else
		{
			m_bDrawDownArrow = !m_listCommands.IsEmpty ();
		}

		if (pWndParent->IsKindOf (RUNTIME_CLASS (CBCGPopupMenuBar)))
		{
			m_bMenuMode = TRUE;
			m_bText = TRUE;
			m_bImage = FALSE;
			m_bDrawDownArrow = !m_listCommands.IsEmpty ();
		}
		else
		{
			m_bMenuMode = FALSE;
		}
	}

	m_pWndParent = pWndParent;
}
//****************************************************************************************
void CBCGToolbarMenuButton::CreateFromMenu (HMENU hMenu)
{
	while (!m_listCommands.IsEmpty ())
	{
		delete m_listCommands.RemoveHead ();
	}

	CMenu* pMenu = CMenu::FromHandle (hMenu);
	if (pMenu == NULL)
	{
		return;
	}

	UINT uiDefaultCmd = ::GetMenuDefaultItem (hMenu, FALSE, GMDI_USEDISABLED);

	int iCount = (int) pMenu->GetMenuItemCount ();
	for (int i = 0; i < iCount; i ++)
	{
		CBCGToolbarMenuButton* pItem = new CBCGToolbarMenuButton;
		ASSERT_VALID (pItem);

		pItem->m_nID = pMenu->GetMenuItemID (i);
		pMenu->GetMenuString (i, pItem->m_strText, MF_BYPOSITION);

		if (pItem->m_nID == -1)	// Sub-menu...
		{
			CMenu* pSubMenu = pMenu->GetSubMenu (i);
			ASSERT (pSubMenu != NULL);

			pItem->CreateFromMenu (pSubMenu->GetSafeHmenu ());
		}
		else if (pItem->m_nID == uiDefaultCmd)
		{
			pItem->m_bDefault = TRUE;
		}

		m_listCommands.AddTail (pItem);
	}
}
//****************************************************************************************
HMENU CBCGToolbarMenuButton::CreateMenu () const
{
	if (m_listCommands.IsEmpty ())
	{
		return NULL;
	}

	CMenu menu;
	if (!menu.CreatePopupMenu ())
	{
		TRACE(_T("CBCGToolbarMenuButton::CreateMenu (): Can't create popup menu!\n"));
		return NULL;
	}

	BOOL bRes = TRUE;
	DWORD dwLastError = 0;

	UINT uiDefaultCmd = (UINT) -1;

	int i = 0;
	for (POSITION pos = m_listCommands.GetHeadPosition (); pos != NULL; i ++)
	{
		CBCGToolbarMenuButton* pItem = (CBCGToolbarMenuButton*) m_listCommands.GetNext (pos);
		ASSERT (pItem != NULL);
		ASSERT_KINDOF (CBCGToolbarButton, pItem);

		switch (pItem->m_nID)
		{
		case 0:	// Separator
			bRes = menu.AppendMenu (MF_SEPARATOR);
			if (!bRes)
			{
				dwLastError = GetLastError ();
			}
			break;

		case -1:			// Sub-menu
			{
				HMENU hSubMenu = pItem->CreateMenu ();
				ASSERT (hSubMenu != NULL);

				bRes = menu.AppendMenu (MF_POPUP | MF_STRING,
										(UINT) hSubMenu, pItem->m_strText);
				if (!bRes)
				{
					dwLastError = GetLastError ();
				}

				//--------------------------------------------------------
				// This is incompatibility between Windows 95 and 
				// NT API! (IMHO). CMenu::AppendMenu with MF_POPUP flag 
				// COPIES sub-menu resource under the Win NT and 
				// MOVES sub-menu under Win 95!
				//--------------------------------------------------------
				if (globalData.bIsWindowsNT)
				{
					::DestroyMenu (hSubMenu);
				}
			}
			break;

		default:
			if (pItem->m_bDefault)
			{
				uiDefaultCmd = pItem->m_nID;
			}

			bRes = menu.AppendMenu (MF_STRING, pItem->m_nID, pItem->m_strText);
			if (!bRes)
			{
				dwLastError = GetLastError ();
			}
		}

		if (!bRes)
		{
			TRACE(_T("CBCGToolbarMenuButton::CreateMenu (): Can't add menu item: %d\n Last error = %x\n"), pItem->m_nID, dwLastError);
			return NULL;
		}
	}

	HMENU hMenu = menu.Detach ();
	if (uiDefaultCmd != (UINT)-1)
	{
		::SetMenuDefaultItem (hMenu, uiDefaultCmd, FALSE);
	}

	return hMenu;
}
//*****************************************************************************************
void CBCGToolbarMenuButton::DrawMenuItem (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages, 
					BOOL bCustomizeMode, BOOL bHighlight)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (this);

	if (!bHighlight && m_pPopupMenu != NULL)
	{
		bHighlight = TRUE;
	}

	BOOL bDisabled = (bCustomizeMode && !IsEditable ()) ||
		(!bCustomizeMode && (m_nStyle & TBBS_DISABLED));

	CFont* pOldFont = NULL;

	CBCGPopupMenuBar* pParentMenu =
		DYNAMIC_DOWNCAST (CBCGPopupMenuBar, m_pWndParent);
	if (m_nID != 0 && m_nID != (UINT) -1 &&
		pParentMenu != NULL && pParentMenu->GetDefaultMenuId () == m_nID)
	{
		pOldFont = (CFont*) pDC->SelectObject (&globalData.fontBold);
	}

	//----------------
	// Draw the image:
	//----------------
	CRect rectImage;
	rectImage = rect;
	rectImage.left += 2;
	rectImage.right = rectImage.left + CBCGToolBar::GetMenuImageSize ().cx + 2;

	if (!IsDrawImage ())	// Try to find a matched image
	{
		BOOL bImageSave = m_bImage;
		BOOL bUserButton = m_bUserButton;
		BOOL bSuccess = TRUE;

		m_bImage = TRUE;	// Always try to draw image!
		m_bUserButton = TRUE;

		if (GetImage () < 0)
		{
			m_bUserButton = FALSE;

			if (GetImage () < 0)
			{
				bSuccess = FALSE;
			}
		}

		if (!bSuccess)
		{
			m_bImage = bImageSave;
			m_bUserButton = bUserButton;
		}
	}

	BOOL bImageIsReady = FALSE;

	CRgn rgnClip;
	rgnClip.CreateRectRgnIndirect (&rectImage);

	if (IsDrawImage ())
	{
		pDC->SelectObject (&rgnClip);

		CPoint ptImageOffset (1, (rect.Height () - CBCGToolBar::GetMenuImageSize ().cy) / 2);

		if ((m_nStyle & TBBS_CHECKED) && !bCustomizeMode)
		{
			ptImageOffset.x ++;
			ptImageOffset.y ++;
		}

		if ((m_nStyle & TBBS_PRESSED) || !(m_nStyle & TBBS_DISABLED) ||
						bCustomizeMode)
		{
			pImages->Draw (pDC, rectImage.left, rectImage.top, ptImageOffset, GetImage (),
				FALSE, FALSE, FALSE, TRUE);
			if (bCustomizeMode || m_nStyle & TBBS_PRESSED)
			{
				bImageIsReady = TRUE;
			}
		}

		if (!bImageIsReady)
		{
			BOOL bHighlightImage = bHighlight;
			if (!bHighlightImage)
			{
				bHighlightImage = !(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE));
			}

			pImages->Draw (pDC, rectImage.left, rectImage.top, ptImageOffset, 
							GetImage (), !bHighlightImage, bDisabled, FALSE,
							TRUE);
			bImageIsReady = TRUE;
		}
	}
	else
	{
		//------------------------------------
		// Get chance to user draw menu image:
		//------------------------------------
		CBCGMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGMDIFrameWnd, AfxGetMainWnd ());
		if (pMainFrame != NULL)
		{
			bImageIsReady = pMainFrame->OnDrawMenuImage (pDC, this, rectImage);
		}
		else	// Maybe, SDI frame...
		{
			CBCGFrameWnd* pFrame = DYNAMIC_DOWNCAST (CBCGFrameWnd, AfxGetMainWnd ());
			if (pFrame != NULL)
			{
				bImageIsReady = pFrame->OnDrawMenuImage (pDC, this, rectImage);
			}
			else	// Maybe, OLE frame...
			{
				CBCGOleIPFrameWnd* pOleFrame = 
					DYNAMIC_DOWNCAST (CBCGOleIPFrameWnd, AfxGetMainWnd ());
				if (pOleFrame != NULL)
				{
					bImageIsReady = pOleFrame->OnDrawMenuImage (pDC, this, rectImage);
				}
			}
		}
	}

	pDC->SelectClipRgn (NULL);
	rectImage.right ++;

	if (m_nStyle & TBBS_CHECKED && !bImageIsReady)
	{
		CRect rectCheck = rectImage;
		rectCheck.InflateRect (-2, -2);

		if (!bHighlight)
		{
			CBCGToolBarImages::FillDitheredRect (pDC, rectCheck);
		}

		CPoint pointCheck (
			rectCheck.left + (rectCheck.Width () - m_sizeImageArrow.cx) / 2,
			rectCheck.top + (rectCheck.Height () - m_sizeImageArrow.cy) / 2);

		int iImage = (m_nStyle & TBBS_DISABLED) ? iImgIdCheckDsbl : iImgIdCheck;
		m_Images.Draw (pDC, iImage, pointCheck, ILD_NORMAL);

		pDC->Draw3dRect (&rectCheck, globalData.clrBtnShadow, globalData.clrBtnHilite);
	}
	else if (bImageIsReady && bHighlight && !bDisabled && !(m_nStyle & TBBS_CHECKED))
	{
		pDC->Draw3dRect (&rectImage, globalData.clrBtnHilite, globalData.clrBtnShadow);
	}
	else if (bImageIsReady && (m_nStyle & TBBS_CHECKED))
	{
		pDC->Draw3dRect (&rectImage, globalData.clrBtnShadow, globalData.clrBtnHilite);
	}

	int iSystemImageId = -1;

	//-------------------------------
	// Try to draw system menu icons:
	//-------------------------------
	if (!bImageIsReady)
	{
		switch (m_nID)
		{
		case SC_MINIMIZE:
			iSystemImageId = bDisabled ? iImgIdMinimizeDsbl : iImgIdMinimize;
			break;

		case SC_RESTORE:
			iSystemImageId = bDisabled ? iImgIdRestoreDsbl : iImgIdRestore;
			break;

		case SC_CLOSE:
			iSystemImageId = bDisabled ? iImgIdCloseDsbl : iImgIdClose;
			break;

		case SC_MAXIMIZE:
			iSystemImageId = bDisabled ? iImgIdMaximizeDsbl : iImgIdMaximize;
			break;
		}

		if (iSystemImageId != -1)
		{
			CRect rectSysImage = rectImage;
			rectSysImage.InflateRect (-2, -2);

			CPoint pointSysImage (
				rectSysImage.left + (rectSysImage.Width () - m_sizeImageArrow.cx) / 2,
				rectSysImage.top + (rectSysImage.Height () - m_sizeImageArrow.cy) / 2);

			m_Images.Draw (pDC, iSystemImageId, pointSysImage, ILD_NORMAL);

			if (bHighlight)
			{
				pDC->Draw3dRect (&rectSysImage, globalData.clrBtnHilite, globalData.clrBtnShadow);
			}
		}
	}

	//-------------------------------
	// Fill text area if highlighted:
	//-------------------------------
	CRect rectText = rect;
	rectText.left = rectImage.right + 1;

	COLORREF clrText;

	if (bHighlight && !bCustomizeMode)
	{
		CRect rectFill = rect;
		if ((m_nStyle & (TBBS_CHECKED) || bImageIsReady) ||
			iSystemImageId != -1)
		{
			rectFill.left = rectText.left - 1;
		}
		else
		{
			rectFill.left += TEXT_MARGIN;
		}

		pDC->FillSolidRect (&rectFill, globalData.clrHilite);
		clrText =  bDisabled ?
						globalData.clrBtnFace : 
						globalData.clrTextHilite;
	}
	else
	{
		clrText	= bDisabled ?
						globalData.clrGrayedText : 
						globalData.clrBtnText;
	}

	//-------------------------
	// Find acceleration label:
	//-------------------------
	CString strText = m_strText;
	CString strAccel;

	int iTabOffset = m_strText.Find (_T('\t'));
	if (iTabOffset >= 0)
	{
		strText = strText.Left (iTabOffset);
		strAccel = m_strText.Mid (iTabOffset + 1);
	}

	//-----------
	// Draw text:
	//-----------
	rectText.left += TEXT_MARGIN;

	if (bDisabled && !bHighlight)
	{
		pDC->SetTextColor (globalData.clrBtnHilite);

		CRect rectShft = rectText;
		rectShft.OffsetRect (1, 1);
		pDC->DrawText (strText, &rectShft, DT_SINGLELINE | DT_VCENTER);
	}

	pDC->SetTextColor (clrText);
	pDC->DrawText (strText, &rectText, DT_SINGLELINE | DT_VCENTER);

	//------------------------
	// Draw accelerator label:
	//------------------------
	if (!strAccel.IsEmpty ())
	{
		CRect rectAccel = rectText;
		rectAccel.right -= TEXT_MARGIN + iImageWidth;

		if (bDisabled && !bHighlight)
		{
			pDC->SetTextColor (globalData.clrBtnHilite);

			CRect rectAccelShft = rectAccel;
			rectAccelShft.OffsetRect (1, 1);
			pDC->DrawText (strAccel, &rectAccelShft, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);
		}

		pDC->SetTextColor (clrText);
		pDC->DrawText (strAccel, &rectAccel, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);
	}

	//--------------------------------------------
	// Draw triangle image for the cascade menues:
	//--------------------------------------------
	if (m_nID == (UINT) -1 || m_bDrawDownArrow)
	{
		CRect rectTriangle = rect;
		rectTriangle.left = rectTriangle.right - iImageWidth;

		CPoint pointTriangle (
			rectTriangle.left + (rectTriangle.Width () - m_sizeImageArrow.cx) / 2,
			rectTriangle.top + (rectTriangle.Height () - m_sizeImageArrow.cy) / 2);

		int iImage = (bHighlight && !bCustomizeMode) ?
						(bDisabled ? iImgIdArowLeftWhiteDsbl : iImgIdArowLeftWhite) :
						(bDisabled ? iImgIdArowLeftDsbl : iImgIdArowLeft);
		m_Images.Draw (pDC, iImage, pointTriangle, ILD_NORMAL);
	}

	if (pOldFont != NULL)
	{
		pDC->SelectObject (pOldFont);
	}
}
//****************************************************************************************
void CBCGToolbarMenuButton::OnCancelMode ()
{
	if (m_pPopupMenu != NULL && ::IsWindow (m_pPopupMenu->m_hWnd))
	{
		m_pPopupMenu->SaveState ();
		m_pPopupMenu->m_bAutoDestroyParent = FALSE;
		m_pPopupMenu->DestroyWindow ();
	}

	m_pPopupMenu = NULL;

	if (m_pWndParent != NULL && ::IsWindow (m_pWndParent->m_hWnd))
	{
		m_pWndParent->InvalidateRect (m_rect);
		m_pWndParent->UpdateWindow ();
	}
}
//****************************************************************************************
BOOL CBCGToolbarMenuButton::OpenPopupMenu (CWnd* pWnd)
{
	if (m_pPopupMenu != NULL)
	{
		return FALSE;
	}

	if (pWnd == NULL)
	{
		pWnd = m_pWndParent;
	}

	ASSERT (pWnd != NULL);

	//---------------------------------------------------------------
	// Define a new menu position. Place the menu in the right side
	// of the current menu in the poup menu case or under the current 
	// item by default:
	//---------------------------------------------------------------
	CPoint point;

	CBCGPopupMenuBar* pParentMenu =
		DYNAMIC_DOWNCAST (CBCGPopupMenuBar, m_pWndParent);

	CBCGMenuBar* pParentMenuBar =
		DYNAMIC_DOWNCAST (CBCGMenuBar, m_pWndParent);

	if (pParentMenu != NULL)
	{
		point = CPoint (0, m_rect.top - 2);
		pWnd->ClientToScreen (&point);

		CRect rectParent;
		pParentMenu->GetWindowRect (rectParent);

		point.x = rectParent.right + 1;
	}
	else if (pParentMenuBar != NULL && 
		(pParentMenuBar->m_dwStyle & CBRS_ORIENT_HORZ) == 0)
	{
		//------------------------------------------------
		// Parent menu bar is docked vertical, place menu 
		// in the left or right side of the parent frame:
		//------------------------------------------------
		point = CPoint (m_rect.right + 1, m_rect.top);
		pWnd->ClientToScreen (&point);
	}
	else
	{
		point = CPoint (m_rect.left - 1, m_rect.bottom);
		pWnd->ClientToScreen (&point);
	}

	HMENU hMenu = CreateMenu ();
	if (hMenu == NULL && !IsEmptyMenuAllowed ())
	{
		return FALSE;
	}

	m_pPopupMenu = CreatePopupMenu ();
	if (m_pPopupMenu == NULL)
	{
		return FALSE;
	}

	m_pPopupMenu->m_pParentBtn = this;
	if (!m_pPopupMenu->Create (pWnd, point.x, point.y, hMenu))
	{
		m_pPopupMenu = NULL;
		return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarMenuButton diagnostics

#ifdef _DEBUG
void CBCGToolbarMenuButton::AssertValid() const
{
	CObject::AssertValid();
}
//******************************************************************************************
void CBCGToolbarMenuButton::Dump(CDumpContext& dc) const
{
	CObject::Dump (dc);

	CString strId;
	strId.Format (_T("%x"), m_nID);

	dc << "[" << m_strText << " >>>>> ]";
	dc.SetDepth (dc.GetDepth () + 1);

	dc << "{\n";
	for (POSITION pos = m_listCommands.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_listCommands.GetNext (pos);
		ASSERT_VALID (pButton);

		pButton->Dump (dc);
		dc << "\n";
	}

	dc << "}\n";
	dc.SetDepth (dc.GetDepth () - 1);
	dc << "\n";
}

#endif

//******************************************************************************************
int CBCGToolbarMenuButton::OnDrawOnCustomizeList (
	CDC* pDC, const CRect& rect, BOOL bSelected)
{
	CBCGToolbarButton::OnDrawOnCustomizeList (pDC, rect, bSelected);

	if (m_nID == (UINT) -1)	// Popup menu
	{
		CRect rectTriangle = rect;
		rectTriangle.left = rectTriangle.right - iImageWidth;

		CPoint pointTriangle (
			rectTriangle.left + (rectTriangle.Width () - m_sizeImageArrow.cx) / 2,
			rectTriangle.top + (rectTriangle.Height () - m_sizeImageArrow.cy) / 2);

		int iImage = (bSelected) ? iImgIdArowLeftWhite : iImgIdArowLeft;
		m_Images.Draw (pDC, iImage, pointTriangle, ILD_NORMAL);
	}

	return rect.Width ();
}
//*******************************************************************************************
BOOL CBCGToolbarMenuButton::OnBeforeDrag () const
{
	if (m_pPopupMenu != NULL)	// Is dropped down
	{
		m_pPopupMenu->CollapseSubmenus ();
	}

	return CBCGToolbarButton::OnBeforeDrag ();
}
