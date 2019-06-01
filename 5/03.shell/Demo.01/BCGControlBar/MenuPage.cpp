// MenuPage.cpp : implementation file
//

#include "stdafx.h"
#include "globals.h"
#include "MenuPage.h"
#include "bcglocalres.h"
#include "bcgmenubar.h"
#include "MenuHash.h"
#include "BCGPopupMenu.h"
#include "BCGContextMenuManager.h"
#include "BCGMultiDocTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CObList	gAllToolbars;

CPoint CMenuPage::m_ptMenuLastPos = CPoint (100, 100);

/////////////////////////////////////////////////////////////////////////////
// CMenuPage property page

IMPLEMENT_DYNCREATE(CMenuPage, CPropertyPage)

CMenuPage::CMenuPage() : CPropertyPage(CMenuPage::IDD)
{
	//{{AFX_DATA_INIT(CMenuPage)
	m_strMenuDescr = _T("");
	m_strContextMenuName = _T("");
	m_strMenuName = _T("");
	m_iMenuAnimationType = (int) CBCGPopupMenu::m_AnimationType;
	//}}AFX_DATA_INIT

	m_pMenuBar = NULL;
	m_hmenuCurr = NULL;
	m_hmenuSelected = NULL;
	m_pContextMenu = NULL;
}

CMenuPage::~CMenuPage()
{
}

void CMenuPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenuPage)
	DDX_Control(pDX, IDC_BCGBARRES_CONTEXT_FRAME, m_wndContextFrame);
	DDX_Control(pDX, IDC_BCGBARRES_CONTEXT_HINT, m_wndContextHint);
	DDX_Control(pDX, IDC_BCGBARRES_RESET_MENU, m_wndResetMenuButton);
	DDX_Control(pDX, IDC_BCGBARRES_CONTEXT_MENU_CAPTION, m_wndContextMenuCaption);
	DDX_Control(pDX, IDC_BCGBARRES_CONTEXT_MENU_LIST, m_wndContextMenus);
	DDX_Control(pDX, IDC_BCGBARRES_TEMPL_ICON, m_wndIcon);
	DDX_Control(pDX, IDC_BCGBARRES_MENU_LIST, m_wndMenuesList);
	DDX_Text(pDX, IDC_BCGBARRES_MENU_DESCRIPTION, m_strMenuDescr);
	DDX_CBString(pDX, IDC_BCGBARRES_CONTEXT_MENU_LIST, m_strContextMenuName);
	DDX_CBString(pDX, IDC_BCGBARRES_MENU_LIST, m_strMenuName);
	DDX_CBIndex(pDX, IDC_BCGBARRES_MENU_ANIMATION, m_iMenuAnimationType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMenuPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMenuPage)
	ON_CBN_SELCHANGE(IDC_BCGBARRES_MENU_LIST, OnSelchangeMenuList)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_BCGBARRES_CONTEXT_MENU_LIST, OnSelchangeContextMenuList)
	ON_BN_CLICKED(IDC_BCGBARRES_RESET_MENU, OnResetMenu)
	ON_BN_CLICKED(IDC_BCGBARRES_RESET_FRAME_MENU, OnBcgbarresResetFrameMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuPage message handlers

BOOL CMenuPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	//----------------------------------------------------------
	// Find application Menu Bar object (assume that only one):
	//---------------------------------------------------------
	for (POSITION pos = gAllToolbars.GetHeadPosition (); 
		m_pMenuBar == NULL && pos != NULL;)
	{
		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (pos);
		ASSERT_VALID(pToolBar);

		m_pMenuBar = DYNAMIC_DOWNCAST (CBCGMenuBar, pToolBar);
	}

	if (m_pMenuBar != NULL)
	{
		int iCurrMenu = 0;

		//---------------------------
		// Save MenuBar current menu:
		//---------------------------
		m_hmenuCurr = m_pMenuBar->GetMenu ();

		m_pMenuBar->OnChangeHot (-1);
		g_menuHash.SaveMenuBar (m_hmenuCurr, m_pMenuBar);

		//-------------------------------------------------------------------
		// Find all application document templates and fill menues combobox
		// by document template data:
		//------------------------------------------------------------------
		CDocManager* pDocManager = AfxGetApp ()->m_pDocManager;
		if (pDocManager != NULL)
		{
			//---------------------------------------
			// Walk all templates in the application:
			//---------------------------------------
			for (POSITION pos = pDocManager->GetFirstDocTemplatePosition (); pos != NULL;)
			{
				CBCGMultiDocTemplate* pTemplate = 
					(CBCGMultiDocTemplate*) pDocManager->GetNextDocTemplate (pos);
				ASSERT_VALID (pTemplate);
				ASSERT_KINDOF (CDocTemplate, pTemplate);

				//-----------------------------------------------------
				// We are interessing CMultiDocTemplate objects with
				// the shared menu only....
				//-----------------------------------------------------
				if (!pTemplate->IsKindOf (RUNTIME_CLASS (CMultiDocTemplate)) ||
					pTemplate->m_hMenuShared == NULL)
				{
					continue;
				}

				CString strName;
				pTemplate->GetDocString (strName, CDocTemplate::docName);

				int iIndex = m_wndMenuesList.AddString (strName);
				m_wndMenuesList.SetItemData (iIndex, (DWORD) pTemplate);

				if (pTemplate->m_hMenuShared == m_hmenuCurr)
				{
					iCurrMenu = iIndex;
				}
			}
		}

		//--------------------------
		// Add a default frame menu:
		//--------------------------
		CString strName;
		{
			CBCGLocalResource locaRes;
			strName.LoadString (IDS_BCGBARRES_DEFUALT_MENU);
		}

		int iIndex = m_wndMenuesList.AddString (strName);
		m_wndMenuesList.SetItemData (iIndex, (DWORD) NULL);

		if (m_pMenuBar->GetDefaultMenu () == m_hmenuCurr)
		{
			iCurrMenu = iIndex;
		}

		m_hmenuSelected = m_hmenuCurr;
		m_wndMenuesList.SetCurSel (iCurrMenu);

		UpdateData (FALSE);
		OnSelchangeMenuList ();
	}
	else
	{
		//-------------------------------------------------
		// No menubar found, disable menu selecting engine:
		//-------------------------------------------------
		m_wndMenuesList.EnableWindow (FALSE);

		CBCGLocalResource locaRes;
		m_strMenuDescr.LoadString (IDS_BCGBARRES_NO_MENUBAR);

		UpdateData (FALSE);
	}

	//--------------------------
	// Initialize context menus:
	//--------------------------
	{
		CBCGLocalResource locaRes;

		CString strNoContextMenu;
		strNoContextMenu.LoadString (IDS_BCGBARRES_NO_CONTEXT);

		m_wndContextMenus.AddString (strNoContextMenu);
		m_wndContextMenus.SetCurSel (0);
	}

	if (g_pContextMenuManager != NULL)
	{
		CStringList listOfNames;
		g_pContextMenuManager->GetMenuNames (listOfNames);

		for (pos = listOfNames.GetHeadPosition (); pos != NULL;)
		{
			CString strName = listOfNames.GetNext (pos);
			m_wndContextMenus.AddString (strName);
		}

		m_wndContextMenuCaption.EnableWindow (m_wndContextMenus.GetCount () > 1);
		m_wndContextMenus.EnableWindow (m_wndContextMenus.GetCount () > 1);
	}
	else
	{
		//-------------------------------
		// Hide all context menus fields:
		//-------------------------------
		m_wndContextMenuCaption.ShowWindow (SW_HIDE);
		m_wndContextMenus.ShowWindow (SW_HIDE);
		m_wndContextHint.ShowWindow (SW_HIDE);
		m_wndContextFrame.ShowWindow (SW_HIDE);
		m_wndResetMenuButton.ShowWindow (SW_HIDE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//********************************************************************************************
void CMenuPage::OnSelchangeMenuList() 
{
	UpdateData ();

	if (m_pMenuBar == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	if (m_hmenuSelected != NULL)
	{
		m_pMenuBar->OnChangeHot (-1);
		g_menuHash.SaveMenuBar (m_hmenuSelected, m_pMenuBar);
	}

	int iIndex = m_wndMenuesList.GetCurSel ();
	if (iIndex == CB_ERR)
	{
		m_strMenuDescr = _T("");
		m_wndIcon.SetIcon (NULL);
		UpdateData (FALSE);
		m_hmenuSelected = NULL;
		return;
	}

	HICON hicon = NULL;
	HMENU hmenu = NULL;

	CBCGMultiDocTemplate* pTemplate = 
			(CBCGMultiDocTemplate*) m_wndMenuesList.GetItemData (iIndex);
	if (pTemplate != NULL)
	{
		ASSERT_VALID (pTemplate);

		pTemplate->GetDocString (m_strMenuDescr, CDocTemplate::regFileTypeName);

		hicon = AfxGetApp ()->LoadIcon (pTemplate->GetResId ());
		if (hicon == NULL)
		{
			hicon = ::LoadIcon(NULL, IDI_APPLICATION);
		}

		hmenu = pTemplate->m_hMenuShared;
	}
	else
	{
		{
			CBCGLocalResource locaRes;
			m_strMenuDescr.LoadString (IDS_BCGBARRES_DEFAULT_MENU_DESCR);
		}

		CWnd* pWndMain = AfxGetMainWnd ();
		if (pWndMain != NULL)
		{
			hicon = (HICON) GetClassLong (*pWndMain, GCL_HICON);
		}

		hmenu = m_pMenuBar->GetDefaultMenu ();
	}

	ASSERT (hmenu != NULL);

	m_pMenuBar->CreateFromMenu (hmenu);
	m_wndIcon.SetIcon (hicon);

	m_hmenuSelected = hmenu;
	UpdateData (FALSE);
}
//***********************************************************************************************
void CMenuPage::OnDestroy() 
{
	UpdateData ();

	CBCGPopupMenu::m_AnimationType = 
		(CBCGPopupMenu::ANIMATION_TYPE) m_iMenuAnimationType;

	if (m_pMenuBar != NULL)
	{
		//------------------------------
		// Save the selected menu state:
		//------------------------------
		if (m_hmenuSelected != NULL)
		{
			m_pMenuBar->OnChangeHot (-1);	// To close and save all popups
			g_menuHash.SaveMenuBar (m_hmenuSelected, m_pMenuBar);
		}

		//--------------------------
		// Restore the current menu:
		//--------------------------
		if (m_hmenuCurr != NULL)
		{
			m_pMenuBar->CreateFromMenu (m_hmenuCurr);
		}
	}

	//------------------------------------
	// Release the context menu resources:
	//------------------------------------
	if (m_pContextMenu != NULL)
	{
		SaveMenu ();
		m_pContextMenu->SendMessage (WM_CLOSE);
	}

	CPropertyPage::OnDestroy();
}
//************************************************************************************************
void CMenuPage::OnSelchangeContextMenuList() 
{
	m_wndResetMenuButton.EnableWindow (FALSE);

	if (g_pContextMenuManager == NULL)
	{
		return;
	}

	//----------------------------------------
	// First, save and close the current menu:
	//----------------------------------------
	if (m_pContextMenu != NULL)
	{
		SaveMenu ();

		CBCGPopupMenu* pMenu = m_pContextMenu;
		m_pContextMenu = NULL;
		pMenu->SendMessage (WM_CLOSE);
	}

	if (m_wndContextMenus.GetCurSel () <= 0)
	{
		//--------------------------------------
		// No is menu selected, nothing to do...
		//--------------------------------------
		return;
	}

	UpdateData ();

	HMENU hMenu = g_pContextMenuManager->GetMenuByName (m_strContextMenuName);

	if (hMenu == NULL)
	{
		MessageBeep ((UINT) -1);
		return;
	}

	HMENU hmenuPopup = ::GetSubMenu (hMenu, 0);
	if (hmenuPopup == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	m_pContextMenu = new CBCGPopupMenu (this, m_strContextMenuName);
	ASSERT (m_pContextMenu != NULL);

	if (!globalData.bIsWindowsNT)
	{
		m_pContextMenu->SetAutoDestroy (FALSE);
	}

	if (!m_pContextMenu->Create (AfxGetMainWnd (),
			m_ptMenuLastPos.x, m_ptMenuLastPos.y,
			hmenuPopup))
	{
		AfxMessageBox (_T("Can't create context menu!"));
	}
	else
	{
		m_wndResetMenuButton.EnableWindow ();
	}
}
//************************************************************************************************
void CMenuPage::CloseContextMenu (CBCGPopupMenu* pMenu)
{
	if (m_pContextMenu == NULL)
	{
		return;
	}

	ASSERT(m_pContextMenu == pMenu);

	SaveMenu ();

	if (m_pContextMenu != NULL)
	{
		m_pContextMenu = NULL;
		m_wndContextMenus.SetCurSel (0);
		
		m_wndResetMenuButton.EnableWindow (FALSE);
	}
}
//***********************************************************************************************
void CMenuPage::SaveMenu ()
{
	if (m_pContextMenu == NULL)
	{
		return;
	}

	//-----------------------------
	// Save current menu position:
	//-----------------------------
	CRect rectMenu;
	m_pContextMenu->GetWindowRect (&rectMenu);
	m_ptMenuLastPos = rectMenu.TopLeft ();

	//-------------------
	// Save menu context:
	//-------------------
	g_menuHash.SaveMenuBar (m_pContextMenu->m_hMenu, &m_pContextMenu->m_wndMenuBar);
}
//***********************************************************************************************
void CMenuPage::OnResetMenu() 
{
	if (g_pContextMenuManager == NULL)
	{
		return;
	}

	ASSERT (m_pContextMenu != NULL);

	{
		CBCGLocalResource locaRes;

		CString strPrompt;
		strPrompt.Format (IDS_BCGBARRES_RESET_MENU_FMT, m_strContextMenuName);

		if (MessageBox (strPrompt, NULL, MB_YESNO | MB_ICONQUESTION) != IDYES)
		{
			return;
		}
	}

	HMENU hMenu = g_pContextMenuManager->GetMenuByName (m_strContextMenuName);
	if (hMenu == NULL)
	{
		MessageBeep ((UINT) -1);
		return;
	}

	m_pContextMenu->m_wndMenuBar.ImportFromMenu (::GetSubMenu (hMenu, 0));
	m_pContextMenu->RecalcLayout ();
}
//*****************************************************************************************
void CMenuPage::OnBcgbarresResetFrameMenu() 
{
	UpdateData ();

	if (m_pMenuBar == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	int iIndex = m_wndMenuesList.GetCurSel ();
	if (iIndex == CB_ERR)
	{
		ASSERT (FALSE);
		return;
	}

	{
		CBCGLocalResource locaRes;

		CString strPrompt;
		strPrompt.Format (IDS_BCGBARRES_RESET_MENU_FMT, m_strMenuName);

		if (MessageBox (strPrompt, NULL, MB_YESNO | MB_ICONQUESTION) != IDYES)
		{
			return;
		}
	}

	CBCGMultiDocTemplate* pTemplate = 
			(CBCGMultiDocTemplate*) m_wndMenuesList.GetItemData (iIndex);
	if (pTemplate != NULL)	// Document's menu
	{
		ASSERT_VALID (pTemplate);

		HINSTANCE hInst = AfxFindResourceHandle (
			MAKEINTRESOURCE (pTemplate->GetResId ()), RT_MENU);

		pTemplate->m_hMenuShared = ::LoadMenu (hInst, MAKEINTRESOURCE (pTemplate->GetResId ()));
		m_pMenuBar->CreateFromMenu (pTemplate->m_hMenuShared, FALSE);
		g_menuHash.SaveMenuBar (pTemplate->m_hMenuShared, m_pMenuBar);
	}
	else	// Frame's default menu
	{
		UINT uiDefMenuResId = m_pMenuBar->GetDefaultMenuResId ();
		if (uiDefMenuResId != 0)
		{
			HINSTANCE hInst = AfxFindResourceHandle (
				MAKEINTRESOURCE (uiDefMenuResId), RT_MENU);

			HMENU hDefaultMenu = ::LoadMenu (hInst, MAKEINTRESOURCE (uiDefMenuResId));

			m_pMenuBar->CreateFromMenu (hDefaultMenu, TRUE);
			g_menuHash.SaveMenuBar (hDefaultMenu, m_pMenuBar);
		}
	}
}
