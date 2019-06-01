// DemoClockClassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoClockClass.h"
#include "DemoClockClassDlg.h"

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
// CDemoClockClassDlg dialog

CDemoClockClassDlg::CDemoClockClassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoClockClassDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoClockClassDlg)
	m_iFormat = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoClockClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CLOCK, m_Clock);
	DDX_Control(pDX, IDC_STATIC_STYLE_EXA, m_StyleExampleA);
	DDX_Control(pDX, IDC_STATIC_STYLE_EXB, m_StyleExampleB);
	//{{AFX_DATA_MAP(CDemoClockClassDlg)
	DDX_Radio(pDX, IDC_RADIO_12HR, m_iFormat);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoClockClassDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoClockClassDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_12HR, OnRadio12hr)
	ON_BN_CLICKED(IDC_RADIO_24HR, OnRadio24hr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoClockClassDlg message handlers

BOOL CDemoClockClassDlg::OnInitDialog()
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
	
	m_StyleExampleB.SetOn(FALSE);
	m_StyleExampleB.SetTextOffColor(RGB(255,255,255));
	m_StyleExampleB.SetPointFont(11,"Times New Roman");
//	m_StyleExampleB.SetBold();
    //m_StyleExampleB.FlashBackground(TRUE); 
    //m_StyleExampleB.FlashText(TRUE);
    m_StyleExampleB.SetUnderline(); 
	m_StyleExampleB.SetColorFrame(TRUE,2,RGB(190,0,0));
	m_StyleExampleB.Start();

	m_StyleExampleA.SetOn(FALSE);
	m_StyleExampleA.SetTextOffColor(RGB(0,180,255));
	m_StyleExampleA.SetBackgroundOffColor(RGB(0,0,50));
	m_StyleExampleA.SetPointFont(12,"Comic Sans MS");
    //m_StyleExampleA.SetHatch(TRUE, HS_CROSS); 
    //m_StyleExampleA.TextOn(); 
    //m_StyleExampleA.FlashBackgroundAsym(TRUE, TRUE, 2, 0.5f); 
	//m_StyleExampleA.SetBold();
    m_StyleExampleA.SetItalic(); 
	m_StyleExampleA.SetSunken();
	m_StyleExampleA.Start();


	m_Clock.SetOn(FALSE);
	m_Clock.SetTextOffColor(RGB(0,180,255));
	m_Clock.SetBackgroundOffColor(RGB(0,0,50));
	//m_Clock.SetBold();
	m_Clock.SetPointFont(9,"Arial");
	m_Clock.SetModalFrame();
    //m_Clock.FlashBackgroundPulsed(TRUE); 
	m_Clock.Start();



	SYSTEMTIME CurrentTime;
	GetLocalTime(&CurrentTime);
	m_Clock.SetAlarm(CurrentTime.wHour,CurrentTime.wMinute+1);
	m_Clock.ActivateAlarm();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoClockClassDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoClockClassDlg::OnPaint() 
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
HCURSOR CDemoClockClassDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDemoClockClassDlg::OnRadio12hr() 
{
	m_Clock.Format();	
}

void CDemoClockClassDlg::OnRadio24hr() 
{
	m_Clock.Format(TRUE);	
}



