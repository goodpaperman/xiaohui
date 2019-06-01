// MacButtonTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MacButtonTest.h"
#include "MacButtonTestDlg.h"

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
// CMacButtonTestDlg dialog

CMacButtonTestDlg::CMacButtonTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMacButtonTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMacButtonTestDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_rectWindow = CRect(0, 0, 0, 0);
}

void CMacButtonTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMacButtonTestDlg)
	DDX_Control(pDX, IDOK, m_buttonOK);
	DDX_Control(pDX, IDC_BUTTON_MOREBUTTON, m_buttonMoreButton);
	DDX_Control(pDX, IDC_BUTTON_MORERADIO, m_buttonMoreRadio);
	DDX_Control(pDX, IDC_BUTTON_MORECHECKBOX, m_buttonMoreCheckbox);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_checkDisable);
	DDX_Control(pDX, IDC_RADIO_NONE, m_radioNone);
	DDX_Control(pDX, IDC_RADIO_CHECK, m_radioCheck);
	DDX_Control(pDX, IDC_RADIO_ICON, m_radioIcon);
	DDX_Control(pDX, IDC_RADIO1, m_radio1);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK3, m_check3);
	DDX_Control(pDX, IDC_CHECK4, m_check4);
	DDX_Control(pDX, IDC_CHECK5, m_check5);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_BUTTON3, m_button3);
	DDX_Control(pDX, IDC_BUTTON4, m_button4);
	DDX_Control(pDX, IDC_BUTTON5, m_button5);
	DDX_Control(pDX, IDC_BUTTON6, m_button6);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_RADIO2, m_radio2);
	DDX_Control(pDX, IDC_RADIO3, m_radio3);
	DDX_Control(pDX, IDC_RADIO4, m_radio4);
	DDX_Control(pDX, IDC_RADIO5, m_radio5);
	DDX_Control(pDX, IDC_RADIO_BITMAP, m_radioBitmap);
	DDX_Control(pDX, IDC_RADIO_TEXT, m_radioText);
	DDX_Control(pDX, IDC_RADIO_RAISED, m_radioRaised);
	DDX_Control(pDX, IDC_RADIO_SUNKEN, m_radioSunken);
	DDX_Control(pDX, IDC_RADIO_CROSS, m_radioCross);
	DDX_Control(pDX, IDC_RADIO_TRISTATE, m_radioTri);
}

BEGIN_MESSAGE_MAP(CMacButtonTestDlg, CDialog)
	//{{AFX_MSG_MAP(CMacButtonTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_BITMAP, OnRadioBitmap)
	ON_BN_CLICKED(IDC_RADIO_ICON, OnRadioIcon)
	ON_BN_CLICKED(IDC_RADIO_TEXT, OnRadioText)
	ON_BN_CLICKED(IDC_RADIO_CHECK, OnRadioCheck)
	ON_BN_CLICKED(IDC_RADIO_CROSS, OnRadioCross)
	ON_BN_CLICKED(IDC_RADIO_RAISED, OnRadioRaised)
	ON_BN_CLICKED(IDC_RADIO_SUNKEN, OnRadioSunken)
	ON_BN_CLICKED(IDC_RADIO_NONE, OnRadioNone)
	ON_BN_CLICKED(IDC_CHECK_ENABLE, OnCheckEnable)
	ON_BN_CLICKED(IDC_BUTTON_MOREBUTTON, OnButtonMorebutton)
	ON_BN_CLICKED(IDC_BUTTON_MORECHECKBOX, OnButtonMorecheckbox)
	ON_BN_CLICKED(IDC_BUTTON_MORERADIO, OnButtonMoreradio)
	ON_BN_CLICKED(IDC_RADIO_TRISTATE, OnRadioTristate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMacButtonTestDlg message handlers

BOOL CMacButtonTestDlg::OnInitDialog()
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
	GetWindowRect(m_rectWindow);
	//SetWindowPos(&wndTop, 0, 0, m_rectWindow.Width(), 53, SWP_NOMOVE);

	m_buttonMoreRadio.SetColor(RGB(255, 64, 64));
	m_buttonMoreCheckbox.SetColor(RGB(0, 128, 0));
	m_buttonMoreButton.SetColor(RGB(64, 64, 255));

	m_buttonMoreRadio.SetTextAlign(ALIGN_TEXT_RIGHT);
	m_buttonMoreButton.SetTextAlign(ALIGN_TEXT_RIGHT);

	m_radioCheck.SetCheck(0);
	m_radioText.SetCheck(0);
	m_radioNone.SetCheck(0);

	GetDlgItem(IDC_STATIC_IMAGEEFFECT)->EnableWindow(FALSE);
	m_radioNone.EnableWindow(FALSE);
	m_radioRaised.EnableWindow(FALSE);
	m_radioSunken.EnableWindow(FALSE);

	m_check1.SetCheck(1);
	m_check2.SetCheck(1);
	m_check3.SetCheck(1);
	m_check4.SetCheck(1);
	m_check5.SetCheck(1);

	m_buttonOK.SetBold();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMacButtonTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMacButtonTestDlg::OnPaint() 
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
HCURSOR CMacButtonTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMacButtonTestDlg::OnRadioBitmap() 
{
	HBITMAP hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));

	m_radio1.SetBitmap(hBitmap);
	m_radio2.SetBitmap(hBitmap);
	m_radio3.SetBitmap(hBitmap);
	m_radio4.SetBitmap(hBitmap);
	m_radio5.SetBitmap(hBitmap);

	m_check1.SetBitmap(hBitmap);
	m_check2.SetBitmap(hBitmap);
	m_check3.SetBitmap(hBitmap);
	m_check4.SetBitmap(hBitmap);
	m_check5.SetBitmap(hBitmap);
		
	m_button1.SetBitmap(hBitmap);
	m_button2.SetBitmap(hBitmap);
	m_button3.SetBitmap(hBitmap);
	m_button4.SetBitmap(hBitmap);
	m_button5.SetBitmap(hBitmap);
	m_button6.SetBitmap(hBitmap);

	GetDlgItem(IDC_STATIC_IMAGEEFFECT)->EnableWindow();
	m_radioNone.EnableWindow();
	m_radioRaised.EnableWindow();
	m_radioSunken.EnableWindow();
}

