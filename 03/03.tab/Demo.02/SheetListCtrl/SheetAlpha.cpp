/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/21/98 10:12:24 AM
  Comments: SheetAlpha.cpp: implementation of the CSheetAlpha class.
 ************************************/

#include "stdafx.h"
#include "SheetAlpha.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define IDTIMERWAITTODRAG 1000
#define WAITTODRAG 500
#define IDTIMERSCROLL 1001
#define WAITSCROLL 10

BEGIN_MESSAGE_MAP(CSheetAlpha, CSheetsWnd)
	//{{AFX_MSG_MAP(CSheetAlpha)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Function name	: CSheetAlpha::CSheetAlpha
// Description	    : Default constructor of object
// Return type		: 
CSheetAlpha::CSheetAlpha()
{
	m_nActive = -1;
	m_fDXScrollBar = (double)2 / 5;
	m_nDXSplitter = 5;
	m_bCaptured = FALSE;
}

// Function name	: CSheetAlpha::~CSheetAlpha
// Description	    : Destructor of this object
// Return type		: 
CSheetAlpha::~CSheetAlpha()
{

}

// Function name	: CSheetAlpha::GetFirstView overridable
// Description	    : See CSheetsWnd::GetFirstView
// Return type		: CWnd* 
CWnd* CSheetAlpha::GetFirstView()
{
	m_nFind = -1;
	return GetNextView();
}

// Function name	: CSheetAlpha::GetNextView overridable
// Description	    : See CSheetsWnd::GetNextView
// Return type		: CWnd* 
CWnd* CSheetAlpha::GetNextView()
{
	if (++m_nFind < m_strTitles.GetSize())
		return (CWnd*)&m_strTitles[m_nFind];
	return NULL;
}

// Function name	: CSheetAlpha::GetActiveView overridable
// Description	    : See: CSheetsWnd::GetActiveView
// Return type		: CWnd* 
CWnd* CSheetAlpha::GetActiveView()
{
	if ((m_nActive>=0) && (m_nActive < m_strTitles.GetSize()))
	{
		m_nFind = m_nActive;
		return (CWnd*)&m_strTitles[m_nActive];
	}
	return NULL;
}

// Function name	: CSheetAlpha::SetActiveView
// Description	    : Sets the active view
// Return type		: void 
// Argument         : CWnd* pView
void CSheetAlpha::SetActiveView(CWnd* pView)
{
	if (pView)
	{
		CWnd* pParent = GetParent();
		int n = GetPageIndex((LPCTSTR)(CString&)*pView);
		pParent->SendMessage(GetMessagePageChanging(), (WPARAM)GetActiveView(), (LPARAM)pView);
		{
			if (n != m_nActive)
			{
				m_nActive = n;
				Invalidate();
				pParent->SendMessage(GetMessagePageChanged(), (WPARAM)pView, 0);
			}
		}
	}
}

// Function name	: CSheetAlpha::GetViewTitle overridable
// Description	    : See CSheetsWnd::GetViewTitle
// Return type		: CString 
// Argument         : CWnd* pView
CString CSheetAlpha::GetViewTitle(CWnd* pView)
{
	return CString((CString&)*pView);
}

// Function name	: CSheetAlpha::OnLButtonDown
// Description	    : When user click in one of the pages..., it's different by CSheetsWnd::OnLButtonDown,
// because in that object pages are not childs of parent object!
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CSheetAlpha::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();
	if (GetSplitterRect().PtInRect(point))
	{
		m_bPointCaptured = point;
		m_bCaptured = TRUE;
		SetCapture();
	}

	BeginDrag(point);

	CSheetsWnd::OnLButtonDown	(nFlags, point);
}

// Function name	: CSheetAlpha::OnMouseMove
// Description	    : When user move mouse and drag the splitter...
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CSheetAlpha::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bCaptured)
	{
		CRect rect; GetClientRect(rect);
		m_fDXScrollBar = 1 - (double)point.x / rect.Width();
		Resize(GetParent()->m_hWnd);
		Invalidate();
	}

	TrackDrag(point);
	
	CSheetsWnd::OnMouseMove(nFlags, point);
}

// Function name	: CSheetAlpha::OnLButtonUp
// Description	    : Release the capture if object is captured. Remember spliter
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CSheetAlpha::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bCaptured)
	{
		m_bCaptured = FALSE;
		ReleaseCapture();
	}

	EndDrag(point);
	
	CSheetsWnd::OnLButtonUp(nFlags, point);
}

