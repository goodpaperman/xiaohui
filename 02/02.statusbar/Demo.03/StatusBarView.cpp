// StatusBarView.cpp : implementation of the CStatusBarView class
//

#include "stdafx.h"
#include <afxcview.h>
#include "StatusBar.h"

#include "StatusBarDoc.h"
#include "StatusBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView

IMPLEMENT_DYNCREATE(CStatusBarView, CListView)

BEGIN_MESSAGE_MAP(CStatusBarView, CListView)
	//{{AFX_MSG_MAP(CStatusBarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView construction/destruction

CStatusBarView::CStatusBarView()
{
	// TODO: add construction code here

}

CStatusBarView::~CStatusBarView()
{
}

BOOL CStatusBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

       cs.style |= LVS_REPORT;

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView drawing

void CStatusBarView::OnDraw(CDC* pDC)
{
	CStatusBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView diagnostics

#ifdef _DEBUG
void CStatusBarView::AssertValid() const
{
	CListView::AssertValid();
}

void CStatusBarView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CStatusBarDoc* CStatusBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatusBarDoc)));
	return (CStatusBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusBarView message handlers

/****************************************************************************
*                          CStatusBarView::AddString
* Inputs:
*       CString s: String to add
* Result: int
*       Place where string is added
* Effect: 
*       Adds the string to the control
****************************************************************************/

int CStatusBarView::AddString(UINT id, CString s)
    {
     int n = GetListCtrl().GetItemCount();

     CString event;
     event.LoadString(id);
     GetListCtrl().InsertItem(n, event);

     GetListCtrl().SetItem(n, 1, LVIF_TEXT, s, 0,0,0,0);

     GetListCtrl().EnsureVisible(n, FALSE);

     return n;
    } // CStatusBarView::AddString

void CStatusBarView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	CString heading;
	heading.LoadString(IDS_EVENT);
	GetListCtrl().InsertColumn(0, heading);

	CRect r;
	GetClientRect(&r);

	heading.LoadString(IDS_TEXT);
	GetListCtrl().InsertColumn(1, heading);

	GetListCtrl().SetColumnWidth(0, r.Width()/3);
	GetListCtrl().SetColumnWidth(1, r.Width()/4);
}
