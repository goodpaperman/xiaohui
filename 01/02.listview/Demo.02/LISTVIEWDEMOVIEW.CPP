// ListViewDemoView.cpp : implementation of the CListViewDemoView class
//

#include "stdafx.h"
#include "ListViewDemo.h"

#include "ListViewDemoDoc.h"
#include "ListViewDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView

IMPLEMENT_DYNCREATE(CListViewDemoView, CView)

BEGIN_MESSAGE_MAP(CListViewDemoView, CView)
	//{{AFX_MSG_MAP(CListViewDemoView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView construction/destruction

CListViewDemoView::CListViewDemoView()
{
}

CListViewDemoView::~CListViewDemoView()
{
}

BOOL CListViewDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView drawing

void CListViewDemoView::OnDraw(CDC* pDC)
{
	CListViewDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView printing

BOOL CListViewDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CListViewDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CListViewDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView diagnostics

#ifdef _DEBUG
void CListViewDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CListViewDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CListViewDemoDoc* CListViewDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListViewDemoDoc)));
	return (CListViewDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView message handlers
