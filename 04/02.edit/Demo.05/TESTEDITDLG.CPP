// TestEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestEdit.h"
#include "TestEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestEditDlg dialog


CTestEditDlg::CTestEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestEditDlg)
	m_EditMaxH = _T("23");
	m_EditMaxM = _T("59");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CTestEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestEditDlg)
	DDX_Control(pDX, IDC_EDIT7, m_EditPCodeCtrl);
	DDX_Control(pDX, IDC_EDIT6, m_EditIPCtrl);
	DDX_Control(pDX, IDC_EDIT5, m_EditPhoneCtrl);
	DDX_Control(pDX, IDC_EDIT4, m_DateEditCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_TimeEditCtrl);
	DDX_Text(pDX, IDC_EDIT2, m_EditMaxH);
	DDV_MaxChars(pDX, m_EditMaxH, 2);
	DDX_Text(pDX, IDC_EDIT3, m_EditMaxM);
	DDV_MaxChars(pDX, m_EditMaxM, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestEditDlg, CDialog)
	//{{AFX_MSG_MAP(CTestEditDlg)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestEditDlg message handlers

void CTestEditDlg::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_TimeEditCtrl.SetHours(atoi(m_EditMaxH));
}

void CTestEditDlg::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_TimeEditCtrl.SetMins(atoi(m_EditMaxM));
}

BOOL CTestEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//CTimeEdit Initialisation
	m_TimeEditCtrl.SetTime(COleDateTime::GetCurrentTime());
	//CDateEdit Initialisation
	m_DateEditCtrl.SetDate(COleDateTime::GetCurrentTime());
	//CMaskEdit - Telephone Initialisation
	m_EditPhoneCtrl.m_bisTime	     = FALSE;
	m_EditPhoneCtrl.m_isdate	     = FALSE;
	m_EditPhoneCtrl.m_bUseMask       = TRUE;
	m_EditPhoneCtrl.m_strMask        = "0000 0000000";
	m_EditPhoneCtrl.m_strLiteral     = "____ _______";
	m_EditPhoneCtrl.m_str            = "0116 2111111";
	m_EditPhoneCtrl.m_strMaskLiteral = m_EditPhoneCtrl.m_str;
	m_EditPhoneCtrl.SetWindowText(m_EditPhoneCtrl.m_str);
	//CMaskEdit - IP Address Initialisation
	m_EditIPCtrl.m_bisTime	      = FALSE;
	m_EditIPCtrl.m_isdate	      = FALSE;
	m_EditIPCtrl.m_bUseMask       = TRUE;
	m_EditIPCtrl.m_strMask        = "999.999.999.999";
	m_EditIPCtrl.m_strLiteral     = "___.___.___.___";
	m_EditIPCtrl.m_str            = "209.66 .99 .126";
	m_EditIPCtrl.m_strMaskLiteral = m_EditIPCtrl.m_str;
	m_EditIPCtrl.SetWindowText(m_EditIPCtrl.m_str);
	//CMaskEdit - IPost Code Initialisation
	m_EditPCodeCtrl.m_bisTime	     = FALSE;
	m_EditPCodeCtrl.m_isdate	     = FALSE;
	m_EditPCodeCtrl.m_bUseMask       = TRUE;
	m_EditPCodeCtrl.m_strMask        = "LL00 0LL";
	m_EditPCodeCtrl.m_strLiteral     = "____ ___";
	m_EditPCodeCtrl.m_str            = "LE12 7AT";
	m_EditPCodeCtrl.m_strMaskLiteral = m_EditPCodeCtrl.m_str;
	m_EditPCodeCtrl.SetWindowText(m_EditPCodeCtrl.m_str);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestEditDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestEditDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
