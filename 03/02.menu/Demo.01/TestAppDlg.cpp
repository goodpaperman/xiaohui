// TestAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestApp.h"
#include "TestAppDlg.h"
#include "CBmpMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestAppDlg dialog

CTestAppDlg::CTestAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestAppDlg)
	m_csWidth = _T("");
	m_nStretch = -1;
	m_bShowBmp = FALSE;
	m_bShow4All = FALSE;
	m_bShowSlider = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestAppDlg)
	DDX_Text(pDX, IDC_WIDTH, m_csWidth);
	DDX_Radio(pDX, IDC_STRETCH, m_nStretch);
	DDX_Check(pDX, IDC_SHOWBMP, m_bShowBmp);
	DDX_Check(pDX, IDC_SHOW4ALL, m_bShow4All);
	DDX_Check(pDX, IDC_SHOWSLIDER, m_bShowSlider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestAppDlg, CDialog)
	//{{AFX_MSG_MAP(CTestAppDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_POPUPMENU, OnPopupmenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestAppDlg message handlers

BOOL CTestAppDlg::OnInitDialog()
{
	m_csWidth = CString("30");
	m_nStretch = 1;
	m_bShowBmp = TRUE;
	m_bShow4All = TRUE;

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestAppDlg::OnPaint() 
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
HCURSOR CTestAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestAppDlg::OnPopupmenu() 
{
	// TODO: Add your control notification handler code here
	HBITMAP hBitmap = LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_VERTBMP));

	UpdateData();

	CBmpMenu oMenu(atoi(m_csWidth.GetBuffer(0)), m_bShow4All, m_bShowBmp?hBitmap:0, (m_nStretch==0)?TRUE:FALSE);

	oMenu.LoadMenu(IDR_TESTMENU);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_ITEMCHECKED);
	CBitmap bmp1;
	bmp1.LoadBitmap(IDB_ITEMUNCHECKED);

	oMenu.SetMenuItemBitmaps( 2, MF_BYPOSITION, &bmp1, &bmp);
	oMenu.SetMenuItemBitmaps( 0, MF_BYPOSITION, &bmp1, &bmp);
	oMenu.SetMenuItemBitmaps( 3, MF_BYPOSITION, &bmp, &bmp);

	CPoint pt;
	//GetCursorPos(&pt); 
	//oMenu.TrackPopupMenu(0, pt.x, pt.y, this);
    CRect rect; 
    GetDlgItem(IDC_POPUPMENU)->GetWindowRect(&rect); 
    oMenu.TrackPopupMenu(0, rect.left, rect.bottom, this/*, &rect*/); 
}

LRESULT CTestAppDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	static HMENU hMainMenu = 0;

	//slider control processing
	if(message == WM_ENTERMENULOOP)
	{
		if(m_bShowSlider)
		{
			if(IsWindow((HWND)lParam))
			{
				//we have got handle of menu window...draw a child window inside menu
				if(!IsWindow(m_Slider.m_hWnd))
				{
					CRect rect;
					FromHandle((HWND)lParam)->GetClientRect(&rect);
					rect.right = atoi(m_csWidth.GetBuffer(0));
					rect.left = atoi(m_csWidth.GetBuffer(0))/2;
					m_Slider.Create(TBS_VERT|TBS_AUTOTICKS|WS_VISIBLE|TBS_FIXEDLENGTH, rect, FromHandle(HWND(lParam)), 2001);
					m_Slider.SendMessage(TBM_SETTHUMBLENGTH, atoi(m_csWidth.GetBuffer(0))/3, 0);
					m_Slider.SetRange(0,4);

					hMainMenu = (HMENU)wParam;
				}
			}
		}		
	}

	//set the slider position whenever a menu item is selected
	if(message == WM_MENUSELECT)
	{
		int		nId = LOWORD(wParam);
		HMENU	hMenu = (HMENU)lParam;

		//set the slider position
		if(hMenu == hMainMenu)
		{
			//check if this a popup menu
			if(HIWORD(wParam) == MF_POPUP)
			{
				m_Slider.SetPos(nId);
			}
			else
			{
				for(int i=0; i<GetMenuItemCount(hMenu); i++)
				{
					int MenuItem = GetMenuItemID(hMenu, i);
					if(nId == MenuItem)
					{
						m_Slider.SetPos(i);
						break;
					}
				}
			}
		}
	}

	return CDialog::DefWindowProc(message, wParam, lParam);
}
