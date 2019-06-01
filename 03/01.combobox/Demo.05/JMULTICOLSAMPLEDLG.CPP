// JMultiColSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JMultiColSample.h"
#include "JMultiColSampleDlg.h"

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
// CJMultiColSampleDlg dialog

CJMultiColSampleDlg::CJMultiColSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJMultiColSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJMultiColSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJMultiColSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJMultiColSampleDlg)
	DDX_Control(pDX, IDC_COMBO4, m_jcbCheckBox);
	DDX_Control(pDX, IDC_COMBO3, m_jcbShowTitletip);
	DDX_Control(pDX, IDC_COMBO2, m_jcbHideColumn);
	DDX_Control(pDX, IDC_COMBO1, m_jcbSearch);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJMultiColSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CJMultiColSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//ON_CBN_DROPDOWN(IDC_COMBO2, OnDropdownCombo2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJMultiColSampleDlg message handlers

BOOL CJMultiColSampleDlg::OnInitDialog()
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
	



	///////////////////////////////////////////////////////////////
	// TODO: Add extra initialization here
	//////////////////////////////////////////////
	// We start here ......
	OnInitSearchComboBox();
	OnInitShowTitletip();
	OnInitCheckBox();
	OnInitHideColumn();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJMultiColSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJMultiColSampleDlg::OnPaint() 
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
HCURSOR CJMultiColSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CJMultiColSampleDlg::OnInitSearchComboBox()
{
		m_jcbSearch.FormatList(4,DT_LEFT,FALSE,EDGE,0); //number of columns
		// fill up the combo
		CString str;
		for (int row=0;row<5;row++)
		{
			for (int col=0;col<4;col++)
			{
				str.Format("%d-%d",col,row);
				if (col==3)	switch(row)
				{
					case 0:
						str = "Swan";
					break;
					case 1:
						str = "Dog0123456789012345678901234567890123456789";
					break;
					case 2:
						str = "Walla";
					break;
					case 3:
						str = "Wombat";
					break;
					case 4:
						str = "KuKu";
					break;
				}
				m_jcbSearch.AddItem(str,col,row);
			}

		}
		
		//select one for example
		//m_jcbSearch.SelectString("Column:1 ,row:2");
		//set the default text to display
		CWnd::GetDlgItem(IDC_EDIT1)->SetWindowText( "KuKu");
		OnChangeEdit1();
}

void CJMultiColSampleDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString rString;
	CWnd::GetDlgItem(IDC_EDIT1)->GetWindowText( rString );
	m_jcbSearch.SelectString(rString); 
	UpdateData(FALSE);
}

void CJMultiColSampleDlg::OnButton1() 
{
	OnChangeEdit1();
}

void CJMultiColSampleDlg::OnInitHideColumn()
{

	///////////////////////////////////////////////////////
	//HEY, YOU MUST READ THE COMMENT CAREFULLY
	//     TO BE ABLE TO USE ALL MY TRICKY FUNCTIONS.  (-:  :-)
	////// Total column can only have 1 , tCol=1
		//ColDisplay = 0 , is the selected column you want to display
		//m_jcbHideColumn.ResetContent(1,DT_LEFT,FALSE,NORMAL,0);

		// Total column can only have 1 , tCol=1
		//ColDisplay = 1 , is the selected column you want to display
		m_jcbHideColumn.ResetContent(1,DT_LEFT,FALSE,NORMAL,1);

		// Total column can only have 1 , tCol=1
		//ColDisplay = 2 , is the selected column you want to display
		//m_jcbHideColumn.ResetContent(1,DT_LEFT,FALSE,NORMAL,2);

		// Total column can only have 1 , tCol=1
		//ColDisplay = 3 , is the selected column you want to display
		//m_jcbHideColumn.ResetContent(1,DT_LEFT,FALSE,NORMAL,3);




		/////////////////////////////////////////////////////////
		// fill up the combo
		CString str;
		for (int row=0;row<250;row++)
		{
			for (int col=0;col<4;col++) //Although, I have 4 columns....
			{							//***You can have as many column, 
										//but you can only display one at a time
				str.Format("Column:%d ,row:%d",col,row);
				m_jcbHideColumn.AddItem(str,col,row);
			}

		}
		
		// Must call this Function here to terminate the link-list.
		
		//if you want to search for everything
		m_jcbHideColumn.SetCurSel(0);

}

void CJMultiColSampleDlg::OnInitCheckBox()
{
		m_jcbCheckBox.ResetContent(2,DT_LEFT,TRUE,EDGE,0);
		// fill up the combo
		CString str;
		for (int row=0;row<5;row++)
		{
			for (int col=0;col<2;col++)
			{
				str.Format("Column:%d ,row:%d",col,row);
				m_jcbCheckBox.AddItem(str,col,row);
			}

		}
		m_jcbCheckBox.SetCurSel(2);
		
}

void CJMultiColSampleDlg::OnInitShowTitletip()
{
		m_jcbShowTitletip.ResetContent(4,DT_LEFT,FALSE,EDGE,0);
		// fill up the combo
		CString str;
		for (int row=0;row<5;row++)
		{
			for (int col=0;col<4;col++)
			{
				str.Format("Column:%d ,row:%d",col,row);
				m_jcbShowTitletip.AddItem(str,col,row);
			}

		}
		
		// Must call this Function here to terminate the link-list.
		
		//if you want to search for everything
		m_jcbShowTitletip.SetCurSel(0); 

}

/*
void CJMultiColSampleDlg::DisplayPopdownWindow()
{
	//I am trying to do a popup-dropdown window like Aravind Corera. 
	//but, it doesn't work properly in VC++6.0

	//Get the combo's alignment	
	CRect rectCombo;
	m_jcbHideColumn.GetWindowRect(&rectCombo);	//if window is already present delete it
	if(m_pWndPopDown) delete m_pWndPopDown;		///Register class and create window
	LPCTSTR lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW);
	m_pWndPopDown = new CWnd();
	m_pWndPopDown->CreateEx(WS_EX_TOPMOST | WS_EX_TOOLWINDOW|WS_EX_PALETTEWINDOW,
	                        lpszClass, 	                        
							_T(""),
	                        WS_POPUP | WS_VISIBLE,
	                        rectCombo.left,rectCombo.bottom, 
	                        rectCombo.Width(),200,
	                        m_jcbHideColumn.GetSafeHwnd(),
	                        NULL,	                        NULL);
}

void CJMultiColSampleDlg::OnDropdownCombo2() 
{
	// prevent drop down of the combo	
	m_jcbHideColumn.ShowDropDown(FALSE);  
	// Display our own popdown window instead 	
	DisplayPopdownWindow(); 	
}
*/