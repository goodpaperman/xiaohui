// DVMView1.cpp : implementation of the CDVMView1 class
//

#include "stdafx.h"
#include "DualViewMDI.h"

#include "DVMDoc.h"
#include "DVMView1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDVMView1

IMPLEMENT_DYNCREATE(CDVMView1, CScrollView)

BEGIN_MESSAGE_MAP(CDVMView1, CScrollView)
	//{{AFX_MSG_MAP(CDVMView1)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDVMView1 construction/destruction

CDVMView1::CDVMView1()
{
	// TODO: add construction code here

}

CDVMView1::~CDVMView1()
{
}

BOOL CDVMView1::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDVMView1 drawing

void CDVMView1::OnDraw(CDC* pDC)
{
	CDVMDoc	*pDoc = GetDocument();
	CFont	fntText, *pFntOld ;
	CRect	rctClient ;
	CString	strTestText ;

	ASSERT_VALID(pDoc);

	GetClientRect(&rctClient);

// This will show the text the right way up.
	fntText.CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
						ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
						PROOF_QUALITY, VARIABLE_PITCH|FF_SWISS, NULL);

	pFntOld = (CFont *)pDC->SelectObject(&fntText);
	strTestText = pDoc->GetTestText();
	pDC->DrawText(strTestText, &rctClient, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pDC->SelectObject(pFntOld);

	fntText.DeleteObject();
}

void CDVMView1::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CDVMView1 printing

BOOL CDVMView1::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDVMView1::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDVMView1::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDVMView1 diagnostics

#ifdef _DEBUG
void CDVMView1::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDVMView1::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDVMDoc* CDVMView1::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDVMDoc)));
	return (CDVMDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDVMView1 message handlers
