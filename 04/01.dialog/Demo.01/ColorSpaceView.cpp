// ColorSpaceView.cpp : implementation of the CColorSpaceView class
//

#include "stdafx.h"
#include "ColorSpace.h"

#include "ColorSpaceDoc.h"
#include "ColorSpaceView.h"
#include "ColorPickerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceView

IMPLEMENT_DYNCREATE(CColorSpaceView, CView)

BEGIN_MESSAGE_MAP(CColorSpaceView, CView)
	//{{AFX_MSG_MAP(CColorSpaceView)
	ON_COMMAND(ID_VIEW_COLORSPACE, OnViewColorspace)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceView construction/destruction

CColorSpaceView::CColorSpaceView()
{
	// TODO: add construction code here
	// Demo - setup initial color as gray */
	m_Color = RGB(128,128,128);
}

CColorSpaceView::~CColorSpaceView()
{
}

BOOL CColorSpaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceView drawing

void CColorSpaceView::OnDraw(CDC* pDC)
{
	CColorSpaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
CRect cr;
	GetClientRect(&cr);
	pDC->FillSolidRect(&cr,m_Color);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceView printing

BOOL CColorSpaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CColorSpaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CColorSpaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceView diagnostics

#ifdef _DEBUG
void CColorSpaceView::AssertValid() const
{
	CView::AssertValid();
}

void CColorSpaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColorSpaceDoc* CColorSpaceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorSpaceDoc)));
	return (CColorSpaceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColorSpaceView message handlers

void CColorSpaceView::OnViewColorspace() 
{
CColorPickerDlg dlg(m_Color);
	if(dlg.DoModal() == IDOK)
	{
		m_Color = dlg.GetColor();
		Invalidate(FALSE);
	}
	
}
