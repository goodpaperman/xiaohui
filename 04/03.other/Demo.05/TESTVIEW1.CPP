// TestView1.cpp : implementation of the CTestView1 class
//

#include "stdafx.h"
#include "OutBarDemo.h"

#include "GlobalDoc.h"
#include "TestView1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView1

IMPLEMENT_DYNCREATE(CTestView1, CView)

BEGIN_MESSAGE_MAP(CTestView1, CView)
	//{{AFX_MSG_MAP(CTestView1)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView1 construction/destruction

CTestView1::CTestView1()
{
	// TODO: add construction code here

}

CTestView1::~CTestView1()
{
}

BOOL CTestView1::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView1 drawing

void CTestView1::OnDraw(CDC* pDC)
{
	CGlobalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rc;
	GetClientRect(rc);
	pDC->SetBkMode(TRANSPARENT); 
	pDC->DrawText(CString("TEST VIEW"), rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestView1 printing

BOOL CTestView1::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView1::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView1::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView1 diagnostics

#ifdef _DEBUG
void CTestView1::AssertValid() const
{
	CView::AssertValid();
}

void CTestView1::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGlobalDoc* CTestView1::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGlobalDoc)));
	return (CGlobalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView1 message handlers

void CTestView1::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	ModifyStyleEx(0,WS_EX_CLIENTEDGE,SWP_FRAMECHANGED);	
}
