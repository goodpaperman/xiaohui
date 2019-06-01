// TestDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GfxList.h"
#include "TestDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDialog dialog


CTestDialog::CTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	lima.Create(IDB_ARANLIST, 16, 0, RGB(255,0,255));
	limah.Create(IDB_ARANCOL, 11, 0, RGB(255,0,255));

	ftTimes.CreatePointFont(90, "Times New Roman");
}


void CTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDialog)
	DDX_Control(pDX, IDC_LIST1, wndList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDialog, CDialog)
	//{{AFX_MSG_MAP(CTestDialog)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, OnGetdispinfoList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDialog message handlers

BOOL CTestDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	return true;
	
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

	int _DEFCOLS[] = { 0,2,4,5,6,3,1,8,7 };

	pManager->DefineDefaultColumns(sizeof(_DEFCOLS)/sizeof(int), _DEFCOLS);

	pManager->ReadFromProfile("TheDialogList");

	wndList.SetItemImageList(&lima);
	wndList.SetHeaderImageList(&limah);
	
	wndList.OnInit();
	wndList.ModifyFlag(0,fHighRowSelect|fVertGrid|fHorizGrid|fAutoSort,0);

	wndList.SetupColumnData();

//	SetWindowPos(0,0,0,0,0,SWP_FRAMECHANGED);
	

	wndList.SetItemCount(200);

	for (int t = 0; t < 200; t++)
		wndList.InsertItemEx(t,t);

	wndList.SetItemHeight(17);

	wndList.SetCategoryCallback((void (CWnd::*)(CGfxCategoryManager * , long &))CategoryCallBack);
	wndList.SetExInfoCallback((long (CWnd::*)(LXHDREX *))GetExInfoCallback);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CTestDialog::CategoryCallBack(CGfxCategoryManager * pCatMan, long & lData)
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

void CTestDialog::OnGetdispinfoList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = 0;

	long index = pDispInfo->item.iItem;
	long subItem = pDispInfo->item.iSubItem;
	long objCode = pDispInfo->item.lParam;

	if(pDispInfo->item.mask & LVIF_TEXT)
	{
		CString cs;

		int rc = wndList.GetColumnIndex(subItem);
		if (rc == 4) cs = "1";
		else if (rc == 5) cs = "2";
		else if (rc == 6) cs = "3";
		else if (rc == 2) cs.Format("%d", objCode);
		else if (rc == 3) cs.Format("col 3 -  item %d", objCode);
		else cs.Format("%d, %d", objCode, rc);

		lstrcpyn(pDispInfo->item.pszText, cs, pDispInfo->item.cchTextMax);
		*pResult = 1;

	}
	
	if(pDispInfo->item.mask & LVIF_IMAGE) pDispInfo->item.iImage = 0;//set image to first in list	
	
}

long CTestDialog::GetExInfoCallback(LXHDREX * pLx)
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
	};

	return 0L;
}

BOOL CTestDialog::DestroyWindow() 
{
	if (wndList.GetCategoryManager()) wndList.EnableCategoryView(false);
	CGfxColumnManager * pManager = wndList.GetColumnManager();
	pManager->RetrieveColumnData(&wndList);
	pManager->WriteToProfile("TheDialogList");
	
	return CDialog::DestroyWindow();
}