void CMacButtonTestDlg::OnRadioIcon() 
{
	m_radio1.SetIcon(m_hIcon);
	m_radio2.SetIcon(m_hIcon);
	m_radio3.SetIcon(m_hIcon);
	m_radio4.SetIcon(m_hIcon);
	m_radio5.SetIcon(m_hIcon);

	m_check1.SetIcon(m_hIcon);
	m_check2.SetIcon(m_hIcon);
	m_check3.SetIcon(m_hIcon);
	m_check4.SetIcon(m_hIcon);
	m_check5.SetIcon(m_hIcon);
	
	m_button1.SetIcon(m_hIcon);
	m_button2.SetIcon(m_hIcon);
	m_button3.SetIcon(m_hIcon);
	m_button4.SetIcon(m_hIcon);
	m_button5.SetIcon(m_hIcon);
	m_button6.SetIcon(m_hIcon);

	GetDlgItem(IDC_STATIC_IMAGEEFFECT)->EnableWindow();
	m_radioNone.EnableWindow();
	m_radioRaised.EnableWindow();
	m_radioSunken.EnableWindow();
}

void CMacButtonTestDlg::OnRadioText() 
{
	m_radio1.SetBitmap(NULL);
	m_radio2.SetBitmap(NULL);
	m_radio3.SetBitmap(NULL);
	m_radio4.SetBitmap(NULL);
	m_radio5.SetBitmap(NULL);

	m_check1.SetBitmap(NULL);
	m_check2.SetBitmap(NULL);
	m_check3.SetBitmap(NULL);
	m_check4.SetBitmap(NULL);
	m_check5.SetBitmap(NULL);
	
	m_button1.SetBitmap(NULL);
	m_button2.SetBitmap(NULL);
	m_button3.SetBitmap(NULL);
	m_button4.SetBitmap(NULL);
	m_button5.SetBitmap(NULL);
	m_button6.SetBitmap(NULL);

	GetDlgItem(IDC_STATIC_IMAGEEFFECT)->EnableWindow(FALSE);
	m_radioNone.EnableWindow(FALSE);
	m_radioRaised.EnableWindow(FALSE);
	m_radioSunken.EnableWindow(FALSE);
}

void CMacButtonTestDlg::OnRadioCheck() 
{
	m_check1.SetCheckStyle(CHECK_STYLE_CHECK);
	m_check2.SetCheckStyle(CHECK_STYLE_CHECK);
	m_check3.SetCheckStyle(CHECK_STYLE_CHECK);
	m_check4.SetCheckStyle(CHECK_STYLE_CHECK);
	m_check5.SetCheckStyle(CHECK_STYLE_CHECK);
	m_check1.SetCheck(1);
	m_check2.SetCheck(1);
	m_check3.SetCheck(1);
	m_check4.SetCheck(1);
	m_check5.SetCheck(1);
}

void CMacButtonTestDlg::OnRadioCross() 
{
	m_check1.SetCheckStyle(CHECK_STYLE_CROSS);
	m_check2.SetCheckStyle(CHECK_STYLE_CROSS);
	m_check3.SetCheckStyle(CHECK_STYLE_CROSS);
	m_check4.SetCheckStyle(CHECK_STYLE_CROSS);
	m_check5.SetCheckStyle(CHECK_STYLE_CROSS);
	m_check1.SetCheck(1);
	m_check2.SetCheck(1);
	m_check3.SetCheck(1);
	m_check4.SetCheck(1);
	m_check5.SetCheck(1);
}

