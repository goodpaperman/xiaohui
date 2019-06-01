// TestPage2.cpp : implementation file
//

#include "stdafx.h"
#include "WizDlg.h"
#include "TestPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPage2 dialog


CTestPage2::CTestPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPage2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestPage2)
	iTestInt = 0;
	//}}AFX_DATA_INIT
}


void CTestPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPage2)
	DDX_Text(pDX, IDC_EDIT1, iTestInt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestPage2, CDialog)
	//{{AFX_MSG_MAP(CTestPage2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPage2 message handlers

void CTestPage2::OnCancel() { }
void CTestPage2::OnOK() { }
