// MyListView.cpp : implementation file
//

#include "stdafx.h"
#include "CGfxListView.h"
#include "MyListView.h"
#include "CGfxListViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CGfxListView)

CMyListView::CMyListView()
{
	lima.Create(IDB_ARANLIST, 16, 0, RGB(255,0,255));
	limah.Create(IDB_ARANCOL, 11, 0, RGB(255,0,255));
}

CMyListView::~CMyListView()
{
}


BEGIN_MESSAGE_MAP(CMyListView, CGfxListView)
	//{{AFX_MSG_MAP(CMyListView)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_COMMAND(ID_TEST_CAT, OnTestCat)
	ON_UPDATE_COMMAND_UI(ID_TEST_CAT, OnUpdateTestCat)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListView drawing

void CMyListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyListView diagnostics

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CGfxListView::AssertValid();
}

void CMyListView::Dump(CDumpContext& dc) const
{
	CGfxListView::Dump(dc);
}


CCGfxListViewDoc* CMyListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGfxListViewDoc)));
	return (CCGfxListViewDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyListView message handlers


void CMyListView::GetTextCallback(int iIndex, int iSubItem, long lCode, CString &cs)
{
	cs = "";
	int rc = GetColumnIndex(iSubItem);
	if (rc == 4) cs = "1";
	else if (rc == 5) cs = "2";
	else if (rc == 6) cs = "3";
	else if (rc == 2) cs.Format("%d", lCode);
	else if (rc == 3) cs.Format("ma perche' non funziona ? non riesco a capire, porcaccia miseria %d", lCode);
	else cs.Format("%d, %d", lCode, rc);
}

void CMyListView::CategoryCallBack(CGfxCategoryManager * pCatMan, long & lData)
{
	long value = lData;
	int iCat = pCatMan->FindCategory(value);
	if (iCat < 0)
	{
		CString cs;
		long val1 = value / 20;
		val1 *= 20;
		long val2 = val1 + 20;

		cs.Format("%d - %d", val1, val2);
		iCat = pCatMan->AddCategory(cs, val1, val2);
	}
	if (iCat >= 0)
	{
		pCatMan->AddItemToCategory(iCat, value);
	}
	if (lData > 310)
	{
		pCatMan->AddItemToCategory(0, value);
	}
}	

long CMyListView::GetExInfoCallback(LXHDREX * pLx)
{
	ASSERT(pLx);

	switch(pLx->iNotifyCode)
	{
	case NTEX_ITEMINFO:
		if (pLx->dwItemData < 25 || (pLx->dwItemData > 200 && pLx->dwItemData % 2 == 0))
			pLx->dwFlag |= LXHDREX::exBold;

		if (pLx->iSubItem == 7) pLx->dwFlag |= LXHDREX::exUnderline;
		if (pLx->iSubItem == 3) 
		{
			pLx->dwFlag |= LXHDREX::exTextColor;
			pLx->crText = RGB(255,0,0);
		}
		if (pLx->iSubItem == 8) 
		{
			pLx->dwFlag |= LXHDREX::exTextColor;
			pLx->crText = RGB(255,0,128);
		}
		return 1;
		break;
	case NTEX_COMBOREQUEST:
		{
			pLx->pComboArray->Add(CString(""));
			pLx->pComboArray->Add(pLx->csText);
			pLx->pComboArray->Add(CString("Provincia"));
			pLx->pComboArray->Add(CString("Anas"));
			pLx->pComboArray->Add(CString("Comune"));
			return 1;
		}
		break;
	case NTEX_SETTEXT:
		return 1;
	case NTEX_AUTOPREVIEW:
		{
			if (pLx->dwItemData % 2 == 0) return 0;

			LXHDREX_DIV * pLxEx = (LXHDREX_DIV *) pLx;

			COLORREF ocr = pLxEx->pDC->SetTextColor(RGB(0,0,255));
			CString cs;
			cs.Format("TpLxEx->pDC->his is a test about item autopreview. We are writing some trash here. The autopreview is obtained handling the NTEX_AUTOPREVIEW subcode in the exinfo callback/message and the height of autopreview pane have to be fixed for all items and can be set by the SetAutoPreviewHeight(height) function and retrieved by the GetAutoPreviewHeight function.");
			pLxEx->pDC->DrawText(cs, pLxEx->rcItem, DT_END_ELLIPSIS|DT_WORDBREAK);
			pLxEx->pDC->SetTextColor(ocr);
			return 0;
		}
	};

	return 0L;
}

void CMyListView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = 0;

	long index = pDispInfo->item.iItem;
	long subItem = pDispInfo->item.iSubItem;
	long objCode = pDispInfo->item.lParam;

	if(pDispInfo->item.mask & LVIF_TEXT)
	{
		CString cs;
		GetTextCallback(index, subItem, objCode, cs);

		lstrcpyn(pDispInfo->item.pszText, cs, pDispInfo->item.cchTextMax);
		*pResult = 1;

	}
	
	if(pDispInfo->item.mask & LVIF_IMAGE) pDispInfo->item.iImage = 0;//set image to first in list	
}

