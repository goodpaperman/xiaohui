// PageThreeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "PageThreeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageThreeDialog dialog


CPageThreeDialog::CPageThreeDialog(CWnd* pParent /*=NULL*/)
	: TStackedPage(CPageThreeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageThreeDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageThreeDialog::DoDataExchange(CDataExchange* pDX)
{
	TStackedPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageThreeDialog)
	DDX_Control(pDX, IDC_TREE, m_Tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageThreeDialog, TStackedPage)
	//{{AFX_MSG_MAP(CPageThreeDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageThreeDialog message handlers

BOOL CPageThreeDialog::OnInitDialog() 
{
	TStackedPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	HTREEITEM htroot = m_Tree.InsertItem("Test root");
  m_Tree.InsertItem("Child A", htroot);
  m_Tree.InsertItem("Child B", htroot);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
