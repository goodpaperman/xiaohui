// GHCustomDrawView.cpp : implementation of the CGHCustomDrawView class
//

#include "stdafx.h"
#include "GHCustomDraw.h"

#include "GHCustomDrawDoc.h"
#include "GHCustomDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawView

IMPLEMENT_DYNCREATE(CGHCustomDrawView, CListView)

BEGIN_MESSAGE_MAP(CGHCustomDrawView, CListView)
	//{{AFX_MSG_MAP(CGHCustomDrawView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawView construction/destruction

CGHCustomDrawView::CGHCustomDrawView()
{
	// TODO: add construction code here

}

CGHCustomDrawView::~CGHCustomDrawView()
{
}

BOOL CGHCustomDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawView drawing

void CGHCustomDrawView::OnDraw(CDC* pDC)
{
	CGHCustomDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CGHCustomDrawView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawView printing

BOOL CGHCustomDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGHCustomDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGHCustomDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawView diagnostics

#ifdef _DEBUG
void CGHCustomDrawView::AssertValid() const
{
	CListView::AssertValid();
}

void CGHCustomDrawView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CGHCustomDrawDoc* CGHCustomDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGHCustomDrawDoc)));
	return (CGHCustomDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGHCustomDrawView message handlers
void CGHCustomDrawView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
