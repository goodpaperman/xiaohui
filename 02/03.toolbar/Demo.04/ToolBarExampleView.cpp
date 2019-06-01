// ToolBarExampleView.cpp : implementation of the CToolBarExampleView class
//

#include "stdafx.h"
#include "ToolBarExample.h"

#include "ToolBarExampleDoc.h"
#include "ToolBarExampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleView

IMPLEMENT_DYNCREATE(CToolBarExampleView, CEditView)

BEGIN_MESSAGE_MAP(CToolBarExampleView, CEditView)
	//{{AFX_MSG_MAP(CToolBarExampleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleView construction/destruction

CToolBarExampleView::CToolBarExampleView()
{
	// TODO: add construction code here

}

CToolBarExampleView::~CToolBarExampleView()
{
}

BOOL CToolBarExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleView drawing

void CToolBarExampleView::OnDraw(CDC* pDC)
{
	CToolBarExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleView diagnostics

#ifdef _DEBUG
void CToolBarExampleView::AssertValid() const
{
	CEditView::AssertValid();
}

void CToolBarExampleView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CToolBarExampleDoc* CToolBarExampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolBarExampleDoc)));
	return (CToolBarExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolBarExampleView message handlers
