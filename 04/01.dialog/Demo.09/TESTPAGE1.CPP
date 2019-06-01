// TestPage1.cpp : implementation file
//

#include "stdafx.h"
#include "WizDlg.h"
#include "TestPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPage1 dialog


CTestPage1::CTestPage1(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPage1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestPage1, CDialog)
	//{{AFX_MSG_MAP(CTestPage1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPage1 message handlers

void CTestPage1::OnCancel() { }
void CTestPage1::OnOK() { }
