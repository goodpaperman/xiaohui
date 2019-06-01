// SuperGrid1View.cpp : implementation of the CSuperGrid1View class
//

#include "stdafx.h"
#include "GfxList.h"

#include "SuperGrid1Doc.h"
#include "SuperGrid1View.h"

#include "GfxCustomizeColumnDlg.h"
#include "GfxFormatColumnDlg.h"
#include "TestDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperGrid1View

IMPLEMENT_DYNCREATE(CSuperGrid1View, CFormView)

BEGIN_MESSAGE_MAP(CSuperGrid1View, CFormView)
	//{{AFX_MSG_MAP(CSuperGrid1View)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, OnGetdispinfoList1)
	ON_COMMAND(ID_CUSTOMHEADER, OnCustomheader)
	ON_COMMAND(ID_FORMATHEADER, OnFormatheader)
	ON_COMMAND(ID_TESTCAT, OnTestcat)
	ON_UPDATE_COMMAND_UI(ID_TESTCAT, OnUpdateTestcat)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_COMMAND(ID_ADDANITEM, OnAddanitem)
	ON_WM_DESTROY()
	ON_COMMAND(ID_BLENDBMP, OnBlendbmp)
	ON_UPDATE_COMMAND_UI(ID_BLENDBMP, OnUpdateBlendbmp)
	ON_COMMAND(ID_TRYBITMAP1, OnTrybitmap1)
	ON_UPDATE_COMMAND_UI(ID_TRYBITMAP1, OnUpdateTrybitmap1)
	ON_COMMAND(ID_TRYBITMAP2, OnTrybitmap2)
	ON_UPDATE_COMMAND_UI(ID_TRYBITMAP2, OnUpdateTrybitmap2)
	ON_COMMAND(ID_DRAGGABLECOL, OnDraggablecol)
	ON_UPDATE_COMMAND_UI(ID_DRAGGABLECOL, OnUpdateDraggablecol)
	ON_COMMAND(ID_GRIDH, OnGridh)
	ON_UPDATE_COMMAND_UI(ID_GRIDH, OnUpdateGridh)
	ON_COMMAND(ID_GRIDV, OnGridv)
	ON_UPDATE_COMMAND_UI(ID_GRIDV, OnUpdateGridv)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_TESTDAO, OnTestdao)
	ON_UPDATE_COMMAND_UI(ID_TESTDAO, OnUpdateTestdao)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_COMMAND(ID_AUTOPREVIEW, OnAutopreview)
	ON_UPDATE_COMMAND_UI(ID_AUTOPREVIEW, OnUpdateAutopreview)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_MESSAGE(WM_LISTEX_NOTIFY, OnListExNotify)
END_MESSAGE_MAP()
//	ON_UPDATE_COMMAND_UI_RANGE(1, 10, OnListCmdUpdate)

/////////////////////////////////////////////////////////////////////////////
// CSuperGrid1View construction/destruction

CSuperGrid1View::CSuperGrid1View()
	: CFormView(CSuperGrid1View::IDD)
{
	//{{AFX_DATA_INIT(CSuperGrid1View)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	lima.Create(IDB_ARANLIST, 16, 0, RGB(255,0,255));
	limah.Create(IDB_ARANCOL, 11, 0, RGB(255,0,255));

	ftTimes.CreatePointFont(90, "Times New Roman");

	iSelBmp = -1;
}

CSuperGrid1View::~CSuperGrid1View()
{
}

void CSuperGrid1View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperGrid1View)
	DDX_Control(pDX, IDC_LIST1, wndList);
	//}}AFX_DATA_MAP
}

BOOL CSuperGrid1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSuperGrid1View printing

BOOL CSuperGrid1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSuperGrid1View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	wndList.SetPrintFlag(ptUseColor|ptUseFonts|ptListName|ptPageNumbers|ptPageDate);
	wndList.SetPrintName("here's the data name");
	wndList.SetMargins(15,10,10,10);
	wndList.OnBeginPrinting(pDC, pInfo);
}

void CSuperGrid1View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	wndList.OnEndPrinting(pDC, pInfo);
}

void CSuperGrid1View::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	wndList.OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CSuperGrid1View diagnostics

#ifdef _DEBUG
void CSuperGrid1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CSuperGrid1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSuperGrid1Doc* CSuperGrid1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSuperGrid1Doc)));
	return (CSuperGrid1Doc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CSuperGrid1View message handlers

void CSuperGrid1View::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	if (wndList.GetSafeHwnd()) wndList.SetWindowPos(0,2,2,cx-4,cy-4,SWP_NOZORDER);

	SetScrollSizes(MM_TEXT, CSize(cx,cy));
	
}

