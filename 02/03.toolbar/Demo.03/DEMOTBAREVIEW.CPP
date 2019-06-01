// DemoTBarEView.cpp : implementation of the CDemoTBarEView class
//

#include "stdafx.h"
#include "DemoTBarE.h"

#include "DemoTBarEDoc.h"
#include "DemoTBarEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEView

IMPLEMENT_DYNCREATE(CDemoTBarEView, CView)

BEGIN_MESSAGE_MAP(CDemoTBarEView, CView)
	//{{AFX_MSG_MAP(CDemoTBarEView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEView construction/destruction

CDemoTBarEView::CDemoTBarEView()
{
	// TODO: add construction code here

}

CDemoTBarEView::~CDemoTBarEView()
{
}

BOOL CDemoTBarEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEView drawing

void CDemoTBarEView::OnDraw(CDC* pDC)
{
	CDemoTBarEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEView printing

BOOL CDemoTBarEView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemoTBarEView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemoTBarEView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEView diagnostics

#ifdef _DEBUG
void CDemoTBarEView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoTBarEView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoTBarEDoc* CDemoTBarEView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoTBarEDoc)));
	return (CDemoTBarEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarEView message handlers
