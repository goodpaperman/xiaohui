/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/19/98 11:29:37 AM
  Comments: SheetsWnd.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "SheetsWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEFAULTFORMATDRAWTEXT DT_CENTER | DT_VCENTER | DT_SINGLELINE

/////////////////////////////////////////////////////////////////////////////
// CSheetsWnd

#define unknown _T("Sheet")
#define LRB 6
#define FONTNAME _T("Arial")


// Function name	: CSheetsWnd::CSheetsWnd
// Description	    : Default constructor of this object
// Return type		: 
CSheetsWnd::CSheetsWnd()
{
	m_wndProcParent = NULL;
	m_DrawRect.SetRectEmpty();
	m_rectMoveBar.SetRectEmpty();
	m_nHorzScroll = 0;
	m_nMaxHorzScroll = 0;
	m_pRollPoint = NULL;
	m_nDisplacement = 0;
}

// Function name	: CSheetsWnd::~CSheetsWnd
// Description	    : Destructor
// Return type		: 
CSheetsWnd::~CSheetsWnd()
{
}

BEGIN_MESSAGE_MAP(CSheetsWnd, CWnd)
	//{{AFX_MSG_MAP(CSheetsWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSheetsWnd message handlers

// Function name	: WindowProcParent
// Description	    : 
// Return type		: LRESULT CALLBACK 
// Argument         :  HWND hwnd
// Argument         : UINT uMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CALLBACK WindowProcParent( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch (uMsg)
	{
	case WM_DESTROY:
			{
				CSheetsWnd::RestoreWndProc(hwnd);
				break;
			}
		case WM_WINDOWPOSCHANGED:
		case WM_SIZE:
			{
				CSheetsWnd::ResizeStatical(hwnd);
				return NULL;
			}
		case WM_PARENTNOTIFY:
			{
				if (LOWORD(wParam) == WM_CREATE)
					CSheetsWnd::GetWndSheet(hwnd)->Invalidate();
				break;
			}

	}
	return CallWindowProc(CSheetsWnd::GetWndSheet(hwnd)->GetWindowProc(), hwnd, uMsg, wParam, lParam );
}

// Function name	: CSheetsWnd::GetRect
// Description	    : Return the wished rect of this object
// Return type		: CRect 
// Argument         : CWnd* pWndParent
CRect CSheetsWnd::GetRect(CWnd* pWndParent)
{
	CRect rect; pWndParent->GetClientRect(rect);
	rect.top = rect.bottom - GetSystemMetrics(SM_CYVTHUMB);
	return rect;
}

// Function name	: CSheetsWnd::GetRect
// Description	    : Return the wished rect of this object
// Return type		: CRect 
// Argument         : HWND hWndParent
CRect CSheetsWnd::GetRect(HWND hWndParent)
{
	return GetRect(CWnd::FromHandle(hWndParent));
}

// Function name	: CSheetsWnd::Attach
// Description	    : Create object as child of pWndParent with rgbBackground
// Return type		: BOOL 
// Argument         : CWnd * pWndParent
// Argument         : COLORREF rgbBackground
BOOL CSheetsWnd::Attach(CWnd * pWndParent, COLORREF rgbBackground)
{
	ASSERT (pWndParent && IsWindow(pWndParent->m_hWnd));
	CRect rect = GetRect(pWndParent);
	m_brBackground.CreateSolidBrush(rgbBackground);
	ASSERT(pWndParent->GetDlgItem(IDTHIS) == NULL);
	pWndParent->ModifyStyle(0, WS_CLIPCHILDREN);
	BOOL bResult = Create(AfxRegisterWndClass(0,AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)m_brBackground,0), _T(""), WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, rect, pWndParent, IDTHIS);
	if (bResult)
		// Subclass window procedure of parent object for receive some message. See WindowProcParent for detail
		m_wndProcParent = (WNDPROC)SetWindowLong(pWndParent->m_hWnd, GWL_WNDPROC, (long)WindowProcParent);
	return bResult;
}

