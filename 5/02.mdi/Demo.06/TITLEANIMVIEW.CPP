// titleAnimView.cpp : implementation of the CTitleAnimView class
//

#include "stdafx.h"
#include "titleAnim.h"

#include "titleAnimDoc.h"
#include "titleAnimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTitleAnimView

IMPLEMENT_DYNCREATE(CTitleAnimView, CView)

BEGIN_MESSAGE_MAP(CTitleAnimView, CView)
	//{{AFX_MSG_MAP(CTitleAnimView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTitleAnimView construction/destruction

CTitleAnimView::CTitleAnimView()
{
	// TODO: add construction code here

}

CTitleAnimView::~CTitleAnimView()
{
}

BOOL CTitleAnimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTitleAnimView drawing

void CTitleAnimView::OnDraw(CDC* pDC)
{
	CTitleAnimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTitleAnimView diagnostics

#ifdef _DEBUG
void CTitleAnimView::AssertValid() const
{
	CView::AssertValid();
}

void CTitleAnimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTitleAnimDoc* CTitleAnimView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTitleAnimDoc)));
	return (CTitleAnimDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTitleAnimView message handlers
