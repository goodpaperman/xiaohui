// BCGDockBar.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"    // for CDockContext
#include <..\\src\\afximpl.h>
#include "BCGDockBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int nEdge = 6;
static const int nGripperSize = 20;

IMPLEMENT_DYNAMIC(CBCGDockBar, CControlBar)

/////////////////////////////////////////////////////////////////////////////
// CBCGDockBar

CBCGDockBar::CBCGDockBar()
{
    m_sizeMin = CSize(32, 32);
    m_sizeHorz = CSize(200, 200);
    m_sizeVert = CSize(200, 200);
    m_sizeFloat = CSize(200, 200);
    m_bTracking = FALSE;
    m_bInRecalcNC = FALSE;
	m_bClosePressed = FALSE;
	m_bCloseFocused = FALSE;
}

CBCGDockBar::~CBCGDockBar()
{
}

BEGIN_MESSAGE_MAP(CBCGDockBar, CControlBar)
    //{{AFX_MSG_MAP(CBCGDockBar)
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_SETCURSOR()
    ON_WM_WINDOWPOSCHANGED()
    ON_WM_NCPAINT()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_NCHITTEST()
    ON_WM_NCCALCSIZE()
    ON_WM_LBUTTONDOWN()
    ON_WM_CAPTURECHANGED()
    ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CANCELMODE()
    ON_WM_SIZE()
	ON_WM_NCLBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGDockBar message handlers

void CBCGDockBar::OnUpdateCmdUI(class CFrameWnd *pTarget, int bDisableIfNoHndler)
{
    UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

BOOL CBCGDockBar::Create(CWnd* pParentWnd, CSize sizeDefault, UINT nID, DWORD dwStyle) 
{
    ASSERT_VALID(pParentWnd);   // must have a parent
    ASSERT (!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));

    // save the style
	m_dwStyle = (dwStyle & CBRS_ALL);

    dwStyle &= ~CBRS_ALL;
    dwStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;

    m_sizeHorz = sizeDefault;
    m_sizeVert = sizeDefault;
    m_sizeFloat = sizeDefault;

	//----------------------------
	// Initialize common controls:
	//----------------------------
	VERIFY (AfxDeferRegisterClass (AFX_WNDCOMMCTLS_REG));

	CRect rect;
	rect.SetRectEmpty();

	LPCTSTR lpszClass = ::AfxRegisterWndClass (
		CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_BTNFACE + 1), NULL);
	ASSERT (lpszClass != NULL);

	if (!CWnd::Create (lpszClass, NULL, dwStyle, rect, pParentWnd, nID))
	{
		TRACE (_T("Can't create CBCGDockBar. Last error = %x\n"),
				GetLastError ());
		return FALSE;
	}

	return TRUE;
}

class CBCGTempDockBar : public CDockBar
{
	friend CBCGDockBar;
};

CSize CBCGDockBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	CRect rectClient;
	rectClient.SetRectEmpty();        // only need top and left
	CalcInsideRect (rectClient, bHorz);

	MapWindowPoints (GetDockingFrame (), rectClient);

	//------------------------------------------
	// Try to occupy the maximum possible space:
	//------------------------------------------
	CRect rect;
	rect.SetRectEmpty ();

	if (m_pDockBar != NULL)
	{
		rect = ((CBCGTempDockBar*) m_pDockBar)->m_rectLayout;
	}

	if (!rect.IsRectEmpty () || bStretch)
	{
		if (bHorz)
		{
			return CSize (bStretch ? 32767 : rect.Width (), m_sizeHorz.cy);
		}
		else
		{
			return CSize (m_sizeVert.cx, bStretch ? 32767 : rect.Height ());
		}
	}
	else
	{
		CRect rc;

		m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rc);
		int nHorzDockBarWidth = bStretch ? 32767 : rc.Width() + 4;
		m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(rc);
		int nVertDockBarHeight = bStretch ? 32767 : rc.Height() + 4;

		if (bHorz)
			return CSize(nHorzDockBarWidth, m_sizeHorz.cy);
		else
			return CSize(m_sizeVert.cx, nVertDockBarHeight);
	}
}

