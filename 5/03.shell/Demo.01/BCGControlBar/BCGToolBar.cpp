// bcgtoolbar.cpp : definition of CBCGToolBar
//
// This code is based on the Microsoft Visual C++ sample file
// TOOLBAR.C from the OLDBARS example
//

#include "stdafx.h"
#include "bcgbarres.h"
#include <afxpriv.h>
#include <..\\src\\afximpl.h>
#include "BCGtoolbar.h"
#include "globals.h"
#include "BCGToolbarButton.h"
#include "BCGToolbarDropSource.h"
#include "ButtonAppearanceDlg.h"
#include "CBCGToolbarCustomize.h"
#include "bcglocalres.h"
#include "Registry.h"
#include "BCGMDIFrameWnd.h"
#include "BCGFrameWnd.h"
#include "BCGKeyboardManager.h"
#include "BCGToolbarMenuButton.h"
#include "BCGToolbarSystemMenuButton.h"
#include "BCGPopupMenu.h"
#include "ImageHash.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define TEXT_MARGIN			3
#define STRETCH_DELTA		6
#define BUTTON_MIN_WIDTH	5
#define LINE_OFFSET			5

#define REG_SECTION_FMT		_T("%sBCGToolBar-%d")
#define REG_SECTION_FMT_EX	_T("%sBCGToolBar-%d%x")
#define REG_PARAMS_FMT		_T("%sBCGToolbarParameters")
#define REG_ENTRY_NAME		_T("Name")
#define REG_ENTRY_BUTTONS	_T("Buttons")
#define REG_ENTRY_TOOLTIPS	_T("Tooltips")
#define REG_ENTRY_KEYS		_T("ShortcutKeys")
#define REG_ENTRY_ANIMATION	_T("MenuAnimation")

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar notification messages:

UINT BCGM_TOOLBARMENU		= ::RegisterWindowMessage (_T("BCGTOOLBAR_POPUPMENU"));
UINT BCGM_CUSTOMIZETOOLBAR	= ::RegisterWindowMessage (_T("BCGTOOLBAR_CUSTOMIZE"));
UINT BCGM_CREATETOOLBAR		= ::RegisterWindowMessage (_T("BCGTOOLBAR_CREATE"));
UINT BCGM_DELETETOOLBAR		= ::RegisterWindowMessage (_T("BCGTOOLBAR_DELETE"));
UINT BCGM_CUSTOMIZEHELP		= ::RegisterWindowMessage (_T("BCGTOOLBAR_CUTOMIZEHELP"));
UINT BCGM_RESETTOOLBAR		= ::RegisterWindowMessage (_T("BCGTOOLBAR_RESETTOOLBAR"));

/////////////////////////////////////////////////////////////////////////////
// All CBCGToolBar collection:
CObList	gAllToolbars;

BOOL CBCGToolBar::m_bCustomizeMode = FALSE;
BOOL CBCGToolBar::m_bShowTooltips = TRUE;
BOOL CBCGToolBar::m_bShowShortcutKeys = TRUE;
CBCGToolbarDropSource CBCGToolBar::m_DropSource;

CBCGToolBarImages	CBCGToolBar::m_Images;
CBCGToolBarImages	CBCGToolBar::m_ColdImages;
CBCGToolBarImages	CBCGToolBar::m_MenuImages;
CBCGToolBarImages*	CBCGToolBar::m_pUserImages = NULL;

CSize CBCGToolBar::m_sizeButton = CSize (23, 22);
CSize CBCGToolBar::m_sizeImage	= CSize (16, 15);
CSize CBCGToolBar::m_sizeMenuImage	= CSize (-1, -1);
CSize CBCGToolBar::m_sizeMenuButton	= CSize (-1, -1);

CMap<UINT, UINT, int, int> CBCGToolBar::m_DefaultImages;

COLORREF CBCGToolBar::m_clrTextHot = (COLORREF) -1;
extern CBCGToolbarCustomize* g_pWndCustomize;

HHOOK CBCGToolBar::m_hookMouseHelp = NULL;
CBCGToolBar* CBCGToolBar::m_pLastHookedToolbar = NULL;

CList<UINT, UINT> CBCGToolBar::m_lstUnpermittedCommands;

BOOL CBCGToolBar::m_bAltCustomization = FALSE;

static inline BOOL IsSystemCommand (UINT uiCmd)
{
	return (uiCmd >= 0xF000 && uiCmd < 0xF1F0);
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar
IMPLEMENT_SERIAL(CBCGToolBar, CControlBar, VERSIONABLE_SCHEMA | 1)

CBCGToolBar::CBCGToolBar() :
	m_bMenuMode (FALSE)
{
	m_iButtonCapture = -1;      // nothing captured
	m_iHighlighted = -1;
	m_iSelected = -1;
	m_iHot = -1;

	m_iDragIndex = -1;
	m_rectDrag.SetRectEmpty ();
	m_pDragButton = NULL;
	m_ptStartDrag = CPoint (-1, -1);
	m_bIsDragCopy = FALSE;

	//---------------------
	// UISG standard sizes:
	//---------------------
	m_cyTopBorder = m_cyBottomBorder = 1;   // 1 pixel for top/bottom gaps

	m_bStretchButton = FALSE;
	m_rectTrack.SetRectEmpty ();

	m_iImagesOffset = 0;
	m_uiOriginalResID = 0;

	m_bTracked = FALSE;
	m_ptLastMouse = CPoint (-1, -1);
	m_pWndLastCapture = NULL;
	m_hwndLastFocus = NULL;

	m_bLocked = FALSE;
	m_bShowHotBorder = TRUE;
	m_bGrayDisabledButtons = TRUE;
}
//******************************************************************************************
CBCGToolBar::~CBCGToolBar()
{
	RemoveAllButtons ();
}
//******************************************************************************************
BOOL CBCGToolBar::Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID)
{
	return CBCGToolBar::CreateEx (pParentWnd, TBSTYLE_FLAT,
							dwStyle,
							CRect(1, 1, 1, 1),
							nID);
}
//******************************************************************************************
BOOL CBCGToolBar::CreateEx (CWnd* pParentWnd, 
							DWORD dwCtrlStyle,
							DWORD dwStyle,
							CRect rcBorders,
							UINT nID)
{
	dwStyle |= CBRS_GRIPPER;

	if (pParentWnd != NULL)
	{
		ASSERT_VALID(pParentWnd);   // must have a parent
	}

	if (rcBorders.left < 1)
	{
		rcBorders.left = 1;	// Otherwise, I have a problem woith a "double" grippers
	}

	if (rcBorders.top < 1)
	{
		rcBorders.top = 1;	// Otherwise, I have a problem woith a "double" grippers
	}

	SetBorders (rcBorders);

	//----------------
	// Save the style:
	//----------------
	m_dwStyle = (dwStyle & CBRS_ALL);
	if (nID == AFX_IDW_TOOLBAR)
	{
		m_dwStyle |= CBRS_HIDE_INPLACE;
	}

	dwStyle &= ~CBRS_ALL;
	dwStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;
	dwStyle |= dwCtrlStyle;

	//----------------------------
	// Initialize common controls:
	//----------------------------
	VERIFY (AfxDeferRegisterClass (AFX_WNDCOMMCTLS_REG));

	//-----------------
	// Create the HWND:
	//-----------------
	CRect rect;
	rect.SetRectEmpty();

	//-----------------------------
	// Register a new window class:
	//-----------------------------
	HINSTANCE hInst = AfxGetInstanceHandle();
	UINT uiClassStyle = CS_DBLCLKS;
	HCURSOR hCursor = ::LoadCursor (NULL, IDC_ARROW);
	HBRUSH hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

	CString strClassName;
	strClassName.Format (_T("BCGToolBar:%x:%x:%x:%x"), 
		(UINT)hInst, uiClassStyle, (UINT)hCursor, (UINT)hbrBackground);

	//---------------------------------
	// See if the class already exists:
	//---------------------------------
	WNDCLASS wndcls;
	if (::GetClassInfo (hInst, strClassName, &wndcls))
	{
		//-----------------------------------------------
		// Already registered, assert everything is good:
		//-----------------------------------------------
		ASSERT (wndcls.style == uiClassStyle);
	}
	else
	{
		//-------------------------------------------
		// Otherwise we need to register a new class:
		//-------------------------------------------
		wndcls.style = uiClassStyle;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = hCursor;
		wndcls.hbrBackground = hbrBackground;
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = strClassName;
		
		if (!AfxRegisterClass (&wndcls))
		{
			AfxThrowResourceException();
		}
	}

	if (!CControlBar::Create (strClassName, NULL, dwStyle, rect, pParentWnd, nID))
	{
		return FALSE;
	}

	return TRUE;
}
//******************************************************************************************
void CBCGToolBar::SetSizes (SIZE sizeButton, SIZE sizeImage)
{
	ASSERT(sizeButton.cx > 0 && sizeButton.cy > 0);

	//-----------------------------------------------------------------
	// Button must be big enough to hold image + 3 pixels on each side:
	//-----------------------------------------------------------------
	ASSERT(sizeButton.cx >= sizeImage.cx + 6);
	ASSERT(sizeButton.cy >= sizeImage.cy + 6);

	m_sizeButton = sizeButton;
	m_sizeImage = sizeImage;

	m_Images.SetSizes (m_sizeButton, m_sizeImage);
	m_ColdImages.SetSizes (m_sizeButton, m_sizeImage);

	if (m_pUserImages != NULL)
	{
		m_pUserImages->SetSizes (m_sizeButton, m_sizeImage);
	}
}
//******************************************************************************************
void CBCGToolBar::SetHeight(int cyHeight)
{
	ASSERT_VALID (this);

	int nHeight = cyHeight;
	
	if (m_dwStyle & CBRS_BORDER_TOP)
	{
		cyHeight -= afxData.cyBorder2;
	}

	if (m_dwStyle & CBRS_BORDER_BOTTOM)
	{
		cyHeight -= afxData.cyBorder2;
	}

	m_cyBottomBorder = (cyHeight - GetRowHeight ()) / 2;
	
	//-------------------------------------------------------
	// If there is an extra pixel, m_cyTopBorder will get it:
	//-------------------------------------------------------
	m_cyTopBorder = cyHeight - GetRowHeight () - m_cyBottomBorder;
	
	if (m_cyTopBorder < 0)
	{
		TRACE(_T("Warning: CBCGToolBar::SetHeight(%d) is smaller than button.\n"),
			nHeight);
		m_cyBottomBorder += m_cyTopBorder;
		m_cyTopBorder = 0;  // will clip at bottom
	}

	if (GetSafeHwnd () != NULL)
	{
		Invalidate ();
	}
}
//******************************************************************************************
BOOL CBCGToolBar::SetUserImages (CBCGToolBarImages* pUserImages)
{
	ASSERT (pUserImages != NULL);
	if (!pUserImages->IsValid ())
	{
		ASSERT (FALSE);
		return FALSE;
	}

	if (m_sizeImage != pUserImages->GetImageSize ())
	{
		ASSERT (FALSE);
		return FALSE;
	}

	m_pUserImages = pUserImages;
	return TRUE;
}
//******************************************************************************************
BOOL CBCGToolBar::SetButtons(const UINT* lpIDArray, int nIDCount)
{
	ASSERT_VALID(this);
	ASSERT(nIDCount >= 1);  // must be at least one of them
	ASSERT(lpIDArray == NULL ||
		AfxIsValidAddress(lpIDArray, sizeof(UINT) * nIDCount, FALSE));

	RemoveAllButtons ();

	if (lpIDArray == NULL)
	{
		while (nIDCount-- > 0)
		{
			InsertSeparator ();
		}
		
		return TRUE;
	}

	int iImage = m_iImagesOffset;

	//--------------------------------
	// Go through them adding buttons:
	//--------------------------------
	for (int i = 0; i < nIDCount; i ++)
	{
		int iCmd = *lpIDArray ++;

		if (iCmd == 0)	// Separator
		{
			InsertSeparator ();
		}
		else
		{
			if (InsertButton (CBCGToolbarButton (iCmd, iImage)) >= 0)
			{
				m_DefaultImages.SetAt (iCmd, iImage ++);
			}
		}
	}

	if (GetSafeHwnd () != NULL)
	{
		//------------------------------------
		// Allow to produce some user actions:
		//------------------------------------
		OnReset ();
		CWnd* pParentFrame = (m_pDockSite == NULL) ?
			GetParent () : m_pDockSite;
		if (pParentFrame != NULL)
		{
			pParentFrame->SendMessage (BCGM_RESETTOOLBAR, (WPARAM) m_uiOriginalResID);
		}
	}

	return TRUE;
}
//******************************************************************************************
BOOL CBCGToolBar::LoadBitmap (UINT uiResID, UINT uiColdResID, UINT uiMenuResID, 
							  BOOL bLocked)
{
	m_bLocked = bLocked;
	if (m_bLocked)
	{
		//------------------------------------------
		// Don't add bitmap to the shared resources!
		//------------------------------------------
		if (!m_ImagesLocked.Load (uiResID, AfxGetResourceHandle (), TRUE))
		{
			return FALSE;
		}

		if (uiColdResID != 0)
		{
			if (!m_ColdImagesLocked.Load (uiColdResID, AfxGetResourceHandle (), TRUE))
			{
				return FALSE;
			}

			ASSERT (m_ImagesLocked.GetCount () == m_ColdImagesLocked.GetCount ());
		}
		
		if (uiMenuResID != 0)
		{
			if (!m_MenuImagesLocked.Load (uiMenuResID, AfxGetResourceHandle (), TRUE))
			{
				return FALSE;
			}

			ASSERT (m_ImagesLocked.GetCount () == m_MenuImagesLocked.GetCount ());
		}
		
		return TRUE;
	}

	m_iImagesOffset = m_Images.GetCount ();
	if (!m_Images.Load (uiResID, AfxGetResourceHandle (), TRUE))
	{
		return FALSE;
	}

	if (uiColdResID != 0)
	{
		if (!m_ColdImages.Load (uiColdResID, AfxGetResourceHandle (), TRUE))
		{
			return FALSE;
		}

		ASSERT (m_Images.GetCount () == m_ColdImages.GetCount ());
		ASSERT (m_Images.GetImageSize ().cy == m_ColdImages.GetImageSize ().cy);
	}

	if (uiMenuResID != 0)
	{
		if (!m_MenuImages.Load (uiMenuResID, AfxGetResourceHandle (), TRUE))
		{
			return FALSE;
		}

		ASSERT (m_Images.GetCount () == m_MenuImages.GetCount ());
		ASSERT (m_MenuImages.GetImageSize ().cy == m_sizeMenuImage.cy);
	}

	ASSERT (m_Images.GetImageSize ().cy == m_sizeImage.cy);
	return TRUE;
}
//******************************************************************************************
BOOL CBCGToolBar::LoadToolBar(UINT uiResID, UINT uiColdResID, UINT uiMenuResID, 
							  BOOL bLocked)
{
	struct CToolBarData
	{
		WORD wVersion;
		WORD wWidth;
		WORD wHeight;
		WORD wItemCount;

		WORD* items()
			{ return (WORD*)(this+1); }
	};

	ASSERT_VALID(this);

	if (m_uiOriginalResID == 0 && 
		!LoadBitmap (uiResID, uiColdResID, uiMenuResID, bLocked))
	{
		return FALSE;
	}

	LPCTSTR lpszResourceName = MAKEINTRESOURCE (uiResID);
	ASSERT(lpszResourceName != NULL);

	//---------------------------------------------------
	// determine location of the bitmap in resource fork:
	//---------------------------------------------------
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, RT_TOOLBAR);
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
	if (hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
	if (pData == NULL)
		return FALSE;
	ASSERT(pData->wVersion == 1);

	SetSizes (	CSize (pData->wWidth + 6, pData->wHeight + 6),
				CSize (pData->wWidth, pData->wHeight));

	UINT* pItems = new UINT[pData->wItemCount];
	int iImageIndex = m_iImagesOffset;

	for (int i = 0; i < pData->wItemCount; i++)
	{
		pItems[i] = pData->items()[i];
		if (pItems [i] > 0)
		{
			m_DefaultImages.SetAt (pItems[i], iImageIndex ++);
		}
	}

	m_uiOriginalResID = uiResID;
	BOOL bResult = SetButtons(pItems, pData->wItemCount);
	if (!bResult)
	{
		m_uiOriginalResID = 0;
	}

	delete[] pItems;

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return bResult;
}
//*****************************************************************************************
int CBCGToolBar::InsertButton (const CBCGToolbarButton& button, int iInsertAt)
{
	CRuntimeClass* pClass = button.GetRuntimeClass ();
	ASSERT (pClass != NULL);

	CBCGToolbarButton* pButton = (CBCGToolbarButton*) pClass->CreateObject ();
	ASSERT_VALID(pButton);

	pButton->CopyFrom (button);

	int iIndex = InsertButton (pButton, iInsertAt);
	if (iIndex < 0)
	{
		delete pButton;
	}

	return iIndex;
}
//******************************************************************************************
int CBCGToolBar::InsertButton (CBCGToolbarButton* pButton, int iInsertAt)
{
	ASSERT (pButton != NULL);

	if (!IsCommandPermitted (pButton->m_nID))
	{
		return -1;
	}

	if (iInsertAt != -1 &&
		(iInsertAt < 0 || iInsertAt > m_Buttons.GetCount ()))
	{
		return -1;
	}

	int iIndex = -1;

	if (iInsertAt == -1 || iInsertAt == m_Buttons.GetCount ())
	{
		//-------------------------
		// Add to the toolbar tail:
		//-------------------------
		m_Buttons.AddTail (pButton);
		pButton->OnChangeParentWnd (this);
		iIndex = m_Buttons.GetCount () - 1;
	}
	else
	{
		int i = 0;
		for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
		{
			if (i == iInsertAt)
			{
				m_Buttons.InsertBefore (pos, pButton);
				pButton->OnChangeParentWnd (this);
				iIndex = i;
				break;
			}

			m_Buttons.GetNext (pos);
		}
	}

	if (iIndex != -1)
	{
		pButton->m_bDragFromCollection = FALSE;

		HWND hwnd = pButton->GetHwnd ();
		if (hwnd != NULL)
		{
			::EnableWindow (hwnd, !IsCustomizeMode () || m_bLocked);
		}
	}

	return iIndex;
}
//******************************************************************************************
int CBCGToolBar::InsertSeparator (int iInsertAt)
{
	CBCGToolbarButton* pButton = new CBCGToolbarButton;
	ASSERT (pButton != NULL);

	pButton->m_nStyle = TBBS_SEPARATOR;

	int iNewButtonOndex = InsertButton (pButton, iInsertAt);
	if (iNewButtonOndex == -1)
	{
		delete pButton;
	}

	return iNewButtonOndex;
}
//******************************************************************************************
void CBCGToolBar::RemoveAllButtons ()
{
	m_iButtonCapture = -1;      // nothing captured
	m_iHighlighted = -1;
	m_iSelected = -1;

	while (!m_Buttons.IsEmpty ())
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.RemoveHead ();
		ASSERT_VALID (pButton);
		pButton->OnCancelMode ();

		delete pButton;
	}
}
//******************************************************************************************
BOOL CBCGToolBar::RemoveButton (int iIndex)
{
	POSITION pos = m_Buttons.FindIndex (iIndex);
	if (pos == NULL)
	{
		return FALSE;
	}

	CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetAt (pos);
	ASSERT_VALID (pButton);

	m_Buttons.RemoveAt (pos);
	pButton->OnCancelMode ();

	delete pButton;

	if (iIndex == m_iSelected)
	{
		m_iSelected = -1;
	}
	else if (iIndex < m_iSelected && m_iSelected >= 0)
	{
		m_iSelected --;
	}

	if (iIndex == m_iButtonCapture)
	{
		m_iButtonCapture = -1;
	}
	else if (iIndex < m_iButtonCapture && m_iButtonCapture >= 0)
	{
		m_iButtonCapture --;
	}

	if (iIndex == m_iHighlighted)
	{
		m_iHighlighted = -1;
		OnChangeHot (m_iHighlighted);
	}
	else if (iIndex < m_iHighlighted && m_iHighlighted >= 0)
	{
		m_iHighlighted --;
		OnChangeHot (m_iHighlighted);
	}

	//-----------------------------------------
	// If last button is separator - remove it:
	//-----------------------------------------
	while (!m_Buttons.IsEmpty ())
	{
		CBCGToolbarButton* pLastButton = (CBCGToolbarButton*) m_Buttons.GetTail ();
		ASSERT_VALID (pLastButton);

		if (pLastButton->m_nStyle & TBBS_SEPARATOR)
		{
			delete m_Buttons.RemoveTail ();
		}
		else
		{
			//----------------------
			// Regular button, stop!
			//----------------------
			break;
		}
	}

	RebuildAccelerationKeys ();
	return TRUE;
}