// Function name	: CSheetsWnd::GetWndSheet
// Description	    : Return pointer to sheet window
// Return type		: CSheetsWnd* 
// Argument         : HWND hWndParent
CSheetsWnd* CSheetsWnd::GetWndSheet(HWND hWndParent)
{
	return (CSheetsWnd*)CWnd::FromHandle(::GetDlgItem(hWndParent, IDTHIS));
}

// Function name	: CSheetsWnd::RestoreWndProc
// Description	    : When parent of this object become to be destroyed then restore window procedure
// Return type		: void 
// Argument         : HWND hWndParent
void CSheetsWnd::RestoreWndProc(HWND hWndParent)
{
	if (IsWindow(hWndParent))
	{
		long curent = (long)((CSheetsWnd*)CWnd::FromHandle(::GetDlgItem(hWndParent, IDTHIS)))->m_wndProcParent;
		if (GetWindowLong(hWndParent, GWL_WNDPROC) != curent)
			SetWindowLong(hWndParent, GWL_WNDPROC, curent);
	}
}

// Function name	: CSheetsWnd::Resize
// Description	    : 
// Return type		: void 
// Argument         : HWND hWndParent
void CSheetsWnd::Resize(HWND hWndParent)
{
	CRect rect = GetRect(hWndParent);
	MoveWindow(rect);
	rect.bottom = rect.top; rect.top = 0;
	CWnd* pChild = GetFirstView();
	while (pChild)
	{
		pChild->MoveWindow(rect);
		pChild = GetNextView();
	}
	GetClientRect(rect);
	m_DrawRect.right = rect.right;		
}

// Function name	: CSheetsWnd::ResizeStatical
// Description	    : All childs of parent, without this must be resized
// Return type		: void 
// Argument         : HWND hWndParent
void CSheetsWnd::ResizeStatical(HWND hWndParent)
{
	if (CSheetsWnd* pThis = GetWndSheet(hWndParent))
		pThis->Resize(hWndParent);
}

// Function name	: CSheetsWnd::GetFirstView
// Description	    : Get first view from object parent
// Return type		: CWnd* 
CWnd* CSheetsWnd::GetFirstView()
{
	m_pViewFind = GetParent()->GetWindow(GW_CHILD);
	while (m_pViewFind && m_pViewFind->m_hWnd == m_hWnd)
		m_pViewFind = m_pViewFind->GetWindow(GW_HWNDNEXT);
	return m_pViewFind;
}

// Function name	: CSheetsWnd::GetNextView
// Description	    : Get next view from object parent
// Return type		: CWnd* 
CWnd* CSheetsWnd::GetNextView()
{
	if (m_pViewFind)
	{
		m_pViewFind = m_pViewFind->GetWindow(GW_HWNDNEXT);
		while (m_pViewFind && m_pViewFind->m_hWnd == m_hWnd)
			m_pViewFind = m_pViewFind->GetWindow(GW_HWNDNEXT);
		return m_pViewFind;
	}
	return NULL;
}

// Function name	: CSheetsWnd::GetViewTitle
// Description	    : Return the default window title
// Return type		: CString 
// Argument         : CWnd * pView
CString CSheetsWnd::GetViewTitle(CWnd * pView)
{
	CString result; pView->GetWindowText(result);
	if (result.IsEmpty())
		result = unknown;
	return result;
}

// Function name	: CSheetsWnd::GetActiveView
// Description	    : Return the first active view
// Return type		: CWnd* 
CWnd* CSheetsWnd::GetActiveView()
{
	CWnd* pWnd = GetFirstView();
	while (pWnd)
		if (pWnd->IsWindowVisible())
			return pWnd;
		else
			pWnd = GetNextView();

	return pWnd;
}