CSize CBCGDockBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
    if (dwMode & (LM_HORZDOCK | LM_VERTDOCK))
    {
        if (nLength == -1)
            GetDockingFrame()->DelayRecalcLayout();
        return CControlBar::CalcDynamicLayout(nLength,dwMode);
    }

    if (dwMode & LM_MRUWIDTH)
        return m_sizeFloat;

    if (dwMode & LM_COMMIT)
    {
        m_sizeFloat.cx = nLength;
        return m_sizeFloat;
    }

    if (dwMode & LM_LENGTHY)
        return CSize(m_sizeFloat.cx,
            m_sizeFloat.cy = max(m_sizeMin.cy, nLength));
    else
        return CSize(max(m_sizeMin.cx, nLength), m_sizeFloat.cy);
}

void CBCGDockBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
    CControlBar::OnWindowPosChanged(lpwndpos);
	RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE);

    if (m_bInRecalcNC) return;

    // Find on which side are we docked
    UINT nDockBarID = GetParent()->GetDlgCtrlID();

    // Return if dropped at same location
    if (nDockBarID == m_nDockBarID // no docking side change
        && (lpwndpos->flags & SWP_NOSIZE) // no size change
        && ((m_dwStyle & CBRS_BORDER_ANY) != CBRS_BORDER_ANY))
        return; 

    m_nDockBarID = nDockBarID;

    // Force recalc the non-client area
    m_bInRecalcNC = TRUE;
    SetWindowPos(NULL, 0, 0, 0, 0,
        SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER |
        SWP_NOACTIVATE | SWP_FRAMECHANGED);
    m_bInRecalcNC = FALSE;
}

BOOL CBCGDockBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if ((nHitTest != HTSIZE) || m_bTracking)
        return CControlBar::OnSetCursor(pWnd, nHitTest, message);

    if (IsHorz())
        SetCursor (m_hcurVertSize);
    else
        SetCursor (m_hcurHorzSize);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// Mouse Handling
//
void CBCGDockBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bClosePressed)
	{
		if (GetCapture () == this)
		{
			ReleaseCapture ();
		}

		if (m_bClosePressed && m_bCloseFocused)
		{
			GetParentFrame ()->ShowControlBar (this, FALSE, FALSE);
		}

		m_bClosePressed = FALSE;
		m_bCloseFocused = FALSE;

		RedrawWindow (m_rectClose, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME);
	}

    if (!m_bTracking)
        CControlBar::OnLButtonUp(nFlags, point);
    else
    {
        ClientToWnd(point);
        StopTracking(TRUE);
    }
}

void CBCGDockBar::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (IsFloating() || !(m_bTracking || m_bClosePressed))
    {
        CControlBar::OnMouseMove(nFlags, point);
        return;
    }

    ClientToWnd (point);
	if (m_bClosePressed)
	{
		BOOL bCloseWasFocused = m_bCloseFocused;
		m_bCloseFocused = m_rectClose.PtInRect(point);

		if (bCloseWasFocused != m_bCloseFocused)
		{
			RedrawWindow (m_rectClose, NULL,
				RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME);
		}

		return;
	}

    CPoint cpt = m_rectTracker.CenterPoint();

    if (IsHorz())
    {
        if (cpt.y != point.y)
        {
            OnInvertTracker(m_rectTracker);
            m_rectTracker.OffsetRect(0, point.y - cpt.y);
            OnInvertTracker(m_rectTracker);
        }
    }
    else 
    {
        if (cpt.x != point.x)
        {
            OnInvertTracker(m_rectTracker);
            m_rectTracker.OffsetRect(point.x - cpt.x, 0);
            OnInvertTracker(m_rectTracker);
        }
    }
}

