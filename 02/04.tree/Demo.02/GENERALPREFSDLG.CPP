// GeneralPrefsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TPS_Demo.h"
#include "GeneralPrefsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralPrefsDlg dialog


CGeneralPrefsDlg::CGeneralPrefsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneralPrefsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeneralPrefsDlg)
	m_bISee = ((CTPS_DemoApp*)AfxGetApp())->gprf_bISee;
	m_bDontLike = ((CTPS_DemoApp*)AfxGetApp())->gprf_bDontLike;
	m_bLikeBeer = ((CTPS_DemoApp*)AfxGetApp())->gprf_bLikeBeer;
	m_nWhen = ((CTPS_DemoApp*)AfxGetApp())->gprf_nWhen;
	//}}AFX_DATA_INIT
}


void CGeneralPrefsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralPrefsDlg)
	DDX_Check(pDX, IDC_CHECK1, m_bISee);
	DDX_Check(pDX, IDC_CHECK2, m_bDontLike);
	DDX_Check(pDX, IDC_CHECK3, m_bLikeBeer);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nWhen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeneralPrefsDlg, CDialog)
	//{{AFX_MSG_MAP(CGeneralPrefsDlg)
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneralPrefsDlg message handlers

BOOL CGeneralPrefsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGeneralPrefsDlg::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	((CTPS_DemoApp*)AfxGetApp())->gprf_bISee = m_bISee;
	((CTPS_DemoApp*)AfxGetApp())->gprf_bDontLike = m_bDontLike;
	((CTPS_DemoApp*)AfxGetApp())->gprf_bLikeBeer = m_bLikeBeer;
	((CTPS_DemoApp*)AfxGetApp())->gprf_nWhen = m_nWhen;
}
