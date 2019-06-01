// MCComboBoxSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MCComboBoxSample.h"
#include "MCComboBoxSampleDlg.h"

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
// CMCComboBoxSampleDlg dialog

CMCComboBoxSampleDlg::CMCComboBoxSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMCComboBoxSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMCComboBoxSampleDlg)
	m_ComboBoxString1 = _T("");
	m_ComboBoxString2 = _T("");
	m_ComboBoxString3 = _T("");
	m_ComboBoxString4 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCComboBoxSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMCComboBoxSampleDlg)
	DDX_Control(pDX, IDC_COMBO4, m_ComboBoxControl4);
	DDX_Control(pDX, IDC_COMBO3, m_ComboBoxControl3);
	DDX_Control(pDX, IDC_COMBO2, m_ComboBoxControl2);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBoxControl1);
	DDX_CBString(pDX, IDC_COMBO1, m_ComboBoxString1);
	DDX_CBString(pDX, IDC_COMBO2, m_ComboBoxString2);
	DDX_CBString(pDX, IDC_COMBO3, m_ComboBoxString3);
	DDX_CBString(pDX, IDC_COMBO4, m_ComboBoxString4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMCComboBoxSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CMCComboBoxSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENABLEDDISABLED, OnEnableddisabled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMCComboBoxSampleDlg message handlers

BOOL CMCComboBoxSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	CString	ColumnString0, ColumnString1, ColumnString2, ColumnString3;
	int		Index;

	m_ComboBoxControl1.FormatComboBox();
	m_ComboBoxControl1.SetColumnWidth(30, 100);
	for (Index = 0; Index < 20; Index++)
	{
		ColumnString0.Format("ID%u", Index);
		ColumnString1.Format("Description%u", Index);
		m_ComboBoxControl1.AddRow(ColumnString0, ColumnString1);
	}

	m_ComboBoxControl2.FormatComboBox(2, 1, 0);
	m_ComboBoxControl2.SetColumnWidth(150, 0);
	m_ComboBoxControl2.SetColumnAlignStyle(DT_LEFT, DT_CENTER);
	for (Index = 0; Index < 20; Index++)
	{
		ColumnString0.Format("ID%u", Index);
		ColumnString1.Format("Description%u", Index);
		m_ComboBoxControl2.AddRow(ColumnString1, ColumnString0);
	}

	m_ComboBoxControl3.FormatComboBox(3);
	m_ComboBoxControl3.SetColumnWidth(0, 90, 100);
	m_ComboBoxControl3.SetColumnAlignStyle(DT_CENTER, DT_CENTER, DT_RIGHT);
	for (Index = 0; Index < 20; Index++)
	{
		ColumnString0.Format("ID%u", Index);
		ColumnString1.Format("Description%u", Index);
		ColumnString2.Format("Remarks%u", Index);
		m_ComboBoxControl3.AddRow(ColumnString0, ColumnString1, ColumnString2);
	}
	m_ComboBoxControl3.LimitText(13);

  	m_ComboBoxControl4.FormatComboBox(4);
	m_ComboBoxControl4.SetColumnWidth(40, 50, 50, 50);
	m_ComboBoxControl4.SetColumnAlignStyle(DT_LEFT, DT_RIGHT, DT_RIGHT, DT_RIGHT);
	for (Index = 0; Index < 20; Index++)
	{
		ColumnString0.Format("Rate%u", Index);
		ColumnString1.Format("Desc%u", Index);
		ColumnString2.Format("%.2f", Index / 3.0);
		ColumnString3.Format("%.2f", Index / 4.0);
		m_ComboBoxControl4.AddRow(ColumnString0, ColumnString1, ColumnString2, ColumnString3);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMCComboBoxSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMCComboBoxSampleDlg::OnPaint() 
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
HCURSOR CMCComboBoxSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMCComboBoxSampleDlg::OnEnableddisabled() 
{
	// TODO: Add your control notification handler code here
	BOOL	ControlEnabled = GetDlgItem(IDC_COMBO3)->IsWindowEnabled();

	GetDlgItem(IDC_COMBO1)->EnableWindow(!ControlEnabled);
	GetDlgItem(IDC_COMBO2)->EnableWindow(!ControlEnabled);
	GetDlgItem(IDC_COMBO3)->EnableWindow(!ControlEnabled);
	GetDlgItem(IDC_COMBO4)->EnableWindow(!ControlEnabled);
	GetDlgItem(IDC_ENABLEDDISABLED)->SetWindowText(ControlEnabled ? "Enable All ComboBox Controls" : "Disable All ComboBox Controls");
}

void CMCComboBoxSampleDlg::OnOK() 
{
	CString	TextString;

	UpdateData(TRUE);
	TextString.Format("Text in combo box 1 is %s\nText in combo box 2 is %s\nText in combo box 3 is %s\nText in combo box 4 is %s\n",
		m_ComboBoxString1, m_ComboBoxString2, m_ComboBoxString3, m_ComboBoxString4);

	MessageBox(TextString);
	
	TextString = m_ComboBoxControl3.GetCurColumnItem(1);
	MessageBox(TextString);

	CDialog::OnOK();
}
