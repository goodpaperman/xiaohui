/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/20/98 3:21:25 PM
  Comments: SheetListCtrl.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "SheetListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSheetListCtrl
// Function name	: CSheetListCtrl::CSheetListCtrl
// Description	    : Default constructor of this object
// Return type		: 
CSheetListCtrl::CSheetListCtrl()
{
	m_nInsideCalc = -1;
}

// Function name	: CSheetListCtrl::~CSheetListCtrl
// Description	    : Destructor of this object
// Return type		: 
CSheetListCtrl::~CSheetListCtrl()
{
}


BEGIN_MESSAGE_MAP(CSheetListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSheetListCtrl)
	ON_WM_NCCALCSIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSheetListCtrl message handlers

// Function name	: CSheetListCtrl::OnNcCalcSize
// Description	    : When WM_NCCALCSIZE occurs, then horisontal scroll of scroll must be removed
// Return type		: void 
// Argument         : BOOL bCalcValidRects
// Argument         : NCCALCSIZE_PARAMS FAR* lpncsp
void CSheetListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	if (++m_nInsideCalc == 0)
	{
		ModifyStyle(WS_HSCROLL, 0, SWP_NOREDRAW | SWP_NOSENDCHANGING);
		CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
		ActivateScrollBar();
	}
	m_nInsideCalc--;
}

// Function name	: CSheetListCtrl::SubclassWindow
// Description	    : Call this member function to "dynamically subclass" a window and attach it to this CWnd object
// !Do not call PreSubclassWindow virtual function, because a control which is about subclassed
// !do not set already GWL_WNDPROC style. Call instead SubclassWindow(GetDlgItem(ID)->m_hWnd)
// Return type		: BOOL 
// Argument         : HWND hWnd
BOOL CSheetListCtrl::SubclassWindow( HWND hWnd )
{
	BOOL bResult = CListCtrl::SubclassWindow(hWnd);

	if (bResult && !m_wndSheet.GetSafeHwnd())
	{
		ModifyStyle(0, WS_CLIPCHILDREN);
		m_wndSheet.Attach(this);
		m_wndSheet.SetWindowPos(&CWnd::wndTop,0,0,0,0, SWP_NOSIZE | SWP_NOMOVE);
	}
	return bResult;
}

// Function name	: CSheetListCtrl::SumWidthColumns
// Description	    : Return the total width of columns. Required in NeedScroll.
// Return type		: int 
int CSheetListCtrl::SumWidthColumns()
{
	int result = 0;
	LV_COLUMN column; column.mask = LVCF_WIDTH;
	for (int i = 0; GetColumn(i, &column); i++)
		result += column.cx;
	return result;
}

// Function name	: CSheetListCtrl::NeedScroll
// Description	    : Return TRUE if control need scroll bar
// Return type		: BOOL 
BOOL CSheetListCtrl::NeedScroll()
{
	CRect rect; GetClientRect(rect);
	return rect.Width() < SumWidthColumns() - 1;
}

// Function name	: CSheetListCtrl::OnNotify
// Description	    : Overwrite this function for intercept any changes in header of control
// Return type		: BOOL 
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
// Argument         : LRESULT* pResult
BOOL CSheetListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	ActivateScrollBar();
	
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

// Function name	: CSheetListCtrl::ActivateScrollBar
// Description	    : If necessarly, scroll will be appear
// Return type		: void 
void CSheetListCtrl::ActivateScrollBar()
{
	BOOL bShow = NeedScroll();
	m_wndSheet.ShowScrollBar(bShow);
	if (bShow)
	{
		CRect rect; GetClientRect(rect);
		m_wndSheet.GetScrollBar().SetScrollRange(0, SumWidthColumns() - rect.Width());
	}
}