void CMacButtonTestDlg::OnRadioTristate() 
{
	m_check1.SetCheck(2);
	m_check2.SetCheck(2);
	m_check3.SetCheck(2);
	m_check4.SetCheck(2);
	m_check5.SetCheck(2);
}

void CMacButtonTestDlg::OnRadioNone() 
{
	m_radio1.SetImageEffect(IMAGE_EFFECT_NONE);
	m_radio2.SetImageEffect(IMAGE_EFFECT_NONE);
	m_radio3.SetImageEffect(IMAGE_EFFECT_NONE);
	m_radio4.SetImageEffect(IMAGE_EFFECT_NONE);
	m_radio5.SetImageEffect(IMAGE_EFFECT_NONE);

	m_check1.SetImageEffect(IMAGE_EFFECT_NONE);
	m_check2.SetImageEffect(IMAGE_EFFECT_NONE);
	m_check3.SetImageEffect(IMAGE_EFFECT_NONE);
	m_check4.SetImageEffect(IMAGE_EFFECT_NONE);
	m_check5.SetImageEffect(IMAGE_EFFECT_NONE);
	
	m_button1.SetImageEffect(IMAGE_EFFECT_NONE);
	m_button2.SetImageEffect(IMAGE_EFFECT_NONE);
	m_button3.SetImageEffect(IMAGE_EFFECT_NONE);
	m_button4.SetImageEffect(IMAGE_EFFECT_NONE);
	m_button5.SetImageEffect(IMAGE_EFFECT_NONE);
	m_button6.SetImageEffect(IMAGE_EFFECT_NONE);
}

void CMacButtonTestDlg::OnRadioRaised() 
{
	m_radio1.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_radio2.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_radio3.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_radio4.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_radio5.SetImageEffect(IMAGE_EFFECT_RAISED);

	m_check1.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_check2.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_check3.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_check4.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_check5.SetImageEffect(IMAGE_EFFECT_RAISED);
	
	m_button1.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_button2.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_button3.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_button4.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_button5.SetImageEffect(IMAGE_EFFECT_RAISED);
	m_button6.SetImageEffect(IMAGE_EFFECT_RAISED);
}

void CMacButtonTestDlg::OnRadioSunken() 
{
	m_radio1.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_radio2.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_radio3.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_radio4.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_radio5.SetImageEffect(IMAGE_EFFECT_SUNKEN);

	m_check1.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_check2.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_check3.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_check4.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_check5.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	
	m_button1.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_button2.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_button3.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_button4.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_button5.SetImageEffect(IMAGE_EFFECT_SUNKEN);
	m_button6.SetImageEffect(IMAGE_EFFECT_SUNKEN);
}

void CMacButtonTestDlg::OnCheckEnable() 
{
	BOOL bEnable = !m_checkDisable.GetCheck();
	
	m_radio1.EnableWindow(bEnable);
	m_radio2.EnableWindow(bEnable);
	m_radio3.EnableWindow(bEnable);
	m_radio4.EnableWindow(bEnable);
	m_radio5.EnableWindow(bEnable);

	m_check1.EnableWindow(bEnable);
	m_check2.EnableWindow(bEnable);
	m_check3.EnableWindow(bEnable);
	m_check4.EnableWindow(bEnable);
	m_check5.EnableWindow(bEnable);
	
	m_button1.EnableWindow(bEnable);
	m_button2.EnableWindow(bEnable);
	m_button3.EnableWindow(bEnable);
	m_button4.EnableWindow(bEnable);
	m_button5.EnableWindow(bEnable);
	m_button6.EnableWindow(bEnable);

	m_buttonMoreRadio.EnableWindow(bEnable);
	m_buttonMoreCheckbox.EnableWindow(bEnable);
	m_buttonMoreButton.EnableWindow(bEnable);
}

void CMacButtonTestDlg::OnButtonMorebutton() 
{
	SetWindowPos(&wndTop, 0, 0, m_rectWindow.Width(), 
		m_buttonMoreButton.GetMoreShown() ? 235 : m_rectWindow.Height(), SWP_NOMOVE);
}

void CMacButtonTestDlg::OnButtonMorecheckbox() 
{
	SetWindowPos(&wndTop, 0, 0, m_rectWindow.Width(), 
		m_buttonMoreCheckbox.GetMoreShown() ? 130 : 
			(m_buttonMoreButton.GetMoreShown() ? m_rectWindow.Height() : 235), SWP_NOMOVE);
}

void CMacButtonTestDlg::OnButtonMoreradio() 
{
	SetWindowPos(&wndTop, 0, 0, m_rectWindow.Width(), 
		m_buttonMoreRadio.GetMoreShown() ? 53 : 
			(m_buttonMoreCheckbox.GetMoreShown() ? 
				(m_buttonMoreButton.GetMoreShown() ? m_rectWindow.Height() : 235) : 130), SWP_NOMOVE);
}
