// PageTwoDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "PageTwoDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageTwoDialog dialog


CPageTwoDialog::CPageTwoDialog(CWnd* pParent /*=NULL*/)
	: TStackedPage(CPageTwoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageTwoDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageTwoDialog::DoDataExchange(CDataExchange* pDX)
{
	TStackedPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageTwoDialog)
	DDX_Control(pDX, IDC_LIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageTwoDialog, TStackedPage)
	//{{AFX_MSG_MAP(CPageTwoDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageTwoDialog message handlers

BOOL CPageTwoDialog::OnInitDialog() 
{
	TStackedPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_List.InsertColumn(0, "First column");
  m_List.InsertColumn(1, "Second column");

  m_List.InsertItem(0, "Test item 1");
  m_List.InsertItem(1, "Test item 2");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
