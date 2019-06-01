// MyListView.cpp : implementation file
//

#include "stdafx.h"
#include "ListViewDemo.h"
#include "MyListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CMultiColumnSortListView)

CMyListView::CMyListView()
{
}

CMyListView::~CMyListView()
{
}


BEGIN_MESSAGE_MAP(CMyListView, CMultiColumnSortListView)
	//{{AFX_MSG_MAP(CMyListView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListView drawing

void CMyListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CMyListView diagnostics

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyListView message handlers

int CMyListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMultiColumnSortListView::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	return 0;
}

void CMyListView::OnInitialUpdate() 
{
	CMultiColumnSortListView::OnInitialUpdate();
	CListCtrl &rListCtrl = GetListCtrl();
    rListCtrl.DeleteAllItems(); 
    CHeaderCtrl* pHeader = rListCtrl.GetHeaderCtrl(); 
    while(pHeader->GetItemCount())
        pHeader->DeleteItem(0); 

	rListCtrl.InsertColumn( 0, "Name", LVCFMT_LEFT, 200, 0 );
	rListCtrl.InsertColumn( 1, "City", LVCFMT_LEFT, 200, 0 );
	rListCtrl.InsertColumn( 2, "Age", LVCFMT_LEFT, 200, 0 );
	rListCtrl.InsertColumn( 3, "Height", LVCFMT_LEFT, 200, 0 );
    rListCtrl.InsertColumn( 4, "Num1", LVCFMT_RIGHT, 200, 0); 
    rListCtrl.InsertColumn( 5, "Num2", LVCFMT_RIGHT, 200, 0); 

	SetColumnNumeric( 2 );
	SetColumnNumeric( 3 );
    SetColumnNumeric( 4 ); 
    SetColumnNumeric( 5 ); 
	
	int iSubItem = 1;
	int iRootItem = 0;
	
	rListCtrl.InsertItem( iRootItem, "Craig" );
	rListCtrl.SetItemText( iRootItem, iSubItem++, "Fort Lauderdale");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "20");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "6");
    rListCtrl.SetItemText( iRootItem, iSubItem++, "1"); 
    rListCtrl.SetItemText( iRootItem, iSubItem++, "10"); 

	iSubItem = 1;

	rListCtrl.InsertItem( iRootItem, "Joe" );
	rListCtrl.SetItemText( iRootItem, iSubItem++, "Fort Lauderdale");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "23");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "6");
    rListCtrl.SetItemText( iRootItem, iSubItem++, "3"); 
    rListCtrl.SetItemText( iRootItem, iSubItem++, "9");

	iSubItem = 1;

	rListCtrl.InsertItem( iRootItem, "Andy" );
	rListCtrl.SetItemText( iRootItem, iSubItem++, "Fort Lauderdale");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "24");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "6");
    rListCtrl.SetItemText( iRootItem, iSubItem++, "5"); 
    rListCtrl.SetItemText( iRootItem, iSubItem++, "8");

	iSubItem = 1;

	rListCtrl.InsertItem( iRootItem, "Bob" );
	rListCtrl.SetItemText( iRootItem, iSubItem++, "Fort Lauderdale");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "28");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "6");
    rListCtrl.SetItemText( iRootItem, iSubItem++, "6"); 
    rListCtrl.SetItemText( iRootItem, iSubItem++, "8");

	iSubItem = 1;

	rListCtrl.InsertItem( iRootItem, "Chris" );
	rListCtrl.SetItemText( iRootItem, iSubItem++, "Fort Lauderdale");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "82");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "6");
    rListCtrl.SetItemText( iRootItem, iSubItem++, "8"); 
    rListCtrl.SetItemText( iRootItem, iSubItem++, "6");

	iSubItem = 1;

	rListCtrl.InsertItem( iRootItem, "Bob" );
	rListCtrl.SetItemText( iRootItem, iSubItem++, "Orlando");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "23");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "7");
    rListCtrl.SetItemText( iRootItem, iSubItem++, "9"); 
    rListCtrl.SetItemText( iRootItem, iSubItem++, "5");
	
	iSubItem = 1;

	rListCtrl.InsertItem( iRootItem, "Carl" );
	rListCtrl.SetItemText( iRootItem, iSubItem++, "Orlando");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "43");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "7");
    rListCtrl.SetItemText( iRootItem, iSubItem++, "10"); 
    rListCtrl.SetItemText( iRootItem, iSubItem++, "4");

	iSubItem = 1;

	rListCtrl.InsertItem( iRootItem, "David" );
	rListCtrl.SetItemText( iRootItem, iSubItem++, "Orlando");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "24");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "7");
    rListCtrl.SetItemText( iRootItem, iSubItem++, "10"); 
    rListCtrl.SetItemText( iRootItem, iSubItem++, "2");
	
	iSubItem = 1;

	rListCtrl.InsertItem( iRootItem, "Eddy" );
	rListCtrl.SetItemText( iRootItem, iSubItem++, "Orlando");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "13");
	rListCtrl.SetItemText( iRootItem, iSubItem++, "7");
    rListCtrl.SetItemText( iRootItem, iSubItem++, "11"); 
    rListCtrl.SetItemText( iRootItem, iSubItem++, "1");

	LoadColumnWidths();
	
}