// Function name	: CSheetAlpha::OnSetCursor
// Description	    : When user scan splitter rect must be LR cursor.
// Return type		: BOOL 
// Argument         : CWnd* pWnd
// Argument         : UINT nHitTest
// Argument         : UINT message
BOOL CSheetAlpha::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	CPoint p;
	if (GetCursorPos(&p))
	{
		ScreenToClient(&p);
		if (GetSplitterRect().PtInRect(p))
			if (!m_sPageDrag.IsDragging())
			{
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
				return TRUE;
			}
	}
	
	return CSheetsWnd::OnSetCursor(pWnd, nHitTest, message);
}

// Function name	: CSheetAlpha::RecalcDrawRect
// Description	    : If something occurs in that object, like scroll bar, splitter then
// m_DrawRect member variable, must be overwrite, for painting message.
// Return type		: void 
void CSheetAlpha::RecalcDrawRect()
{
	CRect rect; GetClientRect(rect);
	if (m_sbHorz.IsWindowVisible())
	{
		m_sbHorz.GetWindowRect(rect);
		ScreenToClient(rect);
		rect.right = rect.left;
	}
	m_DrawRect.right = rect.right - (bSplitter() ? m_nDXSplitter : 0);
}

// Function name	: CSheetAlpha::Resize
// Description	    : Do not call base Resize, because it's not the same situation
// Return type		: void 
// Argument         : HWND hWndParent
void CSheetAlpha::Resize(HWND hWndParent)
{
	CRect rect = GetRect(hWndParent);
	MoveWindow(rect);
	GetWindowRect(rect);
	ScreenToClient(rect);
	CRect rectBtns; m_btns.GetWindowRect(rectBtns);
	ScreenToClient(rectBtns);
	rect.left = min(max(rectBtns.right + GetSplitterRect().Width(), rect.right - (int)((double)rect.Width() * m_fDXScrollBar)), rect.Width() - 8);
	m_sbHorz.MoveWindow(rect);
	RecalcDrawRect();
}

// Function name	: CSheetAlpha::OnCreate
// Description	    : Create a new scrollbar, for substitute an just in case that parent object 
// need a horizontal scroll bar
// Return type		: int 
// Argument         : LPCREATESTRUCT lpCreateStruct
int CSheetAlpha::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSheetsWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_sbHorz.Create(WS_CHILD | SBS_HORZ, CRect(0,0,0,0), this, IDBTNS + 1);

	return 0;
}

// Function name	: CSheetAlpha::Draw
// Description	    : Draw the pages of object, like CSheetsWnd::Draw() and complete the image of splitter.
// Return type		: void 
// Argument         : CDC * pDC
void CSheetAlpha::Draw(CDC * pDC)
{
	CSheetsWnd::Draw(pDC);
	CRect rSplitter = GetSplitterRect();
	if (!rSplitter.IsRectEmpty())
	{
		pDC->FillRect(rSplitter, &CBrush(RGB(192,192,192)));
		CPen pWhite(PS_SOLID,1,RGB(255,255,255));
		CPen  pGray(PS_SOLID,1,RGB(128,128,128));
		pDC->SelectObject(&pGray);
		CPoint p = rSplitter.TopLeft() + CPoint(1,1);
		p += CPoint(2,0);
		pDC->MoveTo(p);
		p += CPoint(0,rSplitter.Height() - 2);
		pDC->LineTo(p);
		p += CPoint(-2,0);
		pDC->LineTo(p);
		pDC->SelectObject(&pWhite);
		p += CPoint(0,-(rSplitter.Height() - 2));
		pDC->LineTo(p);
		p += CPoint(2,0);
		pDC->LineTo(p);
	}
}

// Function name	: CSheetAlpha::ShowScrollBar
// Description	    : Show or hide the scroll bar.m_sbHorz
// Return type		: void 
// Argument         : BOOL bShow
void CSheetAlpha::ShowScrollBar(BOOL bShow)
{
	m_sbHorz.ShowWindow(bShow ? SW_SHOW : SW_HIDE);
	RecalcDrawRect();
	Invalidate();
}

