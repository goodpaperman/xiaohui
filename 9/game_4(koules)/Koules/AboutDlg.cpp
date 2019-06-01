// AboutDlg.cpp : implementation file
//

#include "headers.h"
#include "AboutDlg.h"
#include "ksrc\koules.h"
#include "ksrc\interface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog


CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_ver.LoadString(IDS_CHINASTR);
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_TIME, m_stat);
	DDX_Text(pDX, IDC_STATICINFO, m_ver);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ShowCursor(TRUE);
	SetTimer(0x100,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
	static count=0;
	count++;
	CString s;
	s.Format("%d",5-count);
	m_stat.SetWindowText(s);
	if(count==5)
		PostMessage(WM_CLOSE,NULL,NULL);
	CDialog::OnTimer(nIDEvent);
}

BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc,RGB(0,0,100));
	return TRUE;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr=CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor==CTLCOLOR_BTN || nCtlColor==CTLCOLOR_STATIC || nCtlColor==CTLCOLOR_EDIT)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(166,202,240));
		hbr=CreateSolidBrush(RGB(0,0,100));
	}
	return hbr;
}
