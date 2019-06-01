// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "GHCustomDraw.h"

#include "GHCustomDrawDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here

}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CGHCustomDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	
	PopulateTree();
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CGHCustomDrawDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGHCustomDrawDoc)));
	return (CGHCustomDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers


/////////////////////////////////////////////////////////////////////////////////////////
//  This method populates the tree ctrl
//
//  Copyright © Garen Hartunian  
/////////////////////////////////////////////////////////////////////////////////////////
void CLeftView::PopulateTree()
{
	CTreeCtrl &tc = GetTreeCtrl();

	// Create image list
	m_ImageList.Create(16, 16, ILC_COLORDDB | ILC_MASK, 0, 1);

	CBitmap bmClassical, bmJazz, bmRock;

	// load images and populate image list -GGH
	bmClassical.LoadBitmap(IDB_CLASSICAL);
	bmJazz.LoadBitmap(IDB_JAZZ);
	bmRock.LoadBitmap(IDB_ROCK);

	m_ImageList.Add(&bmClassical, RGB(192, 192, 192));
	m_ImageList.Add(&bmJazz, RGB(192, 192, 192));
	m_ImageList.Add(&bmRock, RGB(192, 192, 192));

	tc.SetImageList(&m_ImageList, TVSIL_NORMAL);

	HTREEITEM hItem;
	hItem = tc.InsertItem("Classical", 0, 0);
	if (hItem)
	{
		tc.InsertItem("J. S. Bach", 0, 0, hItem);
		tc.InsertItem("W. A. Mozart", 0, 0, hItem);
		tc.InsertItem("F. Chopin", 0, 0, hItem);
	}
	// expand
	tc.Expand(hItem, TVE_EXPAND);
	
	hItem = tc.InsertItem("Jazz", 1, 1);
	if (hItem)
	{
		tc.InsertItem("Johnny Hodges", 1, 1, hItem);
		tc.InsertItem("Charlie Parker", 1, 1, hItem);
		tc.InsertItem("John Coltrane", 1, 1, hItem);
	}
	// expand
	tc.Expand(hItem, TVE_EXPAND);

	hItem = tc.InsertItem("Rock", 2, 2);
	if (hItem)
	{
		tc.InsertItem("Genesis", 2, 2, hItem);
		tc.InsertItem("Jethro Tull", 2, 2, hItem);
		tc.InsertItem("Yes", 2, 2, hItem);
	}
	// expand
	tc.Expand(hItem, TVE_EXPAND);	
}


