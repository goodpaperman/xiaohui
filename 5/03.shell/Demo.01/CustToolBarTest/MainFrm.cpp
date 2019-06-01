// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "afxpriv.h"
#include "CustToolBarTest.h"
#include "MainFrm.h"

#include "imagehash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int  iMaxUserToolbars		= 10;

const UINT uiMenuBarId			= AFX_IDW_CONTROLBAR_FIRST + 20;
const UINT uiUserBarId			= AFX_IDW_CONTROLBAR_FIRST + 21;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

#define CONTROL_BARS	_T("Control Bars")

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CBCGMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_USER_TOOBAR, OnViewUserToobar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USER_TOOBAR, OnUpdateViewUserToobar)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_WM_CLOSE()
	ON_COMMAND(ID_USER_CONFIGURATION, OnUserConfiguration)
	ON_COMMAND(ID_POPUP_ONE, OnPopupOne)
	ON_COMMAND(ID_POPUP_TWO, OnPopupTwo)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_USER_TOOLS, OnUserTool)
	ON_COMMAND_EX_RANGE(ID_VIEW_USER_TOOLBAR1, ID_VIEW_USER_TOOLBAR1 + iMaxUserToolbars - 1, OnToolsViewUserToolbar)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_USER_TOOLBAR1, ID_VIEW_USER_TOOLBAR1 + iMaxUserToolbars - 1, OnUpdateToolsViewUserToolbar)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnHelpCustomizeToolbars)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_CBN_SELENDOK(ID_USER_CONFIGURATION, OnSelectUserConfiguration)
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
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//--------------------------
	// Load toolbar user images:
	//--------------------------
	if (!m_UserImages.Load (_T("User Buttons.bmp")))
	{
		MessageBox ("Can't find 'User Buttons.bmp' file");

		TRACE0("Failed to load user images\n");
		//return -1;      // fail to create
	}

	CBCGToolBar::SetUserImages (&m_UserImages);

	//----------------------------------------------
	// Create menu bar (replaces the standard menu):
	//----------------------------------------------
	if (!m_wndMenuBar.Create (this, WS_CHILD | WS_VISIBLE | CBRS_TOP, uiMenuBarId))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	//---------------------------
	// Load the standard toolbar:
	//---------------------------
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetWindowText (_T("Standard"));

	//-------------------------
	// Load the "user" toolbar:
	//-------------------------
	if (!m_wndUserToolBar.Create(this, 
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_HIDE_INPLACE, 
		uiUserBarId))
	{
		TRACE0("Failed to create user toolbar\n");
		return -1;      // fail to create
	}

	m_wndUserToolBar.SetWindowText (_T("User"));

	CMenu menu;
	menu.LoadMenu (IDR_BUTTON_MENU);
	CMenu* pPopupMenu = menu.GetSubMenu (0);
	VERIFY (pPopupMenu != NULL);

	m_wndUserToolBar.InsertButton (CBCGToolbarMenuButton 
		(ID_USER_TOOLS, pPopupMenu->GetSafeHmenu (), 0, "Select", TRUE));
	m_wndUserToolBar.InsertButton (CBCGToolbarButton 
		(ID_USER_TOOL1, 1, "User Tool 1", TRUE));
	m_wndUserToolBar.InsertButton (CBCGToolbarButton 
		(ID_USER_TOOL2, 2, "User Tool 2", TRUE));
	m_wndUserToolBar.InsertButton (CBCGToolbarButton 
		(ID_USER_TOOL3, 3, "User Tool 3", TRUE));


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
	m_wndUserToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndMenuBar.EnableDocking (CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndUserToolBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar (&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndUserToolBar, AFX_IDW_DOCKBAR_BOTTOM);

    CString strControlBarRegEntry = REGISTRY_ROOT;
    strControlBarRegEntry += CONTROL_BARS;

	CBCGToolBar::LoadParameters (strControlBarRegEntry);

	//----------------------------------------------
	// Enable quick customization mode ("Alt+drag"):
	//----------------------------------------------
	CBCGToolBar::EnableQuickCustomization ();

	//----------------------------------------
	// Allow user-defined toolbars operations:
	//----------------------------------------
	InitUserToobars (strControlBarRegEntry,
					uiFirstUserToolBarId,
					uiLastUserToolBarId);

	//------------------------
	// Load standard toolbars:
	//------------------------
	m_wndToolBar.LoadState (strControlBarRegEntry);
	m_wndMenuBar.LoadState (strControlBarRegEntry);
	m_wndUserToolBar.LoadState (strControlBarRegEntry);

	//----------------------------
	// Load user defined toolbars:
	//----------------------------
	LoadUserToolbars ();

	//-------------------------------------
	// Load control bar states and context:
	//-------------------------------------
	CDockState dockState;
	dockState.LoadState (CONTROL_BARS);

	if (IsDockStateValid (dockState))
	{
		SetDockState (dockState);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnViewUserToobar() 
{
	ShowControlBar (&m_wndUserToolBar,
					!(m_wndUserToolBar.GetStyle () & WS_VISIBLE),
					FALSE);
}

void CMainFrame::OnUpdateViewUserToobar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndUserToolBar.GetStyle () & WS_VISIBLE);
}

