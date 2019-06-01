// WindowTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"       // main symbols
#include "WindowTabCtrl.h"
#include "ViewManager.h"
#include "PopupMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CX_BORDER  1
#define CY_BORDER  1

/////////////////////////////////////////////////////////////////////////////
// CWindowTabCtrl

CWindowTabCtrl::CWindowTabCtrl() : m_bDisplayIcons(TRUE)
{
	m_crSelColor    = RGB(0,  0, 255);
	m_crUnselColor  = RGB(50, 50, 50);
	m_rcDocModified = RGB(255, 0, 0);
}

CWindowTabCtrl::~CWindowTabCtrl()
{
	m_SelFont.DeleteObject();
	m_UnselFont.DeleteObject();
}


BEGIN_MESSAGE_MAP(CWindowTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CWindowTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowTabCtrl message handlers

void CWindowTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR->hwndFrom == NULL)
		return;                    // just to avoid level 4 compilation warning

	int idx = GetCurSel();

	TCITEM tci;
	tci.mask = TCIF_PARAM;
	GetItem(idx, &tci);
	CView* pView = reinterpret_cast<CView*>(tci.lParam);
	static_cast<CMDIFrameWnd*>(AfxGetMainWnd())->MDIActivate(pView->GetParent());
	*pResult = 0;
}

void CWindowTabCtrl::SetIconDisplay(BOOL bDisplayIt)
{
	m_bDisplayIcons = bDisplayIt;
}

int CWindowTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
	{
		TRACE0(_T("OnCreate function call failed!"));
		return -1;
	}
	ModifyStyle(0, TCS_OWNERDRAWFIXED);
	
	HFONT hFont  = reinterpret_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
	CFont* pFont = CFont::FromHandle(hFont);
	SetFont(pFont);
	
	return 0;
}

void CWindowTabCtrl::PreSubclassWindow() 
{
	CTabCtrl::PreSubclassWindow();
	ModifyStyle(0, TCS_OWNERDRAWFIXED); //TODO must go!
}


void CWindowTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{	
	CRect rcTab   =  CRect(&(lpDrawItemStruct->rcItem));
	int nTabIndex = lpDrawItemStruct->itemID;
	if (nTabIndex < 0)
		return;
	
	BOOL bSelected = (nTabIndex == GetCurSel());
	
	TCHAR szLabel[_MAX_PATH];
	TCITEM tci;
	tci.mask       = TCIF_TEXT | TCIF_IMAGE | TCIF_PARAM;
	tci.pszText    = szLabel;     
	tci.cchTextMax = _MAX_PATH - 1;    	
	if (!GetItem(nTabIndex, &tci)) 
		return;
	
	CDC dc;
	if (!dc.Attach(lpDrawItemStruct->hDC)) 
		return;
	
	DWORD dwStyle = GetStyle();
    rcTab.NormalizeRect();
	if ((dwStyle & TCS_BOTTOM) == 0)
	{
		rcTab.DeflateRect(CX_BORDER, CY_BORDER);
		rcTab.top += ::GetSystemMetrics(SM_CYEDGE);
	}
	
	dc.SetBkMode(TRANSPARENT);
	dc.FillSolidRect(rcTab, ::GetSysColor(COLOR_BTNFACE));
	
	CView* pView    = reinterpret_cast<CView*>(tci.lParam);
	CDocument* pDoc = pView->GetDocument();

	// Draw image
	if (m_bDisplayIcons)
	{
		CImageList* pImageList = GetImageList();
		CMDIChildWnd* pViewFrame = static_cast<CMDIChildWnd*>(pView->GetParent());
        HICON hIcon = reinterpret_cast<HICON>(GetClassLong(pViewFrame->m_hWnd, GCL_HICONSM));
		pImageList->Replace(nTabIndex, hIcon);

		if (pImageList && tci.iImage >= 0) 
		{
			rcTab.left += dc.GetTextExtent(_T(" ")).cx;		// Set a little margin
			
			// Get the height of image 
			IMAGEINFO info;
			pImageList->GetImageInfo(tci.iImage, &info);
			CRect ImageRect(info.rcImage);
			int nYpos = rcTab.top;
			
			pImageList->Draw(&dc, tci.iImage, CPoint(rcTab.left, nYpos), ILD_TRANSPARENT);
			rcTab.left += ImageRect.Width();
		}
	}
	
	if (bSelected) 
	{
		if (pDoc->IsModified())
			dc.SetTextColor(m_rcDocModified);
		else
			dc.SetTextColor(m_crSelColor);
		dc.SelectObject(&m_SelFont);
		rcTab.top -= ::GetSystemMetrics(SM_CYEDGE);
	} 
	else 
	{
		if (pDoc->IsModified())
			dc.SetTextColor(m_rcDocModified);
		else
			dc.SetTextColor(m_crUnselColor);
		dc.SelectObject(&m_UnselFont);
	}
	
	dc.DrawText(szLabel, rcTab, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	dc.Detach();
}


/////////////////////////////////////////////////////////////////////////////
// CWindowTabCtrl operations

void CWindowTabCtrl::SetColors(COLORREF bSelColor, COLORREF bUnselColor, 
							   COLORREF rcDocModified)
{
	m_crSelColor    = bSelColor;
	m_crUnselColor  = bUnselColor;
	m_rcDocModified = rcDocModified;
	Invalidate();
}

void CWindowTabCtrl::SetFonts(CFont* pSelFont, CFont* pUnselFont)
{
	ASSERT(pSelFont && pUnselFont);

	LOGFONT lFont;
	int nSelHeight, nUnselHeight;

	m_SelFont.DeleteObject();
	m_UnselFont.DeleteObject();

	pSelFont->GetLogFont(&lFont);
	m_SelFont.CreateFontIndirect(&lFont);
	nSelHeight = lFont.lfHeight;

	pUnselFont->GetLogFont(&lFont);
	m_UnselFont.CreateFontIndirect(&lFont);
	nUnselHeight = lFont.lfHeight;

	SetFont((nSelHeight > nUnselHeight)? &m_SelFont : &m_UnselFont);
}


void CWindowTabCtrl::SetFonts(int nSelWeight,   BOOL bSelItalic,   BOOL bSelUnderline,
						  int nUnselWeight, BOOL bUnselItalic, BOOL bUnselUnderline)
{
	// Free any memory currently used by the fonts.
	m_SelFont.DeleteObject();
	m_UnselFont.DeleteObject();

	// Get the current font
	LOGFONT lFont;
	CFont *pFont = GetFont();
	if (pFont)
		pFont->GetLogFont(&lFont);
	else 
	{
		NONCLIENTMETRICS ncm;
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 
			sizeof(NONCLIENTMETRICS), &ncm, 0));
		lFont = ncm.lfMessageFont; 
	}

	// Create the "Selected" font
	lFont.lfWeight    = static_cast<LONG>(nSelWeight);
	lFont.lfItalic    = static_cast<BYTE>(bSelItalic);
	lFont.lfUnderline = static_cast<BYTE>(bSelUnderline);
	m_SelFont.CreateFontIndirect(&lFont);

	// Create the "Unselected" font
	lFont.lfWeight    = static_cast<LONG>(nUnselWeight);
	lFont.lfItalic    = static_cast<BYTE>(bUnselItalic);
	lFont.lfUnderline = static_cast<BYTE>(bUnselUnderline);
	m_UnselFont.CreateFontIndirect(&lFont);

	SetFont((nSelWeight > nUnselWeight) ? &m_SelFont : &m_UnselFont);
}

void CWindowTabCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// Select the tab which is clicked and activate the attached view
    TCHITTESTINFO   hti;
    
    hti.pt = CPoint(GetMessagePos());
    ScreenToClient(&hti.pt);
    int iTab = HitTest(&hti);
    if (iTab < 0)
        return;
	SetCurSel(iTab);                    // Select it

	TCITEM tci;
	tci.mask = TCIF_PARAM;
	GetItem(iTab, &tci);
	CView* pView = reinterpret_cast<CView*>(tci.lParam);
	static_cast<CMDIFrameWnd*>(AfxGetMainWnd())->MDIActivate(pView->GetParent());

	// Now, process the popup menu for the tab control
	POINT  ptScreen = point;
	// Convert the mouse point to screen coordinates since that is what is used by
	// the TrackPopupMenu() function.
	ClientToScreen(&ptScreen);
	CPopupMenu cMenu;
	cMenu.CreatePopupMenu();
	
	cMenu.AppendMenu(MF_STRING, ID_FILE_CLOSE, _T("&Close"));
	cMenu.AppendMenu(MF_STRING, ID_FILE_SAVE, _T("&Save\tCtrl+S"));
	cMenu.AppendMenu(MF_STRING, ID_FILE_SAVE_AS, _T("Save &As..."));
	cMenu.AppendMenu(MF_SEPARATOR);
	cMenu.AppendMenu(MF_STRING, ID_FILE_PRINT, _T("&Print\tCtrl+P"));
	cMenu.AppendMenu(MF_STRING, ID_FILE_PRINT_PREVIEW, _T("Print Pre&view"));
	
	cMenu.LoadToolBarResource(IDR_TABVIEW_MENU);
	cMenu.RemapMenu(&cMenu);
	cMenu.EnableMenuItems(&cMenu, AfxGetMainWnd());
	
    // insert a separator item at the top
    cMenu.InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR, 0, _T(""));

    // insert title item
    // note: item is not selectable (disabled) but not grayed
    cMenu.InsertMenu(0, MF_BYPOSITION | MF_STRING | MF_DISABLED, 0, _T("Active View Tab"));

    ::SetMenuDefaultItem(cMenu.m_hMenu, 0, TRUE);

	cMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptScreen.x, ptScreen.y, AfxGetMainWnd());
	
	cMenu.DestroyMenu();
	
	CTabCtrl::OnRButtonDown(nFlags, point);
}
