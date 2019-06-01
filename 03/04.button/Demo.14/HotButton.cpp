// HotButton.cpp : implementation file
//

#include "stdafx.h"
#include "CButtonX.h"
#include "HotButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonX
// a standard text button with a hot red "X" at the right that highlights on mouse-over 
// and sends BN_XCLICKED instead
//

CHotButton::CHotButton()
{
	m_bHotAreaActive = FALSE;
	m_ToolTip.m_hWnd = NULL;
	m_bIsHot = TRUE;
	m_bShowBitmap = TRUE;
	m_iBitmap = 0;
	m_pAppImageList = NULL;
}

CHotButton::~CHotButton()
{
	if (m_pAppImageList)
		delete m_pAppImageList;
}


BEGIN_MESSAGE_MAP(CHotButton, CButton)
	//{{AFX_MSG_MAP(CHotButton)
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_CAPTURECHANGED()
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotButton message handlers

void CHotButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();

	ModifyStyle(0, BS_OWNERDRAW);
	// create the internal hot image list
	m_ImageList.Create(IDB_HOT_INTERNAL, 14, 1, RGB(255,0,255));
	IMAGEINFO	ImageInfo;
	m_ImageList.GetImageInfo(0, &ImageInfo);
	m_rectBMP = ImageInfo.rcImage;
	m_pCurImageList = &m_ImageList;
	UseBitmap(0);
}


void CHotButton::EnableHotSpot(BOOL bEnable /*= TRUE*/)
{
	BOOL	bWasEnabled = m_bIsHot;

	m_bIsHot = bEnable;

	if (bWasEnabled && !bEnable) {
		if (m_bHotAreaActive) {
			ReleaseCapture();
			Invalidate();
		}
	}
	else if (!bWasEnabled && bEnable)
		Invalidate();

	ActivateTooltip(m_bIsHot);
}


void CHotButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	UINT	uState = DFCS_BUTTONPUSH;
	int		iOffset = 0;

	// offset elements if depressed
	if (lpDIS->itemState & ODS_SELECTED) {
		iOffset = 1;
		uState |= DFCS_PUSHED;
	}

	// draw the frame border
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	pDC->DrawFrameControl(&lpDIS->rcItem, DFC_BUTTON, uState);

	// draw the icon
	if (m_bShowBitmap) {
		CRect	rect(lpDIS->rcItem);
		m_pCurImageList->DrawIndirect(pDC, (m_iBitmap * 2) + ((m_bHotAreaActive && m_bIsHot) ? 0 : 1),
														 CPoint(m_rectX.left + iOffset, m_rectX.top + iOffset), 
														 CSize(m_rectX.Width(), m_rectX.Height()), CPoint(rect.left, rect.top));
	}

	// draw the text
	CString sTitle;
	GetWindowText(sTitle);
	DWORD	style = GetStyle();
	DWORD	drawStyle;
	
	CRect	rectDraw(m_rectFocus);
	rectDraw.OffsetRect(iOffset, iOffset);
	rectDraw.DeflateRect(1,1,1,1);	// draw inside the focus rect

	if ((style & BS_LEFT) && (style & BS_RIGHT))
		drawStyle = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	else if (style & BS_LEFT)
		drawStyle = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
	else if (style & BS_RIGHT)
		drawStyle = DT_RIGHT | DT_VCENTER | DT_SINGLELINE;
	else
		drawStyle = DT_CENTER | DT_VCENTER | DT_SINGLELINE;

	pDC->DrawText(sTitle, rectDraw, drawStyle);

	// draw the focus rect
	if (lpDIS->itemState & ODS_FOCUS) {
		CRect rectFocus = (m_bHotAreaActive && m_bIsHot && m_bShowBitmap) ? m_rectHotX : m_rectFocus;
		if (m_bHotAreaActive && m_bIsHot && m_bShowBitmap)
			rectFocus.DeflateRect(0,4,2,4);
		rectFocus.OffsetRect(iOffset, iOffset);	// move if pressed
		pDC->DrawFocusRect(&rectFocus);
	}
}


