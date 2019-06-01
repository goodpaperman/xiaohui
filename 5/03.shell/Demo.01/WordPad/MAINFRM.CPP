// mainfrm.cpp : implementation of the CMainFrame class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"

#include "wordpad.h"
#include "mainfrm.h"
#include "wordpdoc.h"
#include "wordpvw.h"
#include "strings.h"
#include "colorlis.h"
#include "ColorPopupBar.h"

#include "CBCGToolbarCustomize.h"
#include "BCGPopupMenu.h"
#include "BCGPopupMenuBar.h"
#include "FontCombo.h"
#include "ImageHash.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define CONTROL_BARS	_T("Control Bars");

const int  iMaxUserToolbars		= 10;

const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_COMMAND(ID_HELP, OnHelpFinder)
	ON_WM_DROPFILES()
	ON_WM_FONTCHANGE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_DEVMODECHANGE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_WM_CLOSE()
	ON_COMMAND(ID_HELP_INDEX, OnHelpFinder)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_CONTEXT_HELP, CBCGFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, OnHelpFinder)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FORMATBAR, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RULER, OnUpdateControlBarMenu)
	ON_MESSAGE(WPM_BARSTATE, OnBarState)
	ON_REGISTERED_MESSAGE(CWordPadApp::m_nOpenMsg, OnOpenMsg)
	ON_COMMAND_EX(ID_VIEW_STATUS_BAR, OnBarCheck)
	ON_COMMAND_EX(ID_VIEW_TOOLBAR, OnBarCheck)
	ON_COMMAND_EX(ID_VIEW_FORMATBAR, OnBarCheck)
	ON_COMMAND_EX(ID_VIEW_RULER, OnBarCheck)
	ON_COMMAND_EX_RANGE(ID_VIEW_USER_TOOLBAR1, ID_VIEW_USER_TOOLBAR1 + iMaxUserToolbars - 1, OnToolsViewUserToolbar)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_USER_TOOLBAR1, ID_VIEW_USER_TOOLBAR1 + iMaxUserToolbars - 1, OnUpdateToolsViewUserToolbar)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnHelpCustomizeToolbars)
	ON_REGISTERED_MESSAGE(CPN_SELCHANGE, OnChangeColor)
END_MESSAGE_MAP()

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_hIconDoc = theApp.LoadIcon(IDI_ICON_DOC);
	m_hIconText = theApp.LoadIcon(IDI_ICON_TEXT);
	m_hIconWrite = theApp.LoadIcon(IDI_ICON_WRITE);
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	WNDCLASS wndcls;

	BOOL bRes = CBCGFrameWnd::PreCreateWindow(cs);
	HINSTANCE hInst = AfxGetInstanceHandle();

	// see if the class already exists
	if (!::GetClassInfo(hInst, szWordPadClass, &wndcls))
	{
		// get default stuff
		::GetClassInfo(hInst, cs.lpszClass, &wndcls);
		wndcls.style &= ~(CS_HREDRAW|CS_VREDRAW);
		// register a new class
		wndcls.lpszClassName = szWordPadClass;
		wndcls.hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
		ASSERT(wndcls.hIcon != NULL);
		if (!AfxRegisterClass(&wndcls))
			AfxThrowResourceException();
	}
	cs.lpszClass = szWordPadClass;
	CRect rect = theApp.m_rectInitialFrame;
	if (rect.Width() > 0 && rect.Height() > 0)
	{
		// make sure window will be visible
		CDisplayIC dc;
		CRect rectDisplay(0, 0, dc.GetDeviceCaps(HORZRES),
			dc.GetDeviceCaps(VERTRES));
		if (rectDisplay.PtInRect(rect.TopLeft()) &&
			rectDisplay.PtInRect(rect.BottomRight()))
		{
			cs.x = rect.left;
			cs.y = rect.top;
			cs.cx = rect.Width();
			cs.cy = rect.Height();
		}
	}
	return bRes;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!CreateMenuBar())
		return -1;

	if (!CreateToolBar())
		return -1;

	if (!CreateFormatBar())
		return -1;

	if (!CreateStatusBar())
		return -1;

	EnableDocking(CBRS_ALIGN_ANY);

	if (!CreateRulerBar())
		return -1;

	CBCGToolBar::AddToolBarForImageCollection (IDR_TOOLBAR_IMAGES);
	CBCGToolBar::EnableQuickCustomization ();

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFormatBar.EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndFormatBar);

	CWnd* pView = GetDlgItem(AFX_IDW_PANE_FIRST);
	if (pView != NULL)
	{
		pView->SetWindowPos(&wndBottom, 0, 0, 0, 0,
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);
	}

	CString strControlBarRegEntry = REGISTRY_ROOT;
	strControlBarRegEntry += CONTROL_BARS;

	CBCGToolBar::LoadParameters (strControlBarRegEntry);

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
	m_wndFormatBar.LoadState (strControlBarRegEntry);

	//----------------------------
	// Load user defined toolbars:
	//----------------------------
	LoadUserToolbars ();
	return 0;
}

