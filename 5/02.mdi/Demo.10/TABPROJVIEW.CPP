// TabProjView.cpp : implementation of the CTabProjView class
//

#include "stdafx.h"
#include "TabProj.h"

#include "TabProjDoc.h"
#include "TabProjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabProjView

IMPLEMENT_DYNCREATE(CTabProjView, CEditView)

BEGIN_MESSAGE_MAP(CTabProjView, CEditView)
	//{{AFX_MSG_MAP(CTabProjView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()
static int ncount = 0;
/////////////////////////////////////////////////////////////////////////////
// CTabProjView construction/destruction

CTabProjView::CTabProjView()
{
	// TODO: add construction code here
m_nCount = ++ncount;
}

CTabProjView::~CTabProjView()
{
}

BOOL CTabProjView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CTabProjView drawing

void CTabProjView::OnDraw(CDC* pDC)
{
	CTabProjDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTabProjView printing

BOOL CTabProjView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CTabProjView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CTabProjView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CTabProjView diagnostics

#ifdef _DEBUG
void CTabProjView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTabProjView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTabProjDoc* CTabProjView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabProjDoc)));
	return (CTabProjDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabProjView message handlers

void CTabProjView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
CString s;
s.Format("edit view instance %d",m_nCount);
	GetParentFrame()->SetWindowText(s);	
}
