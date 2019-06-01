// AVCDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AVCDemo.h"
#include "AVCDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVCDemoDlg dialog

CAVCDemoDlg::CAVCDemoDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CAVCDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAVCDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAVCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAVCDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAVCDemoDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CAVCDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnApply)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVCDemoDlg message handlers

BOOL CAVCDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	DWORD dwStyle = GetClassLong(m_hWnd, GCL_STYLE);
	dwStyle |= (CS_HREDRAW|CS_VREDRAW);
	SetClassLong(m_hWnd, GCL_STYLE, dwStyle);

	GetDlgItem(IDC_ST_VIDEO)->GetWindowRect(&m_crOrigAVIWnd);
	m_crOrigAVIWnd.OffsetRect(-GetSystemMetrics(SM_CXSIZEFRAME),
							  -(GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYSIZEFRAME)));

	CheckDlgButton(IDC_CHK_CNTRAVI, 1);
	
	SetBitmap(IDB_BACKGROUND, CBitmapDialog::BITMAP_STRETCH);

	VERIFY(m_AviCtrl.SubclassDlgItem(IDC_ST_VIDEO, this));
	//VERIFY(m_AviCtrl.Load(IDR_AVIFILE1, AVC_AUTOPLAY|AVC_CENTERAVI) == NOERROR);
    VERIFY(m_AviCtrl.Load("Test.avi", AVC_AUTOPLAY | AVC_CENTERAVI) == NOERROR); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAVCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAVCDemoDlg::OnPaint() 
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
// the minimized window.
HCURSOR CAVCDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAVCDemoDlg::OnApply() 
{
	DWORD dwFlags = AVC_AUTOPLAY;
	
	if (IsDlgButtonChecked(IDC_CHK_HALFSPEED))		dwFlags |= AVC_HALFSPEED;
	if (IsDlgButtonChecked(IDC_CHK_DBLSPEED))		dwFlags |= AVC_DOUBLESPEED;
	if (IsDlgButtonChecked(IDC_CHK_STRETCHAVI))		dwFlags |= AVC_STRETCHAVI;
	if (IsDlgButtonChecked(IDC_CHK_CNTRAVI))		dwFlags |= AVC_CENTERAVI;
	if (IsDlgButtonChecked(IDC_CHK_CNTRRECT))		dwFlags |= AVC_CENTERRECT;
	if (IsDlgButtonChecked(IDC_CHK_MAPWNDCOL))		dwFlags |= AVC_MAPWINDOWCOLOR;

	GetDlgItem(IDC_ST_VIDEO)->MoveWindow(&m_crOrigAVIWnd);

	VERIFY(m_AviCtrl.Load(IDR_AVIFILE1, dwFlags) == NOERROR);

	Invalidate();
}

void CAVCDemoDlg::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	CBitmapDialog::OnWindowPosChanging(lpwndpos);
	
    //if(lpwndpos->flags & SWP_NOSIZE)
    //    return; 
    
    //m_AviCtrl.ReinitBackground();	
}

void CAVCDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CBitmapDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_AviCtrl.ReinitBackground(); 
}
