// TreeListView.cpp : implementation of the CTreeListView class
//

#include "stdafx.h"
#include "TLView.h"
#include "MainFrm.h"

#include "TreeListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeListView

IMPLEMENT_DYNCREATE(CTreeListView, CFormView)

BEGIN_MESSAGE_MAP(CTreeListView, CFormView)
	//{{AFX_MSG_MAP(CTreeListView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListView construction/destruction

CTreeListView::CTreeListView()
	: CFormView(CTreeListView::IDD)
{
	// TODO: add construction code here
	m_TLInitialized = FALSE;
}

CTreeListView::~CTreeListView()
{
}

void CTreeListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CTreeListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListView printing

BOOL CTreeListView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTreeListView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTreeListView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListView diagnostics

#ifdef _DEBUG
void CTreeListView::AssertValid() const
{
	CView::AssertValid();
}

void CTreeListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

//CLantivUIDoc* CTreeListView::GetDocument() // non-debug version is inline
//{
//    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLantivUIDoc)));
//    return (CLantivUIDoc*)m_pDocument;
//}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeListView message handlers

void CTreeListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}

void CTreeListView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_wndTreeList.SubclassDlgItem(IDC_TREELIST, this);

	m_cImageList.Create(IDB_DOCS_IMAGES, 16, 15, RGB(255, 255, 255));
	m_wndTreeList.m_tree.SetImageList(&m_cImageList, TVSIL_NORMAL);

	CRect m_wndRect;
	GetClientRect(&m_wndRect);
	m_wndTreeList.MoveWindow(0, 0, m_wndRect.Width(), m_wndRect.Height());

	// insert a few items for demonstration
	{
		m_wndTreeList.m_tree.InsertColumn(0, "From", LVCFMT_LEFT, 150);
		m_wndTreeList.m_tree.InsertColumn(1, "Subject", LVCFMT_LEFT, 250);
		m_wndTreeList.m_tree.InsertColumn(2, "Received", LVCFMT_RIGHT, 100);

		HTREEITEM hTmp = m_wndTreeList.m_tree.InsertItem("David Lantsman", 0, 0);
		m_wndTreeList.m_tree.SetItemText(hTmp, 1, "User interface");
		m_wndTreeList.m_tree.SetItemText(hTmp, 2, "1/1/98");
		hTmp = m_wndTreeList.m_tree.InsertItem("David Lantsman1", 0, 0, hTmp);
		m_wndTreeList.m_tree.SetItemText(hTmp, 1, "Re: User interface (hmm.. why am I replying to myself?)");
		m_wndTreeList.m_tree.SetItemText(hTmp, 2, "1/2/98");
		hTmp = m_wndTreeList.m_tree.InsertItem("David Lantsman2", 0, 0, hTmp);
		m_wndTreeList.m_tree.SetItemText(hTmp, 1, "Re: User interface (hmm.. why am I replying to myself???)");
		m_wndTreeList.m_tree.SetItemText(hTmp, 2, "1/3/98");
		hTmp = m_wndTreeList.m_tree.InsertItem("David Lantsman3", 0, 0, hTmp);
		m_wndTreeList.m_tree.SetItemText(hTmp, 1, "Re: User interface (hmm.. why am I replying to myself??)");
		m_wndTreeList.m_tree.SetItemText(hTmp, 2, "1/4/98");
		hTmp = m_wndTreeList.m_tree.InsertItem("David Lantsman4", 0, 0, hTmp);
		m_wndTreeList.m_tree.SetItemText(hTmp, 1, "Re: User interface (hmm.. why am I replying to myself????)");
		m_wndTreeList.m_tree.SetItemText(hTmp, 2, "1/5/98");
		hTmp = m_wndTreeList.m_tree.InsertItem("David6 Lantsman", 1, 1);
		m_wndTreeList.m_tree.SetItemText(hTmp, 1, "This is a TreeList!!");
		m_wndTreeList.m_tree.SetItemText(hTmp, 2, "1/6/98");
		m_wndTreeList.m_tree.SetItemBold(hTmp);
		hTmp = m_wndTreeList.m_tree.InsertItem("David5 Lantsman", 1, 1);
		m_wndTreeList.m_tree.SetItemText(hTmp, 1, "My Email: davidlan@luckynet.co.il");
		m_wndTreeList.m_tree.SetItemText(hTmp, 2, "1/7/98");
		m_wndTreeList.m_tree.SetItemBold(hTmp);
	}

	m_TLInitialized = TRUE;
}

void CTreeListView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	SetScrollRange(SB_HORZ, 0, 0);
	SetScrollRange(SB_VERT, 0, 0);

	if(m_TLInitialized)
		m_wndTreeList.MoveWindow(0, 0, cx, cy);
}
