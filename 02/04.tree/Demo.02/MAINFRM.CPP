// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TPS_Demo.h"

#include "MainFrm.h"

#include "TreePropertySheet.h"
#include "GeneralPrefsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_SPECIALCAPTION, OnViewSpecialCaption)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SPECIALCAPTION, OnUpdateViewSpecialCaption)
	ON_COMMAND(ID_VIEW_NETSCAPESHEET, OnViewNetscapeSheet)
	ON_COMMAND(ID_VIEW_SIMPLESHEET, OnViewSimpleSheet)
	ON_COMMAND(ID_VIEW_FANCYSHEET, OnViewFancySheet)
	ON_COMMAND(ID_VIEW_USERSHEET, OnViewUsersSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
	m_bSpecialCaption=FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnViewSpecialCaption() 
{
	// TODO: Add your command handler code here
	
	m_bSpecialCaption=(m_bSpecialCaption)?FALSE:TRUE;
}

void CMainFrame::OnUpdateViewSpecialCaption(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck(m_bSpecialCaption);
}

void CMainFrame::OnViewNetscapeSheet() 
{
	// TODO: Add your command handler code here
	CTreePropertySheet tps(200, this);
	CDialog	*pGeneralDlg=new CGeneralPrefsDlg();

	tps.AddPage("General info",tps_item_branch,IDD_GENERAL,"Information about yourself",pGeneralDlg);
	tps.AddPage("Animals",tps_item_node,IDD_ANIMALS,"Information about animals");
	tps.AddPage("Cars",tps_item_endbranch,IDD_CARS,"Information about cars");
	tps.AddPage("About TPSDemo",tps_item_node,IDD_ABOUTBOX_CHILD,"About box ...");
	tps.SetLikeNetscape(m_bSpecialCaption);

    HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SEX), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); 
    tps.SetBackgroundBitmap(hbmp); 
	tps.DoModal();
}

void CMainFrame::OnViewSimpleSheet() 
{
	// TODO: Add your command handler code here
	CTreePropertySheet tps;
	CDialog	*pGeneralDlg=new CGeneralPrefsDlg();

	tps.AddPage("General info",tps_item_branch,IDD_GENERAL,"Information about yourself",pGeneralDlg);
	tps.AddPage("Animals",tps_item_node,IDD_ANIMALS,"Information about animals");
	tps.AddPage("Cars",tps_item_endbranch,IDD_CARS,"Information about cars");
	tps.AddPage("About TPSDemo",tps_item_node,IDD_ABOUTBOX_CHILD,"About box ...");
	tps.SetSimple(m_bSpecialCaption);
	tps.DoModal();
}

void CMainFrame::OnViewFancySheet() 
{
	// TODO: Add your command handler code here
	CTreePropertySheet tps;
	CDialog	*pGeneralDlg=new CGeneralPrefsDlg();

	tps.AddPage("General info",tps_item_branch,IDD_GENERAL,"Information about yourself",pGeneralDlg);
	tps.AddPage("Animals",tps_item_node,IDD_ANIMALS,"Information about animals");
	tps.AddPage("Cars",tps_item_endbranch,IDD_CARS,"Information about cars");
	tps.AddPage("About TPSDemo",tps_item_node,IDD_ABOUTBOX_CHILD,"About box ...");
	tps.SetFancy(m_bSpecialCaption);
	tps.DoModal();
}

void CMainFrame::OnViewUsersSheet() 
{
	// TODO: Add your command handler code here
	CTreePropertySheet tps;
	CDialog	*pGeneralDlg=new CGeneralPrefsDlg();

	tps.AddPage("General info",tps_item_branch,IDD_GENERAL,"Information about yourself",pGeneralDlg);
	tps.AddPage("Animals",tps_item_node,IDD_ANIMALS,"Information about animals");
	tps.AddPage("Cars",tps_item_endbranch,IDD_CARS,"Information about cars");
	tps.AddPage("About TPSDemo",tps_item_node,IDD_ABOUTBOX_CHILD,"About box ...");

	CStatic *info=new CStatic();
	CButton	*okBtn=new CButton();
	CButton *cancelBtn=new CButton();
	CButton *helpBtn=new CButton();

	info->Create("<User defined caption>",WS_CHILD,CRect(0,0,200,16),GetDesktopWindow());
	okBtn->Create("OK",WS_CHILD|WS_TABSTOP,CRect(0,0,100,28),GetDesktopWindow(),IDOK);
	cancelBtn->Create("Cancel",WS_CHILD|WS_TABSTOP,CRect(0,0,100,28),GetDesktopWindow(),IDCANCEL);
	helpBtn->Create("Help",WS_CHILD|WS_TABSTOP,CRect(0,0,100,28),GetDesktopWindow(),IDHELP);

	CFont *tempF=tps.GetFont("MS Sans Serif",18);
	info->SetFont(tempF);
	okBtn->SetFont(tempF);
	cancelBtn->SetFont(tempF);
	helpBtn->SetFont(tempF);

	tps.m_clrCaptionLeft	=RGB(0,0,255);
	tps.m_clrCaptionRight	=RGB(192,192,192);
	tps.m_clrCaptionTextLeft=RGB(255,255,255);
	tps.m_clrCaptionTextRight=RGB(0,0,0);

	tps.m_nCaptionBorder	=tps_capborder_none;
	tps.m_bSpecialCaption	=m_bSpecialCaption;

	tps.InsertExtraSpace(tps_below,0,0);
	tps.InsertExtraControl(tps_below,0,okBtn,0,1,116,8,tps_horz_center|tps_vert_center,TRUE);
	tps.InsertExtraControl(tps_below,1,cancelBtn,0,2,116,8,tps_horz_center|tps_vert_center,TRUE);
	tps.InsertExtraControl(tps_below,2,helpBtn,0,3,108,16,tps_horz_right|tps_vert_center,TRUE);
	tps.InsertExtraSpace(tps_below,0,4,16);

	tps.InsertExtraControl(tps_above,3,info,0,0,216,16,tps_horz_right|tps_vert_center,TRUE);
	tps.SetExtraRowSpace(tps_above,0,8,0);
	tps.SetExtraRowSpace(tps_below,0,0,16);
	tps.DoModal();
}
