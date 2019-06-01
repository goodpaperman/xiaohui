// AlexfHistogramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AlexfHistogram.h"
#include "AlexfHistogramDlg.h"

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
// CAlexfHistogramDlg dialog

CAlexfHistogramDlg::CAlexfHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlexfHistogramDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlexfHistogramDlg)
	m_iRadio1 = 0;
	m_iRadio3 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlexfHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlexfHistogramDlg)
	DDX_Control(pDX, IDC_HISTOGRAM, m_sHistogram);
	DDX_Radio(pDX, IDC_RADIO1, m_iRadio1);
	DDX_Radio(pDX, IDC_RADIO3, m_iRadio3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAlexfHistogramDlg, CDialog)
	//{{AFX_MSG_MAP(CAlexfHistogramDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlexfHistogramDlg message handlers

BOOL CAlexfHistogramDlg::OnInitDialog()
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

	m_sHistogram.SetTextWidth(70);
	m_sHistogram.SetTextLines(7);
	m_sHistogram.text[0] = "Z1";
	m_sHistogram.text[1] = "Zz2";
	m_sHistogram.text[2] = "Zzz3";
	m_sHistogram.text[3] = "Zzzz4";
	m_sHistogram.text[4] = "Zzzzzz5";
	m_sHistogram.text[5] = "Zzzzzzz6";
	m_sHistogram.text[6] = "Zzzzzzzz7";
	m_sHistogram.Add(50);
    m_sHistogram.SetMaxValue(200); 
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAlexfHistogramDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAlexfHistogramDlg::OnPaint() 
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
HCURSOR CAlexfHistogramDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAlexfHistogramDlg::OnButton1() 
{
	m_sHistogram.Add((DOUBLE) rand() / (DOUBLE) RAND_MAX * 100);
}

void CAlexfHistogramDlg::OnRadio1() 
{
	m_sHistogram.SetTextLeft();
}

void CAlexfHistogramDlg::OnRadio2() 
{
	m_sHistogram.SetTextLeft(FALSE);
}

void CAlexfHistogramDlg::OnRadio3() 
{
	m_sHistogram.SetMotionLtoR();
}

void CAlexfHistogramDlg::OnRadio4() 
{
	m_sHistogram.SetMotionLtoR(FALSE);
}
