// counterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "counter.h"
#include "counterDlg.h"
#include "Digistring.h"

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
// CCounterDlg dialog

CCounterDlg::CCounterDlg(CWnd* pParent /*=NULL*/)
	: cdxCDynamicDialog(CCounterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCounterDlg)
	m_bSmooth = FALSE;
	m_14Status = 0;
	m_bProportional = TRUE;
	m_LedEdit = _T("MAGIC");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCounterDlg::DoDataExchange(CDataExchange* pDX)
{
	cdxCDynamicDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCounterDlg)
	DDX_Control(pDX, IDC_FRAME1, m_Frame);
	DDX_Control(pDX, IDC_TEXT2_STATIC, m_Text2);
	DDX_Control(pDX, IDC_SCROLL, m_ScrollText);
	DDX_Control(pDX, IDC_TIME_STATIC, m_TheTime);
	DDX_Control(pDX, IDC_DSTRING_STATIC, m_Digistring);
	DDX_Check(pDX, IDC_SMOOTH_CHECK, m_bSmooth);
	DDX_Radio(pDX, IDC_14_RADIO, m_14Status);
	DDX_Check(pDX, IDC_PROP_CHECK, m_bProportional);
	DDX_Text(pDX, IDC_LED_EDIT, m_LedEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCounterDlg, cdxCDynamicDialog)
	//{{AFX_MSG_MAP(CCounterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SMOOTH_CHECK, OnSmoothCheck)
	ON_BN_CLICKED(IDC_14_RADIO, On14Radio)
	ON_BN_CLICKED(IDC_7_RADIO, On7Radio)
	ON_BN_CLICKED(IDC_PROP_CHECK, OnPropCheck)
	ON_EN_CHANGE(IDC_LED_EDIT, OnChangeLedEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCounterDlg message handlers

BOOL CCounterDlg::OnInitDialog()
{
	cdxCDynamicDialog::OnInitDialog();

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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	AddSzControl(m_TheTime, 0, 0, 50, 0); 
	AddSzControl(m_Text2, 50, 0, 100, 0); 
	AddSzControl(m_ScrollText, mdResize, mdNone); 
	AddSzXControl(m_Frame, mdResize); 
	AddSzControl(m_Digistring, mdResize, mdResize); 

	m_Digistring.SetColor(DARKRED, LIGHTRED);
	m_Digistring.SetText(m_LedEdit);
	VERIFY(m_Digistring.ModifyDigiStyle(0, CDigistring::DS_STYLE14 | CDigistring::DS_SZ_PROP));

	m_ScrollText.ScrollText(" Show must go on -"); 
	VERIFY(m_ScrollText.ModifyDigiStyle(0, CDigistring::DS_STYLE14 | CDigistring::DS_SZ_PROP));
	m_ScrollText.SetColor(DARKCYAN, LIGHTCYAN);

	m_ScrollText.SetSpeed(500); 
	m_ScrollText.SetTextLength(12); 
	m_ScrollText.DoScroll(); 
	
	m_Text2.SetBackColor(LIGHTBLUE);
	m_Text2.SetColor(LIGHTBLUE, WHITE);
	m_Text2.SetText("56.873");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCounterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		cdxCDynamicDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCounterDlg::OnPaint() 
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
		cdxCDynamicDialog::OnPaint();
	}
}

HCURSOR CCounterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCounterDlg::OnSmoothCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bSmooth)
		m_Digistring.ModifyDigiStyle(0, CDigistring::DS_SMOOTH);
	else
		m_Digistring.ModifyDigiStyle(CDigistring::DS_SMOOTH, 0);
}

void CCounterDlg::On14Radio() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_14Status < 0) return;
	if (m_14Status == 0)
		m_Digistring.ModifyDigiStyle(0, CDigistring::DS_STYLE14);
	else
		m_Digistring.ModifyDigiStyle(CDigistring::DS_STYLE14, 0);
}

void CCounterDlg::On7Radio() 
{
	// TODO: Add your control notification handler code here
	On14Radio();
}

void CCounterDlg::OnPropCheck() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bProportional)
		m_Digistring.ModifyDigiStyle(0, CDigistring::DS_SZ_PROP);
	else
		m_Digistring.ModifyDigiStyle(CDigistring::DS_SZ_PROP, 0);
}

void CCounterDlg::OnChangeLedEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the cdxCSizingDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Digistring.SetText(m_LedEdit);
}
