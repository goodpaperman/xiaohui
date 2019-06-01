// ClrWellDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClrWellDemo.h"
#include "ClrWellDemoDlg.h"

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
// CClrWellDemoDlg dialog

CClrWellDemoDlg::CClrWellDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClrWellDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClrWellDemoDlg)
	m_Aqua = FALSE;
	m_Black = FALSE;
	m_Blue = FALSE;
	m_Fuschia = FALSE;
	m_Gray = FALSE;
	m_Green = FALSE;
	m_Lime = FALSE;
	m_Maroon = FALSE;
	m_Navy = FALSE;
	m_Olive = FALSE;
	m_Purple = FALSE;
	m_Red = FALSE;
	m_Silver = FALSE;
	m_Teal = FALSE;
	m_White = FALSE;
	m_Yellow = FALSE;
	m_IsotropicWells = FALSE;
	m_OuterBorder = 0;
	m_InnerBorder = 0;
	m_NumCols = 0;
	m_WellHeight = 0;
	m_Shape = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClrWellDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClrWellDemoDlg)
	DDX_Control(pDX, IDC_OUTERBORDER_SPIN, m_OuterBorderSpin);
	DDX_Control(pDX, IDC_NUMCOLS_SPIN, m_NumColsSpin);
	DDX_Control(pDX, IDC_INNERBORDER_SPIN, m_InnerBorderSpin);
	DDX_Control(pDX, IDC_UPDATE, m_Update);
	DDX_Control(pDX, IDC_WELLHEIGHT_SPIN, m_WellHeightSpin);
	DDX_Control(pDX, IDC_WELLHEIGHT_EDIT, m_WellHeightEdit);
	DDX_Control(pDX, IDC_WIDTHSLIDER, m_SliderControl);
	DDX_Check(pDX, IDC_AQUA, m_Aqua);
	DDX_Check(pDX, IDC_BLACK, m_Black);
	DDX_Check(pDX, IDC_BLUE, m_Blue);
	DDX_Check(pDX, IDC_FUSCHIA, m_Fuschia);
	DDX_Check(pDX, IDC_GRAY, m_Gray);
	DDX_Check(pDX, IDC_GREEN, m_Green);
	DDX_Check(pDX, IDC_LIME, m_Lime);
	DDX_Check(pDX, IDC_MAROON, m_Maroon);
	DDX_Check(pDX, IDC_NAVY, m_Navy);
	DDX_Check(pDX, IDC_OLIVE, m_Olive);
	DDX_Check(pDX, IDC_PURPLE, m_Purple);
	DDX_Check(pDX, IDC_RED, m_Red);
	DDX_Check(pDX, IDC_SILVER, m_Silver);
	DDX_Check(pDX, IDC_TEAL, m_Teal);
	DDX_Check(pDX, IDC_WHITE, m_White);
	DDX_Check(pDX, IDC_YELLOW, m_Yellow);
	DDX_Check(pDX, IDC_ISOTROPICWELLS, m_IsotropicWells);
	DDX_Text(pDX, IDC_OUTERBORDER_EDIT, m_OuterBorder);
	DDX_Text(pDX, IDC_INNERBORDER_EDIT, m_InnerBorder);
	DDX_Text(pDX, IDC_NUMCOLS_EDIT, m_NumCols);
	DDX_Text(pDX, IDC_WELLHEIGHT_EDIT, m_WellHeight);
	DDX_Radio(pDX, IDC_SHAPE, m_Shape);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClrWellDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CClrWellDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ISOTROPICWELLS, OnIsotropicwells)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClrWellDemoDlg message handlers

