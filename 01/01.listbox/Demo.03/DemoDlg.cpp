// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"

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
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pCheckList = NULL; 
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
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
	CreateCheckControl(); 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoDlg::OnPaint() 
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
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoDlg::CreateCheckControl()
{
    // Create the Control
    CRect rect; 
    CWnd* pWnd = GetDlgItem(IDC_STATIC1);
    pWnd->GetWindowRect(&rect); 
    ScreenToClient(&rect); 
    pWnd->DestroyWindow(); 
    
    m_font.CreateFont( 20, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS, 
                                 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,
                                 "Arial");
    LISTITEM* pParentItem = NULL;
    m_pCheckList = new CCheckList();
    if( !m_pCheckList->Create( rect, //CRect(50,50,300,300), 
        this, 10001,
        IDB_CHECK, IDB_UNCHECK, IDB_MIDDLECHECK, 
        RGB(224, 252, 224), &m_font))
    {
        return;
    }
    
    // Add some items
    
    for(int i=0; i<3; i++)
    {
        // Root Item
        pParentItem = m_pCheckList->AddString("Exotics(this is a very very very very very very very long text)", NULL, INDETERMINATE);
        m_pCheckList->SetItemData(0, 1); 
        
        // Sub Item
        m_pCheckList->AddString("Lamborghini", pParentItem, CHECKED);
        m_pCheckList->SetItemData(1, 11); 
        
        // Sub Item
        m_pCheckList->AddString("Corvette", pParentItem );
        m_pCheckList->SetItemData(2, 12); 
        
        // Sub Item
        m_pCheckList->AddString("Vector", pParentItem );
        m_pCheckList->SetItemData(3, 13); 
        
        // Sub Item
        m_pCheckList->AddString("Hummer", pParentItem );
        m_pCheckList->SetItemData(4, 14); 
        
        //  Sub-Sub Item
        pParentItem = m_pCheckList->AddString("Porsche", pParentItem );
        m_pCheckList->SetItemData(5, 15); 
        
        //  Sub-Sub Item
        m_pCheckList->AddString("Boxster", pParentItem );
        m_pCheckList->SetItemData(6, 21); 
        
        //  Sub-Sub Item
        m_pCheckList->AddString("928 S4", pParentItem);
        m_pCheckList->SetItemData(7, 22); 
        
        //  Sub-Sub Item
        m_pCheckList->AddString("959", pParentItem );
        m_pCheckList->SetItemData(8, 23); 
        
        // Root Item
        m_pCheckList->AddString("Luxury");
        m_pCheckList->SetItemData(9, 2); 
        
        // Root Item
        m_pCheckList->AddString("Trucks");
        m_pCheckList->SetItemData(10, 3); 
        
        // Root Item
        m_pCheckList->AddString("Sport Utility Vehicles");
        m_pCheckList->SetItemData(11, 4); 
        
        // Root Item
        m_pCheckList->AddString("Classics");
        m_pCheckList->SetItemData(12, 5); 
    }

    //m_pCheckList->DeleteString(0); 
    //m_pCheckList->DeleteString(1); 
    TRACE("There are a total of %d items\n", m_pCheckList->GetCount(/*pParentItem*/)); 
    m_pCheckList->SetTopIndex(3); 
    TRACE("The top index is %d\n", m_pCheckList->GetTopIndex()); 
    TRACE("The item data for %d is %d\n", 6, m_pCheckList->GetItemData(6)); 

    LISTITEM* pItem = m_pCheckList->GetItem(4); 
    TRACE("The item text, data, width for %d is %s, %d, %d\n", 4, pItem->csText, pItem->dwID, pItem->nTotalWidth); 

    pItem = m_pCheckList->GetItem((DWORD)22); 
    TRACE("The item text, level, width for data %d is %s, %d, %d\n", 22, pItem->csText, pItem->nLevel, pItem->nTotalWidth); 

    CString str; 
    m_pCheckList->GetText(10, &str); 
    TRACE("The item text, text len for %d is %s, %d\n", 10, str, m_pCheckList->GetTextLen(10)); 
    
    m_pCheckList->SetCurSel(8); 
    TRACE("Current selected item is %d\n", m_pCheckList->GetCurSel()); 

    //m_pCheckList->ResetContent(); 
    m_pCheckList->SetCheck(0, CHECKED); 
    m_pCheckList->SetCheck(2, INDETERMINATE); 
    m_pCheckList->SetCheck(5, CHECKED);


    //// Function uses
    //// Get Total Count
    //CString csMessage;
    //csMessage.Format("There are a total of %d items",
    //    m_pCheckList->GetCount() );
    
    //AfxMessageBox(csMessage);
    
    //// Get and Set the top index
    //csMessage.Format("The top index is: %d",
    //    m_pCheckList->GetTopIndex() );
    
    //AfxMessageBox(csMessage);
    //m_pCheckList->SetTopIndex(6);
    
    //// Different ways to get an item
    //LISTITEM* pItem =
    //    m_pCheckList->GetItem(
    //    m_pCheckList->GetTopIndex());
    
    //AfxMessageBox(pItem->csText);
    //pItem = m_pCheckList->GetItem((DWORD)5000);
    //if(pItem)
    //    AfxMessageBox(pItem->csText);
    
    //// Get and Set the Item data
    //DWORD dwID =
    //    m_pCheckList->GetItemData(
    //    m_pCheckList->GetTopIndex());
    
    //csMessage.Format("The Data for this item is: %ld", dwID );
    //AfxMessageBox(csMessage);
    //m_pCheckList->SetItemData(6, 2000);
    
    //// Get the text and text length
    //CString csText;
    //m_pCheckList->GetText( 6, &csText );
    //int nTemp = m_pCheckList->GetTextLen( 7 );
    
    //// Get and set the current selection
    //m_pCheckList->SetCurSel(6);
    //nTemp = m_pCheckList->GetCurSel();
    
    //// Get and Set Checks
    //m_pCheckList->SetCheck(6, CHECKED);
    //nTemp = m_pCheckList->GetCheck(6);
    
    //// Remove one item and all its subitems (if it has them)
    //m_pCheckList->DeleteString(6);
    
    //// Delete eveything
    //m_pCheckList->ResetContent();
    
}
