// HiColToolBarView.cpp : implementation of the CHiColToolBarView class
//

#include "stdafx.h"
#include "HiColToolBar.h"

#include "HiColToolBarDoc.h"
#include "HiColToolBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarView

IMPLEMENT_DYNCREATE(CHiColToolBarView, CView)

BEGIN_MESSAGE_MAP(CHiColToolBarView, CView)
	//{{AFX_MSG_MAP(CHiColToolBarView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarView construction/destruction

CHiColToolBarView::CHiColToolBarView()
{
}

CHiColToolBarView::~CHiColToolBarView()
{
}

BOOL CHiColToolBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarView drawing

void CHiColToolBarView::OnDraw(CDC* pDC)
{
	CHiColToolBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarView diagnostics

#ifdef _DEBUG
void CHiColToolBarView::AssertValid() const
{
	CView::AssertValid();
}

void CHiColToolBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHiColToolBarDoc* CHiColToolBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHiColToolBarDoc)));
	return (CHiColToolBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHiColToolBarView message handlers