// Function name	: CSheetsWnd::SetActiveView
// Description	    : Sets the active view. Call EnsureVisible if you want to be enure that page is visible
// Return type		: void 
// Argument         : CWnd* pView
void CSheetsWnd::SetActiveView(CWnd* pView)
{
	CWnd* pOldActiveView = GetActiveView(), *pParent = GetParent();
	if (pView)
		if (pView != pOldActiveView)
		{
			pParent->SendMessage(GetMessagePageChanging(), (WPARAM)pOldActiveView, (LPARAM)pView);
			if (!pOldActiveView || (pOldActiveView && pOldActiveView->m_hWnd != pView->m_hWnd))
			{
				pView->SetWindowPos(0,0,0,0,0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW );
				if (pOldActiveView)
					pOldActiveView->SetWindowPos(0,0,0,0,0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW | SWP_NOREDRAW);
				Invalidate();
				pParent->SendMessage(GetMessagePageChanged(), (WPARAM)pView, 0);
			}
		}
}

// Function name	: CSheetsWnd::OnCreate
// Description	    : Create a new things.
// Return type		: int 
// Argument         : LPCREATESTRUCT lpCreateStruct
int CSheetsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rect; GetClientRect(rect);
	m_font.CreateFont(-rect.Height() * 8 / 10, 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FONTNAME);
	CSize sxy(2 * rect.Height(), rect.Height());
	m_btns.Create(WS_CHILD | WS_VISIBLE | SBS_HORZ, CRect(CPoint(rect.left, rect.top), sxy), this, IDBTNS);
	rect.left += sxy.cx + 2;
	m_DrawRect = rect;
	return 0;
}

// Function name	: CSheetsWnd::OnEraseBkgnd
// Description	    : 
// Return type		: BOOL 
// Argument         : CDC* pDC
BOOL CSheetsWnd::OnEraseBkgnd(CDC* pDC) 
{
	Draw(pDC);
	pDC->ExcludeClipRect(EraseExclude());
	CBrush* pOldBrush = pDC->SelectObject(&m_brBackground);
	CRect rect;
	pDC->GetClipBox(&rect);     // Erase the area needed
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
}

// Function name	: CSheetsWnd::GetPageRect
// Description	    : Return client coordonate of rect ocupied by page of pView
// Return type		: CRect 
// Argument         : CWnd * pView
CRect CSheetsWnd::GetPageRect(CWnd * pView)
{
	CRect rRect(0,m_DrawRect.top,0,m_DrawRect.bottom);
	if (pView)
	{
		CDC* pDC = GetDC();
		CFont* pOldFont = pDC->SelectObject(&m_font);
		CWnd* pChild = GetFirstView();
		int nCont = pChild != NULL ? 2 : 0;
		int cxB = LRB, cx = cxB + m_nHorzScroll + m_DrawRect.left;
		while (nCont)
		{
			nCont = nCont + (pChild == pView ? -1 : (nCont == 1 ? -1 : 0));
			if (nCont)
			{
				if (nCont == 1) rRect.left = cx - LRB - 4;
				CRect rt(cx,0,0,0);
				pDC->DrawText(GetViewTitle(pChild), rt, DEFAULTFORMATDRAWTEXT | DT_CALCRECT);
				rt.top = 0; rt.bottom = m_DrawRect.Height();
				rt.left -= 4; rt.right += 4;
				int next = rt.Width() + LRB ;
				cx += next;
				if (nCont == 1) rRect.right = cx - LRB + 4;
				pChild = GetNextView();
			}
		}
		pDC->SelectObject(pOldFont);
		ReleaseDC(pDC);
	}
	return rRect;
}

// Function name	: CSheetsWnd::DrawMoveBar
// Description	    : Override this function and return empty rect if
// you do not wish to move this object
// Return type		: CRect 
// Argument         : CDC * pDC
// Argument         : int x
CRect CSheetsWnd::DrawMoveBar(CDC * pDC, int x)
{
	// x reprezent last pixel drawen in object
	int y = 1, r = m_DrawRect.right, l = min(x, r); r = l + m_DrawRect.Height();
	CPen pWhite(PS_SOLID,1,RGB(255,255,255));
	CPen  pGray(PS_SOLID,1,RGB(128,128,128));
	pDC->SelectObject(&pWhite);
	pDC->MoveTo(l,y + 2); pDC->LineTo(l,y);pDC->LineTo(r,y);
	pDC->SelectObject(&pGray);
	pDC->LineTo(r,y + 2);pDC->LineTo(l,y + 2);
	// Attention that x is relative position on DC. Already in DC is 
	// selected a view origin to m_DrawRect.left, and then you must 
	// offset the result rect with m_DrawRect.left
	CRect rResult(l,y,r,y + 2); rResult.OffsetRect(m_DrawRect.left,0);
	return rResult;
}

