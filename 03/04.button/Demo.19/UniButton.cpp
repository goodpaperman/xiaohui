// UniButton.cpp : implementation file
//

#include "stdafx.h"
#include "MySphereButton.h"
#include "UniButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUniButton

CUniButton::CUniButton()
{
	m_nColor = GetSysColor(COLOR_BTNFACE);
	m_sColor = m_nColor;
	m_hColor = m_nColor;
	m_dColor = m_nColor;
	m_nBorder = 1;
	m_lfEscapement = 0;
	m_pNormal = NULL;
	m_pSelected = NULL;
	m_pHover = NULL;
	m_pDisabled = NULL;
	m_hRgn = 0;
	m_bHover = false;
	m_bCapture = false;
	m_bMouseDown = false;
	m_bNeedBitmaps = true;
}

CUniButton::~CUniButton()
{
	delete m_pNormal;
	delete m_pSelected;
	delete m_pHover;
	delete m_pDisabled;
	DeleteObject(m_hRgn);
}

BEGIN_MESSAGE_MAP(CUniButton, CButton)
	//{{AFX_MSG_MAP(CUniButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUniButton message handlers

BOOL CUniButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID)
{
	// store region in member variable
	DeleteObject(m_hRgn);
	m_hRgn = CreateRectRgn(0, 0, 31, 31);
	CRect box(0, 0, 0, 0);
	if (m_hRgn != 0) 
		CombineRgn(m_hRgn, hRgn, 0, RGN_COPY);

	// make sure that region bounding rect is located in (0, 0)
	GetRgnBox(m_hRgn, &box);
	OffsetRgn(m_hRgn, -box.left, -box.top);
	GetRgnBox(m_hRgn, &box);

	// update position of region center for caption output
	m_CenterPoint = CPoint(box.left + box.Width() /2 , box.top + box.Height() /2);
	box.OffsetRect(point);

	return CButton::Create(lpszCaption, dwStyle, box, pParentWnd, nID);
}

BOOL CUniButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID, COLORREF color)
{
	m_sColor = color;
	m_hColor = color;

	// call another constructor
	return Create(lpszCaption, dwStyle, point, hRgn, pParentWnd, nID);
}

BOOL CUniButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID, UINT nBorder, LONG lfEscapement, COLORREF nColor, COLORREF sColor, COLORREF hColor, COLORREF dColor)
{
	m_lfEscapement = lfEscapement;
	return Create(lpszCaption, dwStyle, point, hRgn, pParentWnd, nID, nBorder, nColor, sColor, hColor, dColor);
}

BOOL CUniButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID, UINT nBorder, COLORREF nColor, COLORREF sColor, COLORREF hColor, COLORREF dColor)
{
	// change default colors
	m_nBorder = nBorder;
	m_nColor = nColor;
	m_sColor = sColor;
	m_hColor = hColor;
	m_dColor = dColor;

	// call another constructor
	return Create(lpszCaption, dwStyle, point, hRgn, pParentWnd, nID);
}

void CUniButton::PreSubclassWindow() 
{
	// change window style to allow owner draw
	ModifyStyle(0, BS_OWNERDRAW | BS_PUSHBUTTON);	
	CButton::PreSubclassWindow();
}

int CUniButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	// assign new region to a window
	m_bNeedBitmaps = true;
	SetWindowRgn(m_hRgn, true);

	return 0;
}

void CUniButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// record that mouse is down
	m_bMouseDown = true;
	if (!m_bCapture) {
		SetCapture();
		m_bCapture = true;
	}
	CButton::OnLButtonDown(nFlags, point);
}

void CUniButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// record that mouse is released
	CButton::OnLButtonUp(nFlags, point);

	m_bMouseDown = false;	
	if (m_bCapture) {
		ReleaseCapture();
		m_bCapture = false;
	}
	CheckHover(point);
}

void CUniButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Test if mouse is above the button.
	if (!m_bMouseDown)
		CheckHover(point);

	CButton::OnMouseMove(nFlags, point);
}