int _DEFCOLS[] = 
{
	0,2,4,5,6,3,1,8,7
};

void CSuperGrid1View::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	CGfxColumnManager * pManager = wndList.CreateColumnManager();

	pManager->DefineColumn(0, "", NULL, LVCFMT_LEFT, 0, fhNoSortArrow|fhNoResizeColumn);
	pManager->DefineColumn(1, "Colonna 0");
	pManager->DefineColumn(2, "Colonna 1", NULL, LVCFMT_CENTER, 120, fhEdit|fhNumeric|fhSortAble);
	pManager->DefineColumn(3, "Colonna 2", NULL, LVCFMT_LEFT, 220, fhEdit|fhSortAble);
	pManager->DefineColumn(7, "Colonna 3", NULL, LVCFMT_LEFT, 120, fhEdit|fhSortAble);
	pManager->DefineColumn(4, NULL, NULL, LVCFMT_LEFT, 20, fhImage|fhNoSortArrow|fhNoResizeColumn|fhSortAble|fhColumnHasImage, 0, "Image 1");
	pManager->DefineColumn(5, NULL, NULL, LVCFMT_LEFT, 20, fhImage|fhNoSortArrow|fhNoResizeColumn|fhSortAble|fhColumnHasImage, 1, "Image 2");
	pManager->DefineColumn(6, NULL, NULL, LVCFMT_LEFT, 20, fhImage|fhNoSortArrow|fhNoResizeColumn|fhSortAble|fhColumnHasImage, 2, "Image 3");
	pManager->DefineColumn(8, "The Combox", NULL, LVCFMT_LEFT, 120, fhComboBoxEx|fhSortAble);

	pManager->DefineDefaultColumns(sizeof(_DEFCOLS)/sizeof(int), _DEFCOLS);

	pManager->ReadFromProfile("TheMainList");

	wndList.SetItemImageList(&lima);
	wndList.SetHeaderImageList(&limah);
	
	wndList.OnInit();
	wndList.ModifyFlag(0,fHighRowSelect|fVertGrid|fHorizGrid|fAutoSort,0);
	SetWindowPos(0,0,0,0,0,SWP_FRAMECHANGED);
	
	wndList.SetupColumnData();

	wndList.SetItemCount(200);

	for (int t = 0; t < 200; t++)
		wndList.InsertItemEx(t,t);

	wndList.SetItemHeight(17);

	wndList.SetCategoryCallback((void (CWnd::*)(CGfxCategoryManager * , long &))CategoryCallBack);
//	wndList.SetGetTextCallback((void (CWnd::*)(int , int, long, CString &)) GetTextCallback);
	wndList.SetExInfoCallback((long (CWnd::*)(LXHDREX *))GetExInfoCallback);
}

void CSuperGrid1View::GetTextCallback(int iIndex, int iSubItem, long lCode, CString &cs)
{
	cs = "";
	int rc = wndList.GetColumnIndex(iSubItem);
	if (rc == 4) cs = "1";
	else if (rc == 5) cs = "2";
	else if (rc == 6) cs = "3";
	else if (rc == 2) cs.Format("%d", lCode);
	else if (rc == 3) cs.Format("ma perche' non funziona ? non riesco a capire, porcaccia miseria %d", lCode);
	else cs.Format("%d, %d", lCode, rc);
}

void CSuperGrid1View::OnGetdispinfoList1(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CSuperGrid1View::CategoryCallBack(CGfxCategoryManager * pCatMan, long & lData)
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

void CSuperGrid1View::OnCustomheader() 
{
	wndList.OnGfxCustomizehead();
}

void CSuperGrid1View::OnFormatheader() 
{
	wndList.OnGfxFormatheader();
}

void CSuperGrid1View::OnListCmdUpdate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(true);
}

void CSuperGrid1View::OnTestcat() 
{
	if (wndList.GetCategoryManager()) wndList.EnableCategoryView(false);
	else wndList.EnableCategoryView(true);
	
}

void CSuperGrid1View::OnUpdateTestcat(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(wndList.GetCategoryManager() != NULL);
}

void CSuperGrid1View::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	int i = wndList.GetNextItem(-1, LVNI_SELECTED);
	if (i < 0) return;
	int idx = wndList.GetItemData(i);
	CString cs;
	cs.Format("Click on %d", idx);
	AfxMessageBox(cs);	
}

