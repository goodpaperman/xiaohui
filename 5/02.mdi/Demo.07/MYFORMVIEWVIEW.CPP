// MyFormViewView.cpp : implementation of the CMyFormViewView class
//

#include "stdafx.h"
#include "MyFormView.h"

#include "MyFormViewDoc.h"
#include "MyFormViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFormViewView

IMPLEMENT_DYNCREATE(CMyFormViewView, CColorFormView)

BEGIN_MESSAGE_MAP(CMyFormViewView, CColorFormView)
	//{{AFX_MSG_MAP(CMyFormViewView)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, OnChangeBkColor)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CColorFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CColorFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CColorFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFormViewView construction/destruction

CMyFormViewView::CMyFormViewView()
	: CColorFormView(CMyFormViewView::IDD)
{
	//{{AFX_DATA_INIT(CMyFormViewView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
}

CMyFormViewView::~CMyFormViewView()
{
}

void CMyFormViewView::DoDataExchange(CDataExchange* pDX)
{
	CColorFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyFormViewView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CMyFormViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CColorFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyFormViewView printing

BOOL CMyFormViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFormViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFormViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMyFormViewView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// CMyFormViewView diagnostics

#ifdef _DEBUG
void CMyFormViewView::AssertValid() const
{
	CColorFormView::AssertValid();
}

void CMyFormViewView::Dump(CDumpContext& dc) const
{
	CColorFormView::Dump(dc);
}

CMyFormViewDoc* CMyFormViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFormViewDoc)));
	return (CMyFormViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFormViewView message handlers

BOOL CMyFormViewView::OnEraseBkgnd(CDC* pDC) 
{
	return CColorFormView::OnEraseBkgnd(pDC);
}

void CMyFormViewView::OnInitialUpdate() 
{
    SetWindowText(_T("This is my formview"));

    CColorFormView::OnInitialUpdate();
	
	SetBackgroundColor(RGB(0, 128, 0));	
    
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit();
}

void CMyFormViewView::OnChangeBkColor() 
{
	// select color from CColorDialog
	CColorDialog dlg(m_crBackground); 
	int nRet = dlg.DoModal();
	if(IDOK==nRet)
	{
		// set dialog background color
		SetBackgroundColor(dlg.GetColor());

		// see action
		RedrawWindow();
	}
}