void CUniButton::CheckHover(CPoint point)
{
    if (HitTest(point)) {
        if (!m_bCapture) {
            SetCapture();
            m_bCapture = true;
        }
        if (!m_bHover) {
            m_bHover = true;
            RedrawWindow();
        }
    }
    else {
        if (m_bCapture) {
            ReleaseCapture();
            m_bCapture = false;
        }
        m_bHover = false;
        RedrawWindow();
    }
}

LRESULT CUniButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// I have noticed that default windows buttons can be clicked very quickly.
	// Double or single click both result in a button being pushed down.
	// For owner drawn buttons this is not the case. Double click does
	// not push button down. Here is a solution for the problem:
	// double click message is substituted for single click.

	if (message == WM_LBUTTONDBLCLK)
		message = WM_LBUTTONDOWN;
	
	return CButton::DefWindowProc(message, wParam, lParam);
}

BOOL CUniButton::HitTest(CPoint point)
{
	BOOL result = false;

	// Obtain handle to window region.
	HRGN hRgn = CreateRectRgn(0, 0, 0, 0);
	GetWindowRgn(hRgn);
	CRect rgnRect;
	GetRgnBox(hRgn, &rgnRect);

	// First check if point is in region bounding rect.
	// Then check if point is in the region in adition to being in the bouding rect.
	result = PtInRect(&rgnRect, point) && PtInRegion(hRgn, point.x, point.y);

	// Clean up and exit.
	DeleteObject(hRgn);
	return result;
}

BOOL CUniButton::OnEraseBkgnd(CDC* pDC) 
{
	// do not erase background
	return 1;
}

//////////////////////// DRAWING ROUTINES ////////////////////////////

void CUniButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// prepare DC
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct -> hDC);
	CRect rect;
	GetClientRect(rect);

	// prepare bitmaps they need to be prepared
	if (m_bNeedBitmaps)
		PrepareStateBitmaps(pDC, &rect);

	// draw button to the screen
	DrawButton(pDC, &rect, lpDrawItemStruct -> itemState);
}

void CUniButton::PrepareStateBitmaps(CDC * pDC, CRect * pRect)
{
	// prepare memory DC
	CDC * pMemDC;
	pMemDC = new CDC;
	pMemDC -> CreateCompatibleDC(pDC);

	// prepare bitmaps for all button states and for the mask
	PrepareNormalState(pDC, pMemDC, pRect);
	PrepareSelectedState(pDC, pMemDC, pRect);
	PrepareHoverState(pDC, pMemDC, pRect);
	PrepareDisabledState(pDC, pMemDC, pRect);

	// clean up
	delete pMemDC; 
	m_bNeedBitmaps = false;
}


void CUniButton::PrepareNormalState(CDC * pDC, CDC * pMemDC, CRect * pRect)
{
	// prepare MYBS_NORMAL state bitmap
	delete m_pNormal;
	m_pNormal = new CBitmap;
	PaintRgn(pDC, pMemDC, m_pNormal, m_nColor, pRect, true, false);
}

void CUniButton::PrepareSelectedState(CDC * pDC, CDC * pMemDC, CRect * pRect)
{
	// prepare MYBS_SELECTED state bitmap
	delete m_pSelected;
	m_pSelected = new CBitmap;
	PaintRgn(pDC, pMemDC, m_pSelected, m_sColor, pRect, true, true);
}

void CUniButton::PrepareHoverState(CDC * pDC, CDC * pMemDC, CRect * pRect)
{
	// prepare MYBS_HOVER state bitmap
	delete m_pHover;
	m_pHover = new CBitmap;
	PaintRgn(pDC, pMemDC, m_pHover, m_hColor, pRect, true, false);
}

void CUniButton::PrepareDisabledState(CDC * pDC, CDC * pMemDC, CRect * pRect)
{
	// prepare MYBS_DISABLED state bitmap
	delete m_pDisabled;
	m_pDisabled = new CBitmap;
	PaintRgn(pDC, pMemDC, m_pDisabled, m_dColor, pRect, false, false);
}