void CMainFrame::OnViewCustomize() 
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGToolbarCustomize* pDlgCust = new CBCGToolbarCustomize (this,
		TRUE /* Automatic menus scaning */);

	//--------------
	// Adjust combo:
	//--------------
	CBCGToolbarComboBoxButton comboButton (ID_USER_CONFIGURATION, 
		CImageHash::GetImageOfCommand (ID_USER_CONFIGURATION, FALSE));
	comboButton.AddItem ("Win32 Debug");
	comboButton.AddItem ("Win32 Release");
	comboButton.AddItem ("Win32 Unicode Debug");
	comboButton.AddItem ("Win32 Unicode Release");

	pDlgCust->ReplaceButton (ID_USER_CONFIGURATION, comboButton);

	CMenu menu;
	menu.LoadMenu (IDR_BUTTON_MENU);
	CMenu* pPopupMenu = menu.GetSubMenu (0);
	VERIFY (pPopupMenu != NULL);

	pDlgCust->AddButton ("User",
		CBCGToolbarMenuButton (0, pPopupMenu->GetSafeHmenu (), 0, "Select", TRUE));
	pDlgCust->AddButton ("User", 
		CBCGToolbarButton (ID_USER_TOOL1, 1, "User Tool 1", TRUE));
	pDlgCust->AddButton ("User", 
		CBCGToolbarButton (ID_USER_TOOL2, 2, "User Tool 2", TRUE));
	pDlgCust->AddButton ("User", 
		CBCGToolbarButton (ID_USER_TOOL3, 3, "User Tool 3", TRUE));

	pDlgCust->SetUserCategory ("User");

	pDlgCust->EnableUserDefinedToolbars ();
	pDlgCust->Create ();
}

