// MidiSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MidiSample.h"
#include "MidiSampleDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT RWM_POSITIONCHANGED = ::RegisterWindowMessage(TEXT("rwm_positionchanged"));
UINT RWM_PLAYEDOFF = ::RegisterWindowMessage(TEXT("rwm_playedoff"));


/////////////////////////////////////////////////////////////////////////////
// CMidiSampleDlg dialog

CMidiSampleDlg::CMidiSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMidiSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMidiSampleDlg)
	m_nVolume = 0;
	m_strPosition = _T("");
	m_nTempo = 0;
	m_strTempo = _T("");
	m_strVolume = _T("");
	m_bInfinite = FALSE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMidiSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_strVolume.Format("%d %%", m_nVolume);
	m_strTempo.Format("%d %%", m_nTempo);

	//{{AFX_DATA_MAP(CMidiSampleDlg)
	DDX_Control(pDX, IDC_Tempo, m_ctrlTempo);
	DDX_Control(pDX, IDC_Volume, m_ctrlVolume);
	DDX_Control(pDX, IDC_Stop, m_ctrlStop);
	DDX_Control(pDX, IDC_Play, m_ctrlPlay);
	DDX_Control(pDX, IDC_Pause, m_ctrlPause);
	DDX_Slider(pDX, IDC_Volume, m_nVolume);
	DDX_Text(pDX, IDC_Position, m_strPosition);
	DDX_Slider(pDX, IDC_Tempo, m_nTempo);
	DDX_Text(pDX, IDC_TempoText, m_strTempo);
	DDX_Text(pDX, IDC_VolumeText, m_strVolume);
	DDX_Check(pDX, IDC_Loop, m_bInfinite);
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(CMidiSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CMidiSampleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Play, OnPlay)
	ON_BN_CLICKED(IDC_Stop, OnStop)
	ON_BN_CLICKED(IDC_Pause, OnPause)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_Loop, OnLoop)
	//}}AFX_MSG_MAP

	ON_REGISTERED_MESSAGE(RWM_POSITIONCHANGED, OnSetPosition)
	ON_REGISTERED_MESSAGE(RWM_PLAYEDOFF, OnPlayedOff)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidiSampleDlg message handlers

BOOL CMidiSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// The "SetOwner()" method is part of our derived sample MIDI class!
	m_midiMusic.SetOwner(this);

	// Load the music from the resource and prepare it for playback
	//VERIFY(m_midiMusic.Create(IDR_Unforgiven));
	//VERIFY(m_midiMusic.Create(IDR_WindOfChange));
    m_midiMusic.Create(IDR_TEST); 

	// before the sound is playing we need no Stop- or Pause-button
	m_ctrlStop.EnableWindow(FALSE);
	m_ctrlPause.EnableWindow(FALSE);

	// initialise the volume control
	m_ctrlVolume.SetRange(0, 100);
	m_nVolume = m_midiMusic.GetVolume();
	m_ctrlVolume.SetPos(m_nVolume);

	// initialise the tempo control
	m_ctrlTempo.SetRange(0, 500);
	m_nTempo = m_midiMusic.GetTempo();
	m_ctrlTempo.SetPos(m_nTempo);

	// we do not loop by default
	m_bInfinite = FALSE;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMidiSampleDlg::OnPaint() 
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

HCURSOR CMidiSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMidiSampleDlg::OnPlay() 
{
	if(!m_midiMusic.IsPlaying()) {
		m_midiMusic.Play(m_bInfinite);
		m_midiMusic.SetVolume(m_nVolume);
		m_ctrlPlay.EnableWindow(FALSE);
		m_ctrlStop.EnableWindow();
		m_ctrlPause.EnableWindow();
	}
}

void CMidiSampleDlg::OnStop() 
{
	ASSERT(m_midiMusic.IsPlaying());
	m_midiMusic.Stop();
	m_ctrlPlay.EnableWindow();
	m_ctrlStop.EnableWindow(FALSE);
	m_ctrlPause.SetWindowText(TEXT("Pause"));
	m_ctrlPause.EnableWindow(FALSE);
}

void CMidiSampleDlg::OnPause() 
{
	ASSERT(m_midiMusic.IsPlaying());
	if(m_midiMusic.IsPaused()) {
		m_ctrlPause.SetWindowText(TEXT("Pause"));
		m_midiMusic.Continue();
	} else {
		m_ctrlPause.SetWindowText(TEXT("Resume"));
		m_midiMusic.Pause();
	}
}

void CMidiSampleDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// Note that "pScrollBar" is of type CSliderCtrl in reality !
	UpdateData(TRUE);
	m_midiMusic.SetVolume(m_nVolume);
	m_midiMusic.SetTempo(m_nTempo);
	UpdateData(FALSE);
}


LONG CMidiSampleDlg::OnSetPosition(WPARAM wParam, LPARAM) {
	m_strPosition.Format("%lu", DWORD(wParam));
	UpdateData(FALSE);
	return 0;
}


LONG CMidiSampleDlg::OnPlayedOff(WPARAM, LPARAM) {
	m_ctrlPlay.EnableWindow();
	m_ctrlStop.EnableWindow(FALSE);
	m_ctrlPause.SetWindowText(TEXT("Pause"));
	m_ctrlPause.EnableWindow(FALSE);
	return 0;
}

void CMidiSampleDlg::OnLoop() 
{
	UpdateData();
	m_midiMusic.SetInfinitePlay(m_bInfinite);
}
