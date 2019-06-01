// TestAppView.cpp : implementation of the CTestAppView class
//

#include "stdafx.h"
#include "TestApp.h"

#include "TestAppDoc.h"
#include "TestAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestAppView

IMPLEMENT_DYNCREATE(CTestAppView, CView)

BEGIN_MESSAGE_MAP(CTestAppView, CView)
	//{{AFX_MSG_MAP(CTestAppView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAppView construction/destruction

CTestAppView::CTestAppView()
{
	// TODO: add construction code here

}

CTestAppView::~CTestAppView()
{
}

BOOL CTestAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestAppView drawing

void CTestAppView::OnDraw(CDC* /*pDC*/)
{
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestAppView diagnostics

#ifdef _DEBUG
void CTestAppView::AssertValid() const
{
	CView::AssertValid();
}

void CTestAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestAppDoc* CTestAppView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestAppDoc)));
	return (CTestAppDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestAppView message handlers
