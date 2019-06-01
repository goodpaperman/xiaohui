// PageOneDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Sample.h"
#include "PageOneDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageOneDialog dialog


CPageOneDialog::CPageOneDialog(CWnd* pParent /*=NULL*/)
	: TStackedPage(CPageOneDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageOneDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageOneDialog::DoDataExchange(CDataExchange* pDX)
{
	TStackedPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageOneDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageOneDialog, TStackedPage)
	//{{AFX_MSG_MAP(CPageOneDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageOneDialog message handlers
