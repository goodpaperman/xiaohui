// DirTreeDemoView.cpp : implementation of the CDirTreeDemoView class
//

#include "stdafx.h"
#include "DirTreeDemo.h"

#include "DirTreeDemoDoc.h"
#include "DirTreeDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirTreeDemoView

IMPLEMENT_DYNCREATE(CDirTreeDemoView, CListView)

BEGIN_MESSAGE_MAP(CDirTreeDemoView, CListView)
	//{{AFX_MSG_MAP(CDirTreeDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirTreeDemoView construction/destruction

CDirTreeDemoView::CDirTreeDemoView()
{
	// TODO: add construction code here

}

CDirTreeDemoView::~CDirTreeDemoView()
{
}

BOOL CDirTreeDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDirTreeDemoView drawing

void CDirTreeDemoView::OnDraw(CDC* pDC)
{
	CDirTreeDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CDirTreeDemoView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CDirTreeDemoView printing

BOOL CDirTreeDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDirTreeDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDirTreeDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDirTreeDemoView diagnostics

#ifdef _DEBUG
void CDirTreeDemoView::AssertValid() const
{
	CListView::AssertValid();
}

void CDirTreeDemoView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDirTreeDemoDoc* CDirTreeDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDirTreeDemoDoc)));
	return (CDirTreeDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDirTreeDemoView message handlers
void CDirTreeDemoView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