BOOL CMainFrame::CreateMenuBar()
{
	//----------------------------------------------
	// Create menu bar (replaces the standard menu):
	//----------------------------------------------
	if (!m_wndMenuBar.Create (this/*, WS_CHILD | WS_VISIBLE | CBRS_TOP, uiMenuBarId*/))
	{
		TRACE0("Failed to create menubar\n");
		return FALSE;
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER | CBRS_BORDER_3D);

	CString str;
	str.LoadString(IDS_TITLE_MENUBAR);
	m_wndMenuBar.SetWindowText(str);
	return TRUE;
}

BOOL CMainFrame::CreateToolBar()
{
	if (!m_wndToolBar.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC |
			CBRS_GRIPPER | CBRS_BORDER_3D)||
			!m_wndToolBar.LoadToolBar (theApp.m_bLargeIcons ? 
				IDR_MAINFRAME_BIG : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;      // fail to create
	}
/*	if (theApp.m_bLargeIcons)
		m_wndToolBar.SetSizes(CSize(31,30), CSize(24,24));
	else
		m_wndToolBar.SetSizes(CSize(23,22), CSize(16,16));*/
	CString str;
	str.LoadString(IDS_TITLE_TOOLBAR);
	m_wndToolBar.SetWindowText(str);
	return TRUE;
}

BOOL CMainFrame::CreateFormatBar()
{
	if (!m_wndFormatBar.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_HIDE_INPLACE|CBRS_SIZE_DYNAMIC|
		CBRS_GRIPPER | CBRS_BORDER_3D,
		ID_VIEW_FORMATBAR) ||
		!m_wndFormatBar.LoadToolBar (theApp.m_bLargeIcons ? 
				IDR_FORMATBAR_BIG : IDR_FORMATBAR))
	{
		TRACE0("Failed to create FormatBar\n");
		return FALSE;      // fail to create
	}

/*	if (theApp.m_bLargeIcons)
		m_wndFormatBar.SetSizes(CSize(31,30), CSize(24,24));
	else
		m_wndFormatBar.SetSizes(CSize(23,22), CSize(16,16));*/
	CString str;
	str.LoadString(IDS_TITLE_FORMATBAR);
	m_wndFormatBar.SetWindowText(str);
	return TRUE;
}

BOOL CMainFrame::CreateRulerBar()
{
	if (!m_wndRulerBar.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_HIDE_INPLACE, ID_VIEW_RULER))
	{
		TRACE0("Failed to create ruler\n");
		return FALSE;      // fail to create
	}
	return TRUE;
}

BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;      // fail to create
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Operations

