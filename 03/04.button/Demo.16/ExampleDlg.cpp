// ExampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Example.h"
#include "ExampleDlg.h"

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
// CExampleDlg dialog

CExampleDlg::CExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExampleDlg)
	DDX_Control(pDX, IDC_BUTTON3, m_Btn3);
	DDX_Control(pDX, IDC_BUTTON2, m_Btn2);
	DDX_Control(pDX, IDC_BUTTON1, m_Btn1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExampleDlg, CDialog)
	//{{AFX_MSG_MAP(CExampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleDlg message handlers

BOOL CExampleDlg::OnInitDialog()
{

	//
	// Added by the AppWizard
	//
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



	//
	// Example dialog code
	//
	
	// create the tooltip control
	m_ToolTip.Create(this);

	// register the dialog controls with the tooltip
	m_ToolTip.AddTool( &m_Btn1, IDS_TT_BTN1 );
	m_ToolTip.AddTool( &m_Btn2, IDS_TT_BTN2 );
	m_ToolTip.AddTool( &m_Btn3, IDS_TT_BTN3 );
	
	// set the initial state of button 2
	m_Btn2.Depress(true);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExampleDlg::OnPaint() 
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
HCURSOR CExampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExampleDlg::OnButton1() 
{
	// If depressed, disable Btn2 and Btn3
	m_Btn2.EnableWindow( m_Btn1.IsDepressed() );
	m_Btn3.EnableWindow( m_Btn1.IsDepressed() );
}

void CExampleDlg::OnButton2() 
{
	// If depressed, "Unpress" button 3
	// don't let user unpress
	if( m_Btn3.IsDepressed() )
		m_Btn3.Depress( false );
	else
		m_Btn2.Depress( true );
	
}

void CExampleDlg::OnButton3() 
{
	// If depressed, "Unpress" button 2
	// don't let user unpress
	if( m_Btn2.IsDepressed() )
		m_Btn2.Depress( false );
	else
		m_Btn3.Depress( true );	
}

BOOL CExampleDlg::PreTranslateMessage(MSG* pMsg) 
{
	// handle the message for the tooltip before passing it on
    //MSG msg = *pMsg;
    //msg.hwnd = (HWND)m_ToolTip.SendMessage(TTM_WINDOWFROMPOINT,0,(LPARAM)&msg.pt);
    //CPoint pt = pMsg->pt;
    //if( msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST )
    //    ::ScreenToClient(msg.hwnd, &pt );
    //msg.lParam = MAKELONG(pt.x,pt.y);

    //// now let the tooltip handle the event
    //m_ToolTip.RelayEvent(&msg);        
    m_ToolTip.RelayEvent(pMsg); 

	return CDialog::PreTranslateMessage(pMsg);
}
