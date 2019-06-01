// TestTipDayView.cpp : implementation of the CTestTipDayView class
//

#include "stdafx.h"
#include "TestTipDay.h"

#include "TestTipDayDoc.h"
#include "TestTipDayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestTipDayView

IMPLEMENT_DYNCREATE(CTestTipDayView, CView)

BEGIN_MESSAGE_MAP(CTestTipDayView, CView)
	//{{AFX_MSG_MAP(CTestTipDayView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestTipDayView construction/destruction

CTestTipDayView::CTestTipDayView()
{
	// TODO: add construction code here

}

CTestTipDayView::~CTestTipDayView()
{
}

BOOL CTestTipDayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestTipDayView drawing

void CTestTipDayView::OnDraw(CDC* pDC)
{
	CTestTipDayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestTipDayView diagnostics

#ifdef _DEBUG
void CTestTipDayView::AssertValid() const
{
	CView::AssertValid();
}

void CTestTipDayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestTipDayDoc* CTestTipDayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestTipDayDoc)));
	return (CTestTipDayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestTipDayView message handlers
