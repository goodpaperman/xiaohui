// MidiPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MidiPlayer.h"
#include "MidiPlayerDlg.h"

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
	CHyperLink	m_MailLink;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
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
	DDX_Control(pDX, IDC_MAILTO, m_MailLink);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_MailLink.SetURL(_T("mailto:giancarlo@saria.com"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CMidiPlayerDlg dialog

CMidiPlayerDlg::CMidiPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMidiPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMidiPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMidiPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMidiPlayerDlg)
	DDX_Control(pDX, IDC_STOP, m_btnStop);
	DDX_Control(pDX, IDC_PLAY, m_btnPlay);
	DDX_Control(pDX, IDC_PROGRESS, m_ProgressBar);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMidiPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CMidiPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(MM_MCINOTIFY, OnMciNotify)
END_MESSAGE_MAP()

#define TIMER_ID	1

/////////////////////////////////////////////////////////////////////////////
// CMidiPlayerDlg message handlers

BOOL CMidiPlayerDlg::OnInitDialog()
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
	m_btnStop.EnableWindow(FALSE);
	m_btnPlay.EnableWindow(FALSE);
	m_Sequencer.SetCallbackWnd(this);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMidiPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMidiPlayerDlg::OnPaint() 
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
HCURSOR CMidiPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMidiPlayerDlg::OnFileOpen() 
{
	CString strDefExt;

	strDefExt.LoadString(IDS_MAINFRAME);
	
	CFileDialog fd(TRUE, NULL, NULL, 
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strDefExt, this);

	if (fd.DoModal() == IDOK) {
		m_Sequencer.Close();
		// Use MCI error report while opening
		m_Sequencer.ReportErrors(TRUE);
		if (!m_Sequencer.Open(fd.GetPathName())) {	
			// Set the time format
			m_Sequencer.SetTimeFormat(
				CSequencer::FormatMilliseconds);
			DWORD nTrack = m_Sequencer.GetCurrentTrack();			
			OnPlay();			
		}
		m_Sequencer.ReportErrors(FALSE);
	}
}

void CMidiPlayerDlg::OnPlay() 
{
	if (!m_Sequencer.Play()) {
		SetTimer(TIMER_ID, 1000, NULL);		
		m_btnPlay.EnableWindow(FALSE);
		m_btnStop.EnableWindow(TRUE);
	}				
}

void CMidiPlayerDlg::OnStop() 
{
	if (!m_Sequencer.Stop()) {
		KillTimer(TIMER_ID);
		m_Sequencer.SeekToStart();	
		m_ProgressBar.SetPos(0);
		m_btnPlay.EnableWindow(TRUE);
		m_btnStop.EnableWindow(FALSE);
	}
}

void CMidiPlayerDlg::OnTimer(UINT nIDEvent) 
{
	DWORD t = m_Sequencer.GetCurrentTrack();

	m_ProgressBar.SetPos(
		(m_Sequencer.GetCurrentPos() * 100) / 
		m_Sequencer.GetSongLength(t) );

	CDialog::OnTimer(nIDEvent);
}

void CMidiPlayerDlg::OnClose() 
{	
	CAboutDlg ad;
	ad.DoModal();

	m_Sequencer.Close();
	CDialog::OnClose();
}

LONG CMidiPlayerDlg::OnMciNotify(UINT wFlags, LONG lDevId) {	
	switch(wFlags) {
	case MCI_NOTIFY_SUCCESSFUL:		
		// Playback completed		
		OnStop();
		break;
	case MCI_NOTIFY_FAILURE:		
		// Interrupted
		OnStop();
		break;
	case MCI_NOTIFY_SUPERSEDED:
		// Stopped
		break;
	}	
	return 0L;
}


void CMidiPlayerDlg::OnOK() 
{
	SendMessage(WM_CLOSE);	
}

BOOL CMidiPlayerDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.lpszClass = ((CMidiPlayerApp*)AfxGetApp())->GetClassName();
	AfxMessageBox(cs.lpszClass);
	return CDialog::PreCreateWindow(cs);
}

int CMidiPlayerDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class	
	if (!((CMidiPlayerApp*)AfxGetApp())->
		CheckSingleInstance(IDR_MAINFRAME))
	return IDCANCEL;
		else
	return CDialog::DoModal();
}