BOOL CClrWellDemoDlg::OnInitDialog()
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
	
	m_ColorButton.SubclassDlgItem(IDC_COLORBTN, this);

   m_SliderControl.SetRange(10,200);
   m_SliderControl.SetTicFreq(10);
   m_SliderControl.SetPos(100);

   m_InnerBorderSpin.SetRange(0,5);
   m_InnerBorderSpin.SetPos(0);
   m_OuterBorderSpin.SetRange(0,10);
   m_OuterBorderSpin.SetPos(0);
   m_WellHeightSpin.SetRange(5,50);
   m_WellHeightSpin.SetPos(10);
   m_NumColsSpin.SetRange(1,40);
   m_NumColsSpin.SetPos(4);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClrWellDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClrWellDemoDlg::OnPaint() 
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
HCURSOR CClrWellDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClrWellDemoDlg::OnIsotropicwells() 
{
   UpdateData();

   if(m_IsotropicWells)
      {
      m_WellHeightEdit.EnableWindow(FALSE);
      m_WellHeightSpin.EnableWindow(FALSE);
      }
   else
      {
      m_WellHeightEdit.EnableWindow(TRUE);
      m_WellHeightSpin.EnableWindow(TRUE);
      }
}

void CClrWellDemoDlg::OnUpdate() 
{
	// update all values to the color button
   UpdateData();

   // Colors first
   CArray<COLORREF, COLORREF&>* colors;
   colors = new CArray<COLORREF, COLORREF&>;
   COLORREF local_color;

   if(m_Black)
      {
      local_color = RGB(0,0,0);
      colors->Add(local_color);
      }
   if(m_Blue)
      {
      local_color = RGB(0,0,255);
      colors->Add(local_color);
      }
   if(m_Green)
      {
      local_color = RGB(0,56,0);
      colors->Add(local_color);
      }
   if(m_Aqua)
      {
      local_color = RGB(0,255,255);
      colors->Add(local_color);
      }
   if(m_Red) 
      {
      local_color = RGB(255,0,0);
      colors->Add(local_color);
      }
   if(m_Purple) 
      {
      local_color = RGB(56,0,56);
      colors->Add(local_color);
      }
   if(m_Silver) 
      {
      local_color = RGB(137,137,137);
      colors->Add(local_color);
      }
   if(m_White) 
      {
      local_color = RGB(255,255,255);
      colors->Add(local_color);
      }
   if(m_Gray) 
      {
      local_color = RGB(56,56,56);
      colors->Add(local_color);
      }
   if(m_Maroon) 
      {
      local_color = RGB(56,0,0);
      colors->Add(local_color);
      }
   if(m_Fuschia) 
      {
      local_color = RGB(255,0,255);
      colors->Add(local_color);
      }
   if(m_Teal) 
      {
      local_color = RGB(0,56,56);
      colors->Add(local_color);
      }
   if(m_Olive) 
      {
      local_color = RGB(56,56,0);
      colors->Add(local_color);
      }
   if(m_Navy) 
      {
      local_color = RGB(0,0,56);
      colors->Add(local_color);
      }
   if(m_Yellow) 
      {
      local_color = RGB(255,255,0);
      colors->Add(local_color);
      }
   if(m_Lime) 
      {
      local_color = RGB(0,255,0);
      colors->Add(local_color);
      }
	
   m_ColorButton.SetColorsFromArray(colors);
   
   delete colors;

   // Borders
   m_ColorButton.SetBorderThickness(m_OuterBorder,m_InnerBorder);

   // Shape
   m_ColorButton.MakeColorWellsIsotropic(m_IsotropicWells);
   m_ColorButton.SetColorWellHeight(m_WellHeight);
   switch(m_Shape)
      {
      case 0:
          m_ColorButton.SetColorWellShape(CColorBtn::RECTANGLE);
         break;
      case 1:
          m_ColorButton.SetColorWellShape(CColorBtn::ELLIPSE);
         break;
      default:
         ASSERT(FALSE);
         break;
      }

   // number of columns
   m_ColorButton.SetNumColorWellColumns(m_NumCols);

   //width
   short width = m_SliderControl.GetPos();
   CRect temprect;
   m_ColorButton.GetWindowRect(&temprect);
   width = (short)((float)width*(float)temprect.Width()/100);
   m_ColorButton.SetDialogWidth(width); 
      
      

}


