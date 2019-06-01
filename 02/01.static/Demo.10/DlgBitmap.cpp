// DlgBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "ExampleDIB.h"
#include "DlgBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBitmap dialog


CDlgBitmap::CDlgBitmap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBitmap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBitmap)
	m_Option = 0;
	//}}AFX_DATA_INIT
}


void CDlgBitmap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBitmap)
	DDX_Control(pDX, IDC_BMP_EXAMPLE, m_ActualBMP);
	DDX_Radio(pDX, IDC_RADIO1, m_Option);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBitmap, CDialog)
	//{{AFX_MSG_MAP(CDlgBitmap)
	ON_BN_CLICKED(IDC_RADIO1, OnBMP1)
	ON_BN_CLICKED(IDC_RADIO2, OnBMP2)
	ON_BN_CLICKED(IDC_RADIO3, OnBMP3)
	ON_BN_CLICKED(IDC_RADIO4, OnBMP4)
	ON_BN_CLICKED(IDC_RADIO5, OnBMP5)
	ON_BN_CLICKED(IDC_RADIO6, OnBMP6)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBitmap message handlers

void CDlgBitmap::OnBMP1() 
{
	m_ActualBMP.RemoveDib();
	m_ActualBMP.LoadDib("BMP1.bmp");
	m_ActualBMP.UpdateDib();
	return;
}

void CDlgBitmap::OnBMP2() 
{
	m_ActualBMP.RemoveDib();
	m_ActualBMP.LoadDib("BMP2.bmp");
	m_ActualBMP.UpdateDib();
	return;
}

void CDlgBitmap::OnBMP3() 
{
	m_ActualBMP.RemoveDib();
	m_ActualBMP.LoadDib("BMP3.bmp");
	m_ActualBMP.UpdateDib();
	return;
}

void CDlgBitmap::OnBMP4() 
{
	m_ActualBMP.RemoveDib();
	m_ActualBMP.LoadDib("BMP4.bmp");
	m_ActualBMP.UpdateDib();
	return;
}

void CDlgBitmap::OnBMP5() 
{
	m_ActualBMP.RemoveDib();
	m_ActualBMP.LoadDib("BMP5.bmp");
	m_ActualBMP.UpdateDib();
	return;
}

void CDlgBitmap::OnBMP6() 
{
	m_ActualBMP.RemoveDib();
	m_ActualBMP.LoadDib("BMP6.bmp");
	m_ActualBMP.UpdateDib();
	return;
}

BOOL CDlgBitmap::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ActualBMP.LoadDib("BMP1.bmp");
	m_ActualBMP.UpdateDib();

	UpdateData ( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBitmap::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_ActualBMP.RemoveDib();		
	return;
}
