// CustomMoreWindowsView.cpp : implementation of the CCustomMoreWindowsView class
//

#include "stdafx.h"
#include "CustomMoreWindows.h"

#include "CustomMoreWindowsDoc.h"
#include "CustomMoreWindowsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsView

IMPLEMENT_DYNCREATE(CCustomMoreWindowsView, CEditView)

BEGIN_MESSAGE_MAP(CCustomMoreWindowsView, CEditView)
	//{{AFX_MSG_MAP(CCustomMoreWindowsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsView construction/destruction

CCustomMoreWindowsView::CCustomMoreWindowsView()
{
	// TODO: add construction code here

}

CCustomMoreWindowsView::~CCustomMoreWindowsView()
{
}

BOOL CCustomMoreWindowsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsView drawing

void CCustomMoreWindowsView::OnDraw(CDC* pDC)
{
	CCustomMoreWindowsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsView printing

BOOL CCustomMoreWindowsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CCustomMoreWindowsView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CCustomMoreWindowsView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsView diagnostics

#ifdef _DEBUG
void CCustomMoreWindowsView::AssertValid() const
{
	CEditView::AssertValid();
}

void CCustomMoreWindowsView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CCustomMoreWindowsDoc* CCustomMoreWindowsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomMoreWindowsDoc)));
	return (CCustomMoreWindowsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomMoreWindowsView message handlers
