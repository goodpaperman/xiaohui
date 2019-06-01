// MixerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Mixer.h"
#include "MixerDlg.h"

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
// CMixerDlg dialog

CMixerDlg::CMixerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMixerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMixerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMixerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMixerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMixerDlg, CDialog)
	//{{AFX_MSG_MAP(CMixerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMixerDlg message handlers

BOOL CMixerDlg::OnInitDialog()
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
	HMIXER hMixer; 
    int n = ::mixerGetNumDevs(); 
    if(n > 0)
    {
        if(::mixerOpen(&hMixer, 0, NULL, NULL, 0) != MMSYSERR_NOERROR)
            return FALSE; 

        MIXERCAPS mixercaps; 
        if(::mixerGetDevCaps((DWORD)hMixer, &mixercaps, sizeof(MIXERCAPS)) != MMSYSERR_NOERROR)
            return FALSE; 

        TRACE("Mixer: %s.\n", mixercaps.szPname); 
        for(int i=0; i<mixercaps.cDestinations; i++)
        {
            MIXERLINE mixerline; 
            mixerline.cbStruct = sizeof(MIXERLINE); 
            mixerline.dwDestination = i; 
            if(::mixerGetLineInfo((HMIXEROBJ)hMixer, &mixerline, MIXER_GETLINEINFOF_DESTINATION) != MMSYSERR_NOERROR)
                continue; 

            TRACE("\nDestination #%d = %s[%u], type = %d, channel = %d.\n", 
                mixerline.dwDestination, mixerline.szName, 
                mixerline.dwLineID, mixerline.dwComponentType, 
                mixerline.cChannels); 
            GetControlForLine(hMixer, mixerline); 
            for(int j=0; j<mixerline.cConnections; j++)
            {
                MIXERLINE mxl; 
                mxl.cbStruct = sizeof(MIXERLINE); 
                mxl.dwDestination = i; 
                mxl.dwSource = j; 
                if(::mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_GETLINEINFOF_SOURCE) != MMSYSERR_NOERROR)
                    continue; 

                TRACE("\nSource #%d = %s[%u], type = %d, channel = %d.\n", 
                    mxl.dwSource, mxl.szName,
                    mxl.dwLineID, mxl.dwComponentType, 
                    mxl.cChannels); 
                GetControlForLine(hMixer, mxl); 
            }
        }

        MIXERLINE mxl; 
        mxl.cbStruct = sizeof(MIXERLINE); 
        mxl.dwLineID = 0; 
        if(::mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_GETLINEINFOF_LINEID) == MMSYSERR_NOERROR)
        {
            TRACE("Mixer Line with ID 0 is: %s.\n", mxl.szName); 
        }

        mxl.cbStruct = sizeof(MIXERLINE); 
        mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER; 
        if(::mixerGetLineInfo((HMIXEROBJ)hMixer, &mxl, MIXER_GETLINEINFOF_COMPONENTTYPE) == MMSYSERR_NOERROR)
        {
            TRACE("Mixer Line with component type MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER is: %s.\n", mxl.szName); 
        }

        MIXERLINECONTROLS mxlc; 
        MIXERCONTROL mxc; 
        mxlc.cbStruct = sizeof(MIXERLINECONTROLS); 
        mxlc.cControls = 1; 
        mxlc.dwControlID = 0; 
        mxlc.cbmxctrl = sizeof(MIXERCONTROL); 
        mxlc.pamxctrl = &mxc; 
        if(::mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_GETLINECONTROLSF_ONEBYID) == MMSYSERR_NOERROR)
        {
            TRACE("Control with ID 0 is: %s.\n", mxc.szName); 
        }

        mxlc.cbStruct = sizeof(MIXERLINECONTROLS); 
        mxlc.dwLineID = 0; 
        mxlc.cControls = 1; 
        mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME; 
        mxlc.cbmxctrl = sizeof(MIXERCONTROL); 
        mxlc.pamxctrl = &mxc; 
        if(::mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_GETLINECONTROLSF_ONEBYTYPE) == MMSYSERR_NOERROR)
        {
            TRACE("Control with Type MIXERCONTROL_CONTROLTYPE_VOLUME & Line ID 0 is: %s[%d].\n", mxc.szName, mxc.dwControlID); 
        }
        
        MIXERCONTROLDETAILS_UNSIGNED value = { 0 }; 
        MIXERCONTROLDETAILS mxcd; 
        mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS); 
        mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED); 
        mxcd.cChannels = 1; 
        mxcd.cMultipleItems = 0; 
        mxcd.dwControlID = 2;  // mute
        mxcd.paDetails = &value; 
        if(::mixerSetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_SETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR)
        {
            TRACE("Value: %d.\n", value.dwValue); 
        }

        MIXERCONTROLDETAILS_UNSIGNED values[2]; 
        mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS); 
        mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED); 
        mxcd.cChannels = 2; 
        mxcd.cMultipleItems = 0; 
        mxcd.dwControlID = 1; // volume
        mxcd.paDetails = &values[0]; 
        if(::mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR)
        {
            TRACE("the left channel volume is: %d.\n", values[0]); 
            TRACE("the right channel volume is: %d.\n", values[1]); 
        }
        
        values[0].dwValue = 7000; 
        values[1].dwValue = 7000; 
        mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS); 
        mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED); 
        mxcd.cChannels = 2; 
        mxcd.cMultipleItems = 0; 
        mxcd.dwControlID = 1; // volume
        mxcd.paDetails = &values[0]; 
        if(::mixerSetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_SETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR)
        {
            TRACE("the left channel volume is: %d.\n", values[0]); 
            TRACE("the right channel volume is: %d.\n", values[1]); 
        }

        MIXERCONTROLDETAILS_UNSIGNED vals[4]; 
        mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS); 
        mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED); 
        mxcd.cChannels = 1; 
        mxcd.cMultipleItems = 4; 
        mxcd.dwControlID = 0; // 多路转换器
        mxcd.paDetails = &vals[0]; 
        if(::mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR)
        {
            MIXERCONTROLDETAILS_LISTTEXT txts[4]; 
            mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS); 
            mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_LISTTEXT); 
            mxcd.cChannels = 1; 
            mxcd.cMultipleItems = 4; 
            mxcd.dwControlID = 0; // 多路转换器
            mxcd.paDetails = &txts[0]; 
            if(::mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_GETCONTROLDETAILSF_LISTTEXT) == MMSYSERR_NOERROR)
            {   
                TRACE("1.%s(%d, %d) is: %d.\n", txts[0].szName, txts[0].dwParam1, txts[0].dwParam2, vals[0]); 
                TRACE("2.%s(%d, %d) is: %d.\n", txts[1].szName, txts[1].dwParam1, txts[1].dwParam2, vals[1]); 
                TRACE("3.%s(%d, %d) is: %d.\n", txts[2].szName, txts[2].dwParam1, txts[2].dwParam2, vals[2]); 
                TRACE("4.%s(%d, %d) is: %d.\n", txts[3].szName, txts[3].dwParam1, txts[3].dwParam2, vals[3]); 
            }
        }
        
        MIXERCONTROLDETAILS_BOOLEAN val[4]; 
        val[0].fValue = 0; 
        val[1].fValue = 1; 
        val[2].fValue = 0; 
        val[3].fValue = 0; 
        mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS); 
        mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_BOOLEAN); 
        mxcd.cChannels = 1; 
        mxcd.cMultipleItems = 4; 
        mxcd.dwControlID = 0; // 多路转换器
        mxcd.paDetails = &val[0]; 
        if((i = ::mixerSetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_SETCONTROLDETAILSF_VALUE)) == MMSYSERR_NOERROR)
        {
            TRACE("the 1st is: %d.\n", val[0]); 
            TRACE("the 2nd is: %d.\n", val[1]); 
            TRACE("the 3rd is: %d.\n", val[2]); 
            TRACE("the 4th is: %d.\n", val[3]); 
        }
    }
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMixerDlg::GetControlForLine(HMIXER hMixer, MIXERLINE& mxl)
{
    MIXERLINECONTROLS mxlc; 
    MIXERCONTROL mxc[10]; 
    mxlc.cbStruct = sizeof(MIXERLINECONTROLS); 
    mxlc.cControls = mxl.cChannels; 
    mxlc.dwLineID = mxl.dwLineID; 
    mxlc.cbmxctrl = sizeof(MIXERCONTROL); 
    mxlc.pamxctrl = mxc; 
    if(::mixerGetLineControls((HMIXEROBJ)hMixer, &mxlc, MIXER_GETLINECONTROLSF_ALL) == MMSYSERR_NOERROR)
    {
        TRACE("Controls:\n"); 
        for(int i=0; i<mxl.cChannels; i++)
        {
            TRACE("%s[%d], type = %d, (%d, %d), step = %d, item = %d.\n", 
                mxc[i].szName, mxc[i].dwControlID, mxc[i].dwControlType,
                mxc[i].Bounds.dwMinimum, mxc[i].Bounds.dwMaximum, 
                mxc[i].Metrics.cSteps, mxc[i].cMultipleItems); 
            

            MIXERCONTROLDETAILS_UNSIGNED value; 
            MIXERCONTROLDETAILS mxcd; 
            mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS); 
            mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED); 
            mxcd.cChannels = 1; 
            mxcd.cMultipleItems = 0; 
            mxcd.dwControlID = mxc[i].dwControlID; 
            mxcd.paDetails = &value; 
            if(::mixerGetControlDetails((HMIXEROBJ)hMixer, &mxcd, MIXER_GETCONTROLDETAILSF_VALUE) == MMSYSERR_NOERROR)
            {
                TRACE("Value: %d.\n", value.dwValue); 
            }
        }
    }
}

void CMixerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMixerDlg::OnPaint() 
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
HCURSOR CMixerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
