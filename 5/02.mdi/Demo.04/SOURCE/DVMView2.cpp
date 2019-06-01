// DVMView2.cpp : implementation file
//

#include "stdafx.h"
#include "DualViewMDI.h"
#include "DVMDoc.h"
#include "DVMView2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDVMView2

IMPLEMENT_DYNCREATE(CDVMView2, CScrollView)

CDVMView2::CDVMView2()
{
}

CDVMView2::~CDVMView2()
{
}


BEGIN_MESSAGE_MAP(CDVMView2, CScrollView)
	//{{AFX_MSG_MAP(CDVMView2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDVMView2 drawing

void CDVMView2::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CDVMView2::OnDraw(CDC* pDC)
{
	CDVMDoc	*pDoc = (CDVMDoc *)GetDocument();
	CFont	fntText, *pFntOld ;
	CRect	rctClient ;
	CString	strTestText ;

	ASSERT_VALID(pDoc);

	GetClientRect(&rctClient);

// This will show the text upside down.
	fntText.CreateFont(24, 0, 1800, 0, FW_BOLD, FALSE, FALSE, FALSE, 
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						PROOF_QUALITY, VARIABLE_PITCH|FF_SWISS, NULL);

	pFntOld = (CFont *)pDC->SelectObject(&fntText);
	strTestText = pDoc->GetTestText();
	pDC->SetTextAlign(TA_RIGHT|TA_BOTTOM);
	pDC->DrawText(strTestText, &rctClient, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pDC->SelectObject(pFntOld);

	fntText.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CDVMView2 diagnostics

#ifdef _DEBUG
void CDVMView2::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDVMView2::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDVMView2 message handlers
