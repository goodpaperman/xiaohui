// TestPreviewView.cpp : implementation of the CTestPreviewView class
//

#include "stdafx.h"
#include "TestPreview.h"

#include "TestPreviewDoc.h"
#include "TestPreviewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewView

IMPLEMENT_DYNCREATE(CTestPreviewView, CView)

BEGIN_MESSAGE_MAP(CTestPreviewView, CView)
	//{{AFX_MSG_MAP(CTestPreviewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewView construction/destruction

CTestPreviewView::CTestPreviewView()
{
	// TODO: add construction code here

}

CTestPreviewView::~CTestPreviewView()
{
}

BOOL CTestPreviewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewView drawing

void CTestPreviewView::OnDraw(CDC* pDC)
{
	CTestPreviewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewView printing

BOOL CTestPreviewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestPreviewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestPreviewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewView diagnostics

#ifdef _DEBUG
void CTestPreviewView::AssertValid() const
{
	CView::AssertValid();
}

void CTestPreviewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestPreviewDoc* CTestPreviewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestPreviewDoc)));
	return (CTestPreviewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestPreviewView message handlers
