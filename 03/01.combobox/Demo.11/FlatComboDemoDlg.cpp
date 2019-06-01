// FlatComboDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FlatComboDemo.h"
#include "FlatComboDemoDlg.h"

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
// CFlatComboDemoDlg dialog

CFlatComboDemoDlg::CFlatComboDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlatComboDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlatComboDemoDlg)
	m_bDDAutoComp = FALSE;
	m_bDDDisable = FALSE;
	m_bDLDisable = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_clrDLText = RGB( 0, 0, 0 );
	m_clrDLBack = RGB( 255, 255, 255 );
	m_clrDDText = RGB( 0, 0, 0 );
	m_clrDDBack = RGB( 255, 255, 255 );
}

void CFlatComboDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlatComboDemoDlg)
	DDX_Control(pDX, IDC_DROPLIST_TXT_CLR, m_DLTextColor);
	DDX_Control(pDX, IDC_DROPLIST_COMBO, m_DLCombo);
	DDX_Control(pDX, IDC_DROPLIST_BAK_CLR, m_DLBackColor);
	DDX_Control(pDX, IDC_DROPDOWN_TXT_CLR, m_DDTextColor);
	DDX_Control(pDX, IDC_DROPDOWN_COMBO, m_DDCombo);
	DDX_Control(pDX, IDC_DROPDOWN_BAK_CLR, m_DDBackColor);
	DDX_Check(pDX, IDC_DROPDOWN_AUTOCOMP, m_bDDAutoComp);
	DDX_Check(pDX, IDC_DROPDOWN_DISABLE, m_bDDDisable);
	DDX_Check(pDX, IDC_DROPLIST_DISABLE, m_bDLDisable);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFlatComboDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CFlatComboDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DROPLIST_DISABLE, OnDroplistDisable)
	ON_BN_CLICKED(IDC_DROPDOWN_DISABLE, OnDropdownDisable)
	ON_BN_CLICKED(IDC_DROPDOWN_AUTOCOMP, OnDropdownAutocomp)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE( CPN_SELENDOK,  OnSelEndOK )
    ON_MESSAGE( CPN_SELCHANGE, OnSelEndOK )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatComboDemoDlg message handlers

BOOL CFlatComboDemoDlg::OnInitDialog()
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
	
	//////////////////////////////////////
	// set each combo's index.
	//////////////////////////////////////
	m_DDCombo.SetCurSel(0);
	m_DLCombo.SetCurSel(1);

	//////////////////////////////////////
	// enable auto completion based on boolean.
	//////////////////////////////////////
	m_DDCombo.EnableAutoCompletion( m_bDDAutoComp );

	//////////////////////////////////////
	// set the text color controls based on current combo color.
	//////////////////////////////////////
	m_DLTextColor.SetColor( m_clrDLText );
	m_DLBackColor.SetColor( m_clrDLBack );
	m_DDTextColor.SetColor( m_clrDDText );
	m_DDBackColor.SetColor( m_clrDDBack );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFlatComboDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFlatComboDemoDlg::OnPaint() 
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
HCURSOR CFlatComboDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFlatComboDemoDlg::OnSelEndOK(UINT lParam, LONG wParam)
{
	// a color selection was made, update the 
	// appropriate member data.
	switch( wParam )
	{
	case IDC_DROPLIST_TXT_CLR:
		m_clrDLText = m_DLTextColor.GetColor();
		m_DLCombo.Invalidate();
		break;
	
	case IDC_DROPLIST_BAK_CLR:
		m_clrDLBack = m_DLBackColor.GetColor();
		m_DLCombo.Invalidate();
		break;

	case IDC_DROPDOWN_TXT_CLR:
		m_clrDDText = m_DDTextColor.GetColor();
		m_DDCombo.Invalidate();
		break;
	
	case IDC_DROPDOWN_BAK_CLR:
		m_clrDDBack = m_DDBackColor.GetColor();
		m_DDCombo.Invalidate();
		break;
	}
}

void CFlatComboDemoDlg::OnDroplistDisable() 
{
	UpdateData();
	m_DLCombo.EnableWindow( !m_bDLDisable );
}

void CFlatComboDemoDlg::OnDropdownDisable() 
{
	UpdateData();
	m_DDCombo.EnableWindow( !m_bDDDisable );
}

void CFlatComboDemoDlg::OnDropdownAutocomp() 
{
	UpdateData();
	m_DDCombo.EnableAutoCompletion( m_bDDAutoComp );
}

HBRUSH CFlatComboDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// set the combo boxes text and background colors...
	int nItem = pWnd->GetDlgCtrlID();
	switch (nItem)
	{
		case IDC_DROPLIST_COMBO:
			if( pWnd->IsWindowEnabled( )) {
				pDC->SetTextColor(m_clrDLText);
				pDC->SetBkColor(m_clrDLBack);
                pDC->SetBkMode(TRANSPARENT); 
			}
			break;

		case IDC_DROPDOWN_COMBO:
			if( pWnd->IsWindowEnabled( )) {
				pDC->SetTextColor(m_clrDDText);
				pDC->SetBkColor(m_clrDDBack);
			}
			break;
	}

	return hbr;
}
