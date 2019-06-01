// InfoBar.cpp : implementation file
//

#include "stdafx.h"
#include "restart.h"
#include "InfoBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoBar dialog


CInfoBar::CInfoBar(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pParentDlg = pParent;
}


void CInfoBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoBar)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoBar, CDialog)
	//{{AFX_MSG_MAP(CInfoBar)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoBar message handlers

BOOL CInfoBar::Create()
{ 
	return CDialog::Create(CInfoBar::IDD); 
}

BOOL CInfoBar::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
		if((UINT)pMsg->lParam == 65537)
			::PostMessage(pParentDlg->GetSafeHwnd(), WM_DESTROYINFOBAR, 0, 0);

	return CDialog::PreTranslateMessage(pMsg);
}


void CInfoBar::OnClose() 
{
	::PostMessage(pParentDlg->GetSafeHwnd(), WM_DESTROYINFOBAR, 0, 0);
	CDialog::OnClose();
}
