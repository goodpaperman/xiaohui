// TPS_DemoView.cpp : implementation of the CTPS_DemoView class
//

#include "stdafx.h"
#include "TPS_Demo.h"

#include "TPS_DemoDoc.h"
#include "TPS_DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoView

IMPLEMENT_DYNCREATE(CTPS_DemoView, CView)

BEGIN_MESSAGE_MAP(CTPS_DemoView, CView)
	//{{AFX_MSG_MAP(CTPS_DemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoView construction/destruction

CTPS_DemoView::CTPS_DemoView()
{
	// TODO: add construction code here

}

CTPS_DemoView::~CTPS_DemoView()
{
}

BOOL CTPS_DemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoView drawing

void CTPS_DemoView::OnDraw(CDC* pDC)
{
	CTPS_DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoView printing

BOOL CTPS_DemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTPS_DemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTPS_DemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoView diagnostics

#ifdef _DEBUG
void CTPS_DemoView::AssertValid() const
{
	CView::AssertValid();
}

void CTPS_DemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTPS_DemoDoc* CTPS_DemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTPS_DemoDoc)));
	return (CTPS_DemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTPS_DemoView message handlers