// send BN_XCLICKED notification to parent if the button comes up 
// when the mouse is in the Hot X part of the button
//
BOOL CHotButton::PreTranslateMessage(MSG* pMsg) 
{
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);
	
	if (pMsg->message == WM_KEYDOWN) {
		// handle TAB and arrow keys
		BOOL	bShiftPressed = ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000);

		if (pMsg->wParam == VK_TAB) {
			if (!m_bIsHot || !m_bShowBitmap)
				::SetFocus(::GetNextDlgGroupItem(GetParent()->m_hWnd, m_hWnd, bShiftPressed));
			else if (bShiftPressed && m_bHotAreaActive) {
				m_bHotAreaActive = FALSE;
				Invalidate();
			}
			else if (!bShiftPressed && !m_bHotAreaActive) {
				m_bHotAreaActive = TRUE;
				Invalidate();
			}
			else
				::SetFocus(::GetNextDlgGroupItem(GetParent()->m_hWnd, m_hWnd, bShiftPressed && !m_bHotAreaActive));
			if (m_bHotAreaActive)
				SetCapture();
		}
		else if ((pMsg->wParam == VK_LEFT) || (pMsg->wParam == VK_UP)) {
			if (m_bIsHot && m_bShowBitmap && m_bHotAreaActive) {
				m_bHotAreaActive = FALSE;
				Invalidate();
			}
			else
				::SetFocus(::GetNextDlgGroupItem(GetParent()->m_hWnd, m_hWnd, TRUE));
			if (m_bHotAreaActive)
				SetCapture();
		}
		else if ((pMsg->wParam == VK_RIGHT) || (pMsg->wParam == VK_DOWN)) {
			if (m_bIsHot && m_bShowBitmap && !m_bHotAreaActive) {
				m_bHotAreaActive = TRUE;
				Invalidate();
			}
			else
				::SetFocus(::GetNextDlgGroupItem(GetParent()->m_hWnd, m_hWnd, FALSE));
			if (m_bHotAreaActive)
				SetCapture();
		}
	}
	else if (m_bIsHot) {		// handle mouse button
		if (pMsg->message == WM_LBUTTONUP) {
			CRect	rect = m_rectHotX;
			ClientToScreen(&rect);
			if (rect.PtInRect(pMsg->pt)) {
				::SendMessage(GetParent()->m_hWnd, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_HOT_CLICKED), (LPARAM)m_hWnd);
				SetState(FALSE);	// set state to FALSE so that calling base class does not generate a BN_CLICKED
			}
		}
		else if ((pMsg->message == WM_KEYUP) && (pMsg->wParam == VK_SPACE)) {
			if (m_bHotAreaActive) {
				::SendMessage(GetParent()->m_hWnd, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_HOT_CLICKED), (LPARAM)m_hWnd);
				SetState(FALSE);	// set state to FALSE so that calling base class does not generate a BN_CLICKED
			}
		}
	}
	return CButton::PreTranslateMessage(pMsg);
}
	

void CHotButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CButton::OnMouseMove(nFlags, point);

	if (!m_bIsHot)
		return;

	// don't do anything if the mouse enters with the left button pressed
	if (nFlags & MK_LBUTTON && m_bHotAreaActive == FALSE)
		return;

	CWnd* pWnd = GetActiveWindow();
	CWnd* pParent = GetOwner();

	if (m_rectHotX.PtInRect(point) && (GetCapture() != this) && (pWnd != NULL) && (pParent != NULL)) {
		if (!m_bHotAreaActive) {
			m_bHotAreaActive = TRUE;
			SetCapture();
			Invalidate();
		}
	}
	else {
		if (m_bHotAreaActive) {			// Redraw only if mouse moves out
			m_bHotAreaActive = FALSE;
			Invalidate();
		}
		ReleaseCapture();
	}
}

void CHotButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);

  if (m_bHotAreaActive == TRUE) {
    m_bHotAreaActive = FALSE;
		ReleaseCapture();
    Invalidate();
  }
	
}

void CHotButton::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	
	if (GetKeyState(VK_TAB) & 0x8000) { 	// focus from TAB
		m_bHotAreaActive = ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000);
		Invalidate();
	}
	else if ((GetKeyState(VK_LEFT) & 0x8000) || (GetKeyState(VK_UP) & 0x8000)) {	// focus from reverse arrow key
		m_bHotAreaActive = TRUE;
		Invalidate();
	}
	else if (m_bIsHot) {	// focus came from mouse or app SetFocus()
		POINT	pt;
		GetCursorPos(&pt);
		CRect	rect = m_rectHotX;
		ClientToScreen(&rect);
		if (rect.PtInRect(pt)) {
			m_bHotAreaActive = TRUE;
			SetCapture();
			Invalidate();
		}
	}
}

void CHotButton::OnCaptureChanged(CWnd *pWnd) 
{
	if (pWnd != this) {
		m_bHotAreaActive = FALSE;
		Invalidate();
	}
	
	CButton::OnCaptureChanged(pWnd);
}


void CHotButton::SetTooltipText(LPCSTR szText, BOOL bActivate)
{
	if (szText == NULL)
		return;

	// Initialize ToolTip
	InitToolTip();

	// If there is no tooltip tool defined then add it
	if (m_ToolTip.GetToolCount() == 0)
		m_ToolTip.AddTool(this, szText, m_rectHotX, 1);

	// Set text for tooltip
	m_ToolTip.UpdateTipText(szText, this, 1);
	m_ToolTip.Activate(bActivate);
}