#ifdef AFX_CORE3_SEG
#pragma code_seg(AFX_CORE3_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar attribute access

int CBCGToolBar::CommandToIndex(UINT nIDFind) const
{
	ASSERT_VALID(this);

	int i = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		if (pButton->m_nID == nIDFind)
		{
			return i;
		}
	}

	return -1;
}
//*****************************************************************
UINT CBCGToolBar::GetItemID(int nIndex) const
{
	ASSERT_VALID(this);

	return GetButton (nIndex)->m_nID;
}
//*****************************************************************
void CBCGToolBar::GetItemRect(int nIndex, LPRECT lpRect) const
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0 && nIndex < m_Buttons.GetCount ());
	ASSERT(AfxIsValidAddress(lpRect, sizeof(RECT)));

	CBCGToolbarButton* pButton = GetButton (nIndex);
	ASSERT (pButton != NULL);

	*lpRect = pButton->m_rect;
}
//*****************************************************************
UINT CBCGToolBar::GetButtonStyle(int nIndex) const
{
	return GetButton (nIndex)->m_nStyle;
}
//*****************************************************************
int CBCGToolBar::ButtonToIndex (const CBCGToolbarButton* pButton) const
{
	ASSERT_VALID (this);
	ASSERT_VALID (pButton);

	int i = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
	{
		CBCGToolbarButton* pListButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pListButton != NULL);

		if (pListButton == pButton)
		{
			return i;
		}
	}

	return -1;
}
//*****************************************************************
void CBCGToolBar::SetButtonStyle(int nIndex, UINT nStyle)
{
	CBCGToolbarButton* pButton = GetButton (nIndex);
	UINT nOldStyle = pButton->m_nStyle;
	if (nOldStyle != nStyle)
	{
		// update the style and invalidate
		pButton->m_nStyle = nStyle;

		// invalidate the button only if both styles not "pressed"
		if (!(nOldStyle & nStyle & TBBS_PRESSED))
			InvalidateButton(nIndex);
	}
}
//****************************************************************
CSize CBCGToolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
/*	if (m_Buttons.IsEmpty ())
	{
		return m_sizeButton;
	}
*/
	DWORD dwMode = bStretch ? LM_STRETCH : 0;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout (dwMode);
}
//*************************************************************************************
CSize CBCGToolBar::CalcDynamicLayout (int nLength, DWORD dwMode)
{
/*	if (m_Buttons.IsEmpty ())
	{
		return m_sizeButton;
	}
*/
	if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
		((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
	{
		return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
	}

	return CalcLayout(dwMode, nLength);
}
//*************************************************************************************
void CBCGToolBar::GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage) const
{
	ASSERT_VALID(this);

	CBCGToolbarButton* pButton = GetButton(nIndex);
	nID = pButton->m_nID;
	nStyle = pButton->m_nStyle;
	iImage = pButton->GetImage ();
}
//*************************************************************************************
void CBCGToolBar::SetButtonInfo(int nIndex, UINT nID, UINT nStyle, int iImage)
{
	ASSERT_VALID(this);

	CBCGToolbarButton* pButton = GetButton(nIndex);
	ASSERT_VALID (pButton);

	pButton->m_nStyle = nStyle;
	pButton->m_nID = nID;
	pButton->SetImage (iImage);

	if ((nStyle & TBBS_SEPARATOR) && iImage > 0) // iImage parameter is a button width!
	{
		AdjustLayout ();
	}

	InvalidateButton(nIndex);
}
//*************************************************************************************
BOOL CBCGToolBar::SetButtonText(int nIndex, LPCTSTR lpszText)
{
	ASSERT_VALID(this);
	ASSERT(lpszText != NULL);

	CBCGToolbarButton* pButton = GetButton(nIndex);
	if (pButton == NULL)
	{
		return FALSE;
	}

	pButton->m_strText = lpszText;
	return TRUE;
}
//*************************************************************************************
CString CBCGToolBar::GetButtonText( int nIndex ) const
{
	ASSERT_VALID(this);

	CBCGToolbarButton* pButton = GetButton(nIndex);
	ASSERT_VALID (pButton);

	return pButton->m_strText;
}
//*************************************************************************************
void CBCGToolBar::GetButtonText( int nIndex, CString& rString ) const
{
	ASSERT_VALID(this);

	CBCGToolbarButton* pButton = GetButton(nIndex);
	ASSERT_VALID (pButton);

	rString = pButton->m_strText;
}
//*************************************************************************************
void CBCGToolBar::DoPaint(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	BOOL bHorz = m_dwStyle & CBRS_ORIENT_HORZ ? TRUE : FALSE;

	CRect rectClient;
	GetClientRect (rectClient);

	pDC->SetTextColor (globalData.clrBtnText);
	pDC->SetBkMode (TRANSPARENT);

	CRect rect;
	GetClientRect(rect);

	//-----------------------------------
	// Force the full size of the button:
	//-----------------------------------
	if (bHorz)
	{
		rect.bottom = rect.top + GetRowHeight ();
	}
	else
	{
		rect.right = rect.left + GetColumnWidth ();
	}

	CBCGToolBarImages* pImages = !m_bLocked ? 
		&m_Images : &m_ImagesLocked;
	CBCGToolBarImages* pHotImages = pImages;
	CBCGToolBarImages* pColdImages = !m_bLocked ? 
		&m_ColdImages : &m_ColdImagesLocked;
	CBCGToolBarImages* pMenuImages = !m_bLocked ? 
		&m_MenuImages : &m_MenuImagesLocked;

	BOOL bDrawImages = pImages->IsValid ();

	CBCGDrawState ds;
	if (bDrawImages && !pHotImages->PrepareDrawImage (ds))
	{
		return;     // something went wrong
	}

	CFont* pOldFont;
	if (bHorz)
	{
		pOldFont = (CFont*) pDC->SelectObject (&globalData.fontRegular);
	}
	else
	{
		pOldFont = (CFont*) pDC->SelectObject (&globalData.fontVert);
	}

	//--------------
	// Draw buttons:
	//--------------
	int iButton = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		rect = pButton->m_rect;

		BOOL bHighlighted;

		if (IsCustomizeMode () && !m_bLocked)
		{
			bHighlighted = FALSE;
		}
		else
		{
			if (m_bMenuMode)
			{
				bHighlighted = (iButton == m_iHighlighted);
			}
			else
			{
				bHighlighted = ((iButton == m_iHighlighted ||
								iButton == m_iButtonCapture) &&
								(m_iButtonCapture == -1 ||
								iButton == m_iButtonCapture));
			}
		}

		ASSERT(pButton != NULL);
		if (pButton->m_nStyle & TBBS_SEPARATOR)
		{
			BOOL bHorzSeparator = bHorz;
			CRect rectSeparator = rect;

			if (pButton->m_bWrap && bHorz)
			{
				rectSeparator.left = rectClient.left;
				rectSeparator.right = rectClient.right;

				rectSeparator.top = pButton->m_rect.bottom;
				rectSeparator.bottom = rectSeparator.top + LINE_OFFSET;

				bHorzSeparator = FALSE;
			}

			DrawSeparator (pDC, rectSeparator, bHorzSeparator);
		}
		else
		{
			if (pDC->RectVisible(&rect))
			{
				if (bDrawImages)
				{
					CBCGToolBarImages* pNewImages = (pButton->m_bUserButton &&
									pButton->GetImage () >= 0) ?
									m_pUserImages : pHotImages;

					if (!m_bMenuMode && !bHighlighted && 
						(pButton->m_nStyle & TBBS_PRESSED) == 0 &&
						pColdImages->GetCount () > 0 &&
						!pButton->IsDroppedDown ())
					{
						pNewImages = (pButton->m_bUserButton) ?
								m_pUserImages :
								pColdImages;
					}

					if (m_bMenuMode && pMenuImages->GetCount () > 0)
					{
						pNewImages = (pButton->m_bUserButton) ?
							m_pUserImages :
							pMenuImages;
					}

					if (bDrawImages && pNewImages != pImages && pNewImages != NULL)
					{
						pImages->EndDrawImage (ds);
						pNewImages->PrepareDrawImage (ds);

						pImages = pNewImages;
					}
				}

				DrawButton (pDC, pButton, bDrawImages ? pImages : NULL, bHighlighted);
			}
		}
	}

	//-------------------------------------------------------------
	// Highlight selected button in the toolbar customization mode:
	//-------------------------------------------------------------
	if (m_iSelected >= m_Buttons.GetCount ())
	{
		m_iSelected = -1;
	}

	if (IsCustomizeMode () && m_iSelected >= 0 && !m_bLocked)
	{
		CBCGToolbarButton* pSelButton = GetButton (m_iSelected);
		ASSERT (pSelButton != NULL);

		if (pSelButton->CanBeStored ())
		{
			CRect rectDrag = pSelButton->m_rect;
			if (pSelButton->GetHwnd () != NULL)
			{
				rectDrag.InflateRect (0, 2);
			}

			pDC->DrawDragRect (&rectDrag, CSize (2, 2), NULL, CSize (2, 2));
		}
	}

	if (IsCustomizeMode () && m_iDragIndex >= 0 && !m_bLocked)
	{
		DrawDragMarker (pDC);
	}

	pDC->SelectObject (pOldFont);

	if (bDrawImages)
	{
		pHotImages->EndDrawImage(ds);
	}
}
//*************************************************************************************
BOOL CBCGToolBar::DrawButton(CDC* pDC, CBCGToolbarButton* pButton,
							CBCGToolBarImages* pImages,
							BOOL bHighlighted)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	if (pButton->GetHwnd () != NULL &&
		(CWnd::FromHandle (pButton->GetHwnd ())->GetStyle () & WS_VISIBLE))
	{
		return TRUE;
	}

	BOOL bHorz = m_dwStyle & CBRS_ORIENT_HORZ ? TRUE : FALSE;

	CRect rectClient;
	GetClientRect (rectClient);

	//---------------------
	// Draw button context:
	//---------------------
	pButton->OnDraw (pDC, pButton->m_rect, pImages, bHorz, 
		IsCustomizeMode () && !m_bLocked, bHighlighted, m_bShowHotBorder,
		m_bGrayDisabledButtons);
	return TRUE;
}
//*************************************************************************************
CBCGToolbarButton* CBCGToolBar::GetButton(int nIndex) const
{
	POSITION pos = m_Buttons.FindIndex (nIndex);
	ASSERT (pos != NULL);

	CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetAt (pos);
	ASSERT (pButton != NULL);

	return pButton;
}
//*************************************************************************************
void CBCGToolBar::InvalidateButton(int nIndex)
{
	ASSERT_VALID(this);

	CRect rect;
	GetItemRect(nIndex, &rect);
	rect.InflateRect (3, 3);

	InvalidateRect (rect);
}
//*************************************************************************************
int CBCGToolBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	ASSERT_VALID(this);

	if (!m_bShowTooltips)
	{
		return -1;
	}

	// check child windows first by calling CControlBar
	int nHit = CControlBar::OnToolHitTest(point, pTI);
	if (nHit != -1)
		return nHit;

	// now hit test against CBCGToolBar buttons
	nHit = ((CBCGToolBar*)this)->HitTest(point);
	if (nHit != -1)
	{
		CBCGToolbarButton* pButton = GetButton(nHit);
		if (pTI != NULL)
		{
			CString strTipText;

			if ((pButton->m_nID == 0 || pButton->m_bUserButton) &&
				!pButton->m_strText.IsEmpty ())
			{
				// Use button text as tooltip!
				strTipText = pButton->m_strText;

				strTipText.Remove (_T('&'));
			}
			else
			{
				TCHAR szFullText [256];

				AfxLoadString (pButton->m_nID, szFullText);
				AfxExtractSubString(strTipText, szFullText, 1, '\n');
			}

			if (strTipText.IsEmpty ())
			{
				return -1;
			}

			if (pButton->m_nID != 0 && m_bShowShortcutKeys)
			{
				//--------------------
				// Add shortcut label:
				//--------------------
				CString strLabel;
				CFrameWnd* pParent = GetParentFrame ();

				if (pParent != NULL &&
					(CBCGKeyboardManager::FindDefaultAccelerator (
						pButton->m_nID, strLabel, pParent) ||
					CBCGKeyboardManager::FindDefaultAccelerator (
						pButton->m_nID, strLabel, pParent->GetActiveFrame ())))
				{
					strTipText += _T(" (");
					strTipText += strLabel;
					strTipText += ')';
				}
			}

			pTI->lpszText = new TCHAR [strTipText.GetLength () + 1];
			_tcscpy (pTI->lpszText, strTipText);

			GetItemRect(nHit, &pTI->rect);
			pTI->uId = pButton->m_nID;
			pTI->hwnd = m_hWnd;
		}

		nHit = pButton->m_nID;
	}

	return nHit;
}
//*************************************************************************************
int CBCGToolBar::HitTest(CPoint point) // in window relative coords
{
	int iButton = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		if (pButton->m_rect.PtInRect (point))
		{
			return (pButton->m_nStyle & TBBS_SEPARATOR) ? -1 : iButton;
		}
	}

	return -1;      // nothing hit
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar message handlers