HICON CMainFrame::GetIcon(int nDocType)
{
	switch (nDocType)
	{
		case RD_WINWORD6:
		case RD_WORDPAD:
		case RD_EMBEDDED:
		case RD_RICHTEXT:
			return m_hIconDoc;
		case RD_TEXT:
		case RD_OEMTEXT:
			return m_hIconText;
		case RD_WRITE:
			return m_hIconWrite;
	}
	return m_hIconDoc;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnFontChange()
{
	CLocalComboBox::OnPrinterChanged ();
	m_wndFormatBar.SendMessage(CWordPadApp::m_nPrinterChangedMsg);
}

void CMainFrame::OnDevModeChange(LPTSTR lpDeviceName)
{
	theApp.NotifyPrinterChanged();
	CBCGFrameWnd::OnDevModeChange(lpDeviceName); //sends message to descendants
}

void CMainFrame::OnSysColorChange()
{
	CBCGFrameWnd::OnSysColorChange();
	m_wndRulerBar.SendMessage(WM_SYSCOLORCHANGE);
}

void CMainFrame::ActivateFrame(int nCmdShow)
{
	CBCGFrameWnd::ActivateFrame(nCmdShow);
	// make sure and display the toolbar, ruler, etc while loading a document.
	OnIdleUpdateCmdUI();
	UpdateWindow();
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CBCGFrameWnd::OnSize(nType, cx, cy);
	theApp.m_bMaximized = (nType == SIZE_MAXIMIZED);
	if (nType == SIZE_RESTORED)
		GetWindowRect(theApp.m_rectInitialFrame);
}

LONG CMainFrame::OnBarState(UINT wParam, LONG lParam)
{
	if (lParam == -1)
		return 0L;
	ASSERT(lParam != RD_EMBEDDED);
	if (wParam == 0)
	{
		CDockState& ds = theApp.GetDockState(lParam);
		ds.Clear(); // empty out the dock state
		GetDockState(ds);
	}
	else
	{
		if (IsTextType(lParam))
		{
			// in text mode hide the ruler and format bar so that it is the default
			CControlBar* pBar = GetControlBar(ID_VIEW_FORMATBAR);
			if (pBar != NULL)
				pBar->ShowWindow(SW_HIDE);
			pBar = GetControlBar(ID_VIEW_RULER);
			if (pBar != NULL)
				pBar->ShowWindow(SW_HIDE);
		}
		HICON hIcon = GetIcon((int)lParam);
		SendMessage(WM_SETICON, TRUE, (LPARAM)hIcon);

		CDockState& dockState = theApp.GetDockState(lParam);
		if (IsDockStateValid (dockState))
		{
			SetDockState (dockState);
		}
	}
	return 0L;
}

void CMainFrame::OnMove(int x, int y)
{
	CBCGFrameWnd::OnMove(x, y);
	WINDOWPLACEMENT wp;
	wp.length = sizeof(wp);
	GetWindowPlacement(&wp);
	theApp.m_rectInitialFrame = wp.rcNormalPosition;
	CView* pView = GetActiveView();
	if (pView != NULL)
		pView->SendMessage(WM_MOVE);
}

LONG CMainFrame::OnOpenMsg(UINT, LONG lParam)
{
	TCHAR szAtomName[256];
	szAtomName[0] = NULL;
	GlobalGetAtomName((ATOM)lParam, szAtomName, 256);
	CWordPadDoc* pDoc = (CWordPadDoc*)GetActiveDocument();
	if (szAtomName[0] != NULL && pDoc != NULL)
	{
		if (lstrcmpi(szAtomName, pDoc->GetPathName()) == 0)
			return TRUE;
	}
	return FALSE;
}

void CMainFrame::OnHelpFinder()
{
	theApp.WinHelp(0, HELP_FINDER);
}

void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFileName[_MAX_PATH];
	::DragQueryFile(hDropInfo, 0, szFileName, _MAX_PATH);
	::DragFinish(hDropInfo);
	theApp.OpenDocumentFile(szFileName);
}

BOOL CMainFrame::OnQueryNewPalette()
{
	CView* pView = GetActiveView();
	if (pView != NULL)
		return pView->SendMessage(WM_QUERYNEWPALETTE);
	return FALSE;
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	CView* pView = GetActiveView();
	if (pView != NULL)
		pView->SendMessage(WM_PALETTECHANGED, (WPARAM)pFocusWnd->GetSafeHwnd());
}

void CMainFrame::OnViewCustomize() 
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGToolbarCustomize* pDlgCust = new CBCGToolbarCustomize (this,
		TRUE /* Automatic menus scaning */);

	pDlgCust->AddToolBar (_T("Format"), IDR_FORMATBAR);

	CFontNameComboBoxButton comboButtonFontName (IDC_FONTNAME, 
		CImageHash::GetImageOfCommand (IDC_FONTNAME, FALSE),
		WS_TABSTOP | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | CBS_DROPDOWN |
		CBS_SORT | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_OWNERDRAWFIXED,
		(3*LF_FACESIZE*m_wndFormatBar.m_szBaseUnits.cx)/2);
	pDlgCust->ReplaceButton (IDC_FONTNAME, comboButtonFontName);

	CFontSizeComboBoxButton comboButtonFontSize (IDC_FONTSIZE, 
		CImageHash::GetImageOfCommand (IDC_FONTSIZE, FALSE),
		WS_TABSTOP|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|CBS_DROPDOWN,
		10*m_wndFormatBar.m_szBaseUnits.cx + 10);
	pDlgCust->ReplaceButton (IDC_FONTSIZE, comboButtonFontSize);

	pDlgCust->EnableUserDefinedToolbars ();
	pDlgCust->Create ();
}