// Function name	: CSheetsWnd::Draw
// Description	    : Draw the pages of object
// Return type		: void 
// Argument         : CDC * pDC
void CSheetsWnd::Draw(CDC * pDC)
{
	if (!m_DrawRect.IsRectNull())
	{
		CDC dc; CBitmap bitmap;
		if (dc.CreateCompatibleDC(pDC))
			if (bitmap.CreateCompatibleBitmap(pDC, m_DrawRect.Width(), m_DrawRect.Height()))
			{
				CBitmap* pOldBitmap = dc.SelectObject(&bitmap);

				CBrush* pOldBrush = dc.SelectObject(&m_brBackground);
				dc.PatBlt(0,0, m_DrawRect.Width(), m_DrawRect.Height(), PATCOPY);
				CFont* pOldFont = dc.SelectObject(&m_font);
				dc.SetBkMode(TRANSPARENT);
				CWnd *pActiveView = GetActiveView(), *pView = GetFirstView();;
				CRgn rgnActive;
				static const int mP = 4;
				CRect rtActive; CPoint pActivePage[mP];
				int cxB = LRB, cx = m_nHorzScroll + cxB, next = NULL;
				m_nMaxHorzScroll = 0;
				while (pView)
				{
					CString title = GetViewTitle(pView);
					CRect rt(cx,0,0,0);
					dc.DrawText(title, rt, DEFAULTFORMATDRAWTEXT | DT_CALCRECT);
					rt.top = 0; rt.bottom = m_DrawRect.Height();
					rt.left -= 4; rt.right += 4;
					CPoint pPage[mP];
					 pPage[0] = CPoint(rt.left  - cxB, 0);
					 pPage[1] = CPoint(rt.left, rt.bottom);
					 pPage[2] = CPoint(rt.BottomRight());
					 pPage[3] = CPoint(rt.right + cxB, 0);
					CRgn rgn; rgn.CreatePolygonRgn(pPage, 4, WINDING);
					dc.FillRgn(&rgn, &m_brBackground);
					dc.FrameRgn(&rgn, &CBrush(RGB(0,0,0)), 1, 1);
					dc.DrawText(title, rt, DEFAULTFORMATDRAWTEXT);
					if ((pActiveView) && (pView == pActiveView))
					{
						rgnActive.CreatePolygonRgn(pPage, 4, ALTERNATE);
						rtActive = rt;
						for (int i = 0; i < mP ; i++)
							pActivePage[i] = pPage[i];
					}
					pView = GetNextView();
					next = rt.Width() + LRB;
					cx += next;
					m_nMaxHorzScroll += next;
				}
				m_rectMoveBar = DrawMoveBar(&dc, cx);
				if (pActiveView)
				{
					dc.FillRgn(&rgnActive, &CBrush(RGB(255,255,255)));
					dc.FrameRgn(&rgnActive, &CBrush(RGB(0,0,0)), 1, 1);
					dc.DrawText(GetViewTitle(pActiveView), rtActive, DEFAULTFORMATDRAWTEXT);
					int pROP2 = dc.SetROP2(R2_WHITE);
					dc.MoveTo(pActivePage[0]); dc.LineTo(pActivePage[3]);
					dc.SetROP2(R2_COPYPEN);
					CPen pen(PS_DOT,1,RGB(192,192,192));
					dc.SelectObject(&pen);
					dc.MoveTo(pActivePage[0]); dc.LineTo(pActivePage[3]);
				}
				pDC->BitBlt(m_DrawRect.left, m_DrawRect.top, m_DrawRect.Width(), m_DrawRect.Height(), &dc, 0,0, SRCCOPY);
				dc.SelectObject(pOldFont);
				dc.SelectObject(pOldBrush);
				dc.SelectObject(pOldBitmap);
			}
	}
}