void CHotButton::ActivateTooltip(BOOL bActivate)
{
	if (m_ToolTip.GetToolCount() == 0) 
		return;

	m_ToolTip.Activate(bActivate);
}

void CHotButton::InitToolTip()
{
	if (m_ToolTip.m_hWnd == NULL) {
		m_ToolTip.Create(this);
		m_ToolTip.Activate(FALSE);
	}
}

UINT CHotButton::OnGetDlgCode() 
{
	UINT	uiRet = CButton::OnGetDlgCode();
	return uiRet | DLGC_WANTTAB | DLGC_WANTARROWS;
}


void CHotButton::ShowBitmap(BOOL bShow /*=TRUE*/)
{
	m_bShowBitmap = bShow;

	if (bShow)
		UseBitmap(m_iBitmap);
	else {
		m_rectX.SetRectEmpty();
		m_rectHotX.SetRectEmpty();

		CRect	rectClient;
		GetClientRect(&rectClient);
		m_rectFocus = rectClient;
		m_rectFocus.DeflateRect(4, 4, 4, 4);

		m_bHotAreaActive = FALSE;
		m_bShowBitmap = FALSE;
	}

	if (GetCapture() == this)
		ReleaseCapture();
	Invalidate();
}


void CHotButton::UseInternalBitmap(int iBitmap)
{
	IMAGEINFO	ImageInfo;
	m_ImageList.GetImageInfo(0, &ImageInfo);
	m_rectBMP = ImageInfo.rcImage;
	m_pCurImageList = &m_ImageList;
	UseBitmap(iBitmap);
}


void CHotButton::UseAppBitmap(int iBitmap)
{
	IMAGEINFO	ImageInfo;
	ASSERT_VALID(m_pAppImageList);
	m_pAppImageList->GetImageInfo(0, &ImageInfo);
	m_rectBMP = ImageInfo.rcImage;
	m_pCurImageList = m_pAppImageList;
	UseBitmap(iBitmap);
}


void CHotButton::UseBitmap(int iBitmap)
{
	m_iBitmap = iBitmap;

	if (!m_bShowBitmap)
		return;

	// calculate where the "X" bitmap will be drawn
	CRect	rectClient;
	GetClientRect(&rectClient);

	#define BORDER_TOP_LEFT_PIX		1	// # frame border pixels on top/left
	#define BORDER_BOT_RIGHT_PIX	2	// # frame border pixels on bottom/right
	#define BORDER_VERT_PIX		(BORDER_TOP_LEFT_PIX+BORDER_BOT_RIGHT_PIX)	// vertical frame border pixels

	// must resize bitmap if can't fit in button
	if (rectClient.Height() < m_rectBMP.Height() + BORDER_VERT_PIX) {
		m_rectX.top = BORDER_TOP_LEFT_PIX;
		m_rectX.bottom = rectClient.Height() - BORDER_VERT_PIX;
		m_rectX.right = rectClient.right - BORDER_BOT_RIGHT_PIX - 1;
		int	xResized = (int)((m_rectX.Height() * ((float)m_rectBMP.Width() / m_rectBMP.Height())) + 0.5);
		m_rectX.left = m_rectX.right - xResized;
	}
	else {	// else fits, center full sized
		m_rectX.top = (rectClient.Height() - m_rectBMP.Height() - BORDER_VERT_PIX + 1) / 2;
		m_rectX.bottom = m_rectX.top + m_rectBMP.Height();
		m_rectX.right = rectClient.right - BORDER_BOT_RIGHT_PIX - 1;
		m_rectX.left = m_rectX.right - m_rectBMP.Width();
	}

	// determine the hot "X" area of the button
	#define GAP_WIDTH	6		// gap between the text part of the button and the hot X area
	m_rectHotX = rectClient;
	m_rectHotX.left = m_rectX.left - GAP_WIDTH / 2;

	// determine text drawing and focus rect area
	m_rectFocus = rectClient;
	m_rectFocus.DeflateRect(4, 4, 4 + m_rectX.Width() + (GAP_WIDTH / 2), 4);
	
	if (GetCapture() == this)
		ReleaseCapture();
	Invalidate();
}


void CHotButton::SetAppBmp(UINT nBitmapID, int cx, COLORREF crMask)
{
	if (m_pAppImageList)
		delete m_pAppImageList;
	m_pAppImageList = new CImageList;
	m_pAppImageList->Create(nBitmapID, cx, 1, crMask);
	IMAGEINFO	ImageInfo;
	m_pAppImageList->GetImageInfo(0, &ImageInfo);
	m_rectBMP = ImageInfo.rcImage;
	m_pCurImageList = m_pAppImageList;

	UseBitmap(0);
}
