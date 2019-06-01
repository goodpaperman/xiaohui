// CColorStaticST_demoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CColorStaticST_demo.h"
#include "CColorStaticST_demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCColorStaticST_demoDlg dialog

CCColorStaticST_demoDlg::CCColorStaticST_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCColorStaticST_demoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCColorStaticST_demoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCColorStaticST_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCColorStaticST_demoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCColorStaticST_demoDlg, CDialog)
	//{{AFX_MSG_MAP(CCColorStaticST_demoDlg)
	ON_BN_CLICKED(IDB_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER + 10, OnDangerBlink)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCColorStaticST_demoDlg message handlers

BOOL CCColorStaticST_demoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Reset <Danger> blinks count
	m_nDangerCount = 0;

	// Create a font
	m_Font.CreateFont(-16, 0, 0, 0, FW_BOLD, FALSE, FALSE,0,0,0,0,0,0, "Verdana");

	// Create the colored <SoftechSoftware> sign
	m_stcSTSign.SubclassDlgItem(IDC_STSIGN, this);
	// Set the text color
	// Tooltip's foreground color
	m_stcSTSign.SetTextColor(::GetSysColor(COLOR_INFOTEXT));
	// Set the background color
	// Tooltip's background color
	m_stcSTSign.SetBkColor(::GetSysColor(COLOR_INFOBK));


	// Create the colored and blinking <Incoming call>
	m_stcCalling.SubclassDlgItem(IDC_CALLING, this);
	// Set background blinking colors
	// Medium and light green
	m_stcCalling.SetBlinkBkColors(RGB(0, 128, 0), RGB(0,255,0));
	// Start background blinking
	m_stcCalling.StartBkBlink(TRUE, CColorStaticST::ST_FLS_FAST);
	// Set text blinking colors
	// Medium green and black
	m_stcCalling.SetBlinkTextColors(m_stcCalling.GetBkColor(), RGB(0,0,0));
	// Start text blinking
	m_stcCalling.StartTextBlink(TRUE, CColorStaticST::ST_FLS_SLOW);


	// Create the colored and blinking <Danger>
	m_stcDanger.SubclassDlgItem(IDC_DANGER, this);
	// Set background blinking colors
	// Medium and light red
	m_stcDanger.SetBlinkBkColors(RGB(128, 0, 0), RGB(255,0,0));
	// Start background blinking
	m_stcDanger.StartBkBlink(TRUE, CColorStaticST::ST_FLS_FAST);
	// Set text blinking colors
	// Medium red and white
	m_stcDanger.SetBlinkTextColors(RGB(128,0,0), RGB(255,255,255));
	// Start text blinking
	m_stcDanger.StartTextBlink(TRUE, CColorStaticST::ST_FLS_FAST);
	// Set a special font
	m_stcDanger.SetFont(&m_Font);
	// We want be notified when the control blinks
	m_stcDanger.EnableNotify(this, WM_USER + 10);
	
	// Write class version
	CString sVersion;
	sVersion.Format("CColorStaticST v%s", CColorStaticST::GetVersionC());
	SetWindowText(sVersion);

	return TRUE;
} // End of OnInitDialog


// This function will be called each time the <Danger> control blinks
// The notification is sent only on rising blinks (this means only when
// the control goes light red)
LRESULT CCColorStaticST_demoDlg::OnDangerBlink(WPARAM wParam, LPARAM lParam)
{
	SetDlgItemInt(IDC_DANGERCOUNT, ++m_nDangerCount);

	return 0;
} // End of OnDangerBlink


void CCColorStaticST_demoDlg::OnAbout() 
{
	CAboutDlg about;

	about.DoModal();	
} // End of OnAbout