void CMyListView::OnInitialUpdate() 
{
	CGfxListView::OnInitialUpdate();
    //CDaoRecordset* pSet = new CDaoRecordset; 
    //pSet->Open(); 
    //BindDaoRecordset(pSet); 
    //FillRecordsetColumn(); 
    //FillDaoItems(); 
	
    CGfxColumnManager * pManager = CreateColumnManager();

    pManager->DefineColumn(0, "", NULL, LVCFMT_LEFT, 0, fhNoSortArrow|fhNoResizeColumn);
    pManager->DefineColumn(1, "Colonna 0");
    pManager->DefineColumn(2, "Colonna 1", NULL, LVCFMT_CENTER, 120, fhEdit|fhNumeric|fhSortAble);
    pManager->DefineColumn(3, "Colonna 2", NULL, LVCFMT_LEFT, 220, fhEdit|fhSortAble);
    pManager->DefineColumn(7, "Colonna 3", NULL, LVCFMT_LEFT, 120, fhEdit|fhSortAble);
    pManager->DefineColumn(4, NULL, NULL, LVCFMT_LEFT, 20, fhImage|fhNoSortArrow|fhNoResizeColumn|fhSortAble|fhColumnHasImage, 0, "Image 1");
    pManager->DefineColumn(5, NULL, NULL, LVCFMT_LEFT, 20, fhImage|fhNoSortArrow|fhNoResizeColumn|fhSortAble|fhColumnHasImage, 1, "Image 2");
    pManager->DefineColumn(6, NULL, NULL, LVCFMT_LEFT, 20, fhImage|fhNoSortArrow|fhNoResizeColumn|fhSortAble|fhColumnHasImage, 2, "Image 3");
    pManager->DefineColumn(8, "The Combox", NULL, LVCFMT_LEFT, 120, fhComboBox|fhSortAble);

    //int _DEFCOLS[] = { 0,2,4,5,6,3,1,8,7 };
    int _DEFCOLS[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 }; 
    pManager->DefineDefaultColumns(sizeof(_DEFCOLS)/sizeof(int), _DEFCOLS);
    pManager->ReadFromProfile("TheMainList");

    SetItemImageList(&lima);
    SetHeaderImageList(&limah);
    
    //OnInit();
    ModifyFlag(0,fHighRowSelect|fVertGrid|fHorizGrid|fAutoSort,0);
    SetWindowPos(0,0,0,0,0,SWP_FRAMECHANGED);
    
    SetupColumnData();
    GetListCtrl().SetItemCount(200);

    for (int t = 0; t < 200; t++)
        InsertItemEx(t,t);

    SetItemHeight(17);
    SetCategoryCallback((void (CWnd::*)(CGfxCategoryManager * , long &))CategoryCallBack);
    SetGetTextCallback((void (CWnd::*)(int , int, long, CString &)) GetTextCallback);
    SetExInfoCallback((long (CWnd::*)(LXHDREX *))GetExInfoCallback);
    //GetListCtrl().DeleteAllItems(); 
    SetBkImage(IDB_BITMAP1); 
    //SetBkImage(IDB_ARANLIST); 
}

void CMyListView::OnTestCat() 
{
	if (GetCategoryManager()) EnableCategoryView(false);
	else EnableCategoryView(true);
}

void CMyListView::OnUpdateTestCat(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetCategoryManager() != NULL);
	
}

void CMyListView::OnDestroy() 
{
	CGfxListView::OnDestroy();
	
	// TODO: Add your message handler code here
	
	pManager->WriteToProfile("TheMainList");
}
