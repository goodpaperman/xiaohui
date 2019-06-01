// VolumeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Volume.h"
#include "VolumeDlg.h"

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
// CVolumeDlg dialog

CVolumeDlg::CVolumeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVolumeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVolumeDlg)
	m_strStat1 = _T("");
	m_strStat2 = _T("");
	m_strStat3 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVolumeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVolumeDlg)
	DDX_Control(pDX, IDC_SLIDER, m_ctrlSlider);
	DDX_Text(pDX, IDC_STATIC1, m_strStat1);
	DDX_Text(pDX, IDC_STATIC2, m_strStat2);
	DDX_Text(pDX, IDC_STATIC3, m_strStat3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVolumeDlg, CDialog)
	//{{AFX_MSG_MAP(CVolumeDlg)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_MESSAGE(MM_MIXM_CONTROL_CHANGE, OnMixerCtrlChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeDlg message handlers

BOOL CVolumeDlg::OnInitDialog()
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
		this->amdGetMasterVolumeControl();

		// display the line and control name
		m_strStat3.Format(IDS_FMTNAMES,
						  m_strDstLineName, m_strVolumeControlName);

		// Initialize the slider control. For a volume control,
		// the range of acceptable values is 0 through 65,535.
		m_ctrlSlider.SetRange(m_dwMinimum, m_dwMaximum);
        TRACE("Min: %d, Max: %d.\n", m_dwMinimum, m_dwMaximum); 

		// get the initial value of the volume control
		DWORD dwVal;
		if (this->amdGetMasterVolumeValue(dwVal))
			m_ctrlSlider.SetPos(dwVal);

		this->UpdateData(FALSE);
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVolumeDlg::OnDestroy() 
{
	this->amdUninitialize();

	CDialog::OnDestroy();
}

void CVolumeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVolumeDlg::OnPaint() 
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
HCURSOR CVolumeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVolumeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	// set the master volume value according to the slider control
	if (pScrollBar != NULL)
		this->amdSetMasterVolumeValue(((CSliderCtrl *)pScrollBar)->GetPos());
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

LONG CVolumeDlg::OnMixerCtrlChange(UINT wParam, LONG lParam)
{
	if ((HMIXER)wParam == m_hMixer && (DWORD)lParam == m_dwVolumeControlID)
	{
		// The state of the master volume control has changed. Refresh it.
		DWORD dwVal;
		if (this->amdGetMasterVolumeValue(dwVal))
			m_ctrlSlider.SetPos(dwVal);
	}

	return 0L;
}

BOOL CVolumeDlg::amdInitialize()
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

BOOL CVolumeDlg::amdUninitialize()
{
	BOOL bSucc = TRUE;

	if (m_hMixer != NULL)
	{
		bSucc = ::mixerClose(m_hMixer) == MMSYSERR_NOERROR;
		m_hMixer = NULL;
	}

	return bSucc;
}

BOOL CVolumeDlg::amdGetMasterVolumeControl()
{
	m_strDstLineName.Empty();
	m_strVolumeControlName.Empty();

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

	// get dwControlID
	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID = mxl.dwLineID;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
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
    TRACE("SName: %s, Name: %s.\n", mxl.szShortName, mxl.szName); 
	m_strVolumeControlName = mxc.szName;
	m_dwMinimum = mxc.Bounds.dwMinimum;
	m_dwMaximum = mxc.Bounds.dwMaximum;
	m_dwVolumeControlID = mxc.dwControlID;

	return TRUE;
}

BOOL CVolumeDlg::amdGetMasterVolumeValue(DWORD &dwVal) const
{
	if (m_hMixer == NULL ||
		m_strDstLineName.IsEmpty() || m_strVolumeControlName.IsEmpty())
		return FALSE;

	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume;
	MIXERCONTROLDETAILS mxcd;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_dwVolumeControlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVolume;
	if (::mixerGetControlDetails((HMIXEROBJ)m_hMixer,
								 &mxcd,
								 MIXER_OBJECTF_HMIXER |
								 MIXER_GETCONTROLDETAILSF_VALUE)
		!= MMSYSERR_NOERROR)
		return FALSE;
	
	dwVal = mxcdVolume.dwValue;
    TRACE("Volume: %d.\n", dwVal); 
	return TRUE;
}

BOOL CVolumeDlg::amdSetMasterVolumeValue(DWORD dwVal) const
{
	if (m_hMixer == NULL ||
		m_strDstLineName.IsEmpty() || m_strVolumeControlName.IsEmpty())
		return FALSE;

	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume = { dwVal };
	MIXERCONTROLDETAILS mxcd;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_dwVolumeControlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVolume;
	if (::mixerSetControlDetails((HMIXEROBJ)m_hMixer,
								 &mxcd,
								 MIXER_OBJECTF_HMIXER |
								 MIXER_SETCONTROLDETAILSF_VALUE)
		!= MMSYSERR_NOERROR)
		return FALSE;
	
	return TRUE;
}
