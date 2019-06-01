// SwitchTBView1.cpp : implementation file
//

#include "stdafx.h"
#include "SwitchTB.h"
#include "SwitchTBView1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView1

IMPLEMENT_DYNCREATE(CSwitchTBView1, CView)

CSwitchTBView1::CSwitchTBView1()
{
}

CSwitchTBView1::~CSwitchTBView1()
{
}


BEGIN_MESSAGE_MAP(CSwitchTBView1, CView)
	//{{AFX_MSG_MAP(CSwitchTBView1)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView1 drawing

void CSwitchTBView1::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView1 diagnostics

#ifdef _DEBUG
void CSwitchTBView1::AssertValid() const
{
	CView::AssertValid();
}

void CSwitchTBView1::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSwitchTBView1 message handlers

BOOL CSwitchTBView1::OnEraseBkgnd(CDC* pDC) 
{
// This function writes "Toolbar #2" all across the client where
// the text color and background are similar to those of toolbar #2
// This function is NOT important to the toolbar switching mechanism.

	CSize size;
	CString str ("Toolbar #2");
	CRect rc;

	GetClientRect (rc);
	pDC->SetTextColor (RGB (148, 0, 148));
	pDC->SetBkColor (RGB (0, 195, 198));
	size = pDC->GetTextExtent (str);
	pDC->TextOut (0, 0, str);
	pDC->StretchBlt (0, 0, rc.right, rc.bottom,
						pDC,0, 0, size.cx, size.cy, SRCCOPY);
	return (1);
}
