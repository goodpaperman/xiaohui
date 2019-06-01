/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 7/22/98 6:01:00 PM
  Comments: FilterListCtrl.cpp: implementation of the CFilterListCtrl class.
 ************************************/

#include "stdafx.h"
#include "FilterListCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define STARTINSIDE int nSaveOutsideValue = m_nOutsideListCtrl; m_nOutsideListCtrl = -1
#define   ENDINSIDE m_nOutsideListCtrl = nSaveOutsideValue

// Function name	: CFilterListCtrl::CFilterListCtrl
// Description	    : Default contructor of this object
// Return type		: 
CFilterListCtrl::CFilterListCtrl(int nFilterColumn)
{
	m_nOutsideListCtrl = 0;
	m_nFilterColumn = 0;
}

// Function name	: CFilterListCtrl::~CFilterListCtrl
// Description	    : Default destructor
// Return type		: 
CFilterListCtrl::~CFilterListCtrl()
{

}

BEGIN_MESSAGE_MAP(CFilterListCtrl, CSheetListCtrl)
	//{{AFX_MSG_MAP(CFilterListCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Function name	: CFilterListCtrl::PreSubclassWindow
// Description	    : 
// Return type		: void 
void CFilterListCtrl::PreSubclassWindow() 
{
	ASSERT (!m_lcAll.GetSafeHwnd());

	m_lcAll.Create(WS_CHILD | GetStyle() & (LVS_SORTASCENDING | LVS_SORTDESCENDING), CRect(0,0,0,0), this, IDLCALL);

	CSheetListCtrl::PreSubclassWindow();
}

// Function name	: CFilterListCtrl::WindowProc
// Description	    : Intercept all messages from outside of this.
// Return type		: LRESULT 
// Argument         : UINT message
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CFilterListCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT lResult = NULL;
	BOOL bCallParent = TRUE;
	if (++m_nOutsideListCtrl)
		switch (message)
		{
			case LVM_INSERTCOLUMN:
			case LVM_DELETECOLUMN:
			case LVM_INSERTITEM:
			case LVM_SETITEM:
			case LVM_GETITEMCOUNT:
			{
				lResult = m_lcAll.SendMessage(message, wParam, lParam);
				bCallParent = (message == LVM_INSERTCOLUMN) || (message ==  LVM_DELETECOLUMN);
				break;
			}
			default:
			{
				if (message == CSheetsWnd::GetMessagePageChanged())
					Fill(CSheetAlpha::TranslateMessage(wParam));
				break;
			}
		}
	m_nOutsideListCtrl--;
	
	if (bCallParent)
		lResult = CSheetListCtrl::WindowProc(message, wParam, lParam);

	return lResult;
}

// Function name	: CFilterListCtrl::Fill
// Description	    : Fill the object will all items that respect condition
// Return type		: void 
// Argument         : LPCTSTR lpszFilter
void CFilterListCtrl::Fill(LPCTSTR lpszFilter)
{
	STARTINSIDE;
		BOOL bVisible = GetStyle() & WS_VISIBLE;
		ModifyStyle(WS_VISIBLE,0, SWP_NOREDRAW);
		DeleteAllItems();
		for (int i = 0; i < m_lcAll.GetItemCount(); i++)
		 if (IsEqual((LPCTSTR)m_lcAll.GetItemText(i,m_nFilterColumn),lpszFilter))
		 {
			 int nItem = InsertItem(GetItemCount(), _T(""));
			 LV_COLUMN column; column.mask = LVCF_WIDTH;
			 for (int j = 0; m_lcAll.GetColumn(j, &column); j++)
				 SetItemText(nItem, j, m_lcAll.GetItemText(i,j));
			 SetItemData(nItem, m_lcAll.GetItemData(i));
		 }
		if (bVisible)
		{
			ModifyStyle(0,WS_VISIBLE, SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_FRAMECHANGED);
			Invalidate(FALSE);
		}
	ENDINSIDE;
}

// Function name	: CFilterListCtrl::IsEqual
// Description	    : Call by object if something must compare
// Return type		: BOOL 
// Argument         : LPCTSTR lpszSource
// Argument         : LPCTSRT lspzDestination
BOOL CFilterListCtrl::IsEqual(LPCTSTR lpszSource, LPCTSTR lspzDestination)
{
	return CString(lpszSource, strlen(lspzDestination)).CompareNoCase(lspzDestination) == 0;
}

// Function name	: CFilterListCtrl::Refresh
// Description	    : Refresh the list
// Return type		: void 
void CFilterListCtrl::Refresh()
{
	if (CWnd* pWnd = m_wndSheet.GetActiveView())
		Fill(m_wndSheet.GetViewTitle(pWnd));
}
