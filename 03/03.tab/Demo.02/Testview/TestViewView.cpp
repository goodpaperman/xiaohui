// TestViewView.cpp : implementation of the CTestViewView class
//

#include "stdafx.h"
#include "TestView.h"

#include "TestViewDoc.h"
#include "TestViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestViewView

IMPLEMENT_DYNCREATE(CTestViewView, CView)

BEGIN_MESSAGE_MAP(CTestViewView, CView)
	//{{AFX_MSG_MAP(CTestViewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestViewView construction/destruction

CTestViewView::CTestViewView()
{
	// TODO: add construction code here

}

CTestViewView::~CTestViewView()
{
}

BOOL CTestViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestViewView drawing

void CTestViewView::OnDraw(CDC* pDC)
{
	CTestViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestViewView printing

BOOL CTestViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestViewView diagnostics

#ifdef _DEBUG
void CTestViewView::AssertValid() const
{
	CView::AssertValid();
}

void CTestViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestViewDoc* CTestViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestViewDoc)));
	return (CTestViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestViewView message handlers
