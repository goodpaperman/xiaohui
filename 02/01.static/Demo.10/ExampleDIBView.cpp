// ExampleDIBView.cpp : implementation of the CExampleDIBView class
//

#include "stdafx.h"
#include "ExampleDIB.h"

#include "ExampleDIBDoc.h"
#include "ExampleDIBView.h"

#include "DlgBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExampleDIBView

IMPLEMENT_DYNCREATE(CExampleDIBView, CFormView)

BEGIN_MESSAGE_MAP(CExampleDIBView, CFormView)
	//{{AFX_MSG_MAP(CExampleDIBView)
	ON_BN_CLICKED(IDC_BTN_1, OnBtn1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleDIBView construction/destruction

CExampleDIBView::CExampleDIBView()
	: CFormView(CExampleDIBView::IDD)
{
	//{{AFX_DATA_INIT(CExampleDIBView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CExampleDIBView::~CExampleDIBView()
{
}

void CExampleDIBView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExampleDIBView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CExampleDIBView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CExampleDIBView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CExampleDIBView printing

BOOL CExampleDIBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExampleDIBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExampleDIBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CExampleDIBView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CExampleDIBView diagnostics

#ifdef _DEBUG
void CExampleDIBView::AssertValid() const
{
	CFormView::AssertValid();
}

void CExampleDIBView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CExampleDIBDoc* CExampleDIBView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExampleDIBDoc)));
	return (CExampleDIBDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExampleDIBView message handlers

void CExampleDIBView::OnBtn1() 
{
		CDlgBitmap	DlgExample;

		DlgExample.DoModal();
		return;
}