// Function name	: CSheetsWnd::OnHScroll
// Description	    : Left right buttons
// Return type		: void 
// Argument         : UINT nSBCode
// Argument         : UINT nPos
// Argument         : CScrollBar* pScrollBar
void CSheetsWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar->m_hWnd == m_btns.m_hWnd)
	{
		int nCX = 0;
		switch (nSBCode)
		{
			case SB_LINELEFT:
			case SB_LINERIGHT:
				{
					nCX = (nSBCode == SB_LINELEFT ? 1 : - 1) * 16;
					break;
				}
		}
		int n = m_nHorzScroll + nCX;
		if ( n <= 0)
			if (abs(n) < m_nMaxHorzScroll)
		{
			m_nHorzScroll = n;	
			Invalidate();
		}
	}
	
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

// Function name	: CSheetsWnd::Move
// Description	    : 
// Return type		: void 
// Argument         : CPoint point
void CSheetsWnd::Move(CPoint point)
{
	if (m_pRollPoint)
		if (int dy = point.y - m_pRollPoint->y)
		{
			int nDeplacement = m_nDisplacement + dy;
			if ((nDeplacement >= 0) && (nDeplacement< m_DrawRect.Height()))
			{
				CRect rect; GetWindowRect(rect);
				rect.OffsetRect(0, dy);
				GetParent()->ScreenToClient(rect);
				MoveWindow(rect);
				m_nDisplacement = nDeplacement;
			}
		}
}

// Function name	: CSheetsWnd::OnLButtonDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CSheetsWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();
	if (m_DrawRect.PtInRect(point))
		SetActiveView(GetViewFromPoint(point));

	if (m_rectMoveBar.PtInRect(point))
		if (!GetCapture())
		{
			SetCapture();
			m_pRollPoint = new CPoint(point);
			m_nDisplacement = 0;
			Move(point);
		}


	CWnd::OnLButtonDown(nFlags, point);
}

// Function name	: CSheetsWnd::OnLButtonUp
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CSheetsWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_pRollPoint)
	{
		delete m_pRollPoint;
		m_pRollPoint = NULL;
		ReleaseCapture();
		Resize(GetParent()->m_hWnd);
	}
	
	CWnd::OnLButtonUp(nFlags, point);
}

// Function name	: CSheetsWnd::OnMouseMove
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CSheetsWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	Move(point);
	
	CWnd::OnMouseMove(nFlags, point);
}

// Function name	: CSheetsWnd::OnSetCursor
// Description	    : Set the cursor.
// Return type		: BOOL 
// Argument         : CWnd* pWnd
// Argument         : UINT nHitTest
// Argument         : UINT message
BOOL CSheetsWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CPoint pCursor;
	if (GetCursorPos(&pCursor))
	{
		ScreenToClient(&pCursor);
		if (m_rectMoveBar.PtInRect(pCursor))
		{
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
			return TRUE;
		}
	}
	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

// Function name	: CSheetsWnd::GetViewFromPoint
// Description	    : Return pointer to view s.t. page of view contain point
// Return type		: CWnd* 
// Argument         : CPoint point
CWnd* CSheetsWnd::GetViewFromPoint(CPoint point)
{
	if (m_DrawRect.PtInRect(point))
	{
		CWnd* pChild = GetFirstView();
		CDC* pDC = GetDC();
		pDC->SetViewportOrg(m_DrawRect.TopLeft());
		CFont* pOldFont = pDC->SelectObject(&m_font);
		int cxB = LRB, cx = cxB;
		int aPointX = -m_nHorzScroll + point.x - m_DrawRect.left;
		while (pChild)
		{
			CRect rt(cx,0,0,0);
			pDC->DrawText(GetViewTitle(pChild), rt, DEFAULTFORMATDRAWTEXT | DT_CALCRECT);
			rt.top = 0; rt.bottom = m_DrawRect.Height();
			rt.left -= 4; rt.right += 4;
			if ((aPointX > cx - LRB) && (aPointX  <= cx + rt.Width() + LRB))
				break;
			pChild = GetNextView();
			int next = rt.Width() + LRB ;
			cx += next;
		}
		pDC->SelectObject(pOldFont);
		ReleaseDC(pDC);
		return pChild;
	}
	return NULL;
}