void CMainFrame::OnShowPopupMenu (CBCGPopupMenu* pMenuPopup)
{
	CBCGFrameWnd::OnShowPopupMenu (pMenuPopup);

	if (pMenuPopup == NULL)
	{
		return;
	}

	AdjustObjectSubmenu (pMenuPopup);
	AdjustColorsMenu (pMenuPopup, ID_CHAR_COLOR);
}

LRESULT CMainFrame::OnChangeColor(WPARAM wp, LPARAM)
{
	CWordPadView* pView = DYNAMIC_DOWNCAST (CWordPadView, GetActiveView());
	if (pView != NULL)
	{
		pView->SetTextColor ((COLORREF) wp);
	}

	return 0l;
}

void CMainFrame::AdjustObjectSubmenu (CBCGPopupMenu* pMenuPopup)
{
	ASSERT (pMenuPopup != NULL);

	if (pMenuPopup->GetParentPopupMenu () != NULL)
	{
		return;
	}

	CBCGPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT (pMenuBar != NULL);

	int iIndex = pMenuBar->CommandToIndex (ID_OLE_VERB_POPUP);
	if (iIndex < 0)
	{
		return;
	}

	CWordPadDoc* pDoc = (CWordPadDoc*)GetActiveDocument();
	ASSERT_VALID (pDoc);

	// check for single selection
	COleClientItem* pItem = pDoc->GetPrimarySelectedItem(GetActiveView());
	if (pItem == NULL || pItem->GetType() == OT_STATIC)
	{
		// no selection, or is 'static' item
		return;
	}

	// only include Convert... if there is a handler for ID_OLE_EDIT_CONVERT
	UINT nConvertID = ID_OLE_EDIT_CONVERT;
	AFX_CMDHANDLERINFO info;
	if (!pDoc->OnCmdMsg(ID_OLE_EDIT_CONVERT, CN_COMMAND, NULL, &info))
		nConvertID = 0;

	HMENU hMenu = pMenuPopup->GetMenu ();
	ASSERT(hMenu != NULL);

	// update the menu
	AfxOleSetEditMenu(pItem,
		CMenu::FromHandle (hMenu), iIndex,
		ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, nConvertID);

	pMenuBar->ImportFromMenu (hMenu);
}

void CMainFrame::AdjustColorsMenu (CBCGPopupMenu* pMenuPopup, UINT uiID)
{
	CBCGPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT (pMenuBar != NULL);

	int iIndex = pMenuBar->CommandToIndex (uiID);
	if (iIndex < 0)
	{
		return;
	}

	if (DYNAMIC_DOWNCAST (CColorMenuButton, pMenuBar->GetButton (iIndex)) != NULL)
	{
		return;
	}

	pMenuBar->RemoveButton (iIndex);
	if (iIndex > pMenuBar->GetCount ())
	{
		iIndex = pMenuBar->GetCount ();
	}

	CColorMenuButton colorButton;
	pMenuBar->InsertButton (colorButton, iIndex);
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
	str.Format (_T("Help about page number %d"), iPageNum);

	MessageBox (str);

	return 0;
}
//***************************************************************************************
void CMainFrame::OnClose() 
{
	CString strControlBarRegEntry = REGISTRY_ROOT;
	strControlBarRegEntry += CONTROL_BARS;

	CBCGToolBar::SaveParameters (strControlBarRegEntry);

	CDockState dockState;
	GetDockState (dockState);
	dockState.SaveState (strControlBarRegEntry);

	//------------------------
	// Save standard toolbars:
	//------------------------
	m_wndToolBar.SaveState (strControlBarRegEntry);
	m_wndMenuBar.SaveState (strControlBarRegEntry);
	m_wndFormatBar.SaveState (strControlBarRegEntry);

	//----------------------------
	// Save user defined toolbars:
	//----------------------------
	SaveUserToolbars ();

	theApp.SaveCustomState ();
	
	CBCGFrameWnd::OnClose();
}
