// MuteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Mute.h"
#include "MuteDlg.h"

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
// CMuteDlg dialog

CMuteDlg::CMuteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMuteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMuteDlg)
	m_bMute = FALSE;
	m_strStat1 = _T("");
	m_strStat2 = _T("");
	m_strStat3 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMuteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMuteDlg)
	DDX_Check(pDX, IDC_CHECK, m_bMute);
	DDX_Text(pDX, IDC_STATIC1, m_strStat1);
	DDX_Text(pDX, IDC_STATIC2, m_strStat2);
	DDX_Text(pDX, IDC_STATIC3, m_strStat3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMuteDlg, CDialog)
	//{{AFX_MSG_MAP(CMuteDlg)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK, OnMute)
	ON_MESSAGE(MM_MIXM_CONTROL_CHANGE, OnMixerCtrlChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMuteDlg message handlers

BOOL CMuteDlg::OnInitDialog()
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
						  m_mxcaps.wMid, m_mxcaps.wPid, 
                          m_mxcaps.szPname, m_mxcaps.cDestinations,
                          m_mxcaps.fdwSupport, m_mxcaps.vDriverVersion);

		// get the Control ID and the names
		this->amdGetMasterMuteControl();

		// display the line and control name
		m_strStat3.Format(IDS_FMTNAMES,
						  m_strDstLineName, m_strMuteControlName);

		// get the initial value of the mute control
		LONG lVal;
		if (this->amdGetMasterMuteValue(lVal))
			m_bMute = lVal;

		this->UpdateData(FALSE);
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMuteDlg::OnDestroy() 
{
	this->amdUninitialize();

	CDialog::OnDestroy();
}

void CMuteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMuteDlg::OnPaint() 
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
HCURSOR CMuteDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMuteDlg::OnMute() 
{
	// TODO: Add your control notification handler code here
	// set the master mute value according to the state of the check box
	m_bMute = !m_bMute;
	this->amdSetMasterMuteValue(m_bMute);
}

LONG CMuteDlg::OnMixerCtrlChange(UINT wParam, LONG lParam)
{
	if ((HMIXER)wParam == m_hMixer && (DWORD)lParam == m_dwMuteControlID)
	{
		// The state of the master mute control has changed. Refresh it.
		LONG lVal;
		if (this->amdGetMasterMuteValue(lVal))
			m_bMute = lVal;

		this->UpdateData(FALSE);
	}

	return 0L;
}

BOOL CMuteDlg::amdInitialize()
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
						(DWORD)this->GetSafeHwnd(),
						NULL,
						MIXER_OBJECTF_MIXER | CALLBACK_WINDOW)
			!= MMSYSERR_NOERROR)
			return FALSE;

		if (::mixerGetDevCaps((UINT)m_hMixer, &m_mxcaps, sizeof(MIXERCAPS))
			!= MMSYSERR_NOERROR)
			return FALSE;
	}

	return TRUE;
}

BOOL CMuteDlg::amdUninitialize()
{
	BOOL bSucc = TRUE;

	if (m_hMixer != NULL)
	{
		bSucc = ::mixerClose(m_hMixer) == MMSYSERR_NOERROR;
		m_hMixer = NULL;
	}

	return bSucc;
}

BOOL CMuteDlg::amdGetMasterMuteControl()
{
	m_strDstLineName.Empty();
	m_strMuteControlName.Empty();

	if (m_hMixer == NULL)
		return FALSE;

	// get dwLineID
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	if (::mixerGetLineInfo((HMIXEROBJ)m_hMixer,
						   &mxl,
						   MIXER_OBJECTF_HMIXER |
						   MIXER_GETLINEINFOF_COMPONENTTYPE)
		!= MMSYSERR_NOERROR)
		return FALSE;

    TRACE("SName: %s, Name: %s.\n", mxl.szShortName, mxl.szName); 
	// get dwControlID
	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID = mxl.dwLineID;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_MUTE;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(MIXERCONTROL);
	mxlc.pamxctrl = &mxc;
	if (::mixerGetLineControls((HMIXEROBJ)m_hMixer,
							   &mxlc,
							   MIXER_OBJECTF_HMIXER |
							   MIXER_GETLINECONTROLSF_ONEBYTYPE)
		!= MMSYSERR_NOERROR)
		return FALSE;

	// record dwControlID
	m_strDstLineName = mxl.szName;
	m_strMuteControlName = mxc.szName;
	m_dwMuteControlID = mxc.dwControlID;

	return TRUE;
}

BOOL CMuteDlg::amdGetMasterMuteValue(LONG &lVal) const
{
	if (m_hMixer == NULL ||
		m_strDstLineName.IsEmpty() || m_strMuteControlName.IsEmpty())
		return FALSE;

	MIXERCONTROLDETAILS_BOOLEAN mxcdMute;
	MIXERCONTROLDETAILS mxcd;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_dwMuteControlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
	mxcd.paDetails = &mxcdMute;
	if (::mixerGetControlDetails((HMIXEROBJ)m_hMixer,
								 &mxcd,
								 MIXER_OBJECTF_HMIXER |
								 MIXER_GETCONTROLDETAILSF_VALUE)
		!= MMSYSERR_NOERROR)
		return FALSE;
	
	lVal = mxcdMute.fValue;

	return TRUE;
}

BOOL CMuteDlg::amdSetMasterMuteValue(LONG lVal) const
{
	if (m_hMixer == NULL ||
		m_strDstLineName.IsEmpty() || m_strMuteControlName.IsEmpty())
		return FALSE;

	MIXERCONTROLDETAILS_BOOLEAN mxcdMute = { lVal };
	MIXERCONTROLDETAILS mxcd;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_dwMuteControlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN);
	mxcd.paDetails = &mxcdMute;
	if (::mixerSetControlDetails((HMIXEROBJ)m_hMixer,
								 &mxcd,
								 MIXER_OBJECTF_HMIXER |
								 MIXER_SETCONTROLDETAILSF_VALUE)
		!= MMSYSERR_NOERROR)
		return FALSE;
	
	return TRUE;
}