void CBCGDockBar::OnNcCalcSize(BOOL /*bCalcValidRects*/, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
    // Compute the rectangle of the mobile edge
    GetWindowRect(m_rectBorder);
    m_rectBorder = CRect(0, 0, m_rectBorder.Width(), m_rectBorder.Height());

	m_rectGripper = m_rectBorder;
    
    DWORD dwBorderStyle = m_dwStyle | CBRS_BORDER_ANY;

    switch(m_nDockBarID)
    {
    case AFX_IDW_DOCKBAR_TOP:
        dwBorderStyle &= ~CBRS_BORDER_BOTTOM;
        dwBorderStyle &= ~CBRS_BORDER_LEFT;

        lpncsp->rgrc[0].bottom -= nEdge;
		lpncsp->rgrc [0].left += nGripperSize - 4;

        m_rectBorder.top = m_rectBorder.bottom - nEdge;
		m_rectGripper.right = m_rectGripper.left + nGripperSize;
		m_rectGripper.bottom = m_rectBorder.top - 1;

		m_rectClose = m_rectGripper;
		m_rectClose.bottom = m_rectClose.top + m_rectClose.Width ();
		m_rectClose.DeflateRect (5, 5);
		m_rectClose.OffsetRect (1, -2);
		m_rectGripper.bottom -= 4;
		m_rectGripper.top = m_rectClose.bottom + 3;

		m_rectBorder.InflateRect (2, 0);
        break;

    case AFX_IDW_DOCKBAR_BOTTOM:
        dwBorderStyle &= ~CBRS_BORDER_TOP;
        dwBorderStyle &= ~CBRS_BORDER_LEFT;

        lpncsp->rgrc[0].top += nEdge;
		lpncsp->rgrc [0].left += nGripperSize - 4;

        m_rectBorder.bottom = m_rectBorder.top + nEdge;
		m_rectGripper.right = m_rectGripper.left + nGripperSize;
		m_rectGripper.top = m_rectBorder.bottom + 1;

		m_rectClose = m_rectGripper;
		m_rectClose.bottom = m_rectClose.top + m_rectClose.Width ();
		m_rectClose.DeflateRect (5, 5);
		m_rectClose.OffsetRect (1, -2);
		m_rectGripper.bottom -= 4;
		m_rectGripper.top = m_rectClose.bottom + 3;

		m_rectBorder.InflateRect (2, 0);
        break;

    case AFX_IDW_DOCKBAR_LEFT:
        dwBorderStyle &= ~CBRS_BORDER_RIGHT;
		dwBorderStyle &= ~CBRS_BORDER_TOP;

        lpncsp->rgrc[0].right -= nEdge;
		lpncsp->rgrc [0].top += nGripperSize;

        m_rectBorder.left = m_rectBorder.right - nEdge;
		m_rectGripper.bottom = m_rectGripper.top + nGripperSize;
		m_rectGripper.right = m_rectBorder.left - 1;

		m_rectClose = m_rectGripper;
		m_rectClose.left = m_rectClose.right - m_rectClose.Height ();
		m_rectClose.DeflateRect (5, 5);
		m_rectClose.OffsetRect (2, 2);
		m_rectGripper.left += 4;
		m_rectGripper.right = m_rectClose.left - 3;

		m_rectBorder.InflateRect (0, 2);
        break;

    case AFX_IDW_DOCKBAR_RIGHT:
        dwBorderStyle &= ~CBRS_BORDER_LEFT;
		dwBorderStyle &= ~CBRS_BORDER_TOP;

        lpncsp->rgrc[0].left += nEdge;
		lpncsp->rgrc [0].top += nGripperSize;

        m_rectBorder.right = m_rectBorder.left + nEdge;
		m_rectGripper.bottom = m_rectGripper.top + nGripperSize;
		m_rectGripper.left = m_rectBorder.right + 1;

		m_rectClose = m_rectGripper;
		m_rectClose.left = m_rectClose.right - m_rectClose.Height ();
		m_rectClose.DeflateRect (5, 5);
		m_rectClose.OffsetRect (2, 2);
		m_rectGripper.left += 4;
		m_rectGripper.right = m_rectClose.left - 3;

		m_rectBorder.InflateRect (0, 2);
        break;

    default:
        m_rectBorder.SetRectEmpty ();
		m_rectGripper.SetRectEmpty ();
		m_rectClose.SetRectEmpty ();
        break;
    }

    SetBarStyle (m_dwStyle);
}

