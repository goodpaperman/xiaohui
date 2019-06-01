// TestPage3.cpp : implementation file
//

#include "stdafx.h"
#include "WizDlg.h"
#include "TestPage3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPage3 dialog


CTestPage3::CTestPage3(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPage3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestPage3)
	iTestInt = 0;
	//}}AFX_DATA_INIT
}


void CTestPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPage3)
	DDX_Text(pDX, IDC_EDIT1, iTestInt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestPage3, CDialog)
	//{{AFX_MSG_MAP(CTestPage3)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPage3 message handlers

void CTestPage3::OnCancel() { }
void CTestPage3::OnOK() { }
