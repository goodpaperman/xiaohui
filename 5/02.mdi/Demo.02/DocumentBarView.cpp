// DocumentBarView.cpp : implementation of the CDocumentBarView class
//

#include "stdafx.h"
#include "DocumentBar.h"
#include "mainfrm.h"
#include "DocumentBarDoc.h"
#include "DocumentBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarView

IMPLEMENT_DYNCREATE(CDocumentBarView, CEditView)

BEGIN_MESSAGE_MAP(CDocumentBarView, CEditView)
	//{{AFX_MSG_MAP(CDocumentBarView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarView construction/destruction

CDocumentBarView::CDocumentBarView()
{
	// TODO: add construction code here

}

CDocumentBarView::~CDocumentBarView()
{
}

BOOL CDocumentBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarView drawing

void CDocumentBarView::OnDraw(CDC* pDC)
{
	CDocumentBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarView diagnostics

#ifdef _DEBUG
void CDocumentBarView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDocumentBarView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDocumentBarDoc* CDocumentBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocumentBarDoc)));
	return (CDocumentBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDocumentBarView message handlers

void CDocumentBarView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();

	((CMainFrame*)AfxGetMainWnd())->m_wndDocSelector.AddButton( this, IDR_DOCUMETYPE );
}

void CDocumentBarView::OnDestroy() 
{
	((CMainFrame*)AfxGetMainWnd())->m_wndDocSelector.RemoveButton( this );

	CEditView::OnDestroy();
}
