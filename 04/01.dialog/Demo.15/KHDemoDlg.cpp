// KHDemoDlg.cpp : implementation file

#include "stdafx.h"
#include "KHDemo.h"
#include "KHDemoDlg.h"
#include "about.h"
#include "demo2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static const char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKHDemoDlg dialog

BEGIN_MESSAGE_MAP(CKHDemoDlg, CDialog)
    //{{AFX_MSG_MAP(CKHDemoDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
    ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusEdit1)
    ON_BN_CLICKED(IDC_INTRO, OnIntro)
    ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
    ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
    ON_WM_TIMER()
    ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP

    ON_MESSAGE(TTM_RELAYEVENT, OnRelayEvent)

END_MESSAGE_MAP()

CKHDemoDlg::CKHDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CKHDemoDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CKHDemoDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_timerHelpId = 0;
    m_curHelpId = IDC_INTRO;
}

CKHDemoDlg::~CKHDemoDlg()
{
    RemoveMouseMsgHook();
}

void CKHDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CKHDemoDlg)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}

BOOL CKHDemoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_hhctrl.SetChmFile("KhDemo.chm")) {    
        m_hhctrl.ReplaceControl(this, IDC_HHCTRL, TRUE);
        m_hhctrl.NavigateChm(IDC_INTRO);
    }

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

    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    
    SetMouseMsgHook(*this);

    return TRUE;  
}

void CKHDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKHDemoDlg::OnPaint() 
{
    if (IsIconic()) {
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
    else {
        CDialog::OnPaint();
    }
}

HCURSOR CKHDemoDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

// Note that we set the control even though a mouse-over/click would also set
// the help content. This ensures that users that use the keyboard will also
// get the correct help content, and that the help content changes immediately.

void CKHDemoDlg::OnCheck1() 
{
    m_hhctrl.NavigateChm(IDC_CHECK1);
}

void CKHDemoDlg::OnSetfocusEdit1() 
{
    m_hhctrl.NavigateChm(IDC_EDIT1);
}

void CKHDemoDlg::OnIntro() 
{
    m_hhctrl.NavigateChm(IDC_INTRO);
}

void CKHDemoDlg::OnRadio1() 
{
    m_hhctrl.NavigateChm(IDC_RADIO1);
}

void CKHDemoDlg::OnRadio2() 
{
    m_hhctrl.NavigateChm(IDC_RADIO2);
}

LRESULT CKHDemoDlg::OnRelayEvent(WPARAM wParam, LPARAM lParam)
{
    // Every time we get a mouse message, we kill the timer
    if (m_timerHelpId) {
        KillTimer(m_timerHelpId);
        m_timerHelpId = 0;
    }

    int id = ::GetDlgCtrlID(((MSG*) lParam)->hwnd);
    if (m_curHelpId != id) {
        if (m_timerHelpId)
            KillTimer(m_timerHelpId);
        m_timerHelpId = id;
        SetTimer(m_timerHelpId, HOVER_DELAY, NULL);
    }
    return 0;
}

void CKHDemoDlg::OnTimer(UINT nIDEvent) 
{
    // When the timer goes off, it means the mouse has been over a control
    // for HOVER_DELAY milliseconds. The id of the timer is the mapped id
    // of the html file to display.

    KillTimer(m_timerHelpId);
    m_hhctrl.NavigateChm(m_timerHelpId);
    m_curHelpId = m_timerHelpId;
    m_timerHelpId = 0;
}

void CKHDemoDlg::OnDestroy() 
{
    if (m_timerHelpId)
        KillTimer(m_timerHelpId);
    CDialog::OnDestroy();
}

void CKHDemoDlg::OnButton1() 
{
    Demo2 dlg;
    dlg.DoModal();
}
