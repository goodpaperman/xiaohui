// SwitchTBView.cpp : implementation of the CSwitchTBView class
//

#include "stdafx.h"
#include "SwitchTB.h"

#include "SwitchTBDoc.h"
#include "SwitchTBView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView

IMPLEMENT_DYNCREATE(CSwitchTBView, CView)

BEGIN_MESSAGE_MAP(CSwitchTBView, CView)
	//{{AFX_MSG_MAP(CSwitchTBView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView construction/destruction

CSwitchTBView::CSwitchTBView()
{
}

CSwitchTBView::~CSwitchTBView()
{
}

BOOL CSwitchTBView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView drawing

void CSwitchTBView::OnDraw(CDC* pDC)
{
	CSwitchTBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView diagnostics

#ifdef _DEBUG
void CSwitchTBView::AssertValid() const
{
	CView::AssertValid();
}

void CSwitchTBView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSwitchTBDoc* CSwitchTBView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSwitchTBDoc)));
	return (CSwitchTBDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView message handlers

BOOL CSwitchTBView::OnEraseBkgnd(CDC* pDC) 
{
// This function writes "Toolbar #1" all across the client where
// the text color and background are similar to those of toolbar #1
// This function is NOT important to the toolbar switching mechanism.

	CSize size;
	CString str ("Toolbar #1");
	CRect rc;

	GetClientRect (rc);
	pDC->SetTextColor (RGB (0xff, 0xff, 0));
	pDC->SetBkColor (RGB (0, 110, 255));
	size = pDC->GetTextExtent (str);
	pDC->TextOut (0, 0, str);
	pDC->StretchBlt (0, 0, rc.right, rc.bottom,
						pDC,0, 0, size.cx, size.cy, SRCCOPY);
	return (1);
}
