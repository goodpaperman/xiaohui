// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "sdal.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_NOTIFY(NM_CLICK, IDC_LINETREE, OnClickLinetree)
	ON_NOTIFY(NM_DBLCLK, IDC_LINETREE, OnDblclkLinetree)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// extra dialogbar
	if (!CreateLinesBar())
		return -1;

	return 0;
}

BOOL CMainFrame::CreateLinesBar()
{
	CImageList			*pImagelist;
	CImageList			*pStateImagelist;
	TV_INSERTSTRUCT TreeCtrlItem;

	if (!m_wndDlgBar.Create(this, IDD_LINESELECT,
		CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY, IDD_LINESELECT))
	{
		TRACE0("Failed to create DlgBar\n");
		return FALSE;      // fail to create
	}
	
	CTreeCtrl *Property;
	Property = (CTreeCtrl *)m_wndDlgBar.GetDlgItem( IDC_LINETREE );
	if (Property == NULL)
		return FALSE;

	// Initialize Tree...
	pImagelist = new CImageList();
	pImagelist->Create(IDB_FILE, 16, 4, RGB(255, 0, 0));
	pStateImagelist = new CImageList();
	pStateImagelist->Create(IDB_STATE, 16, 4, RGB(255, 255, 0));

	Property->SetImageList(pImagelist, TVSIL_NORMAL);
	Property->SetImageList(pStateImagelist, TVSIL_STATE);

	// add branches...
	TreeCtrlItem.hParent = TVI_ROOT;
	TreeCtrlItem.hInsertAfter = TVI_LAST;
	TreeCtrlItem.item.iImage = 4;
	TreeCtrlItem.item.iSelectedImage = 5;

	TreeCtrlItem.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	TreeCtrlItem.item.pszText = "BHN710";
	TreeCtrlItem.item.lParam = 0;
	HTREEITEM hTreeItem1 = Property->InsertItem(&TreeCtrlItem);

	TreeCtrlItem.hParent = hTreeItem1;
	TreeCtrlItem.item.pszText = "Postion";
	TreeCtrlItem.item.lParam = 1;
	TreeCtrlItem.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_STATE;
	TreeCtrlItem.item.state |= TVIS_STATEIMAGEMASK;
	TreeCtrlItem.item.stateMask = INDEXTOSTATEIMAGEMASK(2);
	Property->InsertItem(&TreeCtrlItem);

	TreeCtrlItem.hParent = hTreeItem1;
	TreeCtrlItem.item.pszText = "Postion2";
	TreeCtrlItem.item.lParam = 1;
	Property->InsertItem(&TreeCtrlItem);

	Property->Expand(hTreeItem1,TVE_EXPAND);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClickLinetree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_HITTESTINFO	TvInfo;
	HTREEITEM 	Item;
	UINT x;
	CTreeCtrl *Property;
	CRect	treerect;
	TV_ITEM	 TvItem;
	DWORD pos = GetMessagePos();
	Property = (CTreeCtrl *)m_wndDlgBar.GetDlgItem( IDC_LINETREE );
	if (Property == NULL)
		return;
	Property->GetWindowRect(&treerect);

	CPoint p;
	GetCursorPos(&p);
	Property->ScreenToClient(&p);


	CPoint pt(LOWORD(pos) - treerect.left, HIWORD(pos) - treerect.top);
	TvInfo.pt = pt;

	// TODO: Add your control notification handler code here
	Property->HitTest(&TvInfo);
	x = TVHT_ONITEMSTATEICON;
	if (TvInfo.flags & TVHT_ONITEMSTATEICON) 
	{

		Item = TvInfo.hItem;
		TvItem.hItem = TvInfo.hItem;
		TvItem.lParam = 1;
		Property->GetItem(&TvItem);
		TvItem.stateMask = INDEXTOSTATEIMAGEMASK(3);
		Property = (CTreeCtrl *)m_wndDlgBar.GetDlgItem( IDC_LINETREE );

		Property->SetItem(&TvItem);
	}
	UpdateData(FALSE);

	*pResult = 0;
}

void CMainFrame::OnDblclkLinetree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	TV_HITTESTINFO	TvInfo;
	HTREEITEM 	Item;
	UINT x;
	CTreeCtrl *Property;
	Property = (CTreeCtrl *)m_wndDlgBar.GetDlgItem( IDC_LINETREE );
	if (Property == NULL)
		return;

	// TODO: Add your control notification handler code here
	Property->HitTest(&TvInfo);
	x = TVHT_ONITEMSTATEICON;
	if (TvInfo.flags & TVHT_ONITEMSTATEICON) 
	{
		Item = TvInfo.hItem;
	}
	
	CMDIFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainFrame::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CMDIFrameWnd::OnLButtonDblClk(nFlags, point);
}
