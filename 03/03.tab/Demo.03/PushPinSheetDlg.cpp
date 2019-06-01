#include "stdafx.h"
#include "MyPropertySheet.h"
#include "PushPinSheet.h"
#include "PushPinSheetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPushPinSheetDlg::CPushPinSheetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPushPinSheetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPushPinSheetDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_pPropFrame = NULL;
}

void CPushPinSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPushPinSheetDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPushPinSheetDlg, CDialog)
	//{{AFX_MSG_MAP(CPushPinSheetDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPushPinSheetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPushPinSheetDlg::OnPaint() 
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

HCURSOR CPushPinSheetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPushPinSheetDlg::OnProperties()
{
	if (m_pPropFrame == NULL)
	{
		m_pPropFrame = new CPushPinFrame;
    ASSERT(m_pPropFrame);
    m_pPropFrame->SetAttachedPropertySheet(RUNTIME_CLASS(CMyPropertySheet));

		CRect rect(0, 0, 0, 0);
		CString strTitle;
		VERIFY(strTitle.LoadString(IDS_PROPSHT_CAPTION));
		if (!m_pPropFrame->Create(NULL, strTitle,	WS_POPUP | WS_CAPTION | WS_SYSMENU, rect, this))
		{
      TRACE("Failed to create the push pin frame\n");
			delete m_pPropFrame;
			m_pPropFrame = NULL;
			return;
		}
		m_pPropFrame->CenterWindow();
	}

	// Before unhiding the modeless property sheet, update its
	// settings appropriately.  For example, if you are reflecting
	// the state of the currently selected item, pick up that
	// information from the active view and change the property
	// sheet settings now.

	if (m_pPropFrame != NULL && !m_pPropFrame->IsWindowVisible())
		m_pPropFrame->ShowWindow(SW_SHOW);
}

void CPushPinSheetDlg::OnButton1() 
{
  OnProperties();
}
