// myothelloDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myothello.h"
#include "myothelloDlg.h"

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
// CMyothelloDlg dialog

CMyothelloDlg::CMyothelloDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyothelloDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyothelloDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CMyothelloDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyothelloDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyothelloDlg, CDialog)
	//{{AFX_MSG_MAP(CMyothelloDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_COMMAND(IDM_ABOUTBOX, OnAboutbox)
	ON_COMMAND(ID_NEWGAME, OnNewgame)
	ON_COMMAND(ID_EASY, OnEasy)
	ON_COMMAND(ID_MID, OnMid)
	ON_COMMAND(ID_ADV, OnAdv)
	ON_COMMAND(ID_MOVEBACK, OnMoveback)
	//}}AFX_MSG_MAP
		ON_MESSAGE(UM_RECALC, OnRecalc)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyothelloDlg message handlers
void CMyothelloDlg::OnRecalc(WPARAM wParam, LPARAM lParam)
{
	CString strStatus;
	if(wParam & 0x80000000)
	   strStatus.Format(" 黑棋:%2d 白棋:%2d  我找到一步好棋，现该你了!", UINT16(lParam), UINT16(wParam&0xFFFF)); 
	else
       strStatus.Format(" 黑棋:%2d 白棋:%2d  我正在想，你别急!" , UINT16(lParam), UINT16(wParam&0xFFFF)); 
	SetDlgItemText(IDC_STATUS, strStatus); 
}

BOOL CMyothelloDlg::OnInitDialog()
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
    m_chess.Create(CRect(5,5, 30,30), this, ID_CHESSBOARD); 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyothelloDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyothelloDlg::OnPaint() 
{
		CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{
	

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
	/*
	CDC imgdc;
	imgdc.CreateCompatibleDC(&dc);
	imgdc.SelectObject(&bitmap); 
    dc.BitBlt(170, 100, 43, 43, &imgdc,0,0,SRCCOPY);  	
	*/
	CString strStatus;
	strStatus.Format(" 黑棋:%2d 白棋:%2d  你先走!" , 2, 2); 
	SetDlgItemText(IDC_STATUS, strStatus); 
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyothelloDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyothelloDlg::OnButton1() 
{
	if(cur_step>0)
		return;
   computer_side = CHESS_BLACK;
   computer_play(&m_chess.m_oChessBoard, m_chess.m_hWnd);
   CMenu *pMenu = GetMenu();   
   (pMenu->GetSubMenu(1))->EnableMenuItem(IDC_BUTTON1, 
		               MF_BYCOMMAND|MF_GRAYED|MF_DISABLED);
   	UINT16 wscore, bscore;
	get_chess_score(&m_chess.m_oChessBoard, wscore, bscore);
    SendMessage(UM_RECALC, WPARAM(wscore|0x80000000), LPARAM(bscore)); 
}

void CMyothelloDlg::OnAboutbox() 
{
 		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
}

void CMyothelloDlg::OnNewgame() 
{
     m_chess.NewGame();
     CMenu *pMenu = GetMenu();   
	 (pMenu->GetSubMenu(1))->EnableMenuItem(IDC_BUTTON1, 
		               MF_BYCOMMAND|MF_ENABLED);//MF_GRAYED|MF_DISABLED);

	CString strStatus;
	strStatus.Format(" 黑棋:%2d 白棋:%2d  你先走!" , 2, 2); 
	SetDlgItemText(IDC_STATUS, strStatus); 
}


void CMyothelloDlg::OnEasy() 
{
   g_iGameLevel = 	GMLEVEL_EASY;
   CMenu *pMenu = GetMenu(); 
   (pMenu->GetSubMenu(1))->CheckMenuItem(ID_EASY, MF_BYCOMMAND|MF_CHECKED);
   (pMenu->GetSubMenu(1))->CheckMenuItem(ID_MID, MF_BYCOMMAND|MF_UNCHECKED);
   (pMenu->GetSubMenu(1))->CheckMenuItem(ID_ADV, MF_BYCOMMAND|MF_UNCHECKED);
  // (pMenu->GetSubMenu(1))->EnableMenuItem(ID_MID, MF_BYCOMMAND| MF_GRAYED);
}

void CMyothelloDlg::OnMid() 
{
  	 g_iGameLevel = GMLEVEL_MID;
	 CMenu *pMenu = GetMenu(); 
   (pMenu->GetSubMenu(1))->CheckMenuItem(ID_EASY, MF_BYCOMMAND|MF_UNCHECKED);
   (pMenu->GetSubMenu(1))->CheckMenuItem(ID_MID, MF_BYCOMMAND|MF_CHECKED);
   (pMenu->GetSubMenu(1))->CheckMenuItem(ID_ADV, MF_BYCOMMAND|MF_UNCHECKED);
}

void CMyothelloDlg::OnAdv() 
{
    g_iGameLevel = 	GMLEVEL_ADV;	
	CMenu *pMenu = GetMenu(); 
   (pMenu->GetSubMenu(1))->CheckMenuItem(ID_EASY, MF_BYCOMMAND|MF_UNCHECKED);
   (pMenu->GetSubMenu(1))->CheckMenuItem(ID_MID, MF_BYCOMMAND|MF_UNCHECKED);
   (pMenu->GetSubMenu(1))->CheckMenuItem(ID_ADV, MF_BYCOMMAND|MF_CHECKED);
}

void CMyothelloDlg::OnMoveback() 
{
   m_chess.MoveBack();
}
