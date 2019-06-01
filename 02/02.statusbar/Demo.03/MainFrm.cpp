// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include <afxcview.h>

#include "StatusBar.h"
#include "StatusBarDoc.h"
#include "StatusBarView.h"

#include "StatusControl.h"
#include "StatusStatic.h"
#include "StatusProgress.h"
#include "StatusEdit.h"
#include "StatusCombo.h"
#include "MainFrm.h"

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
	ON_EN_CHANGE(ID_INDICATOR_EDIT, OnChangeEdit)
	ON_CBN_SELCHANGE(ID_INDICATOR_COMBO, OnSelchangeCombo)
	ON_COMMAND(ID_STATUS_COMBO, OnStatusCombo)
	ON_COMMAND(ID_STATUS_EDIT, OnStatusEdit)
	ON_COMMAND(ID_STATUS_ICON, OnStatusIcon)
	ON_COMMAND(ID_STATUS_PROGRESS, OnStatusProgress)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_EDIT,
	ID_INDICATOR_PROGRESS,
	ID_INDICATOR_COMBO,
	ID_INDICATOR_ICON,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	// ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
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

void CMainFrame::OnStatusCombo() 
{
 if(c_StatusCombo.m_hWnd == NULL)
    { /* create it */
     c_StatusCombo.Create(&m_wndStatusBar, ID_INDICATOR_COMBO,
			 WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST);
			 
     logEvent(IDS_CREATE_COMBO);
     for(int i = IDS_FIRST_VALUE; i <= IDS_LAST_VALUE; i++)
	{ /* load it */
	 CString s;
	 s.LoadString(i);
	 c_StatusCombo.AddString(s);
	} /* load it */

     c_StatusCombo.maxlen = 30; 
    } /* create it */
 else
    { /* destroy it */
     c_StatusCombo.DestroyWindow();
     logEvent(IDS_DESTROY_COMBO);
    } /* destroy it */
}

void CMainFrame::OnStatusEdit() 
{
 if(c_StatusEdit.m_hWnd == NULL)
    { /* create it */
     c_StatusEdit.Create(&m_wndStatusBar, ID_INDICATOR_EDIT, WS_VISIBLE | WS_BORDER);
     logEvent(IDS_CREATE_EDIT);
    } /* create it */
 else
    { /* destroy it */
     c_StatusEdit.DestroyWindow();
     logEvent(IDS_DESTROY_EDIT);
    } /* destroy it */
}

void CMainFrame::OnStatusIcon() 
{
 static int icons[] = {IDI_SMILE1, IDI_SMILE2, IDI_SMILE3};
 if(c_StatusIcon.m_hWnd == NULL)
    { /* create it */
     c_StatusIcon.Create(&m_wndStatusBar, ID_INDICATOR_ICON, WS_VISIBLE | SS_ICON | SS_CENTERIMAGE);
     HICON icon = (HICON)::LoadImage(AfxGetInstanceHandle(),
				     MAKEINTRESOURCE(icons[0]),
				     IMAGE_ICON, 16, 16, LR_SHARED);
     c_StatusIcon.SetIcon(icon);
     logEvent(IDS_CREATE_STATIC);
     iconstate = 0;
     CString s;
     s.Format(_T("%d"), icons[iconstate]);
     logEvent(IDS_SM_SETICON, s);
    } /* create it */
 else
    { /* destroy it */
     iconstate++;
     if(iconstate > 2)
	{ /* destroy it */
	 c_StatusIcon.DestroyWindow();
	 logEvent(IDS_DESTROY_STATIC);
	} /* destroy it */
     else
	{ /* load other icon */
	 CString s;
	 HICON icon = (HICON)::LoadImage(AfxGetInstanceHandle(),
					 MAKEINTRESOURCE(icons[iconstate]),
					 IMAGE_ICON, 16, 16, LR_SHARED);
	 c_StatusIcon.SetIcon(icon);
	 s.Format(_T("%d"), icons[iconstate]);
	 logEvent(IDS_SM_SETICON, s);
	} /* load other icon */
    } /* destroy it */
}

void CMainFrame::OnStatusProgress() 
{
 if(c_StatusProgress.m_hWnd == NULL)
    { /* create */
     c_StatusProgress.Create(&m_wndStatusBar, ID_INDICATOR_PROGRESS, WS_VISIBLE | PBS_SMOOTH);
     c_StatusProgress.SetRange(0, 5);
     c_StatusProgress.SetPos(1);
     logEvent(IDS_CREATE_PROGRESS);
     logEvent(IDS_PBM_SETPOS, _T("1"));
     progress = 1;
    } /* create */
 else
    { /* advance */
     progress++;
     if(progress > 5)
	{ /* destroy it */
	 c_StatusProgress.DestroyWindow();
	 logEvent(IDS_DESTROY_PROGRESS);
	} /* destroy it */
     else
	{ /* step it */
	 c_StatusProgress.SetPos(progress);
	 CString s;
	 s.Format(_T("%d"), progress);
	 logEvent(IDS_PBM_SETPOS, s);
	} /* step it */
    } /* advance */
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
    
    c_StatusProgress.Reposition();
    c_StatusEdit.Reposition();
    c_StatusIcon.Reposition();
    c_StatusCombo.Reposition();
	
}

/****************************************************************************
*                        CMainFrame::OnSelchangeCombo
* Result: void
*       
* Effect: 
*       Handles selection change for combo box
****************************************************************************/

void CMainFrame::OnSelchangeCombo()
    {
     int n = c_StatusCombo.GetCurSel();
     if(n == CB_ERR)
	return;
     CString s;
     c_StatusCombo.GetLBText(n, s);
     logEvent(IDS_CBN_SELCHANGE, s);
    } // CMainFrame::OnSelchangeCombo

/****************************************************************************
*                          CMainFrame::OnChangeEdit
* Result: void
*       
* Effect: 
*       Handles a change in the edit control
****************************************************************************/

void CMainFrame::OnChangeEdit()
    {
     CString s;
     c_StatusEdit.GetWindowText(s);
     logEvent(IDS_EN_CHANGE, s);
    } // CMainFrame::OnChangeEdit

/****************************************************************************
*                            CMainFrame::logEvent
* Inputs:
*       UINT id: ID to log
*	CString s: Text to log with it
* Result: void
*       
* Effect: 
*       Logs the event
****************************************************************************/

void CMainFrame::logEvent(UINT id, CString s)
    {
     CStatusBarView * view = (CStatusBarView *)GetActiveView();
     if(view == NULL)
	return;
     view->AddString(id, s);     
    } // CMainFrame::logEvent
