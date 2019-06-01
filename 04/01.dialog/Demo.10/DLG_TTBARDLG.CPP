#include "stdafx.h"
#include "dlg_ttbar.h"
#include "dlg_ttbarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#define ID_NEW		WM_USER + 100 
#define ID_LIST		WM_USER + 101 
#define ID_CUT		WM_USER + 102 
#define ID_PRINT	WM_USER + 103 
#define ID_EXIT		WM_USER + 104 

CDlg_TTBarDlg::CDlg_TTBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_TTBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_TTBarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_toolbarCtrl = NULL ;
}

CDlg_TTBarDlg::~CDlg_TTBarDlg()
{
	VERIFY(m_toolbarCtrl != NULL );
	delete m_toolbarCtrl;
}

void CDlg_TTBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_TTBarDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_TTBarDlg, CDialog)
	//{{AFX_MSG_MAP(CDlg_TTBarDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_BOTTOM, OnBottom)
	ON_BN_CLICKED(ID_TOP, OnTop)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, NotifyFunction )
END_MESSAGE_MAP()

BOOL CDlg_TTBarDlg::NotifyFunction( UINT id, NMHDR * pTTTStruct, LRESULT * pResult )
{
	pResult = NULL ;	// Not Used 
	id = 0 ;	// Not used 

    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pTTTStruct;    
	UINT nID = pTTTStruct->idFrom;
	switch ( nID)
	{
		case ID_NEW:
			pTTT->lpszText = MAKEINTRESOURCE((LPCSTR)(IDS_NEW));
			break ;
		case ID_LIST:
			pTTT->lpszText = MAKEINTRESOURCE((LPCSTR)(IDS_LIST));
			break ;
		case ID_CUT:
			pTTT->lpszText = MAKEINTRESOURCE((LPCSTR)(IDS_CUT));
			break ;
		case ID_PRINT:
			pTTT->lpszText = MAKEINTRESOURCE((LPCSTR)(IDS_PRINT));
			break ;
		case ID_EXIT:
			pTTT->lpszText = MAKEINTRESOURCE((LPCSTR)(IDS_EXIT));
			break ;
	}
	return(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CDlg_TTBarDlg message handlers

BOOL CDlg_TTBarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	btn[0].iBitmap = 0 ;
	btn[0].idCommand = ID_NEW ;
	btn[0].fsState = TBSTATE_ENABLED  ;
	btn[0].fsStyle = TBSTYLE_BUTTON  ;
	btn[0].dwData = 0 ;
	btn[0].iString = 0;

	btn[1].iBitmap = 1 ;
	btn[1].idCommand = ID_LIST ;
	btn[1].fsState = TBSTATE_ENABLED  ;
	btn[1].fsStyle = TBSTYLE_BUTTON ;
	btn[1].dwData = 0 ;
	btn[1].iString = 1;

	btn[2].iBitmap = 2 ;
	btn[2].idCommand = ID_CUT ;
	btn[2].fsState = TBSTATE_ENABLED  ;
	btn[2].fsStyle = TBSTYLE_BUTTON ;
	btn[2].dwData = 0 ;
	btn[2].iString = 2;

	btn[3].iBitmap = 3 ;
	btn[3].idCommand = ID_PRINT ;
	btn[3].fsState = TBSTATE_ENABLED  ;
	btn[3].fsStyle = TBSTYLE_BUTTON ;
	btn[3].dwData = 0 ;
	btn[3].iString = 3;

	btn[4].iBitmap = 4 ;
	btn[4].idCommand = ID_EXIT ;
	btn[4].fsState = TBSTATE_ENABLED  ;
	btn[4].fsStyle = TBSTYLE_BUTTON ;
	btn[4].dwData = 0 ;
	btn[4].iString = 4;

	EnableToolTips(TRUE);

	SetToolBarPosition(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_TTBarDlg::OnPaint() 
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


BOOL CDlg_TTBarDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch ( wParam )
	{
		case ID_NEW :	MessageBox("New  Button Clicked","Information" , MB_ICONINFORMATION); break ;
		case ID_LIST :	MessageBox("List Button Clicked","Information" , MB_ICONINFORMATION); break ;
		case ID_CUT :	MessageBox("Cut  Button Clicked","Information" , MB_ICONINFORMATION); break ;
		case ID_PRINT : MessageBox("Print Button Clicked","Information" , MB_ICONINFORMATION); break ;
		case ID_EXIT :	MessageBox("Exit Button Clicked" , "Information" , MB_ICONINFORMATION); break ;
		case IDOK : CDialog::OnOK() ; 
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CDlg_TTBarDlg::OnOK() 
{
	CDialog::OnOK();
}

void CDlg_TTBarDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}


void CDlg_TTBarDlg::SetToolBarPosition(int pos)
{
	m_toolbarCtrl = NULL ;
	VERIFY(m_toolbarCtrl == NULL );
	m_toolbarCtrl = new CToolBarCtrl() ;

	CRect wndRect ;
	GetWindowRect(&wndRect);
	CRect rc(0,0,wndRect.right , 50);
	if ( pos == 0 )
		m_toolbarCtrl->Create(TBSTYLE_TOOLTIPS |WS_CHILD | WS_VISIBLE | CCS_TOP | CCS_NODIVIDER, rc ,this , 0 );
	else
		m_toolbarCtrl->Create(TBSTYLE_TOOLTIPS |WS_CHILD | WS_VISIBLE | CCS_BOTTOM  | CCS_NODIVIDER , rc ,this , 0 );

	m_toolbarCtrl->AddButtons(5, btn);
	m_toolbarCtrl->AddBitmap(1, IDR_MAINFRAME);

	CSize sz_btn(30,30);
	m_toolbarCtrl->SetButtonSize(sz_btn);
	
	CSize sz_img(30,30);
	m_toolbarCtrl->SetBitmapSize(sz_img);

	m_toolbarCtrl->AutoSize();
}

void CDlg_TTBarDlg::OnBottom() 
{
	VERIFY(m_toolbarCtrl != NULL );
		delete m_toolbarCtrl ;
	SetToolBarPosition(1);
}

void CDlg_TTBarDlg::OnTop() 
{
	VERIFY(m_toolbarCtrl != NULL );
		delete m_toolbarCtrl ;
	SetToolBarPosition(0);
}