BEGIN_MESSAGE_MAP(CBCGToolBar, CControlBar)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CBCGToolBar)
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_BCGBARRES_TOOLBAR_APPEARANCE, OnToolbarAppearance)
	ON_COMMAND(ID_BCGBARRES_TOOLBAR_DELETE, OnToolbarDelete)
	ON_COMMAND(ID_BCGBARRES_TOOLBAR_IMAGE, OnToolbarImage)
	ON_COMMAND(ID_BCGBARRES_TOOLBAR_IMAGE_AND_TEXT, OnToolbarImageAndText)
	ON_COMMAND(ID_BCGBARRES_TOOLBAR_START_GROUP, OnToolbarStartGroup)
	ON_COMMAND(ID_BCGBARRES_TOOLBAR_TEXT, OnToolbarText)
	ON_WM_LBUTTONUP()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_CTLCOLOR()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_BCGBARRES_TOOLBAR_RESET, OnBcgbarresToolbarReset)
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_NCHITTEST()
	ON_COMMAND(ID_BCGBARRES_COPY_IMAGE, OnBcgbarresCopyImage)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_HELPHITTEST, OnHelpHitTest)
END_MESSAGE_MAP()

void CBCGToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	int iButton = HitTest(point);

	if (iButton < 0) // nothing hit
	{
		m_iButtonCapture = -1;

		if (IsCustomizeMode () && !m_bLocked)
		{
			int iSelected = m_iSelected;
			m_iSelected = -1;

			if (iSelected != -1)
			{
				InvalidateButton (iSelected);
				UpdateWindow ();
			}

			OnChangeHot (-1);
		}

		CControlBar::OnLButtonDown(nFlags, point);
		return;
	}

	//-----------------------------------------------------------------
	// Check for "Alt-customizible mode" (when ALT key is holded down):
	//-----------------------------------------------------------------
	BOOL bAltCustomizeMode = FALSE;
	if (m_bAltCustomization &&
		!m_bCustomizeMode &&
		GetAsyncKeyState (VK_MENU) & 0x8000)	// ALT is pressed
	{
		bAltCustomizeMode = TRUE;
	}

	CBCGToolbarButton* pButton = GetButton(iButton);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	if ((!IsCustomizeMode () && !bAltCustomizeMode) || m_bLocked)
	{
		m_iButtonCapture = iButton;

		// update the button before checking for disabled status
		UpdateButton(m_iButtonCapture);
		if (pButton->m_nStyle & TBBS_DISABLED)
		{
			m_iButtonCapture = -1;
			return;     // don't press it
		}

		pButton->m_nStyle |= TBBS_PRESSED;

		InvalidateButton (iButton);
		UpdateWindow(); // immediate feedback

		ShowCommandMessageString (pButton->m_nID);

		if (pButton->OnClick (this, FALSE /* No delay*/))
		{
			pButton->m_nStyle &= ~TBBS_PRESSED;

			m_iButtonCapture = -1;
			m_iHighlighted = -1;

			OnChangeHot (m_iHighlighted);

			InvalidateButton (iButton);
			UpdateWindow(); // immediate feedback
		}
		else
		{
			m_pWndLastCapture = SetCapture ();
		}
	}
	else
	{
		int iSelected = m_iSelected;
		m_iSelected = iButton;

		CRect rect;
		GetItemRect (iButton, &rect);

		if (iSelected != -1)
		{
			InvalidateButton (iSelected);
		}

		m_pDragButton = GetButton (m_iSelected);
		ASSERT (m_pDragButton != NULL);

		m_bIsDragCopy = (nFlags & MK_CONTROL);

		if (!m_pDragButton->IsEditable ())
		{
			m_iSelected = -1;
			m_pDragButton = NULL;

			if (iSelected != -1)
			{
				InvalidateButton (iSelected);
			}
			return;
		}

		InvalidateButton (iButton);
		UpdateWindow(); // immediate feedback

		if (m_pDragButton->CanBeStretched () &&
			abs (point.x - rect.right) <= STRETCH_DELTA)
		{
			m_bStretchButton = TRUE;

			m_rectTrack = m_pDragButton->m_rect;

			if (m_pDragButton->GetHwnd () != NULL)
			{
				m_rectTrack.InflateRect (2, 2);
			}

			m_pWndLastCapture = SetCapture ();
			::SetCursor (globalData.m_hcurStretch);
		}
		else if (m_pDragButton->CanBeStored () &&
			m_pDragButton->OnBeforeDrag ())
		{
			COleDataSource srcItem;
			m_pDragButton->PrepareDrag (srcItem);

			ShowCommandMessageString (pButton->m_nID);

			m_DropSource.m_bDragStarted = FALSE;
			m_ptStartDrag = point;

			HWND hwndSaved = m_hWnd;

			if (bAltCustomizeMode)
			{
				m_bCustomizeMode = TRUE;
			}

			DROPEFFECT dropEffect = srcItem.DoDragDrop 
				(DROPEFFECT_COPY|DROPEFFECT_MOVE, &rect, &m_DropSource);

			if (!::IsWindow (hwndSaved))
			{
				if (bAltCustomizeMode)
				{
					m_bCustomizeMode = FALSE;
				}

				return;
			}

			CPoint ptDrop;
			::GetCursorPos (&ptDrop);
			ScreenToClient (&ptDrop);

			if (m_DropSource.m_bDragStarted &&
				!rect.PtInRect (ptDrop))
			{
				if (dropEffect != DROPEFFECT_COPY && 
					m_pDragButton != NULL &&
					!m_DropSource.m_bEscapePressed)
				{
					//---------------------
					// Remove source button:
					//---------------------
					RemoveButton (ButtonToIndex (m_pDragButton));
					AdjustLayout ();

					Invalidate ();
				}
			}
			else
			{
				m_iHighlighted = iButton;
				OnChangeHot (m_iHighlighted);
			}

			m_pDragButton = NULL;
			m_ptStartDrag = CPoint (-1, -1);
		}
		else
		{
			m_pDragButton = NULL;
		}
	}

	if (bAltCustomizeMode)
	{
		m_bCustomizeMode = FALSE;
	}
}
//**************************************************************************************
void CBCGToolBar::OnMouseMove(UINT /*nFlags*/, CPoint point)
{
	if (IsCustomizeMode () && !m_bLocked)
	{
		if (m_bStretchButton)
		{
			ASSERT_VALID (m_pDragButton);

			if (point.x - m_pDragButton->m_rect.left >= BUTTON_MIN_WIDTH)
			{
				CClientDC dc (this);

				CRect rectTrackOld = m_rectTrack;
				m_rectTrack.right = point.x;
				dc.DrawDragRect (&m_rectTrack, CSize (2, 2), &rectTrackOld, CSize (2, 2));
			}

			::SetCursor (globalData.m_hcurStretch);
		}

		return;
	}

	if (m_ptLastMouse != CPoint (-1, -1) &&
		abs (m_ptLastMouse.x - point.x) < 1 &&
		abs (m_ptLastMouse.y - point.y) < 1)
	{
		m_ptLastMouse = point;
		return;
	}

	m_ptLastMouse = point;

	int iPrevHighlighted = m_iHighlighted;
	m_iHighlighted = HitTest (point);

	if (m_iHighlighted == -1 && GetFocus () == this)
	{
		m_iHighlighted = iPrevHighlighted; 
		return;
	}

	CBCGToolbarButton* pButton = m_iHighlighted == -1 ?
							NULL : GetButton (m_iHighlighted);
	if (pButton != NULL &&
		(pButton->m_nStyle & TBBS_SEPARATOR || 
		(pButton->m_nStyle & TBBS_DISABLED && !AllowSelectDisabled ())))
	{
		m_iHighlighted = -1;
	}

	if (!m_bTracked)
	{
		m_bTracked = TRUE;
		
		TRACKMOUSEEVENT trackmouseevent;
		trackmouseevent.cbSize = sizeof(trackmouseevent);
		trackmouseevent.dwFlags = TME_LEAVE;
		trackmouseevent.hwndTrack = GetSafeHwnd();
		trackmouseevent.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent (&trackmouseevent);	
	}
	
	if (iPrevHighlighted != m_iHighlighted)
	{
		BOOL bNeedUpdate = FALSE;

		if (m_iButtonCapture != -1)
		{
			CBCGToolbarButton* pTBBCapt = GetButton (m_iButtonCapture);
			ASSERT (pTBBCapt != NULL);
			ASSERT (!(pTBBCapt->m_nStyle & TBBS_SEPARATOR));

			UINT nNewStyle = (pTBBCapt->m_nStyle & ~TBBS_PRESSED);
			if (m_iHighlighted == m_iButtonCapture)
			{
				nNewStyle |= TBBS_PRESSED;
			}

			if (nNewStyle != pTBBCapt->m_nStyle)
			{
				SetButtonStyle (m_iButtonCapture, nNewStyle);
				bNeedUpdate = TRUE;
			}
		}

		if ((m_bMenuMode || m_iButtonCapture == -1 || 
			iPrevHighlighted == m_iButtonCapture) &&
			iPrevHighlighted != -1)
		{
			InvalidateButton (iPrevHighlighted);
			bNeedUpdate = TRUE;
		}

		if ((m_bMenuMode || m_iButtonCapture == -1 || 
			m_iHighlighted == m_iButtonCapture) &&
			m_iHighlighted != -1)
		{
			InvalidateButton (m_iHighlighted);
			bNeedUpdate = TRUE;
		}

		if (bNeedUpdate)
		{
			UpdateWindow ();
		}

		if (m_iHighlighted != -1 && 
			(m_bMenuMode || m_iHighlighted == m_iButtonCapture || m_iButtonCapture == -1))
		{
			ASSERT (pButton != NULL);
			ShowCommandMessageString (pButton->m_nID);
		}
		else if ((m_iButtonCapture == -1 || (m_bMenuMode && m_iHighlighted == -1))
			&& m_hookMouseHelp == NULL)
		{
			GetOwner()->SendMessage (WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
		}

		OnChangeHot (m_iHighlighted);
	}
}
//*************************************************************************************
void CBCGToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (IsCustomizeMode () && !m_bLocked)
	{
		if (m_bStretchButton)
		{
			ASSERT_VALID (m_pDragButton);

			CRect rect = m_pDragButton->m_rect;
			rect.right = point.x;

			if (rect.Width () >= BUTTON_MIN_WIDTH &&
				abs (m_pDragButton->m_rect.right - point.x) > STRETCH_DELTA)
			{
				m_pDragButton->OnSize (rect.Width ());
				AdjustLayout ();
			}

			m_rectTrack.SetRectEmpty ();

			m_pDragButton = NULL;
			m_bStretchButton = FALSE;

			Invalidate ();
			::ReleaseCapture ();

			if (m_pWndLastCapture != NULL)
			{
				m_pWndLastCapture->SetCapture ();
				m_pWndLastCapture = NULL;
			}
		}
		return;
	}

	if (m_iButtonCapture == -1)
	{
		CControlBar::OnLButtonUp(nFlags, point);

		m_ptLastMouse = CPoint (-1, -1);
		OnMouseMove (0, point);
		return;     // not captured
	}

	::ReleaseCapture();
	if (m_pWndLastCapture != NULL)
	{
		m_pWndLastCapture->SetCapture ();
		m_pWndLastCapture = NULL;
	}

	m_iHighlighted = HitTest (point);

	CBCGToolbarButton* pButton = GetButton(m_iButtonCapture);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));
	UINT nIDCmd = 0;

	UINT nNewStyle = (pButton->m_nStyle & ~TBBS_PRESSED);
	if (m_iButtonCapture == m_iHighlighted)
	{
		// we did not lose the capture
		if (HitTest(point) == m_iButtonCapture)
		{
			// give button a chance to update
			UpdateButton(m_iButtonCapture);

			// then check for disabled state
			if (!(pButton->m_nStyle & TBBS_DISABLED))
			{
				// pressed, will send command notification
				nIDCmd = pButton->m_nID;

				if (pButton->m_nStyle & TBBS_CHECKBOX)
				{
					// auto check: three state => down
					if (nNewStyle & TBBS_INDETERMINATE)
						nNewStyle &= ~TBBS_INDETERMINATE;

					nNewStyle ^= TBBS_CHECKED;
				}
			}
		}
	}

	if (m_hookMouseHelp == NULL)
	{
		GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
	}

	int iButtonCapture = m_iButtonCapture;
	m_iButtonCapture = -1;
	m_iHighlighted = -1;

	HWND hwndSaved = m_hWnd;
	RestoreFocus ();
