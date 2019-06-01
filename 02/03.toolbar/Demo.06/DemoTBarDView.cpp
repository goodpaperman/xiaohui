// DemoTBarDView.cpp : implementation of the CDemoTBarDView class
//

#include "stdafx.h"
#include "DemoTBarD.h"

#include "DemoTBarDDoc.h"
#include "DemoTBarDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDView

IMPLEMENT_DYNCREATE(CDemoTBarDView, CView)

BEGIN_MESSAGE_MAP(CDemoTBarDView, CView)
	//{{AFX_MSG_MAP(CDemoTBarDView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDView construction/destruction

CDemoTBarDView::CDemoTBarDView()
{
	// TODO: add construction code here

}

CDemoTBarDView::~CDemoTBarDView()
{
}

BOOL CDemoTBarDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDView drawing

void CDemoTBarDView::OnDraw(CDC* pDC)
{
	CDemoTBarDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDView printing

BOOL CDemoTBarDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemoTBarDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemoTBarDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDView diagnostics

#ifdef _DEBUG
void CDemoTBarDView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoTBarDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoTBarDDoc* CDemoTBarDView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoTBarDDoc)));
	return (CDemoTBarDDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarDView message handlers