//////////////////////////////////////////////
// Toobar message handlers

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM,LPARAM lp)
{
	CPoint point (LOWORD (lp), HIWORD(lp));

	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	//---------------------------------------------------------------
	// Replace toolbar dummy items to the user-defined toolbar names:
	//---------------------------------------------------------------
	for (int i = 0; i < (int) pPopup->GetMenuItemCount ();)
	{
		UINT uiCmd = pPopup->GetMenuItemID (i);

		if (uiCmd >= ID_VIEW_USER_TOOLBAR1 && 
			uiCmd < ID_VIEW_USER_TOOLBAR1 + iMaxUserToolbars)
		{
			//-------------------------------------------------------------------
			// "User toolbar" item. First check that toolbar number 'x' is exist:
			//-------------------------------------------------------------------
			CBCGToolBar* pToolBar = GetUserBarByIndex (uiCmd - ID_VIEW_USER_TOOLBAR1);
			if (pToolBar != NULL)
			{
				//-----------------------------------------------------------
				// Modify the current menu item text to the toolbar title and
				// move next:
				//-----------------------------------------------------------
				CString strToolbarName;
				pToolBar->GetWindowText (strToolbarName);

				pPopup->ModifyMenu (i ++, MF_BYPOSITION | MF_STRING, uiCmd, strToolbarName);
			}
			else
			{
				pPopup->DeleteMenu (i, MF_BYPOSITION);
			}
		}
		else	// Not "user toolbar" item, move next
		{
			i ++;
		}
	}

	CBCGPopupMenu* pPopupMenu = new CBCGPopupMenu;
	pPopupMenu->Create (this, point.x, point.y, pPopup->Detach ());

	return 0;
}
//**********************************************************************************
void CMainFrame::OnToolsViewUserToolbar (UINT uiId)
{
	CBCGToolBar* pUserToolBar = GetUserBarByIndex (uiId - ID_VIEW_USER_TOOLBAR1);
	if (pUserToolBar == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	ShowControlBar (pUserToolBar, !(pUserToolBar->GetStyle () & WS_VISIBLE), FALSE);
	RecalcLayout ();
}
//**********************************************************************************
void CMainFrame::OnUpdateToolsViewUserToolbar (CCmdUI* pCmdUI)
{
	CBCGToolBar* pUserToolBar = GetUserBarByIndex (pCmdUI->m_nID - ID_VIEW_USER_TOOLBAR1);
	if (pUserToolBar == NULL)
	{
		pCmdUI->Enable (FALSE);
		return;
	}

	pCmdUI->Enable ();
	pCmdUI->SetCheck (pUserToolBar->GetStyle () & WS_VISIBLE);
}
//**********************************************************************************
LRESULT CMainFrame::OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp)
{
	int iPageNum = (int) wp;

	CBCGToolbarCustomize* pDlg = (CBCGToolbarCustomize*) lp;
	ASSERT_VALID (pDlg);

	// Test!
	CString str;
	str.Format ("Help about page number %d", iPageNum);

	MessageBox (str);

	return 0;
}
//**********************************************************************************
afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM wp,LPARAM)
{
	UINT uiToolBarId = (UINT) wp;
	if (uiToolBarId == IDR_MAINFRAME)
	{
		//----------------------------------------
		// Add a combobox to the standard toolbar:
		//----------------------------------------
		CBCGToolbarComboBoxButton comboButton (ID_USER_CONFIGURATION, 
			CImageHash::GetImageOfCommand (ID_USER_CONFIGURATION, FALSE));
		comboButton.AddItem ("Win32 Debug");
		comboButton.AddItem ("Win32 Release");
		comboButton.AddItem ("Win32 Unicode Debug");
		comboButton.AddItem ("Win32 Unicode Release");

		int iIndex = m_wndToolBar.CommandToIndex (ID_USER_CONFIGURATION);
		m_wndToolBar.RemoveButton (iIndex);

		if (iIndex > m_wndToolBar.GetCount ())
		{
			iIndex = m_wndToolBar.GetCount ();
		}

		m_wndToolBar.InsertButton (comboButton, iIndex);
	}

	return 0;
}
//**********************************************************************************
void CMainFrame::OnClose() 
{
    CString strControlBarRegEntry = REGISTRY_ROOT;
    strControlBarRegEntry += CONTROL_BARS;

	CBCGToolBar::SaveParameters (strControlBarRegEntry);

	CDockState dockState;
	GetDockState (dockState);
	dockState.SaveState (CONTROL_BARS);

	//------------------------
	// Save standard toolbars:
	//------------------------
	m_wndToolBar.SaveState (strControlBarRegEntry);
	m_wndMenuBar.SaveState (strControlBarRegEntry);
	m_wndUserToolBar.SaveState (strControlBarRegEntry);

	//----------------------------
	// Save user defined toolbars:
	//----------------------------
	SaveUserToolbars ();

	//------------------
	// Save user images:
	//------------------
	m_UserImages.Save ();

	//------------------------
	// Save keyboard settings:
	//------------------------
	//theApp.SaveKbdManager ();

	CBCGMDIFrameWnd::OnClose();
}

//--------------------
// Command examples:
//--------------------
void CMainFrame::OnUserConfiguration() 
{
	MessageBox ("Show User configuration Dlg....");
}
//**********************************************************************************
void CMainFrame::OnPopupOne() 
{
	MessageBox ("Say One!");
}
//**********************************************************************************
void CMainFrame::OnPopupTwo() 
{
	MessageBox ("Say Two!");
}
//**********************************************************************************
void CMainFrame::OnSelectUserConfiguration()
{
	CBCGToolbarComboBoxButton* pSrcCombo = NULL;

	CObList listButtons;
	if (CBCGToolBar::GetCommandButtons (ID_USER_CONFIGURATION, listButtons) > 0)
	{
		for (POSITION posCombo = listButtons.GetHeadPosition (); 
			pSrcCombo == NULL && posCombo != NULL;)
		{
			CBCGToolbarComboBoxButton* pCombo = 
				DYNAMIC_DOWNCAST (CBCGToolbarComboBoxButton, listButtons.GetNext (posCombo));
			ASSERT (pCombo != NULL);

			if (CBCGToolBar::IsLastCommandFromButton (pCombo))
			{
				pSrcCombo = pCombo;
			}
		}
	}

	if (pSrcCombo != NULL)
	{
		LPCSTR lpszSelItem = pSrcCombo->GetItem ();
		CString strSelItem = (lpszSelItem == NULL) ? _T("") : lpszSelItem;

		MessageBox (strSelItem);
	}
	else
	{
		OnUserConfiguration();
	}
}
//**********************************************************************************
void CMainFrame::OnUserTool ()
{
	MessageBox ("User Tool.");
}