void CBCGDockBar::OnNcPaint() 
{
    EraseNonClient();

    CDC *pDC = GetWindowDC();

	CRect rectBorder = m_rectBorder;
    pDC->Draw3dRect(rectBorder, GetSysColor(COLOR_3DLIGHT),
                    GetSysColor (COLOR_3DDKSHADOW));

	rectBorder.InflateRect (-1, -1);
    pDC->Draw3dRect(rectBorder, GetSysColor(COLOR_3DHILIGHT),
                    GetSysColor(COLOR_3DSHADOW));

	CRect rectClient;
	GetClientRect (&rectClient);

	//--------------
	// Draw gripper:
	//--------------
	const int iLinesNum = 2;

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE;
	CRect rectGripper = m_rectGripper;
	CRect rectClose = m_rectGripper;
	
	if (bHorz)
	{
		//-----------------
		// Gripper at left:
		//-----------------
		const int iLineWidth = 3;
		rectGripper.left += rectGripper.Width () / 2 - iLineWidth + 1;
		rectGripper.right = rectGripper.left + iLineWidth;

		for (int i = 0; i < iLinesNum; i ++)
		{
			pDC->Draw3dRect (rectGripper,
							::GetSysColor(COLOR_BTNHIGHLIGHT),
							::GetSysColor(COLOR_BTNSHADOW));
			rectGripper.OffsetRect (iLineWidth + 1, 0);
		}
	} 
	else 
	{
		//----------------
		// Gripper at top:
		//----------------
		const int iLineHeight = 3;
		rectGripper.top += rectGripper.Height () / 2 - iLineHeight + 1;
		rectGripper.bottom = rectGripper.top + iLineHeight;

		for (int i = 0; i < iLinesNum; i ++)
		{
			pDC->Draw3dRect (rectGripper,
							::GetSysColor(COLOR_BTNHIGHLIGHT),
							::GetSysColor(COLOR_BTNSHADOW));
			rectGripper.OffsetRect (0, iLineHeight + 1);
		}
	}

	// Draw close button:
	UINT uiState = DFCS_CAPTIONCLOSE;
	if (m_bClosePressed && m_bCloseFocused)
	{
		uiState |= DFCS_PUSHED;
	}
	pDC->DrawFrameControl (m_rectClose, DFC_CAPTION, uiState);

    ReleaseDC (pDC);
}

void CBCGDockBar::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
    if (m_bTracking) return;

	if (nHitTest == HTCLOSE)
	{
		m_bClosePressed = TRUE;
		m_bCloseFocused = TRUE;
		RedrawWindow (m_rectClose, NULL, 
			RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME);
		SetCapture ();
		return;
	}

    if ((nHitTest == HTSIZE) && !IsFloating())
        StartTracking();
    else    
        CControlBar::OnNcLButtonDown(nHitTest, point);
}

UINT CBCGDockBar::OnNcHitTest(CPoint point) 
{
    if (IsFloating())
        return CControlBar::OnNcHitTest(point);

    CRect rc;
    GetWindowRect(rc);
    point.Offset(-rc.left, -rc.top);

	UINT uiHit;
    if (m_rectBorder.PtInRect(point))
	{
        uiHit = HTSIZE;
	}
    else if (m_rectClose.PtInRect(point))
	{
		uiHit = HTCLOSE;
	}
	else
	{
        uiHit = HTCLIENT;
	}

	return uiHit;
}

void CBCGDockBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // only start dragging if clicked in "void" space
    if (m_pDockBar != NULL)
    {
        // start the drag
        ASSERT(m_pDockContext != NULL);
        ClientToScreen(&point);
        m_pDockContext->StartDrag(point);
    }
    else
    {
        CWnd::OnLButtonDown(nFlags, point);
    }
}

void CBCGDockBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    // only toggle docking if clicked in "void" space
    if (m_pDockBar != NULL)
    {
        // toggle docking
        ASSERT(m_pDockContext != NULL);
        m_pDockContext->ToggleDocking();
    }
    else
    {
        CWnd::OnLButtonDblClk(nFlags, point);
    }
}

void CBCGDockBar::StartTracking()
{
    SetCapture();
	SetFocus ();

    // make sure no updates are pending
    RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);
    m_pDockSite->LockWindowUpdate();

    m_ptOld = m_rectBorder.CenterPoint();
    m_bTracking = TRUE;
    
    m_rectTracker = m_rectBorder;
    if (!IsHorz()) m_rectTracker.bottom -= 4;

    OnInvertTracker(m_rectTracker);
}

void CBCGDockBar::OnCaptureChanged(CWnd *pWnd) 
{
    if (m_bTracking && pWnd != this)
        StopTracking(FALSE); // cancel tracking

    CControlBar::OnCaptureChanged(pWnd);
}