void CUniButton::PaintRgn(CDC * pDC, CDC * pMemDC, CBitmap * pBitmap, COLORREF color, CRect * pRect, BOOL bEnabled, BOOL bSunken)
{
	// create bitmap
	pBitmap -> CreateCompatibleBitmap(pDC, pRect -> Width(), pRect -> Height());
	CBitmap * pOldBitmap = pMemDC -> SelectObject(pBitmap); 

	// prepare region
	HRGN hRgn = CreateRectRgn(0, 0, 0, 0);
	GetWindowRgn(hRgn);

	// fill rect a with transparent color and fill rgn
	HBRUSH hBrush = CreateSolidBrush(color);
	pMemDC -> FillSolidRect(pRect, RGB(0, 0, 0));
	FillRgn(pMemDC -> GetSafeHdc(), hRgn, hBrush);
	DeleteObject(hBrush);

	// draw 3D border and text
	DrawButtonCaption(pMemDC -> GetSafeHdc(), pRect, bEnabled, bSunken);
	FrameRgn3D(pMemDC -> GetSafeHdc(), hRgn, bSunken);

	// clean up
	DeleteObject(hRgn);
	pMemDC -> SelectObject(pOldBitmap); 
}

void CUniButton::DrawButtonCaption(HDC hDC, CRect * pRect, BOOL bEnabled, BOOL bSunken) 
{
	// select parent font
	int nOldMode = SetBkMode(hDC, TRANSPARENT);
	CString text;
	GetWindowText(text);
	LOGFONT lf;
	GetParent() -> GetFont() -> GetLogFont(&lf);
	HFONT hFont = CreateFontIndirect(&lf);
	HFONT hOldFont = (HFONT) SelectObject(hDC, hFont);

	// determine point where to output text
	TEXTMETRIC tm;
	GetTextMetrics(hDC, &tm);
	CPoint p = CPoint(m_CenterPoint.x, m_CenterPoint.y + tm.tmHeight/ 2); 
	if (bSunken) 
		p.Offset(m_nBorder, m_nBorder); 
		
	// draw button caption depending upon button state
	if (bEnabled) {
		SetTextColor(hDC, GetSysColor(COLOR_BTNTEXT));
		SetTextAlign(hDC, TA_CENTER | TA_BOTTOM);
		TextOut(hDC, p.x, p.y, text, text.GetLength());
	}
	else {
		SetTextColor(hDC, GetSysColor(COLOR_3DHILIGHT));
		TextOut(hDC, p.x + 1, p.y + 1, text, text.GetLength());
		SetTextColor(hDC, GetSysColor(COLOR_3DSHADOW));
		TextOut(hDC, p.x, p.y, text, text.GetLength());
	}

	SelectObject(hDC, hOldFont);
	DeleteObject(hFont);
	SetBkMode(hDC, nOldMode);
}

