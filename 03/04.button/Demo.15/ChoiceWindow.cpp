// ChoiceWindow.cpp : implementation file
//

#include "stdafx.h"
#include "dropdownboxdlg.h"
#include "ChoiceWindow.h"
#include "ChoiceWindowBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoiceWindow

#define IDW_LISTVIEW 1001

CChoiceWindow::CChoiceWindow()
{
}

CChoiceWindow::~CChoiceWindow()
{
}


BEGIN_MESSAGE_MAP(CChoiceWindow, CWnd)
	//{{AFX_MSG_MAP(CChoiceWindow)
	ON_NOTIFY(LVN_KEYDOWN, IDW_LISTVIEW,OnListviewKeydown)
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_NOTIFY( NM_KILLFOCUS, IDW_LISTVIEW, OnKillFocusListView )
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChoiceWindow message handlers

void CChoiceWindow::OnKillFocus(CWnd* pNewWnd) 
{
	TRACE("Loosing focus\n");

	CWnd::OnKillFocus(pNewWnd);

	CWnd* pCurrent = CWnd::GetFocus();

	if (pCurrent && ::IsWindow(*pCurrent))
	{
		if (pCurrent->GetParent() == this)
		{
			return;
		}
	}

	HideDropDown();

}

int CChoiceWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the listctrl, but set it's size to null
	VERIFY(m_wndList.Create(WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_NOCOLUMNHEADER, CRect(0, 0, 0, 0), this, IDW_LISTVIEW));
	m_wndList.SetExtendedStyle(LVS_EX_CHECKBOXES);

	// Insert column - set the width to 0
	m_wndList.InsertColumn(0, "", LVCFMT_LEFT, 0);

	UpdateSizeAndPosition();


	return 0;
}

void CChoiceWindow::OnKillFocusListView(NMHDR *pNMHDR, LRESULT *pResult)
{
	TRACE("OnKillFocusListView()\n");
	OnKillFocus(NULL);
}

void CChoiceWindow::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_RETURN || nChar == VK_ESCAPE)
	{
		HideDropDown();
	}
	else
	{
		CWnd::OnChar(nChar, nRepCnt, nFlags);
	}
	
}

void CChoiceWindow::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	m_wndList.SetFocus();
	
}

void CChoiceWindow::OnListviewKeydown(NMHDR* pnmhdr, LRESULT* pResult)
{
	LPNMLVKEYDOWN lpnmkd = LPNMLVKEYDOWN(pnmhdr);

	OnChar(lpnmkd->wVKey, 0, lpnmkd->flags);

	*pResult = 0;
}

void CChoiceWindow::HideDropDown()
{
	// Put the status of the checked items back into the button 
	for (int i=0  ; i<m_pParentBtn->m_choiceArray.GetSize() ; i++)
	{
		CChoiceWindowBtn::CChoice* pChoice = m_pParentBtn->m_choiceArray[i];

		pChoice->bChecked = m_wndList.GetCheck(i);
	}
	
	if (IsWindow(*this))
		ShowWindow(SW_HIDE);	
	
}

void CChoiceWindow::UpdateSizeAndPosition()
{
	CRect rcWindow, rcWndClient;
	CRect rcListClient, rcList, rcItem;
	int iNumberOfItemsInList;

	// Insert items
	iNumberOfItemsInList = m_pParentBtn->m_choiceArray.GetSize();
	ASSERT(iNumberOfItemsInList>0);

	m_wndList.DeleteAllItems();
	for (int i = 0 ; i<iNumberOfItemsInList ; i++)
	{
		CChoiceWindowBtn::CChoice* pChoice = m_pParentBtn->m_choiceArray[i];
		
		m_wndList.InsertItem(i, pChoice->strText);
		m_wndList.SetCheck(i, pChoice->bChecked);
	}
	
	// Calculate the size of the border of the parent window.
	// These numbers will be used to resize the window to fit the list
	// ctrl items. I should use GetSystemMetrics() - but this way I 
	// will not have to change the code if I change the style bit in 
	// CChoiceWindow::Create().
	
	GetClientRect(&rcWndClient);
	GetWindowRect(&rcWindow);
	
	CSize sizeText;
	CDC* pListDC = NULL;
	int iCheckMarkWidth = 0;
	int iListCtrlHeight = 0;
	int iLongestTextItem=0;
	
	// The size of the last item
	m_wndList.GetItemRect(iNumberOfItemsInList - 1, &rcItem, LVIR_BOUNDS);
	iListCtrlHeight = rcItem.bottom;
	
	m_wndList.GetItemRect(0, &rcItem, LVIR_LABEL);
	iCheckMarkWidth = rcItem.left;
	
	// A pointer to the list ctrl CDC
	pListDC = m_wndList.GetDC();
	
	/// Go thru each item and calculate its width - save the widest 
	for (i=0 ; i<iNumberOfItemsInList ; i++)
	{	
		CChoiceWindowBtn::CChoice* pChoice = m_pParentBtn->m_choiceArray[i];
		GetTextExtentPoint32(*pListDC, pChoice->strText, pChoice->strText.GetLength(), &sizeText);
		iLongestTextItem = max(sizeText.cx, iLongestTextItem);
		
	}
	
	// Now Resize the window to the right size - the width should never be 
	// smaller than the button though
	int iFrameWidth, iWidth, iHeight, iButtonWidth;
	CRect rcButton;
	
	// Add the width of the frame as the difference between
	// the client-area and the outer window border
	iFrameWidth = (rcWindow.Width() - rcWndClient.Width())/2;
	
	m_pParentBtn->GetWindowRect(&rcButton);
	
	iWidth  = iLongestTextItem + iCheckMarkWidth + (iFrameWidth*2);
	iHeight = iListCtrlHeight + (iFrameWidth*2);
	iButtonWidth = rcButton.Width();
	
	
	SetWindowPos(NULL, rcButton.left, rcButton.top + rcButton.Height(), max(iWidth, iButtonWidth), iHeight, 0);//SWP_NOMOVE);
	
	// Resize the listctrl to fit the client
	GetClientRect(&rcWndClient);	
	m_wndList.SetWindowPos(NULL, 0, 0, rcWndClient.right, rcWndClient.bottom, SWP_NOMOVE);
	
	// Resize the first column to fit the listctrl client
	m_wndList.GetClientRect(&rcList);
	m_wndList.SetColumnWidth(0, rcList.Width());

}
