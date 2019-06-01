// dragdroptreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dragdroptree.h"
#include "dragdroptreeDlg.h"

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
// CDragdroptreeDlg dialog

CDragdroptreeDlg::CDragdroptreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDragdroptreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDragdroptreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDragdroptreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDragdroptreeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDragdroptreeDlg, CDialog)
	//{{AFX_MSG_MAP(CDragdroptreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragdroptreeDlg message handlers

BOOL CDragdroptreeDlg::OnInitDialog()
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
	RECT rect = {10,10,210,300};
	m_treeCtrl1.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_HASLINES|TVS_LINESATROOT
								|TVS_HASBUTTONS|TVS_TRACKSELECT|TVS_SHOWSELALWAYS , 
								rect,this, 1001);
	

	if(!m_cImageList.Create(16,16, 0, 1, 0)) 
	{
		AfxMessageBox("Problem in creating ImageList Ctrl");
	}
	else 
	{
		CBitmap bmpImage;
		for ( UINT nBitmapId =  IDB_BITMAP1; nBitmapId<= IDB_BITMAP2; nBitmapId++) 
        {
			bmpImage.LoadBitmap(nBitmapId);
			m_cImageList.Add(&bmpImage, (COLORREF)NULL);
			bmpImage.DeleteObject();
		}	
		
		 
	}	
	m_treeCtrl1.SetImageList(&m_cImageList, TVSIL_NORMAL);	
	rect.left = rect.right + 50;
	rect.right = rect.left + 200;

	m_treeCtrl2.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_HASLINES|TVS_LINESATROOT
								|TVS_HASBUTTONS|TVS_TRACKSELECT|TVS_SHOWSELALWAYS , 
								rect,this, 1002);
	PopulateTree(m_treeCtrl1);
	rect.left = rect.right + 50;
	rect.right = rect.left + 200;

	m_treeCtrl3.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_HASLINES|TVS_LINESATROOT
								|TVS_HASBUTTONS|TVS_TRACKSELECT|TVS_SHOWSELALWAYS , 
								rect,this, 1003);
	
	
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDragdroptreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDragdroptreeDlg::OnPaint() 
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
HCURSOR CDragdroptreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDragdroptreeDlg::PopulateTree(CDragDropTreeCtrl &treeCtrl)
{
    HTREEITEM hTItem = treeCtrl.AddItem(TVI_ROOT, "Root", NULL, 0,0,0); 
    HTREEITEM hTItem1 = treeCtrl.AddItem(hTItem, "Child1", TVI_LAST, 0,0,0);
    HTREEITEM hTItem2 = treeCtrl.AddItem(hTItem, "Child2", TVI_LAST, 0,0,0);
    HTREEITEM hTItem3 = treeCtrl.AddItem(hTItem, "Child3", TVI_LAST, 0,0,0);
    HTREEITEM hTItem4 = treeCtrl.AddItem(hTItem, "Child4", TVI_LAST, 0,0,0);
    hTItem = treeCtrl.AddItem(hTItem1, "Child11", TVI_LAST, 0,0,0);
    hTItem = treeCtrl.AddItem(hTItem, "Child3", TVI_LAST, 0,0,0);
    hTItem = treeCtrl.AddItem(hTItem, "Child4", TVI_LAST, 0,0,0);
    hTItem = treeCtrl.AddItem(hTItem, "Child5", TVI_LAST, 0,0,0);
    hTItem = treeCtrl.AddItem(hTItem, "Child6", TVI_LAST, 0,0,0);
    hTItem = treeCtrl.AddItem(hTItem, "Child7", TVI_LAST, 0,0,0);
    HTREEITEM hTItem8 = treeCtrl.AddItem(hTItem, "Child8", TVI_LAST, 0,0,0);
    treeCtrl.AddItem(hTItem8, "Child81", TVI_LAST, 0,0,0);
    treeCtrl.AddItem(hTItem8, "Child82", TVI_LAST, 0,0,0);
    treeCtrl.AddItem(hTItem1, "Child12", TVI_LAST, 0,0,0);
    treeCtrl.AddItem(hTItem2, "Child21", TVI_LAST, 0,0,0);
    treeCtrl.AddItem(hTItem2, "Child22", TVI_LAST, 0,0,0);
    treeCtrl.AddItem(hTItem3, "Child31", TVI_LAST, 0,0,0);
    treeCtrl.AddItem(hTItem3, "Child32", TVI_LAST, 0,0,0);
    treeCtrl.AddItem(hTItem4, "Child41", TVI_LAST, 0,1,0);
    treeCtrl.AddItem(hTItem4, "Child42", TVI_LAST, 0,1,0);   
}