void CUniButton::FrameRgn3D(HDC hDC, const HRGN hRgn, BOOL bSunken)
{
	// we need two differenr regions to keep base region and border region
	HBRUSH hBrush;
	HRGN hBaseRgn = CreateRectRgn(0, 0, 0, 0);

	COLORREF ltOuter, ltInner, rbOuter, rbInner;	// colors of inner and outer shadow for top-left and right-bottom corners

	// decide on color scheme
	if (!bSunken) {
		ltOuter = GetSysColor(COLOR_3DLIGHT);
		ltInner = GetSysColor(COLOR_3DHILIGHT);
		rbOuter = GetSysColor(COLOR_3DDKSHADOW);
		rbInner = GetSysColor(COLOR_3DSHADOW);
	}
	else {
		rbInner = GetSysColor(COLOR_3DLIGHT);
		rbOuter = GetSysColor(COLOR_3DHILIGHT);
		ltInner = GetSysColor(COLOR_3DDKSHADOW);
		ltOuter = GetSysColor(COLOR_3DSHADOW);
	}

	// offset highlight and shadow regions
	// substract them from the base region 
	switch (m_nBorder)
	{
	case 2:
		CombineRgn(hBaseRgn, hRgn, 0, RGN_COPY);
		OffsetRgn(hBaseRgn, 2, 2);
		CombineRgn(hBaseRgn, hRgn, hBaseRgn, RGN_DIFF);
		hBrush = CreateSolidBrush(ltInner);
		FillRgn(hDC, hBaseRgn, hBrush);
		DeleteObject(hBrush);

		CombineRgn(hBaseRgn, hRgn, 0, RGN_COPY);
		OffsetRgn(hBaseRgn, -2, -2);
		CombineRgn(hBaseRgn, hRgn, hBaseRgn, RGN_DIFF);
		hBrush = CreateSolidBrush(rbInner);
		FillRgn(hDC, hBaseRgn, hBrush);
		DeleteObject(hBrush);

		CombineRgn(hBaseRgn, hRgn, 0, RGN_COPY);
		OffsetRgn(hBaseRgn, 1, 1);
		CombineRgn(hBaseRgn, hRgn, hBaseRgn, RGN_DIFF);
		hBrush = CreateSolidBrush(ltOuter);
		FillRgn(hDC, hBaseRgn, hBrush);
		DeleteObject(hBrush);

		CombineRgn(hBaseRgn, hRgn, 0, RGN_COPY);
		OffsetRgn(hBaseRgn, -1, -1);
		CombineRgn(hBaseRgn, hRgn, hBaseRgn, RGN_DIFF);
		hBrush = CreateSolidBrush(rbOuter);
		FillRgn(hDC, hBaseRgn, hBrush);
		DeleteObject(hBrush);
		break;
	default:
		CombineRgn(hBaseRgn, hRgn, 0, RGN_COPY);
		OffsetRgn(hBaseRgn, 1, 1);
		CombineRgn(hBaseRgn, hRgn, hBaseRgn, RGN_DIFF);
		hBrush = CreateSolidBrush(ltInner);
		FillRgn(hDC, hBaseRgn, hBrush);
		DeleteObject(hBrush);

		CombineRgn(hBaseRgn, hRgn, 0, RGN_COPY);
		OffsetRgn(hBaseRgn, -1, -1);
		CombineRgn(hBaseRgn, hRgn, hBaseRgn, RGN_DIFF);
		hBrush = CreateSolidBrush(rbOuter);
		FillRgn(hDC, hBaseRgn, hBrush);
		DeleteObject(hBrush);
		break;
	}
	
	// clean up regions
	DeleteObject(hBaseRgn);
}

void CUniButton::DrawButton(CDC * pDC, CRect * pRect, UINT state)
{
	// create memory DC
	CDC * pMemDC = new CDC;
	pMemDC -> CreateCompatibleDC(pDC);
	CBitmap * pOldBitmap;

	// get region
	HRGN hRgn = CreateRectRgn(0, 0, 0, 0);
	GetWindowRgn(hRgn);

	// select bitmap to paint depending upon button state
	if (state & ODS_DISABLED)
		pOldBitmap = pMemDC -> SelectObject(m_pDisabled);
	else {
		if (state & ODS_SELECTED)
			pOldBitmap = pMemDC -> SelectObject(m_pSelected);
		else {
			if (m_bHover)
				pOldBitmap = pMemDC -> SelectObject(m_pHover);
			else 
				pOldBitmap = pMemDC -> SelectObject(m_pNormal);
		}	
	}

	// paint using region for clipping
	::SelectClipRgn(pDC -> GetSafeHdc(), hRgn);
	pDC -> BitBlt(0, 0, pRect -> Width(), pRect -> Height(), pMemDC, 0, 0, SRCCOPY);
	::SelectClipRgn(pDC -> GetSafeHdc(), NULL);

	// clean up
	DeleteObject(hRgn);
	pMemDC -> SelectObject(pOldBitmap);
	delete pMemDC;
}

void CUniButton::RgnPixelWork(CDC * pDC, CRgn * pRgn)
{
	// get size of data composing region
	int size = pRgn -> GetRegionData(NULL, 0);
	HANDLE hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, size);
	RGNDATA * pData = (RGNDATA *)GlobalLock(hData);

	// retrieve region data
	int res = pRgn -> GetRegionData(pData, size);
	RECT * pRect = (RECT *) pData -> Buffer;

	// now we know how region is represented and we are able to manipulate it as we like
	for (DWORD i = 0; i < pData -> rdh.nCount; i++) {
		RECT rect = *(pRect + i);
		for (int x = rect.left; x < rect.right; x++)
			for (int y = rect.top; y < rect.bottom; y++) {
				// use SetPixel(x, y, color) to do pixel work
			}
	}

	// free region data
	GlobalUnlock(hData);
	GlobalFree(hData);
}