// Function name	: CSheetAlpha::OnHScroll
// Description	    : If the control receive a scroll message from m_sbHorz, then treat this
// Return type		: void 
// Argument         : UINT nSBCode
// Argument         : UINT nPos
// Argument         : CScrollBar* pScrollBar
void CSheetAlpha::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar->m_hWnd == m_sbHorz.m_hWnd)
	{
		CWnd* pParent = GetParent();
		ASSERT (pParent && GetParent()->m_hWnd);
		switch (nSBCode)
		{
			case SB_THUMBTRACK:
			{
				int npp = m_sbHorz.GetScrollPos();
				int n = nPos - npp;
				UINT nCode = n < 0 ? SB_LINELEFT : SB_LINERIGHT;
				int nStep = n < 0 ? -1 : 1;
				n = abs(n);
				for (int i = 0; i < n; i++ )
				{
					pParent->SendMessage(WM_HSCROLL, MAKELONG(nCode,1), (long)pScrollBar->m_hWnd);
					npp = npp + nStep;
					m_sbHorz.SetScrollPos(npp);
				}
				break;
			}
			default:
			{
				pParent->SendMessage(WM_HSCROLL, MAKELONG(nSBCode,nPos), (long)pScrollBar->m_hWnd);
				m_sbHorz.SetScrollPos(pParent->GetScrollPos(SB_HORZ));
				break;
			}
		}
	}
	
	CSheetsWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

// Function name	: CSheetAlpha::bSplitter
// Description	    : Return TRUE if splitter is showen in object, Private function.
// Return type		: BOOL 
BOOL CSheetAlpha::bSplitter()
{
	return !(GetSplitterRect().IsRectEmpty());
}

// Function name	: CSheetAlpha::EraseExclude
// Description	    : When WM_ERASEBKGND occurs, then CSheetsWnd::OnEraseBkGnd,
// require a rect that will be excluded from area erased.
// Return type		: CRect 
CRect CSheetAlpha::EraseExclude()
{
	CRect rSplitter = GetSplitterRect();
	return m_DrawRect + CRect(0,0, rSplitter.IsRectEmpty() ? 0 : m_nDXSplitter,0);
}

// Function name	: CSheetAlpha::GetSplitterRect
// Description	    : If user want no splitter, must override this function, and return empty rect
// Return type		: CRect 
CRect CSheetAlpha::GetSplitterRect()
{
	CRect result(0,0,0,0);
	if (m_sbHorz.IsWindowVisible())
		result = CRect(m_DrawRect.right, m_DrawRect.top, m_DrawRect.right + m_nDXSplitter, m_DrawRect.bottom);
	return result;
}

// Function name	: CSheetAlpha::GetScrollBar
// Description	    : Return the scroll bar of this object, created in OnCreate function
// Return type		: CScrollBar& 
CScrollBar& CSheetAlpha::GetScrollBar()
{
	return m_sbHorz;
}

// Function name	: CSheetAlpha::GetPageIndex
// Description	    : Search for a pags with title lpszTitle, and return its position
// Return type		: int 
// Argument         : LPCTSTR lpszTitle
int CSheetAlpha::GetPageIndex(LPCTSTR lpszTitle)
{
	int n = -1;
	for (int i = 0; i < m_strTitles.GetSize(); i++)
		if (m_strTitles[i].CompareNoCase(lpszTitle) == 0)
		{
			n = i;
			break;
		}
	return n;
}

// Function name	: CSheetAlpha::AddPage
// Description	    : Add a new page to object, and return index position
// Return type		: int 
// Argument         : LPCTSTR lpszTitle
int CSheetAlpha::AddPage(LPCTSTR lpszTitle)
{
	int nResult = m_strTitles.Add(lpszTitle);
	Invalidate();
	return nResult;
}

// Function name	: CSheetAlpha::RemovePage
// Description	    : Remove page with title lpszTitle if founded
// Return type		: void 
// Argument         : LPCTSTR lpszTitle
void CSheetAlpha::RemovePage(LPCTSTR lpszTitle)
{
	int nPage = GetPageIndex(lpszTitle);
	if (nPage >= 0)
	{
		m_strTitles.RemoveAt(nPage);
		Invalidate();
	}
}

// Function name	: CSheetAlpha::RemovePage
// Description	    : Remove page by position
// Return type		: void 
// Argument         : int nPage
void CSheetAlpha::RemovePage(int nPage)
{
		m_strTitles.RemoveAt(nPage);
		Invalidate();
}

