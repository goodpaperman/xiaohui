// NCtrlSizeBar.cpp : implementation file
//

#include "stdafx.h"
#include "NGenericDockBar.h"
#include "NCtrlSizeBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListControlBar
//
// This is a sizeable control bar that has a list box on it.
// It is designed to be created dynamically ie you can have more than one 
// of them.

#define IDC_LIST_CONTROL			100

IMPLEMENT_DYNAMIC(CListControlBar, CNGenericDockBar);

CListControlBar::CListControlBar() 
{
}

CListControlBar::~CListControlBar()
{
}

BEGIN_MESSAGE_MAP(CListControlBar, CNGenericDockBar)
	//{{AFX_MSG_MAP(CListControlBar)
	ON_WM_CREATE()
	ON_WM_RBUTTONUP()

	ON_NOTIFY(NM_CLICK, IDC_LIST_CONTROL, OnClickListControl)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONTROL, OnDblclkListControl)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST_CONTROL, OnKillfocusListControl)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_LIST_CONTROL, OnOutofmemoryListControl)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONTROL, OnRclickListControl)
	ON_NOTIFY(NM_RDBLCLK, IDC_LIST_CONTROL, OnRdblclkListControl)
	ON_NOTIFY(NM_RETURN, IDC_LIST_CONTROL, OnReturnListControl)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_CONTROL, OnSetfocusListControl)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST_CONTROL, OnBegindragListControl)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_CONTROL, OnBeginlabeleditListControl)
	ON_NOTIFY(LVN_BEGINRDRAG, IDC_LIST_CONTROL, OnBeginrdragListControl)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CONTROL, OnColumnclickListControl)
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_LIST_CONTROL, OnDeleteallitemsListControl)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_CONTROL, OnDeleteitemListControl)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_CONTROL, OnEndlabeleditListControl)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_CONTROL, OnGetdispinfoListControl)
	ON_NOTIFY(LVN_INSERTITEM, IDC_LIST_CONTROL, OnInsertitemListControl)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CONTROL, OnItemchangedListControl)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_CONTROL, OnItemchangingListControl)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CONTROL, OnKeydownListControl)
	ON_NOTIFY(LVN_SETDISPINFO, IDC_LIST_CONTROL, OnSetdispinfoListControl)
	ON_NOTIFY(HDN_ITEMCHANGED, IDC_LIST_CONTROL, OnItemchangedListControl)
	ON_NOTIFY(HDN_ITEMCHANGING, IDC_LIST_CONTROL, OnItemchangingListControl)
	ON_NOTIFY(HDN_TRACK, IDC_LIST_CONTROL, OnTrackListControl)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST_CONTROL, OnItemclickListControl)
	ON_NOTIFY(HDN_ITEMDBLCLICK, IDC_LIST_CONTROL, OnItemdblclickListControl)
	ON_NOTIFY(HDN_BEGINTRACK, IDC_LIST_CONTROL, OnBegintrackListControl)
	ON_NOTIFY(HDN_ENDTRACK, IDC_LIST_CONTROL, OnEndtrackListControl)
	ON_NOTIFY(HDN_DIVIDERDBLCLICK, IDC_LIST_CONTROL, OnDividerdblclickListControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CListControlBar message handlers


//-------------------------------------------------------------------
int CListControlBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//-------------------------------------------------------------------
{
	if (CNGenericDockBar::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	CRect rect;
	GetClientRect(&rect);
	
	// create a list box to fill the client area with. Use CreateEx to add the
	// WS_EX_CLIENTEDGE style. 
	if (!m_ListCtrl.Create (LVS_ALIGNLEFT , rect , this , IDC_LIST_CONTROL))
	{
		TRACE(_T("Failed to create list Control\n"));
		return -1;
	}
	
	m_ListCtrl.ModifyStyle (0 , WS_BORDER | WS_CHILD | WS_VISIBLE);
	m_ListCtrl.ModifyStyleEx (0 , WS_EX_CLIENTEDGE);
	
	return 0;					
}


void CListControlBar::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// disable docking.
	CNGenericDockBar::OnRButtonUp(nFlags, point);
}

void CListControlBar::OnClickListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ClickListControl(pNMHDR);
	
	*pResult = 0;
}
void CListControlBar::ClickListControl(NMHDR* pNMHDR)
{
}
void CListControlBar::OnDblclkListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DblclkListControl(pNMHDR);
	
	*pResult = 0;
}
void CListControlBar::DblclkListControl(NMHDR* pNMHDR)
{
}
void CListControlBar::OnKillfocusListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	KillfocusListControl(pNMHDR);
	
	*pResult = 0;
}
void CListControlBar::KillfocusListControl(NMHDR* pNMHDR)
{
}
void CListControlBar::OnOutofmemoryListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OutofmemoryListControl(pNMHDR);
	
	*pResult = 0;
}
void CListControlBar::OutofmemoryListControl(NMHDR* pNMHDR)
{
}
void CListControlBar::OnRclickListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	RclickListControl(pNMHDR);
	
	*pResult = 0;
}
void CListControlBar::RclickListControl(NMHDR* pNMHDR)
{
}
void CListControlBar::OnRdblclkListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	RdblclkListControl(pNMHDR);
	
	*pResult = 0;
}
void CListControlBar::RdblclkListControl(NMHDR* pNMHDR)
{
}
void CListControlBar::OnReturnListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ReturnListControl(pNMHDR);
	
	*pResult = 0;
}
void CListControlBar::ReturnListControl(NMHDR* pNMHDR)
{
}
void CListControlBar::OnSetfocusListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SetfocusListControl(pNMHDR);
	
	*pResult = 0;
}
void CListControlBar::SetfocusListControl(NMHDR* pNMHDR)
{
}
void CListControlBar::OnBegindragListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	BegindragListControl(pNMListView);
	
	*pResult = 0;
}
void CListControlBar::BegindragListControl(NM_LISTVIEW* pNMListView)
{
}
void CListControlBar::OnBeginlabeleditListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	BeginlabeleditListControl(pDispInfo);
	
	*pResult = 0;
}
void CListControlBar::BeginlabeleditListControl(LV_DISPINFO* pDispInfo)
{
}
void CListControlBar::OnBeginrdragListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	BeginrdragListControl(pNMListView);
	
	*pResult = 0;
}
void CListControlBar::BeginrdragListControl(NM_LISTVIEW* pNMListView)
{
}
void CListControlBar::OnColumnclickListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	ColumnclickListControl(pNMListView);
	
	*pResult = 0;
}
void CListControlBar::ColumnclickListControl(NM_LISTVIEW* pNMListView)
{
}
void CListControlBar::OnDeleteallitemsListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	DeleteallitemsListControl(pNMListView);
	
	*pResult = 0;
}
void CListControlBar::DeleteallitemsListControl(NM_LISTVIEW* pNMListView)
{
}
void CListControlBar::OnDeleteitemListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	DeleteitemListControl(pNMListView);
	
	*pResult = 0;
}
void CListControlBar::DeleteitemListControl(NM_LISTVIEW* pNMListView)
{
}
void CListControlBar::OnEndlabeleditListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	EndlabeleditListControl(pDispInfo);
	
	*pResult = 0;
}
void CListControlBar::EndlabeleditListControl(LV_DISPINFO* pDispInfo)
{
}
void CListControlBar::OnGetdispinfoListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	GetdispinfoListControl(pDispInfo);
	
	*pResult = 0;
}
void CListControlBar::GetdispinfoListControl(LV_DISPINFO* pDispInfo)
{
}
void CListControlBar::OnInsertitemListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	InsertitemListControl(pNMListView);
	
	*pResult = 0;
}
void CListControlBar::InsertitemListControl(NM_LISTVIEW* pNMListView)
{
}
void CListControlBar::OnItemchangedListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	ItemchangedListControl(pNMListView);
	
	*pResult = 0;
}
void CListControlBar::ItemchangedListControl(NM_LISTVIEW* pNMListView)
{
}
void CListControlBar::OnItemchangingListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	ItemchangingListControl(pNMListView);
	
	*pResult = 0;
}
void CListControlBar::ItemchangingListControl(NM_LISTVIEW* pNMListView)
{
}
void CListControlBar::OnKeydownListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	KeydownListControl(pLVKeyDow);
	
	*pResult = 0;
}
void CListControlBar::KeydownListControl(LV_KEYDOWN* pLVKeyDow)
{
}
void CListControlBar::OnSetdispinfoListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	SetdispinfoListControl(pDispInfo);
	
	*pResult = 0;
}
void CListControlBar::SetdispinfoListControl(LV_DISPINFO* pDispInfo)
{
}
void CListControlBar::OnTrackListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	TrackListControl(phdn);
	
	*pResult = 0;
}
void CListControlBar::TrackListControl(HD_NOTIFY *phdn)
{
}
void CListControlBar::OnItemclickListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	ItemclickListControl(phdn);
	
	*pResult = 0;
}
void CListControlBar::ItemclickListControl(HD_NOTIFY *phdn)
{
}
void CListControlBar::OnItemdblclickListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	ItemdblclickListControl(phdn);
	
	*pResult = 0;
}
void CListControlBar::ItemdblclickListControl(HD_NOTIFY *phdn)
{
}
void CListControlBar::OnBegintrackListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	BegintrackListControl(phdn);
	
	*pResult = 0;
}
void CListControlBar::BegintrackListControl(HD_NOTIFY *phdn)
{
}
void CListControlBar::OnEndtrackListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	EndtrackListControl(phdn);
	
	*pResult = 0;
}
void CListControlBar::EndtrackListControl(HD_NOTIFY *phdn)
{
}
void CListControlBar::OnDividerdblclickListControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	DividerdblclickListControl(phdn);
	
	*pResult = 0;
}
void CListControlBar::DividerdblclickListControl(HD_NOTIFY *phdn)
{
}
/*
CSize CListControlBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	DWORD dwMode = LM_STRETCH;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout(dwMode);
}

*/