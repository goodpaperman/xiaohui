// PropListBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PropListBox.h"
#include "PropListBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropListBoxDlg dialog

CPropListBoxDlg::CPropListBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropListBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropListBoxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPropListBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropListBoxDlg)
	DDX_Control(pDX, IDC_PROPLIST, m_propList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPropListBoxDlg, CDialog)
	//{{AFX_MSG_MAP(CPropListBoxDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropListBoxDlg message handlers

BOOL CPropListBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
		
	//Add properties to the property list box

	propItem1 = new CPropertyItem("ToolTip Text","",PIT_EDIT,"");
	m_propList.AddPropItem(propItem1);

	propItem2 = new CPropertyItem("Enabled","true",PIT_COMBO,"true|false|");
	m_propList.AddPropItem(propItem2);

	propItem3 = new CPropertyItem("Visible","true",PIT_COMBO,"true|false|");
	m_propList.AddPropItem(propItem3);

	propItem4 = new CPropertyItem("Fore. Color","",PIT_COLOR,"");
	m_propList.AddPropItem(propItem4);
	
	propItem5 = new CPropertyItem("Back. Color","",PIT_COLOR,"");
	m_propList.AddPropItem(propItem5);
	
	propItem6 = new CPropertyItem("Opaque","false",PIT_COMBO,"true|false|");
	m_propList.AddPropItem(propItem6);
	
	propItem7 = new CPropertyItem("Auto. Scroll","true",PIT_COMBO,"true|false|");
	m_propList.AddPropItem(propItem7);
	
	propItem8 = new CPropertyItem("Double Buffered","true",PIT_COMBO,"true|false|");
	m_propList.AddPropItem(propItem8);
	
	propItem9 = new CPropertyItem("Font","",PIT_FONT,"");
	m_propList.AddPropItem(propItem9);

	propItem10 = new CPropertyItem("Text","",PIT_EDIT,"");
	m_propList.AddPropItem(propItem10);

	propItem11 = new CPropertyItem("Horiz. Align","CENTER",PIT_COMBO,"CENTER|LEFT|RIGHT|");
	m_propList.AddPropItem(propItem11);
	
	propItem12 = new CPropertyItem("Vert. Align","CENTER",PIT_COMBO,"CENTER|TOP|BOTTOM|");
	m_propList.AddPropItem(propItem12);

	propItem13 = new CPropertyItem("Icon","",PIT_FILE,"");
	m_propList.AddPropItem(propItem13);

	propItem14 = new CPropertyItem("Border Painted","",PIT_COMBO,"true|false|");
	m_propList.AddPropItem(propItem14);

	propItem15 = new CPropertyItem("Fill Content Area","",PIT_COMBO,"true|false|");
	m_propList.AddPropItem(propItem15);

	propItem16 = new CPropertyItem("Focus Painted","",PIT_COMBO,"true|false|");
	m_propList.AddPropItem(propItem16);

	propItem17 = new CPropertyItem("Horiz. Text Pos.","RIGHT",PIT_COMBO,"RIGHT|LEFT|CENTER|LEADING|TRAILING|");
	m_propList.AddPropItem(propItem17);

    m_propList.AddItem("ni hao ma?"); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPropListBoxDlg::OnPaint() 
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
HCURSOR CPropListBoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

CPropListBoxDlg::~CPropListBoxDlg()
{
	delete propItem1;
	delete propItem2;
	delete propItem3;
	delete propItem4;
	delete propItem5;
	delete propItem6;
	delete propItem7;
	delete propItem8;
	delete propItem9;
	delete propItem10;
	delete propItem11;
	delete propItem12;
	delete propItem13;
	delete propItem14;
	delete propItem15;
	delete propItem16;
	delete propItem17;
}
