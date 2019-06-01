// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AboutDlg.h"

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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EMAILLINK, m_EMailLink);
	DDX_Control(pDX, IDC_HOMEPAGELINK, m_HomePageLink);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Set HyperLink for E-Mail
	m_EMailLink.SetURL(_T(IDS_MAILADDR));
	m_EMailLink.SetUnderline(TRUE);
	m_EMailLink.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	m_EMailLink.SetAutoSize(TRUE);

	// Set HyperLink for Home Page
	m_HomePageLink.SetURL(_T(IDS_HOMEPAGEADDR));
	m_HomePageLink.SetUnderline(TRUE);
	m_HomePageLink.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	m_HomePageLink.SetAutoSize(TRUE);
		
	SetLogoFont("Verdana", -25);

	// Write class version
	CString sVersion;
	sVersion.Format("CColorStaticST v%s", CColorStaticST::GetVersionC());
	GetDlgItem(IDC_VERSION)->SetWindowText(sVersion);

	// Fill friends listbox
	CListBox* lbxFriends;
	lbxFriends = (CListBox*)GetDlgItem(IDC_FRIENDS);
    lbxFriends->AddString("Haihai107@126.com"); 

	return TRUE;
}


void CAboutDlg::SetLogoFont(CString Name, int nHeight, int nWeight, BYTE bItalic, BYTE bUnderline)
{
    if(m_fontLogo.m_hObject) m_fontLogo.Detach();
    
    m_fontLogo.CreateFont(nHeight, 0, 0, 0, nWeight, bItalic, bUnderline,0,0,0,0,0,0, Name);
} // End of SetLogoFont


void CAboutDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    CRect rectDlg;
    GetWindowRect(rectDlg);
    ScreenToClient(rectDlg);

    CFont* OldFont = dc.SelectObject(&m_fontLogo);

    CSize sizeText = dc.GetTextExtent(STSIGN, strlen(STSIGN));

    dc.DrawState(CPoint((rectDlg.Width()-sizeText.cx)/2, 10), 
                 rectDlg.Size(), 
                 STSIGN, 
                 DSS_DISABLED, TRUE, 0, (CBrush*)NULL);

    dc.SelectObject(OldFont);
} // End of OnPaint
