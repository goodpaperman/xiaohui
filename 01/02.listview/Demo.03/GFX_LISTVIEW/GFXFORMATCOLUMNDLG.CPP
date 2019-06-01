// GfxFormatColumnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CGfxListView.h"


#include "GfxFormatColumnDlg.h"
#include "GfxColumnManager.h"
#include "GfxListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxFormatColumnDlg dialog

#define _FCD_IMAGE		"Image"

#define _FCD_TEXT		"Text"
#define _FCD_NUMERIC	"Numeric"
#define _FCD_VALUE		"Valute"

#define _FCD_LIST		"Drop list"
#define _FCD_COMBO		"Drop down list"
#define _FCD_EDIT		"Edit"

/*
#define _FCD_IMAGE	"Immagine"

#define _FCD_TEXT		"Testo"
#define _FCD_NUMERIC	"Numerico"
#define _FCD_VALUE		"Valuta"

#define _FCD_LIST		"Testo da lista multipla"
#define _FCD_COMBO		"Casella di testo con lista multipla"
#define _FCD_EDIT		"Casella di testo"
*/

CGfxFormatColumnDlg::CGfxFormatColumnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGfxFormatColumnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGfxFormatColumnDlg)
	csLabel = _T("");
	csLabelDt = _T("");
	iWidth = 0;
	csType = _T("");
	//}}AFX_DATA_INIT
	pOrigManager = pManager = NULL;
}


void CGfxFormatColumnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGfxFormatColumnDlg)
	DDX_Control(pDX, IDC_CB_FORMAT, wndFormat);
	DDX_Control(pDX, IDC_ACTCOL, wndCol);
	DDX_Text(pDX, IDC_CD_LABEL, csLabel);
	DDX_Text(pDX, IDC_LABEL_DT, csLabelDt);
	DDX_Text(pDX, IDC_WIDTH, iWidth);
	DDV_MinMaxInt(pDX, iWidth, 0, 1024);
	DDX_Text(pDX, IDC_FMT, csType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGfxFormatColumnDlg, CDialog)
	//{{AFX_MSG_MAP(CGfxFormatColumnDlg)
	ON_LBN_SELCHANGE(IDC_ACTCOL, OnSelchangeActcol)
	ON_BN_CLICKED(IDC_RD_CENTER, OnRdCenter)
	ON_BN_CLICKED(IDC_RD_LEFT, OnRdLeft)
	ON_BN_CLICKED(IDC_RD_RIGHT, OnRdRight)
	ON_EN_KILLFOCUS(IDC_WIDTH, OnKillfocusWidth)
	ON_EN_KILLFOCUS(IDC_LABEL_DT, OnKillfocusLabelDt)
	ON_EN_KILLFOCUS(IDC_CD_LABEL, OnKillfocusCdLabel)
	ON_CBN_KILLFOCUS(IDC_CB_FORMAT, OnKillfocusCbFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGfxFormatColumnDlg message handlers

BOOL CGfxFormatColumnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ASSERT(pManager);

	pOrigManager = new CGfxColumnManager(pManager);

	CGfxColumnManager * pt = pManager;

	pManager = pOrigManager;
	pOrigManager = pt;

	int iFirst = -1;
	
	for (int i = 0; i < pManager->iDefColumn; i ++)
	{
		int t = pManager->FindColumnById(pManager->pDefColumn[i]);
		if (t >= 0)
		{
			CString cs;

			if (pManager->pColumnData[t].dwData & fhImage)
				cs = pManager->pColumnData[t].cDescr ? pManager->pColumnData[t].cDescr : pManager->pColumnData[t].cText;
			else
				cs = pManager->pColumnData[t].cText;

			if (cs != "")
			{
				wndCol.SetItemData(wndCol.AddString(cs), t);//pManager->pColumnData[t].iId);
				if (iFirst < 0) iFirst = t; //pManager->pColumnData[t].iId;
			}
		}
	}
	if (iFirst >= 0) 
	{
		SetColumn(iFirst);
		wndCol.SetCurSel(0);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGfxFormatColumnDlg::OnSelchangeActcol() 
{
	int idx = wndCol.GetCurSel();
	if (idx >= 0) SetColumn((int) wndCol.GetItemData(idx));
}

void CGfxFormatColumnDlg::OnOK() 
{
	int ic = pManager->iColumnData;
	CGfxColumnManager::CGfxColumn * ptc = pManager->pColumnData;

	pManager->iColumnData = pOrigManager->iColumnData;
	pManager->pColumnData = pOrigManager->pColumnData;

	pOrigManager->iColumnData = ic;
	pOrigManager->pColumnData = ptc;

//	int i = pManager->iDefColumn;
//	int * ipt = pManager->pDefColumn;

	CDialog::OnOK();
}

void CGfxFormatColumnDlg::SetColumn(const int iId)
{
	csType = "";

	ASSERT(pManager);
	int idx = iId;//pManager->FindColumnById(iId);
	ASSERT(idx >= 0);
	if (idx >= 0)
	{
		CheckDlgButton(IDC_RD_RIGHT, 0);
		CheckDlgButton(IDC_RD_CENTER, 0);
		CheckDlgButton(IDC_RD_LEFT, 0);

		CClientDC dc(this);
		CSize sz = dc.GetTextExtent("AbCdEfGhIj MnOpQrStUvWxYz");
		iWidth = pManager->pColumnData[idx].iWidth / (sz.cx / 26);

		if (pManager->pColumnData[idx].dwData & fhImage)
		{
			csLabel = pManager->pColumnData[idx].cDescr ? pManager->pColumnData[idx].cDescr : pManager->pColumnData[idx].cText;
			csLabelDt = "";
			if (GetDlgItem(IDC_LABEL_DT)->IsWindowEnabled()) GetDlgItem(IDC_LABEL_DT)->EnableWindow(false);
			wndFormat.ResetContent();

			wndFormat.SetItemData(wndFormat.AddString(_FCD_IMAGE), 0);
			wndFormat.SetCurSel(0);
			CheckDlgButton(IDC_RD_CENTER, 1);
			if (GetDlgItem(IDC_RD_RIGHT)->IsWindowEnabled()) GetDlgItem(IDC_RD_RIGHT)->EnableWindow(false);
			if (GetDlgItem(IDC_RD_LEFT)->IsWindowEnabled()) GetDlgItem(IDC_RD_LEFT)->EnableWindow(false);
			if (GetDlgItem(IDC_RD_CENTER)->IsWindowEnabled()) GetDlgItem(IDC_RD_CENTER)->EnableWindow(false);
			if (GetDlgItem(IDC_WIDTH)->IsWindowEnabled()) GetDlgItem(IDC_WIDTH)->EnableWindow(false);
		}
		else
		{
			csLabel = pManager->pColumnData[idx].cText;
			if (!(GetDlgItem(IDC_LABEL_DT)->IsWindowEnabled())) GetDlgItem(IDC_LABEL_DT)->EnableWindow(true);
			wndFormat.ResetContent();
			wndFormat.SetItemData(wndFormat.AddString(_FCD_TEXT), 0);
			wndFormat.SetItemData(wndFormat.AddString(_FCD_NUMERIC), fhNumeric);
			wndFormat.SetItemData(wndFormat.AddString(_FCD_VALUE), fhValute);

			DWORD dw = pManager->pColumnData[idx].dwData;
			if (dw & fhNumeric) wndFormat.SetCurSel(1);
			else if (dw & fhValute) wndFormat.SetCurSel(2);
			else wndFormat.SetCurSel(0);
			if (dw & fhComboBox) csType = _FCD_LIST;
			else if (dw & fhComboBoxEx) csType = _FCD_COMBO;
			else if (dw & fhEdit) csType = _FCD_EDIT;

			if (!(GetDlgItem(IDC_RD_CENTER)->IsWindowEnabled())) GetDlgItem(IDC_RD_CENTER)->EnableWindow(true);
			if (!(GetDlgItem(IDC_RD_RIGHT)->IsWindowEnabled())) GetDlgItem(IDC_RD_RIGHT)->EnableWindow(true);
			if (!(GetDlgItem(IDC_RD_LEFT)->IsWindowEnabled())) GetDlgItem(IDC_RD_LEFT)->EnableWindow(true);

			if (!(GetDlgItem(IDC_WIDTH)->IsWindowEnabled())) GetDlgItem(IDC_WIDTH)->EnableWindow(true);

			if (pManager->pColumnData[idx].iAlign == LVCFMT_RIGHT) CheckDlgButton(IDC_RD_RIGHT, 1);
			else if (pManager->pColumnData[idx].iAlign == LVCFMT_CENTER) CheckDlgButton(IDC_RD_CENTER, 1);
			else CheckDlgButton(IDC_RD_LEFT, 1);
		}
	}
	UpdateData(FALSE);
}


void CGfxFormatColumnDlg::OnRdCenter() 
{
	int idx = wndCol.GetCurSel();
	if (idx >= 0) 
	{
		int id = wndCol.GetItemData(idx);
		pManager->pColumnData[id].iAlign = LVCFMT_CENTER;
	}
}

void CGfxFormatColumnDlg::OnRdLeft() 
{
	int idx = wndCol.GetCurSel();
	if (idx >= 0) 
	{
		int id = wndCol.GetItemData(idx);
		pManager->pColumnData[id].iAlign = LVCFMT_LEFT;
	}
}

void CGfxFormatColumnDlg::OnRdRight() 
{
	int idx = wndCol.GetCurSel();
	if (idx >= 0) 
	{
		int id = wndCol.GetItemData(idx);
		pManager->pColumnData[id].iAlign = LVCFMT_RIGHT;
	}
}

void CGfxFormatColumnDlg::OnKillfocusWidth() 
{
	int idx = wndCol.GetCurSel();
	if (idx >= 0) 
	{
		int id = wndCol.GetItemData(idx);
		if (GetDlgItem(IDC_WIDTH)->IsWindowEnabled())
		{
			CClientDC dc(this);
			CSize sz = dc.GetTextExtent("AbCdEfGhIj MnOpQrStUvWxYz");
			UpdateData(true);
			int iw = iWidth * (sz.cx / 26);
			pManager->pColumnData[id].iWidth = iw;
		}	
	}
}

void CGfxFormatColumnDlg::OnKillfocusLabelDt() 
{
	int idx = wndCol.GetCurSel();
	if (idx >= 0) 
	{
		int id = wndCol.GetItemData(idx);
		if (GetDlgItem(IDC_LABEL_DT)->IsWindowEnabled())
		{
			UpdateData(true);
			
			if (csLabelDt != "")
			{
				ASSERT(!(pManager->pColumnData[id].dwData & fhImage));
				
				if (pManager->pColumnData[id].cTextDt)
					delete [] pManager->pColumnData[id].cTextDt;

				pManager->pColumnData[id].cTextDt = new char[csLabelDt.GetLength() + 1];
				ASSERT(pManager->pColumnData[id].cTextDt);
				lstrcpy(pManager->pColumnData[id].cTextDt, csLabelDt);
			}
		}	
	}
}

void CGfxFormatColumnDlg::OnKillfocusCdLabel() 
{
	int idx = wndCol.GetCurSel();
	if (idx >= 0) 
	{
		int id = wndCol.GetItemData(idx);
		if (GetDlgItem(IDC_CD_LABEL)->IsWindowEnabled())
		{
			UpdateData(true);
			
			if (csLabel != "")
			{
				if (pManager->pColumnData[id].dwData & fhImage)
				{
					if (pManager->pColumnData[id].cDescr)
						delete [] pManager->pColumnData[id].cDescr;

					pManager->pColumnData[id].cDescr = new char[csLabel.GetLength() + 1];
					ASSERT(pManager->pColumnData[id].cDescr);
					lstrcpy(pManager->pColumnData[id].cDescr, csLabel);
				}
				else
				{
					if (pManager->pColumnData[id].cText)
						delete [] pManager->pColumnData[id].cText;

					pManager->pColumnData[id].cText = new char[csLabel.GetLength() + 1];
					ASSERT(pManager->pColumnData[id].cText);
					lstrcpy(pManager->pColumnData[id].cText, csLabel);
				}
				wndCol.DeleteString(idx);
				int newcol = wndCol.InsertString(idx, csLabel);
				wndCol.SetItemData(newcol, id);
				wndCol.SetCurSel(newcol);
			}
		}	
	}
}

void CGfxFormatColumnDlg::OnKillfocusCbFormat() 
{
	int idx = wndCol.GetCurSel();
	if (idx >= 0) 
	{
		int id = wndCol.GetItemData(idx);
		if (GetDlgItem(IDC_CB_FORMAT)->IsWindowEnabled())
		{
			if (!(pManager->pColumnData[id].dwData & fhImage))
			{
				UpdateData(true);

				int id = wndCol.GetItemData(idx);
				int fmtIdx = wndFormat.GetCurSel();
				DWORD fmtDw = wndFormat.GetItemData(fmtIdx);

				pManager->pColumnData[id].dwData &= ~(fhNumeric|fhValute);
				if (fmtDw != 0) pManager->pColumnData[id].dwData |= fmtDw;
			}
		}	
	}
}

BOOL CGfxFormatColumnDlg::DestroyWindow() 
{
	BOOL bRes = CDialog::DestroyWindow();
	if (pManager) delete pManager;
	return bRes;
}