// Function name	: CSheetsWnd::GetDrawRect
// Description	    : Return the painting rect
// Return type		: CRect 
CRect CSheetsWnd::GetDrawRect() const
{
	return m_DrawRect;
}

// Function name	: CSheetsWnd::EraseExclude
// Description	    : When WM_ERASEBKGND occurs, then CSheetsWnd::OnEraseBkGnd,
// require a rect that will be excluded from area erased. That's it.
// Return type		: CRect 
CRect CSheetsWnd::EraseExclude()
{
	return m_DrawRect;
}

// Function name	: CSheetsWnd::GetWindowProc
// Description	    : Return the window procedure of Parent object
// Return type		: WNDPROC 
WNDPROC CSheetsWnd::GetWindowProc()
{
	return m_wndProcParent;
}

// Function name	: CSheetsWnd::OnKeyDown
// Description	    : Treat key as shortcut to page.
// Return type		: void 
// Argument         : UINT nChar
// Argument         : UINT nRepCnt
// Argument         : UINT nFlags
void CSheetsWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (!GetCapture())
		switch (nChar)
		{
			case VK_LEFT:
			case VK_RIGHT:
			{
				SendMessage(WM_HSCROLL, MAKEWPARAM(nChar == VK_LEFT ? SB_LINELEFT : SB_LINERIGHT,0), (long)m_btns.m_hWnd);
				break;
			}
			default:
				JumpToPage(nChar);
		}
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

// Function name	: CSheetsWnd::JumpToPage
// Description	    : Jump to page witch start with tChar
// Return type		: void 
// Argument         : TCHAR tChar
void CSheetsWnd::JumpToPage(TCHAR tChar)
{
	CWnd* pChild = GetActiveView();
	if (!pChild)
		pChild = GetFirstView();
	else
		pChild = GetNextView();
	int n = 2; BOOL bFound = FALSE;
	while (n)
	{
		while (pChild)
		{
			if (IsEqual(GetViewTitle(pChild),CString(tChar)))
			{
				n = 0;
				bFound = TRUE;
				break;
			}
			pChild = GetNextView();
		}
		if (n)
		{
			pChild = GetFirstView();
			n--;
		}
	}
	if (bFound)
		if (GetActiveView() != pChild)
		{
			SetActiveView(pChild);
			EnsureVisible(pChild);
		}
}

// Function name	: CSheetsWnd::IsEqual
// Description	    : Compare if two string is equal, call from JumpToPage
// Return type		: BOOL 
// Argument         : CString s
// Argument         : CString d
BOOL CSheetsWnd::IsEqual(CString s, CString d)
{
	s = s.Left(1); s.MakeUpper();
	d = d.Left(1); d.MakeUpper();
	return s == d;
}

// Function name	: CSheetsWnd::EnsureVisible
// Description	    : Ensure that page pView is visible
// Return type		: void 
// Argument         : CWnd * pView
void CSheetsWnd::EnsureVisible(CWnd * pView)
{
	CRect rect = GetPageRect(pView);
	int mDrawRect = (m_DrawRect.left + m_DrawRect.right) / 2;
	int mRect = (rect.left + rect.right) / 2;
	while (mRect > mDrawRect)
	{
		SendMessage(WM_HSCROLL, MAKEWPARAM(SB_LINERIGHT,0), (long)m_btns.m_hWnd);
		rect = GetPageRect(pView);
		int nmRect = (rect.left + rect.right) / 2;
		if (nmRect >= mRect) break;
		mRect = nmRect;
	}
	while (mRect < mDrawRect)
	{
		SendMessage(WM_HSCROLL, MAKEWPARAM(SB_LINELEFT,0), (long)m_btns.m_hWnd);
		rect = GetPageRect(pView);
		int nmRect = (rect.left + rect.right) / 2;
		if (nmRect <= mRect) break;
		mRect = nmRect;
	}
}