long CSuperGrid1View::GetExInfoCallback(LXHDREX * pLx)
{
	ASSERT(pLx);

	switch(pLx->iNotifyCode)
	{
	case NTEX_ITEMINFO:
		if (pLx->dwItemData < 25 || (pLx->dwItemData > 200 && pLx->dwItemData % 2 == 0))
			pLx->dwFlag |= LXHDREX::exBold;

		if (pLx->iSubItem == 7) pLx->dwFlag |= LXHDREX::exUnderline;
		if (pLx->iSubItem == 2)
		{
			pLx->hfText = (HFONT) ftTimes.GetSafeHandle();
			pLx->dwFlag |= LXHDREX::exHFont;
		}
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

LRESULT CSuperGrid1View::OnListExNotify(WPARAM wParam, LPARAM lParam)
{
	TRACE0("OnListExNotify\n");
	LXHDREX * pLx = (LXHDREX *) lParam;
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
		if (pLx->iSubItem == 2)
		{
			pLx->hfText = (HFONT) ftTimes.GetSafeHandle();
			pLx->dwFlag |= LXHDREX::exHFont;
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
		wndList.SetItemText(pLx->iItem, pLx->iSubItem, pLx->csText);
		return 1;
	};

	return 0L;
}

void CSuperGrid1View::OnAddanitem() 
{
	static int inewitem = 317;
	wndList.InsertItemEx(wndList.GetItemCount(), inewitem++);
}

void CSuperGrid1View::OnDestroy() 
{
	if (wndList.GetCategoryManager()) wndList.EnableCategoryView(false);
	CGfxColumnManager * pManager = wndList.GetColumnManager();
	pManager->RetrieveColumnData(&wndList);
	pManager->WriteToProfile("TheMainList");

	CFormView::OnDestroy();
}

void CSuperGrid1View::OnBlendbmp() 
{
	wndList.SetBlendBitmap(!wndList.bBlendBitmap);
	wndList.Invalidate();
}

void CSuperGrid1View::OnUpdateBlendbmp(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(wndList.bBlendBitmap);
	pCmdUI->Enable(iSelBmp >= 0);

}

void CSuperGrid1View::OnTrybitmap1() 
{
	if (iSelBmp == 0)
	{
		wndList.SetBkImage(-1);
		iSelBmp = -1;
	}
	else 
	{
		wndList.SetBkImage(IDB_BITMAP1);
		iSelBmp = 0;
	}
	wndList.Invalidate();
}

void CSuperGrid1View::OnUpdateTrybitmap1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iSelBmp == 0);
}

void CSuperGrid1View::OnTrybitmap2() 
{
	if (iSelBmp == 1)
	{
		wndList.SetBkImage(-1);
		iSelBmp = -1;
	}
	else 
	{
		wndList.SetBkImage(IDB_BITMAP2);
		iSelBmp = 1;
	}
	wndList.Invalidate();
}

void CSuperGrid1View::OnUpdateTrybitmap2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iSelBmp == 1);
}

void CSuperGrid1View::OnDraggablecol() 
{
	wndList.EnableColumnDrag(!wndList.IsColumnDragEnabled());
}

void CSuperGrid1View::OnUpdateDraggablecol(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(wndList.IsColumnDragEnabled());	
}

void CSuperGrid1View::OnGridh() 
{
	if (wndList.GetFlag() & fHorizGrid) wndList.ModifyFlag(fHorizGrid, 0, 0);
	else wndList.ModifyFlag(0, fHorizGrid, 0);

	Invalidate();
	
}

void CSuperGrid1View::OnUpdateGridh(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(wndList.GetFlag() & fHorizGrid ? 1 : 0);
}

void CSuperGrid1View::OnGridv() 
{
	if (wndList.GetFlag() & fVertGrid) wndList.ModifyFlag(fVertGrid, 0, 0);
	else wndList.ModifyFlag(0, fVertGrid, 0);
	Invalidate();
}

void CSuperGrid1View::OnUpdateGridv(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(wndList.GetFlag() & fVertGrid ? 1 : 0);
	
}

void CSuperGrid1View::OnEditCopy() 
{
	wndList.DoCopyInClipboard(wndList.GetSelectedCount() > 0 ? true : false);
}

void CSuperGrid1View::OnTestdao() 
{
	// see the other demo at codeguru for dao sample, here i putted instead a dialog demo
	CTestDialog dlg;
	dlg.DoModal();
}

void CSuperGrid1View::OnUpdateTestdao(CCmdUI* pCmdUI) 
{

}

void CSuperGrid1View::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CSuperGrid1View::OnAutopreview() 
{
	int oah = wndList.GetAutoPreviewHeight();
	if (oah <= 0) wndList.SetAutoPreviewHeight(30);
	else wndList.SetAutoPreviewHeight(0);
}

void CSuperGrid1View::OnUpdateAutopreview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(wndList.GetAutoPreviewHeight());
	pCmdUI->Enable(wndList.GetCategoryManager() == NULL);
}