// Function name	: CSheetAlpha::BeginDrag
// Description	    : Start the dragging page if is case
// Return type		: void 
// Argument         : CPoint ptn
void CSheetAlpha::BeginDrag(CPoint ptn)
{
	if (GetDrawRect().PtInRect(ptn))
		if (CWnd* pView = GetViewFromPoint(ptn))
		{
			m_sPageDrag.SetTrackDrag(pView);
			SetTimer(IDTIMERWAITTODRAG, WAITTODRAG, NULL);
			SetTimer(IDTIMERSCROLL,WAITSCROLL,NULL);
		}
}

// Function name	: CSheetAlpha::TrackDrag
// Description	    : Continue the dragging page
// Return type		: void 
// Argument         : CPoint ptn
void CSheetAlpha::TrackDrag(CPoint ptn)
{
	if (m_sPageDrag.IsDragging())
	{
		m_sPageDrag.SetTrackDrag(GetViewFromPoint(ptn));
		m_sPageDrag.Draw(this);
	}
}

// Function name	: CSheetAlpha::EndDrag
// Description	    : Stop the draging page
// Return type		: void 
// Argument         : CPoint ptn
void CSheetAlpha::EndDrag(CPoint ptn)
{
	KillTimer(IDTIMERWAITTODRAG);
	if (m_sPageDrag.IsDragging())
	{
		KillTimer(IDTIMERSCROLL);
		m_sPageDrag.SetTrackDrag(GetViewFromPoint(ptn));
		CDragPage sPageDrag(m_sPageDrag);
		// Reset the current values drag
		m_sPageDrag.Reset();
		ReleaseCapture();
		// Draw		
		m_sPageDrag.Draw(this);
		// If case, change pages between them
		if (sPageDrag.GetTrackDrag() && sPageDrag.GetStartDrag())
			if (sPageDrag.GetTrackDrag() != sPageDrag.GetStartDrag())
			{
				int nS = GetPageIndex((CString&)*sPageDrag.GetStartDrag());
				int nE = GetPageIndex((CString&)*sPageDrag.GetTrackDrag());
				CString s = m_strTitles.GetAt(nS);
				CString e = m_strTitles.GetAt(nE);
				m_strTitles.SetAt(nS,e);
				m_strTitles.SetAt(nE,s);
				m_nActive = nE;
				Invalidate();
			}
	}
}

// Function name	: CSheetAlpha::OnTimer
// Description	    : Wait starting to drag
// Return type		: void 
// Argument         : UINT nIDEvent
void CSheetAlpha::OnTimer(UINT nIDEvent) 
{
	CPoint p;
	if (GetCursorPos(&p))
	{
		ScreenToClient(&p);
		switch (nIDEvent)
		{
			case IDTIMERWAITTODRAG:
			{
				if (CWnd* pViewTrackDrag = m_sPageDrag.GetTrackDrag())
					if (GetViewFromPoint(p) == pViewTrackDrag)
					{
						m_sPageDrag.Set(TRUE, pViewTrackDrag);
						m_sPageDrag.Draw(this);
						SetCapture();
					}
				KillTimer(IDTIMERWAITTODRAG);
				break;
			}
			case IDTIMERSCROLL:
			{
				if (m_sPageDrag.IsDragging())
					if (!m_DrawRect.PtInRect(p))
						if (p.y > m_DrawRect.top)
							if (p.y < m_DrawRect.bottom)
							{
								m_sPageDrag.SetTrackDrag(GetViewFromPoint(p));
								m_sPageDrag.Draw(this);
								SendMessage(WM_HSCROLL, MAKEWPARAM(p.x < m_DrawRect.left ? SB_LINELEFT : SB_LINERIGHT, 0), (LPARAM)m_btns.m_hWnd);
							}
				break;
			}

		}
	}
	
	CSheetsWnd::OnTimer(nIDEvent);
}

// Function name	: CSheetAlpha::TranslateMessage
// Description	    : Help in translate wParam and lParam parameter.
// Call when object send SM_CHANGING and SM_CHANGED messages, for translate
// wParam and lParam parametres. Sorry for casting!
// Return type		: CString& 
// Argument         : DWORD dw
CString& CSheetAlpha::TranslateMessage(DWORD dw)
{
	return (CString&)*(DWORD*)dw;
}
