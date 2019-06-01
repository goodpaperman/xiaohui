// BtnTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BtnTest.h"
#include "BtnTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBtnTestDlg dialog

CBtnTestDlg::CBtnTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBtnTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBtnTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBtnTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBtnTestDlg)
    DDX_Control(pDX, IDC_BTN, m_btn); 
    DDX_Control(pDX, IDC_BTN2, m_btn2); 
    DDX_Control(pDX, IDC_BTN3, m_btn3); 
    DDX_Control(pDX, IDC_BTN_3D, m_btn4); 
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBtnTestDlg, CDialog)
	//{{AFX_MSG_MAP(CBtnTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN2, OnBtn2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBtnTestDlg message handlers

BOOL CBtnTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
    m_btn.SetTextColor(RGB(0, 0, 255)); 
    m_btn.SetBkgndColor(RGB(128, 128, 128)); 

    m_btn3.SetIcon(IDI_CD, 32, 32); 
    m_btn3.SetImageOffset(20); 
    m_btn3.SetTextOffset(10); 
    m_btn3.SetColorTab(RGB(0, 0, 255)); 
    m_btn3.SetDefaultButton(); 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBtnTestDlg::OnPaint() 
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
HCURSOR CBtnTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBtnTestDlg::OnBtn2() 
{
	// TODO: Add your control notification handler code here
	MessageBeep(0xFFFFFFFF); 
}
