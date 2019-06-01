// RealDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Real.h"
#include "RealDlg.h"

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
// CRealDlg dialog

CRealDlg::CRealDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRealDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRealDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 변수 초기화
	m_hBmp = NULL;
	m_hSys = NULL;
	m_bClose = FALSE;
	gwl = 0;

}

void CRealDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRealDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRealDlg, CDialog)
	//{{AFX_MSG_MAP(CRealDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DRAWITEM()
	ON_WM_DESTROY()
	ON_WM_ACTIVATE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_MEASUREITEM()
	ON_WM_NCPAINT()
	ON_WM_SETCURSOR()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_INITMENU()
	ON_COMMAND(IDM_CLOSE, OnClose)
	ON_COMMAND(IDM_MOVE, OnMove)
	ON_WM_NCACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealDlg message handlers

BOOL CRealDlg::OnInitDialog()
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

	m_nKeyUp = FALSE;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	gwl = GetWindowLong(m_hWnd, GWL_STYLE);

	CMenu * pMenu = GetMenu();
	pMenu->ModifyMenu(IDM_IMAGE, MF_BYCOMMAND|MF_OWNERDRAW, IDM_IMAGE);


	m_hBmp = (HBITMAP)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOGO), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	BITMAP bm;
	GetObject(m_hBmp, sizeof(bm), &bm);	

	m_rectLogo.left = 15;
	m_rectLogo.right = 15 + bm.bmWidth;
	m_rectLogo.top = 2 ;
	m_rectLogo.bottom = 2 + bm.bmHeight;

	m_hSys = (HBITMAP)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SYSTEM), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	GetObject(m_hSys, sizeof(bm), &bm);	

	m_rectSys.left = 2;
	m_rectSys.right = 2 + bm.bmWidth;
	m_rectSys.top = 4 ;
	m_rectSys.bottom = 4 + bm.bmHeight;

	GetWindowText(m_strTitle);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRealDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		DrawLogo();

		CDialog::OnSysCommand(nID, lParam);
	}
}

void CRealDlg::OnPaint() 
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
HCURSOR CRealDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRealDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	
	if (lpDrawItemStruct->CtlType == ODT_MENU)
	{
		if (lpDrawItemStruct->itemAction == ODA_DRAWENTIRE)
		{
			CDC* pdc=CDC::FromHandle(lpDrawItemStruct->hDC);
			CRect rect(lpDrawItemStruct->rcItem);

			BITMAP bm;
			GetObject(m_hBmp, sizeof(bm), &bm);

			CDC memdc;
			memdc.CreateCompatibleDC(pdc);
			memdc.SelectObject(m_hBmp);

			pdc->BitBlt(15, 2, bm.bmWidth, bm.bmHeight, &memdc, 0, 0, SRCCOPY);
		}
	}

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CRealDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	if (NULL != m_hBmp)
		DeleteObject(m_hBmp);

	if (NULL != m_hSys)
		DeleteObject(m_hSys);

	
}


void CRealDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{

	CDialog::OnActivate(nState, pWndOther, bMinimized);

	DrawLogo();	
}


void CRealDlg::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{

	CPoint pt;
	pt = point;

	CRect rc;
	GetWindowRect(rc);
	pt.y -= rc.top;
	pt.x -= rc.left;

	union temp
	{
		POINTS pt;
		LONG lValue;
	};

	temp t;
	t.pt.x = (short)point.x;
	t.pt.y = (short)point.y;

	if (m_rectLogo.PtInRect(pt))
	{
		ShellExecute(NULL, "open", "http://www.mfc4u.co.kr", NULL, NULL, SW_SHOWNORMAL);
		return;
	}

	if (m_rectSys.PtInRect(pt))
	{
		CMenu * pSystemMenu = GetSystemMenu(FALSE);
		
		pSystemMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
			point.x + 3, point.y + 3, this);
		return;
	}

	
	if (HTSYSMENU == ::SendMessage(m_hWnd, WM_NCHITTEST, 0, t.lValue))
	{
		return;
	}

	if (HTCLOSE == ::SendMessage(m_hWnd, WM_NCHITTEST, 0, t.lValue))
	{
		m_bClose = TRUE;
		CDialog::OnNcLButtonDown(nHitTest, point);
		return ;
	}

	m_bClose = FALSE;

	CDialog::OnNcLButtonDown(nHitTest, point);
}

void CRealDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if (lpMeasureItemStruct->CtlType == ODT_MENU)
	{
		if (lpMeasureItemStruct->itemID == IDM_IMAGE)
			lpMeasureItemStruct->itemWidth = m_rectLogo.Width() + 5;

	}
	
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void CRealDlg::OnNcPaint() 
{
	Default();
	DrawLogo();

}


void CRealDlg::DrawLogo()
{
	CDC* pdc= GetWindowDC();

	COLORREF clrCaption;
	clrCaption = GetSysColor(COLOR_ACTIVECAPTION);


	CDC memdc;	
	memdc.CreateCompatibleDC(pdc);	
	memdc.SelectObject(m_hBmp);	
	pdc->BitBlt(15, 2, m_rectLogo.Width(), m_rectLogo.Height(), &memdc, 0, 0, SRCCOPY);	

	memdc.SelectObject(m_hSys);	
	pdc->BitBlt(4, 4, m_rectSys.Width(), m_rectSys.Height(), &memdc, 0, 0, SRCCOPY);	

	ReleaseDC(pdc);	

}


BOOL CRealDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	DWORD dwPos = ::GetMessagePos();

	CPoint pt((int) LOWORD (dwPos), (int) HIWORD(dwPos));
	CRect rc;
	GetWindowRect(rc);
	pt.y -= rc.top;
	pt.x -= rc.left;

	if (m_rectLogo.PtInRect(pt))
	{
		SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_LOGO)));
		return TRUE;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}



void CRealDlg::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	union temp
	{
		POINTS pt;
		LONG lValue;
	};

	temp t;
	t.pt.x = (short)point.x;
	t.pt.y = (short)point.y;

	
	if (m_bClose == TRUE  && HTCLOSE == ::SendMessage(m_hWnd, WM_NCHITTEST, 0, t.lValue))
	{
		OnClose();
		return ;
	}

	CDialog::OnNcLButtonUp(nHitTest, point);

	
}

void CRealDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
	union temp
	{
		POINTS pt;
		LONG lValue;
	};

	temp t;
	t.pt.x = (short)point.x;
	t.pt.y = (short)point.y;

	if (HTSYSMENU == ::SendMessage(m_hWnd, WM_NCHITTEST, 0, t.lValue))
		return;
	
	CDialog::OnNcLButtonDblClk(nHitTest, point);
}


int CRealDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}



void CRealDlg::OnInitMenu(CMenu* pMenu) 
{
	CDialog::OnInitMenu(pMenu);
	
	DrawLogo();
}


BOOL CRealDlg::OnNcActivate(BOOL bActive) 
{

	return CDialog::OnNcActivate(bActive);
}
