// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "OutBarDemo.h"

#include "MainFrm.h"
#include "GfxOutBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_GFX_LARGEICON, OnGfxLargeicon)
	ON_UPDATE_COMMAND_UI(ID_GFX_LARGEICON, OnUpdateGfxLargeicon)
	ON_COMMAND(ID_GFX_SMALLICON, OnGfxSmallicon)
	ON_UPDATE_COMMAND_UI(ID_GFX_SMALLICON, OnUpdateGfxSmallicon)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_OUTBAR_NOTIFY, OnOutbarNotify)
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
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!wndSplitter.CreateStatic(this, 1, 2)) return false;
	if (!wndSplitter.CreateView(0, 1, pContext->m_pNewViewClass, CSize(0,0), pContext)) return false;

	DWORD dwf = CGfxOutBarCtrl::fDragItems|CGfxOutBarCtrl::fEditGroups|CGfxOutBarCtrl::fEditItems|CGfxOutBarCtrl::fRemoveGroups|
				CGfxOutBarCtrl::fRemoveItems|CGfxOutBarCtrl::fAddGroups|CGfxOutBarCtrl::fAnimation/*|CGfxOutBarCtrl::fSelHighlight*/;

	wndBar.Create(WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), &wndSplitter, wndSplitter.IdFromRowCol(0, 0), dwf);
	wndBar.SetOwner(this);

	imaLarge.Create(IDB_IMAGELIST, 32, 0, RGB(128,128,128));
	imaSmall.Create(IDB_SMALL_IMAGELIST, 16, 0, RGB(0,128,128));

	wndBar.SetImageList(&imaLarge, CGfxOutBarCtrl::fLargeIcon);
	wndBar.SetImageList(&imaSmall, CGfxOutBarCtrl::fSmallIcon);

	wndTree.Create(WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS, CRect(0,0,0,0), &wndBar, 1010);
	wndTree.SetImageList(&imaSmall, TVSIL_NORMAL);

	wndBar.SetAnimationTickCount(20);
	wndBar.SetAnimSelHighlight(200);

	HTREEITEM htm = wndTree.InsertItem("tree 1", 0,0);
	HTREEITEM htm1 = wndTree.InsertItem("tree 2", 1,1, htm);
	wndTree.InsertItem("tree 3", 1,1, htm);

	for (int xx = 0; xx < 30; xx ++)
	{
		htm = wndTree.InsertItem("tree 1", 0,0);
		htm1 = wndTree.InsertItem("tree 2", 1,1, htm);
		wndTree.InsertItem("tree 3", 1,1, htm);

		htm = wndTree.InsertItem("tree 1", 0,0);
		htm1 = wndTree.InsertItem("tree asdasdasdadasdasdasdasdas2", 1,1, htm);
		wndTree.InsertItem("tree 3", 1,1, htm);
	}
	
	wndBar.AddFolder("Folder 1", 0);
	wndBar.AddFolderBar("TreeBar", &wndTree);
	wndBar.AddFolder("Folder 2", 1);
	wndBar.AddFolder("Folder 3", 2);
	wndBar.AddFolder("Folder 4", 3);

	wndBar.InsertItem(0, 0, "Item 1", 0, 0);
	wndBar.InsertItem(0, 1, "Item 2", 1, 0);
	wndBar.InsertItem(0, 2, "Item 3", 2, 0);
	wndBar.InsertItem(0, 3, "Item 4", 3, 0);
	wndBar.InsertItem(0, 4, "Item 5", 4, 0);
	wndBar.InsertItem(0, 5, "Item 6", 5, 0);
	wndBar.InsertItem(0, 6, "Item 7", 6, 0);
	wndBar.InsertItem(0, 7, "Item 8", 0, 0);
	wndBar.InsertItem(0, 8, "Item 9", 1, 0);
	wndBar.InsertItem(0, 9, "Item 10", 2, 0);
	wndBar.InsertItem(0, 10, "Item 11", 3, 0);
	wndBar.InsertItem(0, 11, "Item 12", 4, 0);
	wndBar.InsertItem(0, 12, "Item 13", 5, 0);
	wndBar.InsertItem(0, 13, "Item 14", 6, 0);
	wndBar.InsertItem(0, 14, "Item 15", 0, 0);
	wndBar.InsertItem(0, 15, "Item 16", 1, 0);

	wndBar.InsertItem(0, 16, "Item 17", 2, 0);
	wndBar.InsertItem(0, 17, "Item 18", 3, 0);

	wndBar.InsertItem(2, 0, "Item 1", 0, 0);
	wndBar.InsertItem(2, 1, "Let's see what this Item will become actually 2", 1, 0);
	wndBar.InsertItem(2, 2, "Item 3", 2, 0);
	wndBar.InsertItem(2, 3, "Item 4", 3, 0);

	wndBar.SetSelFolder(0);

	CRect r;
	GetClientRect(&r);

	int w1 = r.Width()/5;
	int w2 = r.Width()/4;

	wndSplitter.SetColumnInfo( 0, w1, w1 );
	wndSplitter.SetColumnInfo( 1, w2, w2 );
	wndSplitter.RecalcLayout();
	return true;
}


long CMainFrame::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case NM_OB_ITEMCLICK:
		// cast the lParam to an integer to get the clicked item
			{
				int index = (int) lParam;
				CString cs, cs1;
				cs1 = wndBar.GetItemText(index);
				cs.Format("Clicked on %d - <%s>", (int)lParam, cs1);
				AfxMessageBox(cs);
			}
		return 0;

		case NM_OB_ONLABELENDEDIT:
		// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the edited item
		// return 1 to do the change and 0 to cancel it
			{
				OUTBAR_INFO * pOI = (OUTBAR_INFO *) lParam;
				TRACE2("Editing item %d, new text:%s\n", pOI->index, pOI->cText);
			}
		return 1;

		case NM_OB_ONGROUPENDEDIT:
		// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the edited folder
		// return 1 to do the change and 0 to cancel it
			{
				OUTBAR_INFO * pOI = (OUTBAR_INFO *) lParam;
				TRACE2("Editing folder %d, new text:%s\n", pOI->index, pOI->cText);
			}
		return 1;

		case NM_OB_DRAGITEM:
		// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the dragged items
		// return 1 to do the change and 0 to cancel it
			{
				OUTBAR_INFO * pOI = (OUTBAR_INFO *) lParam;
				TRACE2("Drag item %d at position %d\n", pOI->iDragFrom, pOI->iDragTo);
			}
		return 1;
        default:
            TRACE("Unknown wParam: %d.\n", wParam); 
            break; 
	}
	return 0;
}

void CMainFrame::OnGfxLargeicon() 
{
	wndBar.SetSmallIconView(false);
}

void CMainFrame::OnUpdateGfxLargeicon(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!wndBar.IsSmallIconView());
}

void CMainFrame::OnGfxSmallicon() 
{
	wndBar.SetSmallIconView(true);
	
}

void CMainFrame::OnUpdateGfxSmallicon(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(wndBar.IsSmallIconView());
}
