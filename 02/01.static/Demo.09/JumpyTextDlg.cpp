// JumpyTextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JumpyText.h"
#include "JumpyTextDlg.h"

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
// CJumpyTextDlg dialog

CJumpyTextDlg::CJumpyTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJumpyTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJumpyTextDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJumpyTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJumpyTextDlg)
	DDX_Control(pDX, IDC_STATIC_JUMPY_DRAW, m_jumpyDraw);
    DDX_Control(pDX, IDC_BUTTON_COLOUR_START, m_GradientStart);
    DDX_Control(pDX, IDC_BUTTON_COLOUR_END, m_GradientEnd);
    DDX_Control(pDX, IDC_BUTTON_COLOUR_TEXT, m_ColourText);
    DDX_Control(pDX, IDC_BUTTON_COLOUR_SHADDOW, m_ColourShaddow);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJumpyTextDlg, CDialog)
	//{{AFX_MSG_MAP(CJumpyTextDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_CUSTOM_ANIMATION, OnButtonCustomAnimation)
	ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
	ON_EN_CHANGE(IDC_EDIT_FONT, OnChangeEditFont)
	ON_EN_CHANGE(IDC_EDIT_SIZE_FONT, OnChangeEditSizeFont)
	ON_EN_CHANGE(IDC_EDIT_TIME, OnChangeEditTime)
	//}}AFX_MSG_MAP
    ON_MESSAGE(CPN_SELENDOK,     OnSelEndOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJumpyTextDlg message handlers

BOOL CJumpyTextDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	
	UpdateData(FALSE);
	m_GradientStart.SetBkColour(RGB(123, 158, 198));
	m_GradientEnd.SetBkColour(RGB(0,0,255));
	m_ColourText.SetBkColour(RGB(0, 255, 0));
	m_ColourShaddow.SetBkColour(RGB(0,0,0));
	GetDlgItem(IDC_EDIT_SIZE_FONT)->SetWindowText("24");
	GetDlgItem(IDC_EDIT_FONT)->SetWindowText("MS Sans Serif");
	GetDlgItem(IDC_EDIT_TEXT)->SetWindowText("The quick brown fox jumps over the lazy dog. 1234567890");
	GetDlgItem(IDC_EDIT_TIME)->SetWindowText("1000");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJumpyTextDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJumpyTextDlg::OnPaint() 
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
HCURSOR CJumpyTextDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CJumpyTextDlg::OnButton2() 
{
	//the only function that need to call for rendering
	m_jumpyDraw.StartJumpyText("The quick brown fox jumps over the lazy dog. 1234567890",
		1000, "MS Sans Serif", 24, RGB(0, 255, 0), RGB(0, 0, 0), 
		RGB(123, 158, 198), RGB(0,0,255));
	//internal settings : do not need this for using in your own application
	m_GradientStart.SetBkColour(RGB(123, 158, 198));
	m_GradientEnd.SetBkColour(RGB(0,0,255));
	m_ColourText.SetBkColour(RGB(0, 255, 0));
	m_ColourShaddow.SetBkColour(RGB(0,0,0));
	GetDlgItem(IDC_EDIT_SIZE_FONT)->SetWindowText("24");
	GetDlgItem(IDC_EDIT_FONT)->SetWindowText("MS Sans Serif");
	GetDlgItem(IDC_EDIT_TEXT)->SetWindowText("The quick brown fox jumps over the lazy dog. 1234567890");
	GetDlgItem(IDC_EDIT_TIME)->SetWindowText("1000");
}

LONG CJumpyTextDlg::OnSelEndOK(UINT lParam, LONG wParam)
{
	switch(wParam)
	{
	case IDC_BUTTON_COLOUR_START:
		m_jumpyDraw.SetGradientStartColor(lParam);
		break;
	case IDC_BUTTON_COLOUR_END:
		m_jumpyDraw.SetGradientEndColor(lParam);
		break;
	case IDC_BUTTON_COLOUR_TEXT:
		m_jumpyDraw.SetTextColor(lParam);
		break;
	case IDC_BUTTON_COLOUR_SHADDOW:
		m_jumpyDraw.SetShaddowColor(lParam);
		break;
	}
    return TRUE;
}

void CJumpyTextDlg::OnButtonCustomAnimation() 
{
	m_jumpyDraw.StartJumpyText();//the only function that need to call for rendering
	m_GradientStart.SetBkColour(m_jumpyDraw.GetGradientStartColor());
	m_GradientEnd.SetBkColour(m_jumpyDraw.GetGradientEndColor());
	m_ColourText.SetBkColour(m_jumpyDraw.GetTextColor());
	m_ColourShaddow.SetBkColour(m_jumpyDraw.GetShaddowColor());
}

void CJumpyTextDlg::OnChangeEditText() 
{
	CString strText;
	GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(strText);
	m_jumpyDraw.SetText(strText);
}

void CJumpyTextDlg::OnChangeEditFont() 
{
	CString strText;
	GetDlgItem(IDC_EDIT_FONT)->GetWindowText(strText);
	m_jumpyDraw.SetFontFace(strText);
}

void CJumpyTextDlg::OnChangeEditSizeFont() 
{
	CString strText;
	GetDlgItem(IDC_EDIT_SIZE_FONT)->GetWindowText(strText);
	int nHeight = atoi((const char*)(LPCTSTR)strText);
	if (nHeight != 0)
		m_jumpyDraw.SetCharHeight(nHeight);
}

void CJumpyTextDlg::OnChangeEditTime() 
{
	CString strText;
	GetDlgItem(IDC_EDIT_TIME)->GetWindowText(strText);
	long nTime = atol((const char*)(LPCTSTR)strText);
	if (nTime != 0)
		m_jumpyDraw.SetJumpyTime(nTime);
}
