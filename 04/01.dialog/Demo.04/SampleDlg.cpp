// SampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sample.h"
#include "SampleDlg.h"

#include "PageOneDialog.h"
#include "PageTwoDialog.h"
#include "PageThreeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg dialog

CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: TStackedDialog(IDC_PLACEHOLDER, CSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_bTimerActive  = FALSE;
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	TStackedDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleDlg)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_COMBO, m_Combo);
	DDX_Control(pDX, IDC_PAGE1, m_Page1Btn);
	DDX_Control(pDX, IDC_PAGE2, m_Page2Btn);
	DDX_Control(pDX, IDC_PAGE3, m_Page3Btn);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSampleDlg, TStackedDialog)
	//{{AFX_MSG_MAP(CSampleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_BN_CLICKED(IDC_PAGE1, OnPage1)
	ON_BN_CLICKED(IDC_PAGE2, OnPage2)
	ON_BN_CLICKED(IDC_PAGE3, OnPage3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SCAN, OnScan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg message handlers

BOOL CSampleDlg::OnInitDialog()
{
	TStackedDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
  // TODO: Add extra initialization here

  // Fill list box so that user may select a page
  m_List.AddString("Page 1");
  m_List.AddString("Page 2");
  m_List.AddString("Page 3");

  // Fill combo box for the same purpose as a list box
  // (This is a sample)
  m_Combo.AddString("Page 1");
  m_Combo.AddString("Page 2");
  m_Combo.AddString("Page 3");

  // Add pages to stacked dialog
	AddPage(IDD_PAGE1);
  AddPage(IDD_PAGE2);
  AddPage(IDD_PAGE3);

  // Select active page
  SetPage(IDD_PAGE2);

 	return TRUE;  // return TRUE  unless you set the focus to a control
}

// Must be implemented
// Create a dialog object based on dialog resource id
TStackedPage *CSampleDlg::CreatePage(UINT nId)
{
  switch (nId) {
  case IDD_PAGE1: return new CPageOneDialog; 
  case IDD_PAGE2: return new CPageTwoDialog;
  case IDD_PAGE3: return new CPageThreeDialog;
  }
  return NULL;    // this will assert
}

// Must be implemented but may have an ampty implementation
// Here, I update the controls based on the currently active page
void CSampleDlg::OnPageChanged(UINT nId, BOOL bActivated)
{
  if (bActivated) {
    switch (nId) {
    case IDD_PAGE1:
      m_List.SetCurSel(0);
      m_Combo.SetCurSel(0);
      m_Page1Btn.SetCheck(TRUE);
      break;
    case IDD_PAGE2:
      m_List.SetCurSel(1);
      m_Combo.SetCurSel(1);
      m_Page2Btn.SetCheck(TRUE);
      break;
    case IDD_PAGE3:
      m_List.SetCurSel(2);
      m_Combo.SetCurSel(2);
      m_Page3Btn.SetCheck(TRUE);
      break;
    }
  } else {
    m_Page1Btn.SetCheck(FALSE);
    m_Page2Btn.SetCheck(FALSE);
    m_Page3Btn.SetCheck(FALSE);
  }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSampleDlg::OnPaint() 
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

HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSampleDlg::OnSelchangeCombo() 
{
  // CLick on a combobox
  // Select stacked page
  int nIndex = m_Combo.GetCurSel();
  switch (nIndex) {
  case 0: SetPage(IDD_PAGE1); break;
  case 1: SetPage(IDD_PAGE2); break;
  case 2: SetPage(IDD_PAGE3); break;
  }
}

void CSampleDlg::OnSelchangeList() 
{
  // CLick on a listbox
  // Select stacked page
  int nIndex = m_List.GetCurSel();
  switch (nIndex) {
  case 0: SetPage(IDD_PAGE1); break;
  case 1: SetPage(IDD_PAGE2); break;
  case 2: SetPage(IDD_PAGE3); break;
  }
}

void CSampleDlg::OnPage1() 
{
  SetPage(IDD_PAGE1);	
}

void CSampleDlg::OnPage2() 
{
  SetPage(IDD_PAGE2);	
}

void CSampleDlg::OnPage3() 
{
  SetPage(IDD_PAGE3);	
}

void CSampleDlg::OnTimer(UINT nIDEvent) 
{
  // If timer is active, select the next stacked page and rollover
  // to first one if end is reached
  SetNextPage();
  
	TStackedDialog::OnTimer(nIDEvent);
}

void CSampleDlg::OnScan() 
{
  if (m_bTimerActive) {
    KillTimer(100);
    m_bTimerActive = FALSE;
  } else {
    SetTimer(100,1000,NULL);
    m_bTimerActive = TRUE;
  }
}
