// CRgnedButtonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CRgnedButton.h"
#include "CRgnedButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCRgnedButtonDlg dialog

CCRgnedButtonDlg::CCRgnedButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCRgnedButtonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCRgnedButtonDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCRgnedButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCRgnedButtonDlg)
	DDX_Control(pDX, IDC_BUTTON3, m_Btn3);
	DDX_Control(pDX, IDC_BUTTON2, m_Btn2);
	DDX_Control(pDX, IDC_BUTTON1, m_Btn1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCRgnedButtonDlg, CDialog)
	//{{AFX_MSG_MAP(CCRgnedButtonDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCRgnedButtonDlg message handlers

BOOL CCRgnedButtonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCRgnedButtonDlg::OnPaint() 
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
HCURSOR CCRgnedButtonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
