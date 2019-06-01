// SuperProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperProgress.h"
#include "SuperProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperProgressDlg dialog

CSuperProgressDlg::CSuperProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuperProgressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nMin = 0;
	m_nMax = 100;
	m_nStep = 10;
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuperProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperProgressDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_MAX, m_nMax);
	DDX_Text(pDX, IDC_MIN, m_nMin);
	DDX_Text(pDX, IDC_STEP, m_nStep);
}

BEGIN_MESSAGE_MAP(CSuperProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CSuperProgressDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_BN_CLICKED(IDC_STEPIT, OnStepIt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperProgressDlg message handlers

BOOL CSuperProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CSuperProgressCtrl::RegisterClass();

	progress.Create(this, 10, 10, LoadBitmap(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_PROGRESS)), 0);
	progress.SetFillStyle(SP_FILL_HORZGRAD);
	progress.SetColours(RGB(0,0,255), RGB(255,0,0));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSuperProgressDlg::OnPaint() 
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
HCURSOR CSuperProgressDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSuperProgressDlg::OnGo() 
{
	UpdateData(TRUE);
	progress.SetRange(m_nMin, m_nMax);
	progress.SetStep(m_nStep);
	// Disable the Go and OK Buttons
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_GO)->EnableWindow(FALSE);
	GetDlgItem(IDC_STEPIT)->EnableWindow(FALSE);
	for(int i=m_nMin; i<=m_nMax; i++)
	{
		progress.SetPos(i);
		// Perform MFC's message loop
		if(!progress.MessageLoop())
			break;
	}
	// Enable the Buttons
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_GO)->EnableWindow(TRUE);
	GetDlgItem(IDC_STEPIT)->EnableWindow(TRUE);
}

void CSuperProgressDlg::OnStepIt() 
{
	UpdateData(TRUE);
	progress.SetRange(m_nMin, m_nMax);
	progress.SetStep(m_nStep);
	progress.StepIt();
}