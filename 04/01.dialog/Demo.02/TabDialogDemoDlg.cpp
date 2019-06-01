// TabDialogDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TabDialogDemo.h"
#include "TabDialogDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabDialogDemoDlg dialog

CTabDialogDemoDlg::CTabDialogDemoDlg(CWnd* pParent /*=NULL*/)
	: CTabDialog(CTabDialogDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabDialogDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	
	m_hTitleIcon = m_hIcon;
	m_sTitle  = "Sample";
	//m_bAutoTabSize = FALSE;
	m_nBorderPos = TAB_BORDER_TOP;
	m_nXpos = 100;
	//m_bCloseBox = FALSE;
}

void CTabDialogDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CTabDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabDialogDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTabDialogDemoDlg, CTabDialog)
	//{{AFX_MSG_MAP(CTabDialogDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDialogDemoDlg message handlers

BOOL CTabDialogDemoDlg::OnInitDialog()
{
	CTabDialog::OnInitDialog();

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

void CTabDialogDemoDlg::OnPaint() 
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
		CTabDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTabDialogDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