void CBCGDockBar::StopTracking(BOOL bAccept)
{
    OnInvertTracker(m_rectTracker);
    m_pDockSite->UnlockWindowUpdate();
    m_bTracking = FALSE;
    ReleaseCapture();
    
    if (!bAccept) return;

    int maxsize, minsize, newsize;
    CRect rcc;
    m_pDockSite->GetClientRect(rcc);

    newsize = IsHorz() ? m_sizeHorz.cy : m_sizeVert.cx;
    maxsize = newsize + (IsHorz() ? rcc.Height() : rcc.Width());
    minsize = IsHorz() ? m_sizeMin.cy : m_sizeMin.cx;

    CPoint point = m_rectTracker.CenterPoint();
    switch (m_nDockBarID)
    {
    case AFX_IDW_DOCKBAR_TOP:
        newsize += point.y - m_ptOld.y; break;
    case AFX_IDW_DOCKBAR_BOTTOM:
        newsize += -point.y + m_ptOld.y; break;
    case AFX_IDW_DOCKBAR_LEFT:
        newsize += point.x - m_ptOld.x; break;
    case AFX_IDW_DOCKBAR_RIGHT:
        newsize += -point.x + m_ptOld.x; break;
    }

    newsize = max(minsize, min(maxsize, newsize));

    if (IsHorz())
        m_sizeHorz.cy = newsize;
    else
        m_sizeVert.cx = newsize;

    m_pDockSite->DelayRecalcLayout();
}

void CBCGDockBar::OnInvertTracker(const CRect& rect)
{
    ASSERT_VALID(this);
    ASSERT(!rect.IsRectEmpty());
    ASSERT(m_bTracking);

    CRect rct = rect, rcc, rcf;
    GetWindowRect(rcc);
    m_pDockSite->GetWindowRect(rcf);

    rct.OffsetRect(rcc.left - rcf.left, rcc.top - rcf.top);
    rct.DeflateRect(1, 1);

    CDC *pDC = m_pDockSite->GetDCEx(NULL,
        DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);

    CBrush* pBrush = CDC::GetHalftoneBrush();
    HBRUSH hOldBrush = NULL;
    if (pBrush != NULL)
        hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);

    pDC->PatBlt(rct.left, rct.top, rct.Width(), rct.Height(), PATINVERT);

    if (hOldBrush != NULL)
        SelectObject(pDC->m_hDC, hOldBrush);

    m_pDockSite->ReleaseDC(pDC);
}

BOOL CBCGDockBar::IsHorz() const
{
    return (m_nDockBarID == AFX_IDW_DOCKBAR_TOP ||
        m_nDockBarID == AFX_IDW_DOCKBAR_BOTTOM);
}

CPoint& CBCGDockBar::ClientToWnd(CPoint& point)
{
    switch(m_nDockBarID)
    {
    case AFX_IDW_DOCKBAR_TOP:
		point.x += nGripperSize;
        break;

    case AFX_IDW_DOCKBAR_BOTTOM:
        point.y += nEdge;
		point.x += nGripperSize;
        break;

    case AFX_IDW_DOCKBAR_LEFT:
		point.y += nGripperSize;
        break;

    case AFX_IDW_DOCKBAR_RIGHT:
        point.x += nEdge;
		point.y += nGripperSize;
        break;
    }

    return point;
}

int CBCGDockBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_hcurHorzSize = AfxGetApp ()->LoadCursor (AFX_IDC_HSPLITBAR);
	m_hcurVertSize = AfxGetApp ()->LoadCursor (AFX_IDC_VSPLITBAR);
	
	return 0;
}

void CBCGDockBar::OnDestroy() 
{
	::DeleteObject (m_hcurHorzSize);
	::DeleteObject (m_hcurVertSize);

	CControlBar::OnDestroy();
}
//*******************************************************************
void CBCGDockBar::OnCancelMode() 
{
	if (m_bTracking)
	{
		StopTracking (FALSE);
	}
	else if (m_bClosePressed)
	{
		if (GetCapture () == this)
		{
			ReleaseCapture ();
		}

		m_bClosePressed = FALSE;
		m_bCloseFocused = FALSE;

		RedrawWindow (m_rectClose, NULL,
			RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME);
	}

	CControlBar::OnCancelMode();
}
//******************************************************************
BOOL CBCGDockBar::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_ESCAPE &&
		m_bTracking)
	{
		StopTracking (FALSE);
		::ShowCursor (TRUE);
	}

	return CControlBar::PreTranslateMessage(pMsg);
}
//******************************************************************
void CBCGDockBar::DoPaint(CDC* /*pDC*/)
{
	// Prevent border drawing
}
//******************************************************************
void CBCGDockBar::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	CControlBar::OnNcLButtonUp(nHitTest, point);

}
