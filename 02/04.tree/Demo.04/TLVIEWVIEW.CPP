// TLViewView.cpp : implementation of the CTLViewView class
//

#include "stdafx.h"
#include "TLView.h"

#include "TLViewDoc.h"
#include "TLViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTLViewView

IMPLEMENT_DYNCREATE(CTLViewView, CTreeListView)

BEGIN_MESSAGE_MAP(CTLViewView, CTreeListView)
	//{{AFX_MSG_MAP(CTLViewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTLViewView construction/destruction

CTLViewView::CTLViewView()
{
	// TODO: add construction code here

}

CTLViewView::~CTLViewView()
{
}

BOOL CTLViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTLViewView drawing

void CTLViewView::OnDraw(CDC* pDC)
{
	CTLViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTLViewView printing

BOOL CTLViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTLViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTLViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTLViewView diagnostics

#ifdef _DEBUG
void CTLViewView::AssertValid() const
{
	CTreeListView::AssertValid();
}

void CTLViewView::Dump(CDumpContext& dc) const
{
	CTreeListView::Dump(dc);
}

CTLViewDoc* CTLViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTLViewDoc)));
	return (CTLViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTLViewView message handlers