//	GetOwner ()->SetFocus ();

	if (HitTest(point) == iButtonCapture && 
		!OnSendCommand (pButton) &&
		nIDCmd != 0)
	{
		InvalidateButton (iButtonCapture);
		UpdateWindow(); // immediate feedback
		GetOwner()->SendMessage (WM_COMMAND, nIDCmd);    // send command
	}

	if (::IsWindow (hwndSaved) &&				// "This" may be destoyed now!
		iButtonCapture < m_Buttons.GetCount ())	// Button may disappear now!
	{
		SetButtonStyle(iButtonCapture, nNewStyle);
		UpdateButton(iButtonCapture);
		InvalidateButton (iButtonCapture);
		UpdateWindow(); // immediate feedback

		m_ptLastMouse = CPoint (-1, -1);
		OnMouseMove (0, point);
	}
}
//*************************************************************************************
void CBCGToolBar::OnCancelMode()
{
	CControlBar::OnCancelMode();

	if (m_bStretchButton)
	{
		m_pDragButton = NULL;
		m_bStretchButton = FALSE;

		m_rectTrack.SetRectEmpty ();

		::ReleaseCapture ();
		if (m_pWndLastCapture != NULL)
		{
			m_pWndLastCapture->SetCapture ();
			m_pWndLastCapture = NULL;
		}
	}

	if (m_iButtonCapture >= 0 ||
		m_iHighlighted >= 0)
	{
		if (m_iButtonCapture >= 0)
		{
			CBCGToolbarButton* pButton = GetButton(m_iButtonCapture);
			ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));
			UINT nNewStyle = (pButton->m_nStyle & ~TBBS_PRESSED);
			if (GetCapture() == this)
			{
				::ReleaseCapture();

				if (m_pWndLastCapture != NULL)
				{
					m_pWndLastCapture->SetCapture ();
					m_pWndLastCapture = NULL;
				}
			}

			SetButtonStyle(m_iButtonCapture, nNewStyle);
		}

		m_iButtonCapture = -1;
		m_iHighlighted = -1;

		OnChangeHot (m_iHighlighted);
	}

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);
	
		pButton->OnCancelMode ();
	}

	Invalidate ();
	UpdateWindow();
}
//*************************************************************************************
void CBCGToolBar::OnSysColorChange()
{
	globalData.UpdateSysColors ();

	m_Images.OnSysColorChange ();
	m_ColdImages.OnSysColorChange ();
	m_ImagesLocked.OnSysColorChange ();
	m_ColdImagesLocked.OnSysColorChange ();

	if (m_pUserImages != NULL)
	{
		m_pUserImages->OnSysColorChange ();
	}

	Invalidate ();
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar idle update through CToolCmdUI class

#define CToolCmdUI COldToolCmdUI

class CToolCmdUI : public CCmdUI        // class private to this file !
{
public: // re-implementations only
	virtual void Enable(BOOL bOn);
	virtual void SetCheck(int nCheck);
	virtual void SetText(LPCTSTR lpszText);
};

void CToolCmdUI::Enable(BOOL bOn)
{
	m_bEnableChanged = TRUE;
	CBCGToolBar* pToolBar = (CBCGToolBar*)m_pOther;
	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CBCGToolBar, pToolBar);
	ASSERT(m_nIndex < m_nIndexMax);

	UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) & ~TBBS_DISABLED;

	if (!bOn)
		nNewStyle |= TBBS_DISABLED;
	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	pToolBar->SetButtonStyle(m_nIndex, nNewStyle);
}
//*************************************************************************************
void CToolCmdUI::SetCheck(int nCheck)
{
	ASSERT (nCheck >= 0);
	if (nCheck > 2)
	{
		nCheck = 1;
	}

	CBCGToolBar* pToolBar = (CBCGToolBar*)m_pOther;
	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CBCGToolBar, pToolBar);
	ASSERT(m_nIndex < m_nIndexMax);

	UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
				~(TBBS_CHECKED | TBBS_INDETERMINATE);
	if (nCheck == 1)
		nNewStyle |= TBBS_CHECKED;
	else if (nCheck == 2)
		nNewStyle |= TBBS_INDETERMINATE;
	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);
}
//*************************************************************************************
void CToolCmdUI::SetText (LPCTSTR lpszText)
{
	ASSERT (lpszText != NULL);

	CBCGToolBar* pToolBar = (CBCGToolBar*)m_pOther;
	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CBCGToolBar, pToolBar);
	ASSERT(m_nIndex < m_nIndexMax);

	CBCGToolbarButton* pButton = pToolBar->GetButton (m_nIndex);
	ASSERT_VALID (pButton);

	if (pButton->m_strText == lpszText)
	{
		return;
	}

	pButton->m_strText = lpszText;
	pToolBar->AdjustLayout ();
}
//*************************************************************************************
void CBCGToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CToolCmdUI state;
	state.m_pOther = this;

	state.m_nIndexMax = (UINT)m_Buttons.GetCount ();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		CBCGToolbarButton* pButton = GetButton(state.m_nIndex);
		state.m_nID = pButton->m_nID;

		// ignore separators and system commands
		if (!(pButton->m_nStyle & TBBS_SEPARATOR) &&
			pButton->m_nID != 0 &&
			!IsSystemCommand (pButton->m_nID) &&
			pButton->m_nID < AFX_IDM_FIRST_MDICHILD)
		{
			state.DoUpdate(pTarget, bDisableIfNoHndler);
		}
	}

	// update the dialog controls added to the toolbar
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}
//*************************************************************************************
void CBCGToolBar::UpdateButton(int nIndex)
{
	// determine target of command update
	CFrameWnd* pTarget = (CFrameWnd*)GetOwner();
	if (pTarget == NULL || !pTarget->IsFrameWnd())
		pTarget = GetParentFrame();

	// send the update notification
	if (pTarget != NULL)
	{
		CToolCmdUI state;
		state.m_pOther = this;
		state.m_nIndex = nIndex;
		state.m_nIndexMax = (UINT)m_Buttons.GetCount ();
		CBCGToolbarButton* pButton = GetButton(nIndex);

		if (!IsSystemCommand (pButton->m_nID) &&
			pButton->m_nID < AFX_IDM_FIRST_MDICHILD)
		{
			state.m_nID = pButton->m_nID;
			state.DoUpdate(pTarget, pTarget->m_bAutoMenuEnable);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar diagnostics

#ifdef _DEBUG
void CBCGToolBar::AssertValid() const
{
	CControlBar::AssertValid();
}

void CBCGToolBar::Dump(CDumpContext& dc) const
{
	CControlBar::Dump (dc);

	CString strName;

	if (::IsWindow (m_hWnd))
	{
		GetWindowText (strName);
	}

	dc << "\n**** Toolbar ***" << strName;
	dc << "\nButtons: " << m_Buttons.GetCount () << "\n";

	dc.SetDepth (dc.GetDepth () + 1);

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		pButton->Dump (dc);
		dc << "\n";
	}

	dc.SetDepth (dc.GetDepth () - 1);
	dc << "\n";
}
#endif

#undef new
#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

//**********************************************************************************************
void CBCGToolBar::DrawGripper (CDC* pDC)
{
	if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) != CBRS_GRIPPER)
	{
		return;
	}

	const int iGripperSize = 3;
	const int iGripperOffset = 3;
	const int iLinesNum = 2;

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE;

	CRect rectGripper;
	
	GetWindowRect (&rectGripper);
	ScreenToClient (&rectGripper);

	rectGripper.OffsetRect (-rectGripper.left, -rectGripper.top);

	if (bHorz)
	{
		//-----------------
		// Gripper at left:
		//-----------------
		rectGripper.DeflateRect (iGripperOffset + 1, 2);
		rectGripper.right = rectGripper.left + iGripperSize;
        
		for (int i = 0; i < iLinesNum; i ++)
		{
			pDC->Draw3dRect (rectGripper, 
							globalData.clrBtnHilite,
							globalData.clrBtnShadow);

			//-----------------------------------
			// To look same as MS Office Gripper!
			//-----------------------------------
			pDC->SetPixel (CPoint (rectGripper.left, rectGripper.bottom - 1),
							globalData.clrBtnHilite);

			rectGripper.OffsetRect (iGripperOffset, 0);
		}
	} 
	else 
	{
		//----------------
		// Gripper at top:
		//----------------
		rectGripper.DeflateRect (2, iGripperOffset + 1);
		rectGripper.bottom = rectGripper.top + iGripperSize;

		for (int i = 0; i < iLinesNum; i ++)
		{
			pDC->Draw3dRect (rectGripper,
							globalData.clrBtnHilite,
							globalData.clrBtnShadow);

			//-----------------------------------
			// To look same as MS Office Gripper!
			//-----------------------------------
			pDC->SetPixel (CPoint (rectGripper.right - 1, rectGripper.top),
							globalData.clrBtnHilite);

			rectGripper.OffsetRect (0, iGripperOffset);
		}
	}
}
//******************************************************************************************
void CBCGToolBar::DrawBorders(CDC* pDC, CRect& rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	DWORD dwStyle = m_dwStyle;
	if (!(dwStyle & CBRS_BORDER_ANY))
		return;

	// Copyright (C) 1997,'98 by Joerg Koenig
	// All rights reserved
	//

	COLORREF clr = (m_dwStyle & CBRS_BORDER_3D) ? globalData.clrBtnHilite : globalData.clrBtnShadow;
	if(m_dwStyle & CBRS_BORDER_LEFT)
		pDC->FillSolidRect(0, 0, 1, rect.Height() - 1, clr);
	if(m_dwStyle & CBRS_BORDER_TOP)
		pDC->FillSolidRect(0, 0, rect.Width()-1 , 1, clr);
	if(m_dwStyle & CBRS_BORDER_RIGHT)
		pDC->FillSolidRect(rect.right, 1, -1, rect.Height() - 1, globalData.clrBtnShadow);
	if(m_dwStyle & CBRS_BORDER_BOTTOM)
		pDC->FillSolidRect(0, rect.bottom, rect.Width()-1, -1, globalData.clrBtnShadow);

	// if undockable toolbar at top of frame, apply special formatting to mesh
	// properly with frame menu
	if(!m_pDockContext) {
		pDC->FillSolidRect(0,0,rect.Width(),1,globalData.clrBtnShadow);
		pDC->FillSolidRect(0,1,rect.Width(),1,globalData.clrBtnHilite);
	}

	if (dwStyle & CBRS_BORDER_LEFT)
		++rect.left;
	if (dwStyle & CBRS_BORDER_TOP)
		++rect.top;
	if (dwStyle & CBRS_BORDER_RIGHT)
		--rect.right;
	if (dwStyle & CBRS_BORDER_BOTTOM)
		--rect.bottom;
}
//****************************************************************************************
int CBCGToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (globalData.m_hcurStretch == NULL)
	{
		globalData.m_hcurStretch = AfxGetApp ()->LoadCursor (AFX_IDC_HSPLITBAR);
	}

	_AFX_THREAD_STATE* pState = AfxGetThreadState();
	if (pState->m_bNeedTerm)	// AfxOleInit was called
	{
		m_DropTarget.Register (this);
	}

	m_penDrag.CreatePen (PS_SOLID, 1, globalData.clrBtnText);

	gAllToolbars.AddTail (this);

	return 0;
}
//****************************************************************************************
DROPEFFECT CBCGToolBar::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	m_iDragIndex = -1;
	m_DropSource.m_bDeleteOnDrop = FALSE;

	return OnDragOver(pDataObject, dwKeyState, point);
}
//****************************************************************************************
void CBCGToolBar::OnDragLeave() 
{
	m_iDragIndex = -1;
	
	CRect rect = m_rectDrag;
	rect.InflateRect (2, 2);
	InvalidateRect (&rect);

	UpdateWindow ();

	m_rectDrag.SetRectEmpty ();
	m_iDragIndex = -1;

	m_DropSource.m_bDeleteOnDrop = TRUE;
}
//****************************************************************************************
DROPEFFECT CBCGToolBar::OnDragOver(COleDataObject* /*pDataObject*/, DWORD dwKeyState, CPoint point) 
{
	BOOL bCopy = (dwKeyState & MK_CONTROL);

	if (m_pDragButton == NULL)	// Drag from the other toolbar
	{
		//------------------
		// Remove selection:
		//------------------
		int iSelected = m_iSelected;
		m_iSelected = -1;

		if (iSelected != -1)
		{
			InvalidateButton (iSelected);
			UpdateWindow ();
		}
	}

	//---------------------
	// Find the drop place:
	//---------------------
	CRect rect = m_rectDrag;
	int iIndex = FindDropIndex (point, m_rectDrag);

	if (rect != m_rectDrag)
	{
		//--------------------
		// Redraw drop marker:
		//--------------------
		m_iDragIndex = iIndex;

		rect.InflateRect (2, 2);
		InvalidateRect (&rect);

		rect = m_rectDrag;
		rect.InflateRect (2, 2);
		InvalidateRect (&m_rectDrag);

		UpdateWindow ();
	}

	int iPrevHighlighted = m_iHighlighted;
	m_iHighlighted = HitTest (point);

	if (iPrevHighlighted != m_iHighlighted)
	{
		OnChangeHot (m_iHighlighted);
	}

	return (bCopy) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
}
//****************************************************************************************
BOOL CBCGToolBar::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	ASSERT_VALID(this);

	int iDragIndex = m_iDragIndex;
	if (iDragIndex < 0)
	{
		return FALSE;
	}

	CBCGToolbarButton* pDragButton = m_pDragButton;
	m_pDragButton = NULL;

	OnDragLeave();

	//----------------------------------------------------
	// Create a button object from the OLE clipboard data:
	//----------------------------------------------------
	CBCGToolbarButton* pButton = CreateDroppedButton (pDataObject);
	if (pButton == NULL)
	{
		return FALSE;
	}

	if (pDragButton != NULL && dropEffect != DROPEFFECT_COPY)
	{
		int iOldIndex = ButtonToIndex (pDragButton);
		if (iDragIndex == iOldIndex || iDragIndex == iOldIndex + 1)
		{
			AddRemoveSeparator (pDragButton, m_ptStartDrag, point);
			delete pButton;
			return TRUE;
		}
		
		RemoveButton (iOldIndex);
		if (iDragIndex > iOldIndex)
		{
			iDragIndex --;
		}
	}

	if (InsertButton (pButton, iDragIndex) == -1)
	{
		ASSERT (FALSE);
		delete pButton;
		return FALSE;
	}

	AdjustLayout ();

	m_iSelected = -1;
	Invalidate ();
	return TRUE;
}
//****************************************************************************************
BOOL CBCGToolBar::SetCustomizeMode (BOOL bSet)
{
	if (m_bCustomizeMode == bSet)
	{
		return FALSE;
	}

	//---------------------------------------------------------------------
	// First step - inform all toolbars about start/end customization mode:
	//---------------------------------------------------------------------
	for (BOOL bToolbarsListWasChanged = TRUE;
		bToolbarsListWasChanged;)
	{
		int iOrigCount = gAllToolbars.GetCount ();
		bToolbarsListWasChanged = FALSE;

		for (POSITION posTlb = gAllToolbars.GetHeadPosition (); 
			posTlb != NULL && !bToolbarsListWasChanged;)
		{
			CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (posTlb);
			ASSERT_VALID(pToolBar);

			pToolBar->OnCustomizeMode (bSet);

			//-------------------------------------------------
			// CBCGToolBar::OnCustomizeMode can add/remove some
			// "sub-toolbars". So, let's start loop again!
			//-------------------------------------------------
			if (gAllToolbars.GetCount () != iOrigCount)
			{
				bToolbarsListWasChanged = TRUE;
			}
		}
	}

	m_bCustomizeMode = bSet;

	//-----------------------------------
	// Second step - redraw all toolbars:
	//-----------------------------------
	for (POSITION posTlb = gAllToolbars.GetHeadPosition (); posTlb != NULL;)
	{
		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (posTlb);
		ASSERT_VALID(pToolBar);

		pToolBar->Invalidate ();
		pToolBar->UpdateWindow ();
	}

	return TRUE;
}
//********************************************************************************
int CBCGToolBar::GetCommandButtons (UINT uiCmd, CObList& listButtons)
{
	listButtons.RemoveAll ();
	if (uiCmd == 0)
	{
		return 0;
	}

	for (POSITION posTlb = gAllToolbars.GetHeadPosition (); posTlb != NULL;)
	{
		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (posTlb);
		ASSERT_VALID(pToolBar);

		for (POSITION pos = pToolBar->m_Buttons.GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) pToolBar->m_Buttons.GetNext (pos);
			ASSERT (pButton != NULL);

			if (pButton->m_nID == uiCmd)
			{
				listButtons.AddTail (pButton);
			}
		}
	}

	return listButtons.GetCount ();
}
//********************************************************************************
int CBCGToolBar::FindDropIndex (const CPoint p, CRect& rectDrag) const
{
	int iDragButton = -1;
	rectDrag.SetRectEmpty ();

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE;

	CPoint point = p;
	if (point.y < 0)
	{
		point.y = 0;
	}

	if (m_Buttons.IsEmpty ())
	{
		GetClientRect (&rectDrag);
		iDragButton = 0;
	}
	else
	{
		if (bHorz)
		{
			int iOffset = GetRowHeight ();
			int iButton = 0;
			CRect rectPrev;

			POSITION pos;
			for (pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++)
			{
				CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
				ASSERT (pButton != NULL);

				CRect rect = pButton->m_rect;

				if (iButton > 0 && rect.top > rectPrev.bottom)
				{
					iOffset	= rect.top - rectPrev.bottom;
					break;
				}

				rectPrev = rect;
			}

			int iCursorRow = point.y / (GetRowHeight () + iOffset);
			int iRow = 0;
			iButton = 0;

			for (pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++)
			{
				CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
				ASSERT (pButton != NULL);

				CRect rect = pButton->m_rect;
				
				if (iButton > 0 && rect.top != rectPrev.top)
				{
					iRow ++;
				}

				if (iRow > iCursorRow)
				{
					rectDrag = rectPrev;
					rectDrag.left = rectDrag.right;
					iDragButton = iButton - 1;
					break;
				}

				if (iRow == iCursorRow)
				{
					if (point.x < rect.left)
					{
						iDragButton = iButton;
						rectDrag = rect;
						rectDrag.right = rectDrag.left;
						break;
					}
					else if (point.x <= rect.right)
					{
						rectDrag = rect;
						if (point.x - rect.left > rect.right - point.x)
						{
							iDragButton = iButton + 1;
							rectDrag.left = rectDrag.right;
						}
						else
						{
							iDragButton = iButton;
							rectDrag.right = rectDrag.left;
						}
						break;
					}
				}

				rectPrev = rect;
			}

			if (iDragButton == -1 && iRow == iCursorRow)
			{
				rectDrag = rectPrev;
				rectDrag.left = rectDrag.right;
				iDragButton = iButton;
			}
		}
		else
		{
			int iButton = 0;
			for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++)
			{
				CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
				ASSERT (pButton != NULL);

				CRect rect = pButton->m_rect;

				if (point.y < rect.top)
				{
					iDragButton = iButton;
					rectDrag = rect;
					rectDrag.bottom = rectDrag.top;
					break;
				}
				else if (point.y <= rect.bottom)
				{
					rectDrag = rect;
					if (point.y - rect.top > rect.bottom - point.y)
					{
						iDragButton = iButton + 1;
						rectDrag.top = rectDrag.bottom;
					}
					else
					{
						iDragButton = iButton;
						rectDrag.bottom = rectDrag.top;
					}
					break;
				}
			}
		}
	}

	if (iDragButton >= 0)
	{
		const int iCursorSize = 6;

		CRect rectClient;	// Client area rectangle
		GetClientRect (&rectClient);

		if (bHorz)
		{
			rectDrag.left = 
				max (rectClient.left, rectDrag.left - iCursorSize / 2);

			rectDrag.right = rectDrag.left + iCursorSize;
			if (rectDrag.right > rectClient.right)
			{
				rectDrag.right = rectClient.right;
				rectDrag.left = rectDrag.right - iCursorSize;
			}
		}
		else
		{
			rectDrag.top = 
				max (rectClient.top, rectDrag.top - iCursorSize / 2);

			rectDrag.bottom = rectDrag.top + iCursorSize;
			if (rectDrag.bottom > rectClient.bottom)
			{
				rectDrag.bottom = rectClient.bottom;
				rectDrag.top = rectDrag.bottom - iCursorSize;
			}
		}
	}

	return iDragButton;
}
//***********************************************************************
void CBCGToolBar::DrawDragMarker (CDC* pDC)
{
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE;

	CPen* pOldPen = (CPen*) pDC->SelectObject (&m_penDrag);

	for (int i = 0; i < 2; i ++)
	{
		if (bHorz)
		{
			pDC->MoveTo (m_rectDrag.left + m_rectDrag.Width () / 2 + i - 1, m_rectDrag.top);
			pDC->LineTo (m_rectDrag.left + m_rectDrag.Width () / 2 + i - 1, m_rectDrag.bottom);

			pDC->MoveTo (m_rectDrag.left + i, m_rectDrag.top + i);
			pDC->LineTo (m_rectDrag.right - i, m_rectDrag.top + i);

			pDC->MoveTo (m_rectDrag.left + i, m_rectDrag.bottom - i - 1);
			pDC->LineTo (m_rectDrag.right - i, m_rectDrag.bottom - i - 1);
		}
		else
		{
			pDC->MoveTo (m_rectDrag.left, m_rectDrag.top + m_rectDrag.Height () / 2 + i - 1);
			pDC->LineTo (m_rectDrag.right, m_rectDrag.top + m_rectDrag.Height () / 2 + i - 1);

			pDC->MoveTo (m_rectDrag.left + i, m_rectDrag.top + i);
			pDC->LineTo (m_rectDrag.left + i, m_rectDrag.bottom - i);

			pDC->MoveTo (m_rectDrag.right - i - 1, m_rectDrag.top + i);
			pDC->LineTo (m_rectDrag.right - i - 1, m_rectDrag.bottom - i);
		}
	}

	pDC->SelectObject (pOldPen);
}
//********************************************************************
void CBCGToolBar::OnDestroy() 
{
	CControlBar::OnDestroy();

	for (POSITION pos = gAllToolbars.GetHeadPosition (); pos != NULL;)
	{
		POSITION posSave = pos;

		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (pos);
		ASSERT_VALID(pToolBar);

		if (pToolBar == this)
		{
			gAllToolbars.RemoveAt (posSave);
			break;
		}
	}
}
//********************************************************************
void CBCGToolBar::Serialize (CArchive& ar)
{
	CControlBar::Serialize (ar);

	POSITION pos;

	CString strName;

	if (ar.IsLoading ())
	{
		RemoveAllButtons ();
		m_Buttons.Serialize (ar);

		for (pos = m_Buttons.GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
			ASSERT (pButton != NULL);

			pButton->OnChangeParentWnd (this);
		}
		
		ar >> m_bShowTooltips;

		AdjustLocations ();

		ar >> strName;

		if (::IsWindow (m_hWnd))
		{
			SetWindowText (strName);
		}

		//--------------------------
		// Remove all "bad" buttons:
		//--------------------------
		for (pos = m_lstUnpermittedCommands.GetHeadPosition (); pos != NULL;)
		{
			UINT uiCmd = m_lstUnpermittedCommands.GetNext (pos);

			int iIndex = CommandToIndex (uiCmd);
			if (iIndex >= 0)
			{
				RemoveButton (iIndex);
			}
		}
	}
	else
	{
		//-----------------------------------
		// Serialize just "Storable" buttons:
		//-----------------------------------
		CObList buttons;

		for (pos = m_Buttons.GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
			ASSERT_VALID (pButton);

			if (pButton->CanBeStored ())
			{
				buttons.AddTail (pButton);
			}
		}

		buttons.Serialize (ar);
		ar << m_bShowTooltips;

		if (::IsWindow (m_hWnd))
		{
			GetWindowText (strName);
		}

		ar << strName;
	}
}
//*********************************************************************
BOOL CBCGToolBar::SaveState (LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	BOOL bResult = FALSE;

	if (nIndex == -1)
	{
		nIndex = GetDlgCtrlID ();
	}

	CString strSection;
	if (uiID == (UINT) -1)
	{
		strSection.Format (REG_SECTION_FMT, lpszProfileName, nIndex);
	}
	else
	{
		strSection.Format (REG_SECTION_FMT_EX, lpszProfileName, nIndex, uiID);
	}

	try
	{
		CMemFile file;

		{
			CArchive ar (&file, CArchive::store);

			Serialize (ar);
			ar.Flush ();
		}

		UINT uiDataSize = file.GetLength ();
		LPBYTE lpbData = file.Detach ();

		if (lpbData != NULL)
		{
			CRegistry reg (FALSE, FALSE);
			if (reg.CreateKey (strSection))
			{
				if (::IsWindow (m_hWnd))
				{
					CString strToolbarName;
					GetWindowText (strToolbarName);

					reg.Write (REG_ENTRY_NAME, strToolbarName);
				}

				bResult = reg.Write (REG_ENTRY_BUTTONS, lpbData, uiDataSize);
			}

			free (lpbData);
		}
	}
	catch (CMemoryException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("Memory exception in CBCGToolBar::SaveState ()!\n"));
	}

	return bResult;
}
//*********************************************************************
BOOL CBCGToolBar::RemoveStateFromRegistry (LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	if (nIndex == -1)
	{
		nIndex = GetDlgCtrlID ();
	}

	CString strSection;
	if (uiID == (UINT) -1)
	{
		strSection.Format (REG_SECTION_FMT, lpszProfileName, nIndex);
	}
	else
	{
		strSection.Format (REG_SECTION_FMT_EX, lpszProfileName, nIndex, uiID);
	}

	CRegistry reg (FALSE, FALSE);
	return reg.DeleteKey (strSection);
}
//*********************************************************************
BOOL CBCGToolBar::LoadState (LPCTSTR lpszProfileName, int nIndex, UINT uiID)
{
	BOOL bResult = FALSE;

	if (nIndex == -1)
	{
		nIndex = GetDlgCtrlID ();
	}

	CString strSection;
	if (uiID == (UINT) -1)
	{
		strSection.Format (REG_SECTION_FMT, lpszProfileName, nIndex);
	}
	else
	{
		strSection.Format (REG_SECTION_FMT_EX, lpszProfileName, nIndex, uiID);
	}

	LPBYTE	lpbData = NULL;
	UINT	uiDataSize;

	CRegistry reg (FALSE, TRUE);
	if (!reg.Open (strSection))
	{
		return FALSE;
	}

	if (!reg.Read (REG_ENTRY_BUTTONS, &lpbData, &uiDataSize))
	{
		return FALSE;
	}

	try
	{
		CMemFile file (lpbData, uiDataSize);
		CArchive ar (&file, CArchive::load);

		Serialize (ar);
		bResult = TRUE;
	}
	catch (CMemoryException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("Memory exception in CBCGToolBar::LoadState ()!\n"));
	}
	catch (CArchiveException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("CArchiveException exception in CBCGToolBar::LoadState ()!\n"));
	}

	if (lpbData != NULL)
	{
		delete lpbData;
	}

	AdjustLayout ();
	return bResult;
}
//*******************************************************************************************
void CBCGToolBar::OnContextMenu(CWnd*, CPoint point)
{
	if (m_bLocked && IsCustomizeMode ())
	{
		MessageBeep ((UINT) -1);
		return;
	}

	OnChangeHot (-1);

	if (!IsCustomizeMode ())
	{
		CFrameWnd* pParentFrame = (m_pDockSite == NULL) ?
			GetDockingFrame() : m_pDockSite;
		ASSERT_VALID(pParentFrame);

		pParentFrame->SendMessage (BCGM_TOOLBARMENU,
			(WPARAM) GetSafeHwnd (),
			MAKELPARAM(point.x, point.y));
		return;
	}

	SetFocus ();

	CPoint ptClient = point;
	ScreenToClient (&ptClient);

	int iButton = HitTest(ptClient);

	int iSelected = m_iSelected;
	m_iSelected = iButton;

	if (iSelected != -1)
	{
		InvalidateButton (iSelected);
	}

	if (m_iSelected != -1)
	{
		InvalidateButton (m_iSelected);
	}

	UpdateWindow ();

	if (iButton < 0) // nothing hit
	{
		return;
	}

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	if (!pButton->IsEditable ())
	{
		m_iSelected = -1;
		InvalidateButton (iButton);
		UpdateWindow ();

		return;
	}

	if (pButton->CanBeStored ())
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CBCGLocalResource locaRes;

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_BCGBARRES_POPUP_BCGTOOL_BAR));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		if (EnableContextMenuItems (pButton, pPopup))
		{
			pPopup->TrackPopupMenu (TPM_LEFTALIGN | TPM_RIGHTBUTTON,
									point.x, point.y, this);
		}
	}
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarAppearance() 
{
	CBCGLocalResource locaRes;

	ASSERT (IsCustomizeMode () && !m_bLocked);
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	if (pButton->m_strText.IsEmpty ())
	{
		OnSetDefaultButtonText (pButton);
	}

	CButtonAppearanceDlg dlg (pButton, m_pUserImages, this, 0, m_bMenuMode);
	if (dlg.DoModal () == IDOK)
	{
		AdjustLayout ();
		Invalidate ();
	}
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarDelete() 
{
	ASSERT (m_iSelected >= 0);
	RemoveButton (m_iSelected);
	
	m_iSelected = -1;

	AdjustLayout ();
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarImage() 
{
	CBCGLocalResource locaRes;

	ASSERT (IsCustomizeMode () && !m_bLocked);
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	BOOL bSaveText = pButton->m_bText;
	BOOL bSaveImage = pButton->m_bImage;

	pButton->m_bText = FALSE;
	pButton->m_bImage = TRUE;

	if (pButton->GetImage () < 0)
	{
		CButtonAppearanceDlg dlg (pButton, m_pUserImages, this, 0, m_bMenuMode);
		if (dlg.DoModal () != IDOK)
		{
			pButton->m_bText = bSaveText;
			pButton->m_bImage = bSaveImage;
			return;
		}
	}

	AdjustLayout ();
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarImageAndText() 
{
	ASSERT (IsCustomizeMode () && !m_bLocked);
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	BOOL bSaveText = pButton->m_bText;
	BOOL bSaveImage = pButton->m_bImage;

	pButton->m_bText = TRUE;
	pButton->m_bImage = TRUE;

	if (pButton->GetImage () < 0)
	{
		CBCGLocalResource locaRes;

		CButtonAppearanceDlg dlg (pButton, m_pUserImages, this, 0, m_bMenuMode);
		if (dlg.DoModal () != IDOK)
		{
			pButton->m_bText = bSaveText;
			pButton->m_bImage = bSaveImage;
			return;
		}
	}

	if (pButton->m_strText.IsEmpty ())
	{
		OnSetDefaultButtonText (pButton);
	}

	if (pButton->m_strText.IsEmpty ())
	{
		MessageBeep ((UINT) -1);

		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
	}

	AdjustLayout ();
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarStartGroup() 
{
	ASSERT (m_iSelected > 0);

	CBCGToolbarButton* pPrevButton = NULL;
	int i = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
	{
		CBCGToolbarButton* pCurrButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pCurrButton);

		if (i == m_iSelected)
		{
			ASSERT (pPrevButton != NULL);	// m_iSelected > 0!

			if (pPrevButton->m_nStyle & TBBS_SEPARATOR)
			{
				VERIFY (RemoveButton (m_iSelected - 1));
			}
			else
			{
				InsertSeparator (m_iSelected ++);
			}

			break;
		}

		pPrevButton = pCurrButton;
	}

	AdjustLayout ();
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarText() 
{
	ASSERT (IsCustomizeMode () && !m_bLocked);
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	pButton->m_bText = TRUE;
	pButton->m_bImage = FALSE;

	if (pButton->m_strText.IsEmpty ())
	{
		OnSetDefaultButtonText (pButton);
	}

	if (pButton->m_strText.IsEmpty ())
	{
		MessageBeep ((UINT) -1);

		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
	}

	AdjustLayout ();
}
//************************************************************************************
void CBCGToolBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CControlBar::OnWindowPosChanged(lpwndpos);
	RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE);

	if (!IsCustomizeMode () || g_pWndCustomize == NULL || m_bLocked)
	{
		return;
	}

	if (lpwndpos->flags & SWP_HIDEWINDOW)
	{
		g_pWndCustomize->ShowToolBar (this, FALSE);
	}
	
	if (lpwndpos->flags & SWP_SHOWWINDOW)
	{
		g_pWndCustomize->ShowToolBar (this, TRUE);
	}
}
//**************************************************************************************
HBRUSH CBCGToolBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CControlBar::OnCtlColor (pDC, pWnd, nCtlColor);
	if (!IsCustomizeMode () || m_bLocked)
	{
		return hbr;
	}

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		HWND hwdList = pButton->GetHwnd ();
		if (hwdList == NULL)	// No control
		{
			continue;
		}

		if (hwdList == pWnd->GetSafeHwnd () ||
			::IsChild (hwdList, pWnd->GetSafeHwnd ()))
		{
			HBRUSH hbrButton = pButton->OnCtlColor (pDC, nCtlColor);
			return (hbrButton == NULL) ? hbr : hbrButton;
		}
	}

	return hbr;
}
//**************************************************************************************
int CBCGToolBar::GetCount () const
{
	return m_Buttons.GetCount ();
}
//*************************************************************************************
BOOL CBCGToolBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	BOOL bStretch = m_bStretchButton;

	if (!bStretch && IsCustomizeMode () && m_iSelected != -1 && !m_bLocked)
	{
		CPoint ptCursor;
		::GetCursorPos (&ptCursor);
		ScreenToClient (&ptCursor);

		if (HitTest (ptCursor) == m_iSelected)
		{
			CBCGToolbarButton* pButton = GetButton (m_iSelected);
			ASSERT_VALID (pButton);

			if (pButton->CanBeStretched () &&
				abs (ptCursor.x - pButton->m_rect.right) <= STRETCH_DELTA)
			{
				bStretch = TRUE;
			}
		}
	}

	if (bStretch)
	{
		::SetCursor (globalData.m_hcurStretch);
		return TRUE;
	}
	
	return CControlBar::OnSetCursor(pWnd, nHitTest, message);
}
//****************************************************************************************
BOOL CBCGToolBar::PreTranslateMessage(MSG* pMsg) 
{
	if (m_bStretchButton &&
		pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_ESCAPE)
	{
		OnCancelMode ();
		return TRUE;
	}

	return CControlBar::PreTranslateMessage(pMsg);
}
//**************************************************************************************
BOOL CBCGToolBar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (IsCustomizeMode () && !m_bLocked)
	{
		return CControlBar::OnCommand (wParam, lParam);
	}

	BOOL bAccelerator = FALSE;
	int nNotifyCode = HIWORD (wParam);

	// Find the control send the message:
	HWND hWndCtrl = (HWND)lParam;
	if (hWndCtrl == NULL)
	{
		if (wParam == IDCANCEL)	// ESC was pressed
		{
//			GetOwner()->SetFocus ();
			RestoreFocus ();
			return TRUE;
		}

		if (wParam != IDOK ||
			(hWndCtrl = ::GetFocus ()) == NULL)
		{
			return FALSE;
		}

		bAccelerator = TRUE;
		nNotifyCode = 0;
	}

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		HWND hwdList = pButton->GetHwnd ();
		if (hwdList == NULL)	// No control
		{
			continue;
		}

		if (hwdList == hWndCtrl || ::IsChild (hwdList, hWndCtrl))
		{
			if (!bAccelerator)
			{
				ASSERT (LOWORD (wParam) == pButton->m_nID);
				if (!pButton->NotifyCommand (nNotifyCode))
				{
					break;
				}
			}

			GetOwner()->PostMessage (WM_COMMAND,
				MAKEWPARAM (pButton->m_nID, nNotifyCode), lParam);
			return TRUE;
		}
	}

	return TRUE;
}
//*************************************************************************************
CBCGToolBar* CBCGToolBar::FromHandlePermanent (HWND hwnd)
{
	for (POSITION posTlb = gAllToolbars.GetHeadPosition (); posTlb != NULL;)
	{
		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (posTlb);
		ASSERT_VALID(pToolBar);

		if (pToolBar->GetSafeHwnd () == hwnd)
		{
			return pToolBar;
		}
	}

	return NULL;
}
//**********************************************************************************
CSize CBCGToolBar::CalcLayout(DWORD dwMode, int nLength)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));
	
	if (dwMode & LM_HORZDOCK)
	{
		ASSERT(dwMode & LM_HORZ);
	}

	CSize sizeResult(0,0);

	if (!(m_dwStyle & CBRS_SIZE_FIXED))
	{
		BOOL bDynamic = m_dwStyle & CBRS_SIZE_DYNAMIC;

		if (bDynamic && (dwMode & LM_MRUWIDTH))
			SizeToolBar(m_nMRUWidth);
		else if (bDynamic && (dwMode & LM_HORZDOCK))
			SizeToolBar(32767);
		else if (bDynamic && (dwMode & LM_VERTDOCK))
		{
			SizeToolBar(0);
		}
		else if (bDynamic && (nLength != -1))
		{
			CRect rect; rect.SetRectEmpty();
			CalcInsideRect(rect, (dwMode & LM_HORZ));
			BOOL bVert = (dwMode & LM_LENGTHY);

			int nLen = nLength + (bVert ? rect.Height() : rect.Width());

			SizeToolBar(nLen, bVert);
		}
		else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
			SizeToolBar(m_nMRUWidth);
		else
			SizeToolBar((dwMode & LM_HORZ) ? 32767 : 0);
	}

	sizeResult = CalcSize ((dwMode & LM_HORZ) == 0);

	if (dwMode & LM_COMMIT)
	{
		if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC) &&
			(dwMode & LM_HORZ))
		{
			m_nMRUWidth = sizeResult.cx;
		}
	}

	//BLOCK: Adjust Margins
	{
		CRect rect; rect.SetRectEmpty();
		CalcInsideRect(rect, (dwMode & LM_HORZ));
		sizeResult.cy -= rect.Height();
		sizeResult.cx -= rect.Width();

		CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
		sizeResult.cx = max(sizeResult.cx, size.cx);
		sizeResult.cy = max(sizeResult.cy, size.cy);
	}

	RebuildAccelerationKeys ();
	return sizeResult;
}
//**********************************************************************************
CSize CBCGToolBar::CalcSize (BOOL bVertDock)
{
	if (m_Buttons.IsEmpty ())
	{
		return m_sizeButton;
	}

	CSize sizeResult (GetColumnWidth (), GetRowHeight ());

	CRect rect; rect.SetRectEmpty();
	CalcInsideRect (rect, !bVertDock);

	int iStartX = bVertDock ? 0 : 1;
	int iStartY = bVertDock ? 1 : 0;

	CPoint cur (iStartX, iStartY);

	CClientDC dc (this);
	CFont* pOldFont = (CFont*) dc.SelectObject (&globalData.fontRegular);
	ASSERT (pOldFont != NULL);

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		CSize sizeButton = pButton->OnCalculateSize (&dc, 
			CSize (GetColumnWidth (), GetRowHeight ()), !bVertDock);

		if (!bVertDock)
		{
			if ((cur.x == iStartX || pButton->m_bWrap)
				&& pButton->m_nStyle & TBBS_SEPARATOR)
			{
				sizeButton = CSize (0, 0);
			}

			sizeResult.cx = max (cur.x + sizeButton.cx, sizeResult.cx);
			sizeResult.cy = max (cur.y + sizeButton.cy, sizeResult.cy);

			cur.x += sizeButton.cx;

			if (pButton->m_bWrap)
			{
				cur.x = iStartX;
				cur.y += GetRowHeight () + LINE_OFFSET;
			}
		}
		else
		{
			sizeResult.cx = max (cur.x + sizeButton.cx, sizeResult.cx);
			sizeResult.cy = max (cur.y + sizeButton.cy, sizeResult.cy);

			cur.x = iStartX;
			cur.y += sizeButton.cy;
		}
	}

	dc.SelectObject (pOldFont);
	return sizeResult;
}
//**********************************************************************************
int CBCGToolBar::WrapToolBar (int nWidth)
{
	int nResult = 0;
	
	BOOL bVertDock = (m_dwStyle & CBRS_ORIENT_HORZ) == 0;

	CClientDC dc (this);

	CFont* pOldFont = (CFont*) dc.SelectObject (&globalData.fontRegular);
	ASSERT (pOldFont != NULL);

	CBCGToolbarButton* pPrevButton = NULL;

	CRect rect;
	GetClientRect(rect);

	int x = 0;
	int y = rect.top;

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		pButton->m_bWrap = FALSE;

		CSize sizeButton = pButton->OnCalculateSize (&dc, 
			CSize (GetColumnWidth (), GetRowHeight ()), !bVertDock);
		
		if (x == 0 && (pButton->m_nStyle & TBBS_SEPARATOR))
		{
			// Don't show separator on the first column!
			sizeButton = CSize (0, 0);
		}

		if (x + sizeButton.cx > nWidth &&
			!(pButton->m_nStyle & TBBS_SEPARATOR))
		{
			if (pPrevButton != NULL)
			{
				pPrevButton->m_bWrap = TRUE;
				x = 0;
				y += sizeButton.cy + LINE_OFFSET;
				nResult ++;
			}
		}

		pPrevButton = pButton;
		x += sizeButton.cx;
	}

	dc.SelectObject (pOldFont);
	return nResult + 1;
}
//**********************************************************************************
void  CBCGToolBar::SizeToolBar (int nLength, BOOL bVert)
{
	CSize size;

	if (!bVert)
	{
		int nMin, nMax, nTarget, nCurrent, nMid;

		// Wrap ToolBar vertically
		nMin = 0;
		nCurrent = WrapToolBar(nMin);

		// Wrap ToolBar as specified
		nMax = nLength;
		nTarget = WrapToolBar(nMax);

		if (nCurrent != nTarget)
		{
			while (nMin < nMax)
			{
				nMid = (nMin + nMax) / 2;
				nCurrent = WrapToolBar(nMid);

				if (nCurrent == nTarget)
					nMax = nMid;
				else
				{
					if (nMin == nMid)
					{
						WrapToolBar(nMax);
						break;
					}
					nMin = nMid;
				}
			}
		}

		size = CalcSize (bVert);
		WrapToolBar (size.cx);
	}
	else
	{
		int iWidth = 32767;
		WrapToolBar (iWidth);

		size = CalcSize (FALSE);
		if (nLength > size.cy)
		{
			iWidth = 0;

			do
			{
				iWidth += m_sizeButton.cx;
				WrapToolBar (iWidth);
				size = CalcSize (FALSE);
			}
			while (nLength < size.cy);
		}

		WrapToolBar (size.cx);
	}
}
//**********************************************************************************
void CBCGToolBar::OnSize(UINT nType, int cx, int cy) 
{
	CControlBar::OnSize(nType, cx, cy);
	
	if (IsCustomizeMode () && !m_bLocked)
	{
		OnCancelMode ();
	}

	AdjustLocations ();

	//------------------------------------------------------
	// Adjust system menu of the floating toolbar miniframe:
	//------------------------------------------------------
	if (IsFloating ())
	{
		CMiniFrameWnd* pMiniFrame = 
			DYNAMIC_DOWNCAST (CMiniFrameWnd, GetParentFrame ());
		if (pMiniFrame != NULL)
		{
			CMenu* pSysMenu = pMiniFrame->GetSystemMenu(FALSE);
			ASSERT (pSysMenu != NULL);

			pSysMenu->DeleteMenu (SC_RESTORE, MF_BYCOMMAND);
			pSysMenu->DeleteMenu (SC_MINIMIZE, MF_BYCOMMAND);
			pSysMenu->DeleteMenu (SC_MAXIMIZE, MF_BYCOMMAND);

			if (!CanBeClosed ())
			{
				pSysMenu->EnableMenuItem (SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
			}
		}
	}
}
//**********************************************************************************
void CBCGToolBar::AdjustLocations ()
{
	ASSERT_VALID(this);

	BOOL bHorz = m_dwStyle & CBRS_ORIENT_HORZ ? TRUE : FALSE;

	CRect rectClient;
	GetClientRect (rectClient);

	CClientDC dc (this);
	CFont* pOldFont;
	if (bHorz)
	{
		pOldFont = (CFont*) dc.SelectObject (&globalData.fontRegular);
	}
	else
	{
		pOldFont = (CFont*) dc.SelectObject (&globalData.fontVert);
	}
	
	ASSERT (pOldFont != NULL);

	int iStartOffset;
	if (bHorz)
	{
		iStartOffset = rectClient.left + 1;
	}
	else
	{
		iStartOffset = rectClient.top + 1;
	}

	int iOffset = iStartOffset;
	int y = rectClient.top;

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		CSize sizeButton = pButton->OnCalculateSize (&dc, 
			CSize (GetColumnWidth (), GetRowHeight ()), bHorz);
		if (iOffset == iStartOffset && pButton->m_nStyle & TBBS_SEPARATOR)
		{
			sizeButton = CSize (0, 0);
		}

		CRect rectButton;
		if (bHorz)
		{
			rectButton.left = iOffset;
			rectButton.right = iOffset + sizeButton.cx;
			rectButton.top = y;
			rectButton.bottom = rectButton.top + sizeButton.cy;
			
			iOffset += sizeButton.cx;
		}
		else
		{
			rectButton.left = rectClient.left;
			rectButton.right = rectClient.left + sizeButton.cx;
			rectButton.top = iOffset;
			rectButton.bottom = iOffset + sizeButton.cy;

			iOffset += sizeButton.cy;
		}

		pButton->m_rect = rectButton;
		pButton->OnMove ();

		if (pButton->m_bWrap && bHorz)
		{
			iOffset = iStartOffset;
			y += GetRowHeight () + LINE_OFFSET;
		}
	}

	dc.SelectObject (pOldFont);
}
//**********************************************************************************
DWORD CBCGToolBar::RecalcDelayShow(AFX_SIZEPARENTPARAMS* lpLayout)
{
	DWORD dwRes = CControlBar::RecalcDelayShow (lpLayout);

	if (!IsFloating ())
	{
		AdjustLocations ();
	}

	return dwRes;
}
//*********************************************************************************
void CBCGToolBar::AddRemoveSeparator (const CBCGToolbarButton* pButton,
						const CPoint& ptStart, const CPoint& ptDrop)
{
	ASSERT_VALID (pButton);
	
	int iIndex = ButtonToIndex (pButton);
	if (iIndex <= 0)
	{
		return;
	}

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	int iDelta = (bHorz) ? ptDrop.x - ptStart.x : ptDrop.y - ptStart.y;

	if (abs (iDelta) < STRETCH_DELTA)
	{
		// Ignore small move....
		return;
	}

	if (iDelta > 0)	// Add a separator left of button
	{
		const CBCGToolbarButton* pLeftButton = GetButton (iIndex - 1);
		ASSERT_VALID (pLeftButton);

		if (pLeftButton->m_nStyle & TBBS_SEPARATOR)
		{
			// Already have separator, do nothing...
			return;
		}

		InsertSeparator (iIndex);
	}
	else	// Remove a separator in the left side
	{
		const CBCGToolbarButton* pLeftButton = GetButton (iIndex - 1);
		ASSERT_VALID (pLeftButton);

		if ((pLeftButton->m_nStyle & TBBS_SEPARATOR) == 0)
		{
			// Not a separator, do nothing...
			return;
		}

		RemoveButton (iIndex - 1);
	}

	AdjustLayout ();

	m_iSelected = -1;
	Invalidate ();
	UpdateWindow ();
}
//***************************************************************************************
void CBCGToolBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int iButton = HitTest(point);
	if (iButton >= 0)
	{
		CBCGToolbarButton* pButton = GetButton (iButton);
		ASSERT_VALID (pButton);

		pButton->OnDblClick (this);

		//----------------------------------------------------------
		// Don't permit dock/undock when user double clicks on item!
		//----------------------------------------------------------
	}
	else
	{
		CControlBar::OnLButtonDblClk(nFlags, point);
	}
}
//***************************************************************************************
void CBCGToolBar::DrawSeparator (CDC* pDC, const CRect& rect, BOOL bHorz)
{
	CRect rectSeparator = rect;
	if (bHorz)
	{
		rectSeparator.left += rectSeparator.Width () / 2 - 1;
		rectSeparator.right = rectSeparator.left + 2;
	}
	else
	{
		rectSeparator.top += rectSeparator.Height () / 2 - 1;
		rectSeparator.bottom = rectSeparator.top + 2;
	}

	pDC->Draw3dRect (rectSeparator, globalData.clrBtnShadow,
									globalData.clrBtnHilite);
}
//***************************************************************************************
CBCGToolbarButton* CBCGToolBar::CreateDroppedButton (COleDataObject* pDataObject)
{
	CBCGToolbarButton* pButton = CBCGToolbarButton::CreateFromOleData (pDataObject);
	ASSERT (pButton != NULL);

	//---------------------------
	// Remove accelerator string:
	//---------------------------
	int iOffset = pButton->m_strText.Find (_T('\t'));
	if (iOffset >= 0)
	{
		pButton->m_strText = pButton->m_strText.Left (iOffset);
	}

	pButton->m_bText = FALSE;
	pButton->m_bImage = TRUE;

	if (pButton->m_bDragFromCollection && pButton->GetImage () == -1)
	{
		//----------------------------------------------
		// User-defined button by default have no image:
		//----------------------------------------------
		CBCGLocalResource locaRes;
		CButtonAppearanceDlg dlg (pButton, m_pUserImages, this, 0, m_bMenuMode);

		if (dlg.DoModal () != IDOK)
		{
			delete pButton;
			return NULL;
		}
	}

	if (pButton->GetImage () < 0)
	{
		pButton->m_bText = TRUE;
		pButton->m_bImage = FALSE;
	}

	return pButton;
}
//****************************************************************************************
CBCGToolbarButton* CBCGToolBar::GetHighlightedButton () const
{
	if (m_iHighlighted < 0)
	{
		return NULL;
	}
	else
	{
		return GetButton (m_iHighlighted);
	}
}
//****************************************************************************************
void CBCGToolBar::RebuildAccelerationKeys ()
{
	m_AcellKeys.RemoveAll ();

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		if (pButton->m_nStyle & TBBS_SEPARATOR)
		{
			continue;
		}

		int iAmpOffset = pButton->m_strText.Find (_T('&'));
		if (iAmpOffset >= 0 && iAmpOffset < pButton->m_strText.GetLength () - 1)
		{
			UINT uHotKey = (UINT) toupper (pButton->m_strText.GetAt (iAmpOffset + 1));
			m_AcellKeys.SetAt (uHotKey, pButton);
		}
	}
}
//****************************************************************************************
void CBCGToolBar::OnCustomizeMode (BOOL bSet)
{
	m_iButtonCapture = -1;
	m_iHighlighted = -1;
	m_iSelected = -1;

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		pButton->OnCancelMode ();

		HWND hwnd = pButton->GetHwnd ();
		if (hwnd != NULL)
		{
			::EnableWindow (hwnd, !bSet);
		}
	}
}
//****************************************************************************************
BOOL CBCGToolBar::RestoreOriginalstate ()
{
	if (m_uiOriginalResID == 0)
	{
		return FALSE;
	}

	BOOL bRes = LoadToolBar (m_uiOriginalResID);

	AdjustLayout ();
	Invalidate ();

	return bRes;
}
//*****************************************************************************************
void CBCGToolBar::ShowCommandMessageString (UINT uiCmdId)
{
	if (m_hookMouseHelp != NULL)
	{
		return;
	}

	if (uiCmdId == (UINT) -1)
	{
		GetOwner()->SendMessage (WM_SETMESSAGESTRING, 0, (LPARAM) _T(""));
		return;
	}

	UINT uiTrackId = uiCmdId;
	if (IsSystemCommand (uiCmdId))
	{
		uiTrackId = ID_COMMAND_FROM_SC (uiCmdId);
		ASSERT (uiTrackId >= AFX_IDS_SCFIRST &&
				uiTrackId < AFX_IDS_SCFIRST + 31);
	}
	else if (uiCmdId >= AFX_IDM_FIRST_MDICHILD)
	{
		// all MDI Child windows map to the same help id
		uiTrackId = AFX_IDS_MDICHILD;
	}

	GetOwner()->SendMessage (WM_SETMESSAGESTRING, (WPARAM) uiTrackId);
}
//*****************************************************************************************
afx_msg LRESULT CBCGToolBar::OnMouseLeave(WPARAM,LPARAM)
{
	if (m_hookMouseHelp != NULL)
	{
		return 0;
	}

	m_bTracked = FALSE;
	m_ptLastMouse = CPoint (-1, -1);

	if (m_iHighlighted >= 0 && GetFocus () != this)
	{
		int iButton = m_iHighlighted;
		m_iHighlighted = -1;

		OnChangeHot (m_iHighlighted);

		InvalidateButton (iButton);
		UpdateWindow(); // immediate feedback

		GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
	}

	return 0;
}
//*****************************************************************************************
BOOL CBCGToolBar::CanBeRestored () const
{
	return (m_uiOriginalResID != 0);
}
//*****************************************************************************************
BOOL CBCGToolBar::IsLastCommandFromButton (CBCGToolbarButton* pButton)
{
	ASSERT_VALID (pButton);

	HWND hwnd = pButton->GetHwnd ();

	if (!::IsWindow(hwnd) ||
		!(::GetWindowLong (hwnd, GWL_STYLE) & WS_VISIBLE))
	{
		return FALSE;
	}

	const MSG* pMsg = CWnd::GetCurrentMessage();
	if (pMsg == NULL)
	{
		return FALSE;
	}

	return (hwnd == (HWND) pMsg->lParam);
}
//*****************************************************************************************
BOOL CBCGToolBar::AddToolBarForImageCollection (UINT uiResID)
{
	CBCGToolBar tlbTmp;
	return tlbTmp.LoadToolBar (uiResID);
}
//*****************************************************************************************
void CBCGToolBar::SetHotTextColor (COLORREF clrText)
{
	m_clrTextHot = clrText;
}
//*****************************************************************************************
COLORREF CBCGToolBar::GetHotTextColor ()
{
	return m_clrTextHot == (COLORREF) -1 ?
		globalData.clrBtnText : m_clrTextHot;
}
//*****************************************************************************************
void CBCGToolBar::OnBcgbarresToolbarReset() 
{
	CBCGLocalResource locaRes;

	ASSERT (IsCustomizeMode () && !m_bLocked);
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	int iImage;
	if (m_DefaultImages.Lookup (pButton->m_nID, iImage))
	{
		pButton->m_bUserButton = FALSE;
		pButton->SetImage (iImage);
		pButton->m_bImage = TRUE;
	}
	else
	{
		pButton->m_bImage = FALSE;
	}

	pButton->m_bText = m_bMenuMode || !pButton->m_bImage;

	//----------------------
	// Restore default text:
	//----------------------
	OnSetDefaultButtonText (pButton);

	AdjustLayout ();
	g_ImageHash.Clear (pButton->m_nID);

	Invalidate ();
}
//***************************************************************************************
afx_msg LRESULT CBCGToolBar::OnHelpHitTest(WPARAM wParam, LPARAM lParam)
{
	OnCancelMode ();

	int nIndex = HitTest ((DWORD) lParam);
	if (nIndex < 0)	// Click into the empty space or separator,
	{				// don't show HELP
		MessageBeep ((UINT) -1);
		return -1;
	}

	CBCGToolbarButton* pButton = GetButton (nIndex);
	ASSERT (pButton != NULL);

	if (pButton->OnContextHelp (this))
	{
		return -1;	// Continue help mode
	}

	LRESULT lres = CControlBar::OnHelpHitTest (wParam, lParam);

	if (lres > 0)
	{
		SetHelpMode (FALSE);
	}

	return lres;
}
//****************************************************************************************
LRESULT CALLBACK CBCGToolBar::BCGToolBarMouseProc (int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode != HC_ACTION)
	{
		return CallNextHookEx (m_hookMouseHelp, nCode, wParam, lParam);
	}

	MOUSEHOOKSTRUCT* lpMS = (MOUSEHOOKSTRUCT*) lParam;
	ASSERT (lpMS != NULL);

	if (wParam == WM_MOUSEMOVE)
	{
		//------------------------------------------
		// Find a toolbar matched to the mouse hook:
		//------------------------------------------
		CBCGToolBar* pWndToolBar = 
			DYNAMIC_DOWNCAST (CBCGToolBar, CWnd::WindowFromPoint (lpMS->pt));
		if (pWndToolBar != NULL)
		{
			CPoint ptClient = lpMS->pt;
			pWndToolBar->ScreenToClient (&ptClient);
			pWndToolBar->OnMouseMove (0, ptClient);
		}

		if (m_pLastHookedToolbar != NULL &&
			m_pLastHookedToolbar != pWndToolBar)
		{
			m_pLastHookedToolbar->m_bTracked = FALSE;
			m_pLastHookedToolbar->m_ptLastMouse = CPoint (-1, -1);

			if (m_pLastHookedToolbar->m_iHighlighted >= 0)
			{
				int iButton = m_pLastHookedToolbar->m_iHighlighted;
				m_pLastHookedToolbar->m_iHighlighted = -1;

				m_pLastHookedToolbar->OnChangeHot (m_pLastHookedToolbar->m_iHighlighted);

				m_pLastHookedToolbar->InvalidateButton (iButton);
				m_pLastHookedToolbar->UpdateWindow(); // immediate feedback
			}
		}

		m_pLastHookedToolbar = pWndToolBar;
	}

	return 0;
}
//***************************************************************************************
void CBCGToolBar::SetHelpMode (BOOL bOn)
{
	if (bOn)
	{
		if (m_hookMouseHelp == NULL)	// Not installed yet, set it now!
		{
			m_hookMouseHelp = ::SetWindowsHookEx (WH_MOUSE, BCGToolBarMouseProc, 
				0, GetCurrentThreadId ());
			if (m_hookMouseHelp == NULL)
			{
				TRACE (_T("CBCGToolBar: Can't set mouse hook!\n"));
			}
		}
	}
	else if (m_hookMouseHelp != NULL)
	{
		::UnhookWindowsHookEx (m_hookMouseHelp);
		m_hookMouseHelp = NULL;

		m_pLastHookedToolbar = NULL;

		for (POSITION posTlb = gAllToolbars.GetHeadPosition (); posTlb != NULL;)
		{
			CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (posTlb);
			ASSERT_VALID(pToolBar);

			pToolBar->OnCancelMode ();
		}
	}
}
//***************************************************************************************
void CBCGToolBar::SetNonPermittedCommands (CList<UINT, UINT>& lstCommands)
{
	m_lstUnpermittedCommands.RemoveAll ();
	m_lstUnpermittedCommands.AddTail (&lstCommands);
}
//***************************************************************************************
void CBCGToolBar::OnNcCalcSize(BOOL /*bCalcValidRects*/, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	CRect rect; rect.SetRectEmpty();
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;

	CControlBar::CalcInsideRect(rect, bHorz);

	// adjust non-client area for border space
	lpncsp->rgrc[0].left += rect.left;
	lpncsp->rgrc[0].top += rect.top;

	lpncsp->rgrc[0].right += rect.right;
	lpncsp->rgrc[0].bottom += rect.bottom;
}
//***************************************************************************************
void CBCGToolBar::OnNcPaint() 
{
	// get window DC that is clipped to the non-client area
	CWindowDC dc(this);
	CRect rectClient;
	GetClientRect(rectClient);
	CRect rectWindow;
	GetWindowRect(rectWindow);
	ScreenToClient(rectWindow);
	rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
	dc.ExcludeClipRect(rectClient);

	// draw borders in non-client area
	rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);
	DrawBorders(&dc, rectWindow);

	// erase parts not drawn
	dc.IntersectClipRect(rectWindow);
	SendMessage(WM_ERASEBKGND, (WPARAM)dc.m_hDC);

	// draw gripper in non-client area
	DrawGripper(&dc);
}
//****************************************************************************************
UINT CBCGToolBar::OnNcHitTest(CPoint /*point*/) 
{
	return HTCLIENT;
}
//***************************************************************************************
void CBCGToolBar::AdjustLayout ()
{
	if (GetSafeHwnd () == NULL)
	{
		return;
	}

	CReBar* pBar = DYNAMIC_DOWNCAST (CReBar, GetParent ());
	if (pBar != NULL)
	{
		CReBarCtrl& wndReBar = pBar->GetReBarCtrl ();
		UINT uiReBarsCount = wndReBar.GetBandCount ();

		REBARBANDINFO bandInfo;
		bandInfo.cbSize = sizeof (bandInfo);
		bandInfo.fMask = (RBBIM_CHILDSIZE | RBBIM_CHILD);

		for (UINT uiBand = 0; uiBand < uiReBarsCount; uiBand ++)
		{
			wndReBar.GetBandInfo (uiBand, &bandInfo);
			if (bandInfo.hwndChild == GetSafeHwnd ())
			{
				break;
			}
		}

		if (uiBand >= uiReBarsCount)
		{
			ASSERT (FALSE);
		}
		else
		{
			CSize sizeMin = CalcSize (FALSE);

			CRect rect; rect.SetRectEmpty();
			CalcInsideRect (rect, TRUE);
			sizeMin.cy -= rect.Height();
			sizeMin.cx -= rect.Width();

			CSize size = CControlBar::CalcFixedLayout (FALSE, TRUE);
			sizeMin.cx = max(sizeMin.cx, size.cx);
			sizeMin.cy = max(sizeMin.cy, size.cy);

			bandInfo.cxMinChild = sizeMin.cx;
			bandInfo.cyMinChild = sizeMin.cy;

			wndReBar.SetBandInfo (uiBand, &bandInfo);
			wndReBar.MinimizeBand (uiBand);
		}
	}
	else
	{
		CFrameWnd* pParent = GetParentFrame ();
		if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
		{
			pParent->RecalcLayout ();
		}
	}

	AdjustLocations ();
	UpdateWindow ();
	Invalidate ();
}
//****************************************************************************************
void CBCGToolBar::OnBcgbarresCopyImage() 
{
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);

	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));
	ASSERT (pButton->GetImage () >= 0);

	CBCGToolBarImages* pImages = (pButton->m_bUserButton) ? 
			m_pUserImages : &m_Images;
	ASSERT (pImages != NULL);

	CWaitCursor wait;
	pImages->CopyImageToClipboard (pButton->GetImage ());
}
//****************************************************************************************
BOOL CBCGToolBar::OnSetDefaultButtonText (CBCGToolbarButton* pButton)
{
	ASSERT_VALID (pButton);

	if (pButton->m_nID == 0 || pButton->m_nID == (UINT) -1)
	{
		return FALSE;
	}

	CString strMessage;
	int iOffset;

	if (strMessage.LoadString (pButton->m_nID) &&
		(iOffset = strMessage.Find (_T('\n'))) != -1)
	{
		pButton->m_strText = strMessage.Mid (iOffset + 1);
		return TRUE;
	}

	return FALSE;
}
//****************************************************************************************
void CBCGToolBar::SetMenuSizes (SIZE sizeButton, SIZE sizeImage)
{
	ASSERT(sizeButton.cx > 0 && sizeButton.cy > 0);

	//-----------------------------------------------------------------
	// Button must be big enough to hold image + 3 pixels on each side:
	//-----------------------------------------------------------------
	ASSERT(sizeButton.cx >= sizeImage.cx + 6);
	ASSERT(sizeButton.cy >= sizeImage.cy + 6);

	m_sizeMenuButton = sizeButton;
	m_sizeMenuImage = sizeImage;

	m_MenuImages.SetSizes (m_sizeMenuButton, m_sizeMenuImage);
}
//****************************************************************************************
CSize CBCGToolBar::GetMenuImageSize ()
{
	if (m_sizeMenuImage.cx == -1)
	{
		return m_sizeImage;
	}
	else
	{
		return m_sizeMenuImage;
	}
}
//****************************************************************************************
CSize CBCGToolBar::GetMenuButtonSize ()
{
	if (m_sizeMenuButton.cx == -1)
	{
		return m_sizeButton;
	}
	else
	{
		return m_sizeMenuButton;
	}
}
//****************************************************************************************
BOOL CBCGToolBar::EnableContextMenuItems (CBCGToolbarButton* pButton, CMenu* pPopup)
{
	ASSERT_VALID (pButton);
	ASSERT_VALID (pPopup);

	if (!pButton->m_bImage || pButton->GetImage () < 0)
	{
		pPopup->EnableMenuItem (ID_BCGBARRES_COPY_IMAGE, MF_BYCOMMAND | MF_GRAYED);
	}

	if (pButton->m_nID == (UINT) -1 || pButton->m_nID == 0)
	{
		pPopup->EnableMenuItem (ID_BCGBARRES_TOOLBAR_RESET, MF_BYCOMMAND | MF_GRAYED);
	}

	if (pButton->m_bText)
	{
		if (pButton->m_bImage)
		{
			pPopup->CheckMenuItem (ID_BCGBARRES_TOOLBAR_IMAGE_AND_TEXT, MF_CHECKED  | MF_BYCOMMAND);
		}
		else
		{
			pPopup->CheckMenuItem (ID_BCGBARRES_TOOLBAR_TEXT, MF_CHECKED  | MF_BYCOMMAND);
		}
	}
	else
	{
		ASSERT (pButton->m_bImage);
		pPopup->CheckMenuItem (ID_BCGBARRES_TOOLBAR_IMAGE, MF_CHECKED  | MF_BYCOMMAND);
	}

	//---------------------------
	// Adjust "Start group" item:
	//---------------------------
	CBCGToolbarButton* pPrevButton = NULL;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pCurrButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pCurrButton);

		if (pCurrButton == pButton)
		{
			if (pPrevButton == NULL)	// First button
			{
				pPopup->EnableMenuItem (ID_BCGBARRES_TOOLBAR_START_GROUP, MF_BYCOMMAND | MF_GRAYED);
			}
			else if (pPrevButton->m_nStyle & TBBS_SEPARATOR)
			{
				pPopup->CheckMenuItem (ID_BCGBARRES_TOOLBAR_START_GROUP, MF_CHECKED  | MF_BYCOMMAND);
			}

			break;
		}

		pPrevButton = pCurrButton;
	}

	return TRUE;
}
//***************************************************************************************
void CBCGToolBar::OnChangeHot (int iHot)
{
	if (m_iHot == iHot && m_iHot >= 0)
	{
		iHot = -1;
	}

	m_iHot = iHot;

	CBCGToolbarMenuButton* pCurrPopupMenu = GetDroppedDownMenu ();
	if (pCurrPopupMenu == NULL && !CBCGToolBar::IsCustomizeMode ())
	{
		return;
	}

	if (iHot < 0)
	{
		if (pCurrPopupMenu != NULL && CBCGToolBar::IsCustomizeMode ())
		{
			pCurrPopupMenu->OnCancelMode ();
		}
		return;
	}

	CBCGToolbarMenuButton* pMenuButton =
		DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, GetButton (iHot));

	if (pMenuButton != pCurrPopupMenu)
	{
		if (pCurrPopupMenu != NULL)
		{
			pCurrPopupMenu->OnCancelMode ();
		}

		if (pMenuButton != NULL &&
			(!CBCGToolBar::IsCustomizeMode () || 
			!pMenuButton->IsKindOf (RUNTIME_CLASS (CBCGToolbarSystemMenuButton))))
		{
			pMenuButton->OnClick (this);
		}
	}
	else
	{
		if (CBCGToolBar::IsCustomizeMode () &&
			pCurrPopupMenu != NULL && pCurrPopupMenu->IsDroppedDown ())
		{
			pCurrPopupMenu->OnCancelMode ();
		}
	}

	//------------------------------------
	// Fixed by Sven Ritter (SpeedProject)
	//------------------------------------
	if (IsCustomizeMode () && m_iDragIndex < 0)
	{
		int nSelected = m_iHighlighted;
		m_iSelected = m_iHot;

		if (nSelected != -1)
		{
			InvalidateButton (nSelected);
		}

		CBCGToolbarButton* pSelButton = GetButton (m_iSelected);
		ASSERT (pSelButton != NULL);
		if (pSelButton->m_nStyle & TBBS_SEPARATOR)
		{
			m_iSelected = -1;
		}
		else
		{
			InvalidateButton (m_iSelected);
		}
	}
	// --- End ----

	if (m_iHot >= 0 && m_iHot != m_iHighlighted)
	{
		int iCurrHighlighted = m_iHighlighted;
		if (iCurrHighlighted >= 0)
		{
			InvalidateButton (iCurrHighlighted);
		}

		m_iHighlighted = m_iHot;

		InvalidateButton (m_iHighlighted);
		UpdateWindow ();
	}
}
//*****************************************************************************************
BOOL CBCGToolBar::PrevMenu ()
{
	int iHot;
	CBCGToolbarMenuButton* pCurrPopupMenu = GetDroppedDownMenu (&iHot);
	if (pCurrPopupMenu == NULL)
	{
		return FALSE;
	}

	int iTotalItems = GetCount ();
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
		if (pMenuButton != NULL && pMenuButton->IsDroppedDown ())
		{
			pMenuButton->m_pPopupMenu->SendMessage (WM_KEYDOWN, VK_HOME);
		}
	}

	return TRUE;
}
//*****************************************************************************************
BOOL CBCGToolBar::NextMenu ()
{
	int iHot;
	CBCGToolbarMenuButton* pCurrPopupMenu = GetDroppedDownMenu (&iHot);
	if (pCurrPopupMenu == NULL)
	{
		return FALSE;
	}

	int iTotalItems = GetCount ();
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
		if (pMenuButton != NULL && pMenuButton->IsDroppedDown ())
		{
			pMenuButton->m_pPopupMenu->SendMessage (WM_KEYDOWN, VK_HOME);
		}
	}

	return TRUE;
}
//*****************************************************************************************
BOOL CBCGToolBar::SetHot (CBCGToolbarButton *pMenuButton)
{
	if (pMenuButton == NULL)
	{
		m_iHot = -1;
		return TRUE;
	}

	int i = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		if (pMenuButton == pButton)
		{
			if (m_iHot != i)
			{
				OnChangeHot (i);
			}
			return TRUE;
		}
	}

	return FALSE;
}
//**************************************************************************************
BOOL CBCGToolBar::DropDownMenu (CBCGToolbarButton* pButton)
{
	ASSERT_VALID (pButton);

	CBCGToolbarMenuButton* pMenuButton =
		DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pButton);
	if (pMenuButton == NULL)
	{
		return FALSE;
	}

	if (!pMenuButton->OnClick (this))
	{
		return FALSE;
	}

	if (m_iHot < 0)
	{
		return FALSE;
	}
			
	//-----------------------
	// Select the first item:
	//-----------------------
	CBCGToolbarMenuButton* pPopupMenuButton =
		DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, GetButton (m_iHot));
	if (pPopupMenuButton != NULL && pPopupMenuButton->IsDroppedDown ())
	{
		pPopupMenuButton->m_pPopupMenu->SendMessage (WM_KEYDOWN, VK_HOME);
	}

	return TRUE;
}
//********************************************************************************************
CBCGToolbarMenuButton* CBCGToolBar::GetDroppedDownMenu (int* pIndex) const
{
	if (m_Buttons.IsEmpty ())
	{
		return NULL;
	}

	int iIndex = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; iIndex ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		CBCGToolbarMenuButton* pMenuButton =
			DYNAMIC_DOWNCAST (CBCGToolbarMenuButton, pButton);

		if (pMenuButton != NULL && pMenuButton->IsDroppedDown ())
		{
			if (pIndex != NULL)
			{
				*pIndex = iIndex;
			}

			return pMenuButton;
		}
	}

	if (pIndex != NULL)
	{
		*pIndex = -1;
	}

	return NULL;
}
//******************************************************************
void CBCGToolBar::Deactivate ()
{
	if (m_iHighlighted >= 0 && m_iHighlighted < m_Buttons.GetCount ())
	{
		int iButton = m_iHighlighted;
		m_iHighlighted = m_iHot = -1;

		InvalidateButton (iButton);
		UpdateWindow ();

		GetOwner()->SendMessage (WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
	}

	RestoreFocus ();
//	GetOwner ()->SetFocus ();
}
//*********************************************************************
BOOL CBCGToolBar::SaveParameters (LPCTSTR lpszProfileName)
{
	BOOL bResult = FALSE;
	ASSERT (lpszProfileName != NULL);

	CString strSection;
	strSection.Format (REG_PARAMS_FMT, lpszProfileName);

	CRegistry reg (FALSE, FALSE);
	if (reg.CreateKey (strSection))
	{
		bResult =	reg.Write (REG_ENTRY_TOOLTIPS, m_bShowTooltips) &&
					reg.Write (REG_ENTRY_KEYS, m_bShowShortcutKeys);
					reg.Write (REG_ENTRY_ANIMATION, (int) CBCGPopupMenu::GetAnimationType ());
	}

	return bResult;
}
//*****************************************************************************************
BOOL CBCGToolBar::LoadParameters (LPCTSTR lpszProfileName)
{
	BOOL bResult = FALSE;

	CString strSection;
	strSection.Format (REG_PARAMS_FMT, lpszProfileName);

	CRegistry reg (FALSE, TRUE);
	if (!reg.Open (strSection))
	{
		return FALSE;
	}

	int iAnimType;
	bResult =	reg.Read (REG_ENTRY_TOOLTIPS, m_bShowTooltips) &&
				reg.Read (REG_ENTRY_KEYS, m_bShowShortcutKeys);
				reg.Read (REG_ENTRY_ANIMATION, iAnimType);

	if (bResult)
	{
		CBCGPopupMenu::SetAnimationType ((CBCGPopupMenu::ANIMATION_TYPE) iAnimType);
	}

	return bResult;
}
//**********************************************************************************
void CBCGToolBar::OnSetFocus(CWnd* pOldWnd) 
{
	CControlBar::OnSetFocus(pOldWnd);

	if (pOldWnd != NULL &&
		DYNAMIC_DOWNCAST (CBCGToolBar, pOldWnd) == NULL &&
		DYNAMIC_DOWNCAST (CBCGToolBar, pOldWnd->GetParent ()) == NULL)
	{
		m_hwndLastFocus = pOldWnd->GetSafeHwnd ();
	}
}
//**********************************************************************************
void CBCGToolBar::RestoreFocus ()
{
	if (::IsWindow (m_hwndLastFocus))
	{
		::SetFocus (m_hwndLastFocus);
	}

	m_hwndLastFocus = NULL;
}
