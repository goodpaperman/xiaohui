// MeterDlg.cpp : implementation file
//

#include "stdafx.h"
#include <stdlib.h>            // abs, __max
#include "Meter.h"
#include "MeterDlg.h"

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
// CMeterDlg dialog

CMeterDlg::CMeterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMeterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeterDlg)
	m_strStat1 = _T("");
	m_strStat2 = _T("");
	m_strStat3 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMeterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeterDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
	DDX_Text(pDX, IDC_STATIC1, m_strStat1);
	DDX_Text(pDX, IDC_STATIC2, m_strStat2);
	DDX_Text(pDX, IDC_STATIC3, m_strStat3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMeterDlg, CDialog)
	//{{AFX_MSG_MAP(CMeterDlg)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeterDlg message handlers

BOOL CMeterDlg::OnInitDialog()
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
	if (this->amdInitialize())
	{
		// display the number of mixer devices present in the system
		m_strStat1.Format(IDS_FMTNUMMIXERS, m_nNumMixers);

		// display the information about the first mixer
		m_strStat2.Format(IDS_FMTCAPS,
						  m_mxcaps.szPname, m_mxcaps.cDestinations);

		// get the Control ID and the names
		this->amdGetWaveMeterControl();

		// display the line and control name
		m_strStat3.Format(IDS_FMTNAMES,
						  m_strWaveLineName, m_strMeterControlName);

		// Initialize the progress control. The range of integer values
		// for the peak meter is -32,768 through 32,767.
		m_ctrlProgress.SetRange(0, __max(::abs(m_lMinimum), ::abs(m_lMaximum)));

		this->UpdateData(FALSE);
	}
	
	m_nTimerID = this->SetTimer(TIMER_ID, TIMER_ELAPSE, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMeterDlg::OnDestroy() 
{
	if (m_nTimerID != 0)
	{
		this->KillTimer(m_nTimerID);
		m_nTimerID = 0;
	}

	this->amdUninitialize();

	CDialog::OnDestroy();
}

void CMeterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMeterDlg::OnPaint() 
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
HCURSOR CMeterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMeterDlg::OnTimer(UINT nIDEvent)
{
	UNREFERENCED_PARAMETER(nIDEvent);

	ASSERT(nIDEvent == m_nTimerID && nIDEvent == TIMER_ID);

	LONG lVal;
	if (this->amdGetWaveMeterValue(lVal))
		m_ctrlProgress.SetPos(::abs(lVal));
		//m_ctrlProgress.SetPos(lVal >= 0 ? lVal : -lVal);
}

BOOL CMeterDlg::amdInitialize()
{
	// get the number of mixer devices present in the system
	m_nNumMixers = ::mixerGetNumDevs();

	m_hMixer = NULL;
	::ZeroMemory(&m_mxcaps, sizeof(MIXERCAPS));

	// open the first mixer
	// A "mapper" for audio mixer devices does not currently exist.
	if (m_nNumMixers != 0)
	{
		if (::mixerOpen(&m_hMixer,
						0,
						0,
						NULL,
						MIXER_OBJECTF_MIXER)
			!= MMSYSERR_NOERROR)
			return FALSE;

		if (::mixerGetDevCaps((UINT)m_hMixer, &m_mxcaps, sizeof(MIXERCAPS))
			!= MMSYSERR_NOERROR)
			return FALSE;
	}

	return TRUE;
}

BOOL CMeterDlg::amdUninitialize()
{
	BOOL bSucc = TRUE;

	if (m_hMixer != NULL)
	{
		bSucc = ::mixerClose(m_hMixer) == MMSYSERR_NOERROR;
		m_hMixer = NULL;
	}

	return bSucc;
}

BOOL CMeterDlg::amdGetWaveMeterControl()
{
	m_strWaveLineName.Empty();
	m_strMeterControlName.Empty();

	if (m_hMixer == NULL)
		return FALSE;

	// get dwLineID
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS; //WAVEOUT;
	if (::mixerGetLineInfo((HMIXEROBJ)m_hMixer,
		                   &mxl,
			    		   MIXER_OBJECTF_HMIXER |
				    	   MIXER_GETLINEINFOF_COMPONENTTYPE)
		!= MMSYSERR_NOERROR)
		return FALSE;

	m_strWaveLineName = mxl.szName;
	// get dwControlID
	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID = mxl.dwLineID;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME; //PEAKMETER;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(MIXERCONTROL);
	mxlc.pamxctrl = &mxc;
	int ret = ::mixerGetLineControls((HMIXEROBJ)m_hMixer,
		                       &mxlc,
			    			   MIXER_OBJECTF_HMIXER |
				    		   MIXER_GETLINECONTROLSF_ONEBYTYPE); 
	if(ret != MMSYSERR_NOERROR)
    {        
        // invalid control ? 
		return FALSE;
    }

	// record dwControlID
	m_strMeterControlName = mxc.szName;
	m_lMinimum = mxc.Bounds.lMinimum;
	m_lMaximum = mxc.Bounds.lMaximum;
	m_dwMeterControlID = mxc.dwControlID;

	return TRUE;
}

BOOL CMeterDlg::amdGetWaveMeterValue(LONG &lVal) const
{
	if (m_hMixer == NULL ||
		m_strWaveLineName.IsEmpty() || m_strMeterControlName.IsEmpty())
		return FALSE;

	MIXERCONTROLDETAILS_SIGNED mxcdMeter;
    MIXERCONTROLDETAILS mxcd;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
    mxcd.dwControlID = m_dwMeterControlID;
    mxcd.cChannels = 1;
    mxcd.cMultipleItems = 0;
    mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_SIGNED);
    mxcd.paDetails = &mxcdMeter;
	if (::mixerGetControlDetails((HMIXEROBJ)m_hMixer,
		                         &mxcd,
		                         MIXER_OBJECTF_HMIXER |
				    			 MIXER_GETCONTROLDETAILSF_VALUE)
		!= MMSYSERR_NOERROR)
		return FALSE;
	
	lVal = mxcdMeter.lValue;

	return TRUE;
}
