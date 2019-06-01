// CBCGToolbarCustomize.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"
#include "bcgbarres.h"
#include "CBCGToolbarCustomize.h"
#include "BCGToolBar.h"
#include "BCGMenuBar.h"
#include "bcglocalres.h"
#include "BCGMouseManager.h"
#include "BCGContextMenuManager.h"
#include "ButtonsTextList.h"
#include "BCGMDIFrameWnd.h"
#include "BCGFrameWnd.h"
#include "BCGKeyboardManager.h"
#include "BCGToolbarMenuButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CBCGToolbarCustomize*	g_pWndCustomize = NULL;

static const int iButtonMargin = 8;

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarCustomize

IMPLEMENT_DYNAMIC(CBCGToolbarCustomize, CPropertySheet)

CBCGToolbarCustomize::CBCGToolbarCustomize(CWnd* pWndParent,
	BOOL bAutoSetFromMenus /* = FALSE */)
	 : CPropertySheet(_T(""), pWndParent),
	 m_bAutoSetFromMenus (bAutoSetFromMenus)
{
	CBCGLocalResource locaRes;

	m_pCustomizePage = new CCustomizePage;
	m_pToolbarsPage = new CToolbarsPage;
	m_pKeyboardPage = new CKeyboardPage;
	m_pMenuPage = new CMenuPage;
	m_pMousePage = new CMousePage;

	ASSERT (pWndParent != NULL);
	m_pParentWnd = pWndParent;

	//---------------------------------------
	// Add two main pages (available always):
	//---------------------------------------
	AddPage (m_pCustomizePage);
	AddPage (m_pToolbarsPage);

	//---------------------------------------------------------
	// Add keyboard customization page (available only if
	// the main application windows accelerator table is exist):
	//---------------------------------------------------------
	CFrameWnd* pWndMain = DYNAMIC_DOWNCAST (CFrameWnd, AfxGetMainWnd ());
	if (g_pKeyboardManager != NULL && pWndMain != NULL &&
		pWndMain->m_hAccelTable != NULL)
	{
		AddPage (m_pKeyboardPage);
	}

	//---------------------------------------------------------------
	// Add menu customization page (available only if the menu bar or
	// context menu manager are available):
	//---------------------------------------------------------------
	BOOL bMenuBarIsAvailable = FALSE;

	CBCGMDIFrameWnd* pMainMDIFrame = DYNAMIC_DOWNCAST (CBCGMDIFrameWnd, AfxGetMainWnd ());
	if (pMainMDIFrame != NULL)
	{
		bMenuBarIsAvailable = (pMainMDIFrame->IsMenuBarAvailable ());
	}
	else
	{
		CBCGFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGFrameWnd, AfxGetMainWnd ());
		if (pMainFrame != NULL)
		{
			bMenuBarIsAvailable = (pMainFrame->IsMenuBarAvailable ());
		}
	}

	if (g_pContextMenuManager != NULL || bMenuBarIsAvailable)
	{	
		AddPage (m_pMenuPage);
	}

	if (g_pMouseManager != NULL)
	{
		AddPage (m_pMousePage);
	}

	//----------------------------
	// Set property sheet caption:
	//----------------------------
	CString strCaption;
	strCaption.LoadString (IDS_BCGBARRES_PROPSHT_CAPTION);

	m_strAllCommands.LoadString (IDS_BCGBARRES_ALL_COMMANDS);
	m_pCustomizePage->SetAllCategory (m_strAllCommands);

	SetTitle (strCaption);

	if (m_bAutoSetFromMenus)
	{
		SetupFromMenus ();
	}
}
//**************************************************************************************
CBCGToolbarCustomize::~CBCGToolbarCustomize()
{
	POSITION pos = m_ButtonsByCategory.GetStartPosition();
	while (pos != NULL)
	{
		CObList* pCategoryButtonsList;
		CString string;
		
		m_ButtonsByCategory.GetNextAssoc (pos, string, pCategoryButtonsList);
		ASSERT_VALID(pCategoryButtonsList);

		while (!pCategoryButtonsList->IsEmpty ())
		{
			delete pCategoryButtonsList->RemoveHead ();
		}

		delete pCategoryButtonsList;
	}

	m_ButtonsByCategory.RemoveAll();

	delete m_pCustomizePage;
	delete m_pToolbarsPage;
	delete m_pKeyboardPage;
	delete m_pMenuPage;
	delete m_pMousePage;
}

BEGIN_MESSAGE_MAP(CBCGToolbarCustomize, CPropertySheet)
	//{{AFX_MSG_MAP(CBCGToolbarCustomize)
	ON_WM_CREATE()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarCustomize message handlers

int CBCGToolbarCustomize::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	
	g_pWndCustomize = this;
	SetFrameCustMode (TRUE);

	return 0;
}
//**************************************************************************************
void CBCGToolbarCustomize::PostNcDestroy()
{
	g_pWndCustomize = NULL;
	SetFrameCustMode (FALSE);

	CPropertySheet::PostNcDestroy();
	delete this;
}
//**************************************************************************************
void CBCGToolbarCustomize::AddButton (UINT uiCategoryId, const CBCGToolbarButton& button,
				int iInsertAfter)
{
	CString strCategory;
	strCategory.LoadString (uiCategoryId);

	AddButton (strCategory, button, iInsertAfter);
}
//**************************************************************************************
void CBCGToolbarCustomize::AddButton (LPCTSTR lpszCategory, const CBCGToolbarButton& button,
										int iInsertAfter)
{
	int iId = (int) button.m_nID;

	if ((iId >= ID_FILE_MRU_FILE1 &&
		iId <= ID_FILE_MRU_FILE16) ||
		(iId >= 0xF000 && iId < 0xF1F0) || // max of 31 SC_s
		iId >= AFX_IDM_FIRST_MDICHILD)      // 0xFF00
	{
		//-------------------------------------------
		// Don't add MRU, system and Window commands:
		//-------------------------------------------
		return;
	}

	if (!CBCGToolBar::IsCommandPermitted (button.m_nID))
	{
		return;
	}

	CString strText = button.m_strText;
	if (strText.IsEmpty ())
	{
		//-------------------------------------------
		// Try to find the command name in resources:
		//-------------------------------------------
		CString strMessage;
		int iOffset;
		if (strMessage.LoadString (button.m_nID) &&
			(iOffset = strMessage.Find (_T('\n'))) != -1)
		{
			strText = strMessage.Mid (iOffset + 1);
		}

		if (strText.IsEmpty () && lpszCategory == m_strAllCommands)
		{
			return;
		}
	}
	else
	{
		strText.Remove (_T('&'));

		//----------------------------------------
		// Remove trailing label (ex.:"\tCtrl+S"):
		//----------------------------------------
		int iOffset = strText.Find (_T('\t'));
		if (iOffset != -1)
		{
			strText = strText.Left (iOffset);
		}
	}
	
	//--------------------------------------------------
	// Find a category entry or create new if not exist:
	//--------------------------------------------------
	CObList* pCategoryButtonsList;
	if (!m_ButtonsByCategory.Lookup (lpszCategory, pCategoryButtonsList))
	{
		//--------------------------------
		// Category not found! Create new:
		//--------------------------------
		pCategoryButtonsList = new CObList;
		m_ButtonsByCategory.SetAt (lpszCategory, pCategoryButtonsList);

		if (lpszCategory != m_strAllCommands)
		{
			m_strCategoriesList.AddTail (lpszCategory);
		}
	}
	else
	{
		//--------------------------------------------------------
		// Category is not a new. Maybe the button is exist also?
		//--------------------------------------------------------
		ASSERT (pCategoryButtonsList != NULL);

		for (POSITION pos = pCategoryButtonsList->GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) pCategoryButtonsList->GetNext (pos);
			ASSERT (pButton != NULL);

			if (pButton->m_nID == button.m_nID)	// The same exist...
			{
				if (pButton->m_strText.IsEmpty ())
				{
					pButton->m_strText = button.m_strText;
				}

				return;
			}
		}
	}

	//-------------------------------------------------------------------
	// Create a new CBCGToolbarButton object (MFC class factory is used):
	//-------------------------------------------------------------------
	CRuntimeClass* pClass = button.GetRuntimeClass ();
	ASSERT (pClass != NULL);

	CBCGToolbarButton* pButton = (CBCGToolbarButton*) pClass->CreateObject ();
	ASSERT_VALID (pButton);

	pButton->CopyFrom (button);
	pButton->m_strText = strText;

	//-------------------------------------------
	// Add a new button to the specific category:
	//-------------------------------------------
	BOOL bInserted = FALSE;
	if (iInsertAfter != -1)
	{
		POSITION pos = pCategoryButtonsList->FindIndex (iInsertAfter);
		if (pos != NULL)
		{
			pCategoryButtonsList->InsertBefore (pos, pButton);
			bInserted = TRUE;
		}
	}

	if (!bInserted)
	{
		pCategoryButtonsList->AddTail (pButton);
	}

	if (lpszCategory != m_strAllCommands)
	{
		AddButton (m_strAllCommands, button);
	}

	pButton->OnAddToCustomizePage ();
}
//**************************************************************************************
int CBCGToolbarCustomize::RemoveButton (UINT uiCategoryId, UINT uiCmdId)
{
	CString strCategory;
	strCategory.LoadString (uiCategoryId);

	return RemoveButton (strCategory, uiCmdId);
}
//**************************************************************************************
int CBCGToolbarCustomize::RemoveButton (LPCTSTR lpszCategory, UINT uiCmdId)
{
	ASSERT (lpszCategory != NULL);

	CObList* pCategoryButtonsList;
	if (!m_ButtonsByCategory.Lookup (lpszCategory, pCategoryButtonsList))
	{
		// Category not found!
		return -1;
	}

	int i = 0;
	for (POSITION pos = pCategoryButtonsList->GetHeadPosition (); pos != NULL; i ++)
	{
		POSITION posSave = pos;

		CBCGToolbarButton* pButton = (CBCGToolbarButton*) pCategoryButtonsList->GetNext (pos);
		ASSERT (pButton != NULL);

		if (pButton->m_nID == uiCmdId)
		{
			pCategoryButtonsList->RemoveAt (posSave);
			delete pButton;
			return i;
		}
	}

	return -1;
}
//**************************************************************************************
BOOL CBCGToolbarCustomize::AddToolBar (UINT uiCategory, UINT uiToolbarResId)
{
	CString strCategory;
	strCategory.LoadString (uiCategory);

	return AddToolBar (strCategory, uiToolbarResId);
}
//**************************************************************************************
BOOL CBCGToolbarCustomize::AddToolBar (LPCTSTR lpszCategory, UINT uiToolbarResId)
{
	struct CToolBarData
	{
		WORD wVersion;
		WORD wWidth;
		WORD wHeight;
		WORD wItemCount;

		WORD* items()
			{ return (WORD*)(this+1); }
	};

	LPCTSTR lpszResourceName = MAKEINTRESOURCE (uiToolbarResId);
	ASSERT(lpszResourceName != NULL);

	//---------------------------------------------------
	// determine location of the bitmap in resource fork:
	//---------------------------------------------------
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, RT_TOOLBAR);
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
	if (hRsrc == NULL)
	{
		TRACE(_T("CBCGToolbarCustomize::AddToolBar: Can't load toolbar %x\n"), uiToolbarResId);
		return FALSE;
	}

	HGLOBAL hGlobal = ::LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
	{
		TRACE(_T("CBCGToolbarCustomize::AddToolBar: Can't load toolbar %x\n"), uiToolbarResId);
		return FALSE;
	}

	CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
	if (pData == NULL)
	{
		TRACE(_T("CBCGToolbarCustomize::AddToolBar: Can't load toolbar %x\n"), uiToolbarResId);
		::FreeResource (hGlobal);
		return FALSE;
	}

	ASSERT (pData->wVersion == 1);

	for (int i = 0; i < pData->wItemCount; i++)
	{
		UINT uiCmd = pData->items() [i];
		if (uiCmd > 0 && uiCmd != (UINT) -1)
		{
			AddButton (lpszCategory, CBCGToolbarButton (uiCmd, -1));
		}
	}

	::UnlockResource (hGlobal);
	::FreeResource (hGlobal);

	return TRUE;
}
//**************************************************************************************
BOOL CBCGToolbarCustomize::AddMenu (UINT uiMenuResId)
{
	CMenu menu;
	if (!menu.LoadMenu (uiMenuResId))
	{
		TRACE(_T("CBCGToolbarCustomize::AddMenu: Can't load menu %x\n"), uiMenuResId);
		return FALSE;
	}

	AddMenuCommands (&menu, FALSE);
	return TRUE;
}
//**************************************************************************************
void CBCGToolbarCustomize::ReplaceButton (UINT uiCmd, const CBCGToolbarButton& button)
{
	CRuntimeClass* pClass = button.GetRuntimeClass ();
	ASSERT (pClass != NULL);

	for (POSITION posCategory = m_strCategoriesList.GetHeadPosition(); 
		posCategory != NULL;)
	{
		CString strCategory = m_strCategoriesList.GetNext (posCategory);

		CObList* pCategoryButtonsList;
		if (!m_ButtonsByCategory.Lookup (strCategory, pCategoryButtonsList))
		{
			ASSERT (FALSE);
		}

		ASSERT_VALID (pCategoryButtonsList);

		for (POSITION pos = pCategoryButtonsList->GetHeadPosition (); pos != NULL;)
		{
			POSITION posSave = pos;
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) pCategoryButtonsList->GetNext (pos);
			ASSERT (pButton != NULL);

			if (pButton->m_nID == uiCmd)	// Found!
			{
				CBCGToolbarButton* pNewButton = (CBCGToolbarButton*) pClass->CreateObject ();
				ASSERT_VALID (pNewButton);

				pNewButton->CopyFrom (button);
				if (pNewButton->m_strText.IsEmpty ())
				{
					pNewButton->m_strText = pButton->m_strText;
				}

				pCategoryButtonsList->SetAt (posSave, pNewButton);
				delete pButton;
			}
		}
	}
}
//**************************************************************************************
BOOL CBCGToolbarCustomize::SetUserCategory (LPCTSTR lpszCategory)
{
	ASSERT (lpszCategory != NULL);

	CObList* pCategoryButtonsList;
	if (!m_ButtonsByCategory.Lookup (lpszCategory, pCategoryButtonsList))
	{
		TRACE(_T("CBCGToolbarCustomize::SetUserCategory: Can't find category '%s'\n"), 
			lpszCategory);
		return FALSE;
	}

	m_pCustomizePage->SetUserCategory (lpszCategory);
	return TRUE;
}
//**************************************************************************************
void CBCGToolbarCustomize::SetFrameCustMode (BOOL bCustMode)
{
	ASSERT_VALID (m_pParentWnd);

	//-------------------------------------------------------------------
	// Enable/disable all parent frame child windows (except docking bars
	// and our toolbars):
	//-------------------------------------------------------------------
	CWnd* pWndChild = m_pParentWnd->GetWindow (GW_CHILD);
	while (pWndChild != NULL)
	{
		CRuntimeClass* pChildClass = pWndChild->GetRuntimeClass ();
		if (pChildClass == NULL ||
			(!pChildClass->IsDerivedFrom (RUNTIME_CLASS (CDockBar)) &&
		#if _MSC_VER >= 1200
			!pChildClass->IsDerivedFrom (RUNTIME_CLASS (CReBar)) &&
		#endif	// _MSC_VER
			 !pChildClass->IsDerivedFrom (RUNTIME_CLASS (CBCGToolBar))))
		{
			pWndChild->EnableWindow (!bCustMode);
		}

		pWndChild = pWndChild->GetNextWindow ();
	}

	//-----------------------------------------------
	// Set/reset costumize mode for ALL our toolbars:
	//-----------------------------------------------
	CBCGToolBar::SetCustomizeMode (bCustMode);

	//-------------------------------------------------------------
	// Inform the parent frame about mode (for additional actions):
	//-------------------------------------------------------------
	m_pParentWnd->SendMessage (BCGM_CUSTOMIZETOOLBAR, (WPARAM) bCustMode);
}
//**************************************************************************************
BOOL CBCGToolbarCustomize::Create () 
{
	CBCGLocalResource locaRes;
	return CPropertySheet::Create (m_pParentWnd);
}
//*************************************************************************************
void CBCGToolbarCustomize::ShowToolBar (CBCGToolBar* pToolBar, BOOL bShow)
{
	m_pToolbarsPage->ShowToolBar (pToolBar, bShow);
}
//*************************************************************************************
BOOL CBCGToolbarCustomize::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	//----------------------
	// Show "Cancel" button:
	//----------------------
	CWnd *pWndCancel = GetDlgItem (IDCANCEL);
	if (pWndCancel == NULL)
	{
		return bResult;
	}

    pWndCancel->ShowWindow (SW_SHOW);
    pWndCancel->EnableWindow ();

	CRect rectClientCancel;
	pWndCancel->GetClientRect (&rectClientCancel);
	pWndCancel->MapWindowPoints (this, &rectClientCancel);

	//-------------------------------
	// Enlarge property sheet window:
	//-------------------------------
	CRect rectWnd;
	GetWindowRect(rectWnd);	

	SetWindowPos(NULL, 0, 0,
		rectWnd.Width (),
		rectWnd.Height () + rectClientCancel.Height () + 2 * iButtonMargin,
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	//-------------------------------------------------
	// Move "Cancel" button to the right bottom corner:
	//-------------------------------------------------
	pWndCancel->SetWindowPos (NULL, 
		rectClient.right - rectClientCancel.Width () - iButtonMargin,
		rectClientCancel.top + iButtonMargin / 2,
		0, 0,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

	//---------------------------------------------------
	// Change "Cancel" button's style to "DEFPUSHBUTTON":
	//---------------------------------------------------
	CWnd *pWndOk = GetDlgItem (IDOK);
	if (pWndOk != NULL)
	{
		pWndOk->ModifyStyle (BS_DEFPUSHBUTTON, 0);
	}

	pWndCancel->ModifyStyle (0, BS_DEFPUSHBUTTON);

	//--------------------------------------------------------
	// Replace "Cancel" text to "Close" 
	// (CPropertyPage::CancelToClose method does nothing in a 
	// modeless property sheet):
	//--------------------------------------------------------
	CBCGLocalResource locaRes;

	CString strCloseText;
	strCloseText.LoadString (IDS_BCGBARRES_CLOSE);

	pWndCancel->SetWindowText (strCloseText);

	//------------------------
	// Adjust the Help button:
	//------------------------
	CButton *pWndHelp = (CButton*) GetDlgItem (IDHELP);
	if (pWndHelp == NULL)
	{
		return bResult;
	}

	pWndHelp->ShowWindow (SW_SHOW);
	pWndHelp->EnableWindow ();

	//-----------------------
	// Set Help button image:
	//-----------------------
	LPCTSTR lpszResourceName = MAKEINTRESOURCE (IDB_BCGBARRES_HELP);
	ASSERT(lpszResourceName != NULL);

	HBITMAP hbmpHelp = (HBITMAP) ::LoadImage (
		AfxFindResourceHandle (lpszResourceName, RT_BITMAP),
		lpszResourceName,
		IMAGE_BITMAP,
		0, 0,
		LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);
	ASSERT (hbmpHelp != NULL);

	pWndHelp->ModifyStyle (0, BS_BITMAP);
	pWndHelp->SetBitmap (hbmpHelp);

	//-------------------------------------------------
	// Move "Help" button to the left bottom corner and
	// adjust its size by the bitmap size:
	//-------------------------------------------------
	BITMAP bmp;
	::GetObject (hbmpHelp, sizeof (BITMAP), &bmp);
	
	pWndHelp->SetWindowPos (NULL, 
		rectClient.left + iButtonMargin,
		rectClientCancel.top,
		bmp.bmWidth + iButtonMargin, bmp.bmHeight + iButtonMargin,
		SWP_NOZORDER | SWP_NOACTIVATE);

	if (!m_bAutoSetFromMenus)
	{
		SetupFromMenus ();
	}

	return bResult;
}
//************************************************************************************
BOOL CBCGToolbarCustomize::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch (LOWORD (wParam))
	{
	case IDCANCEL:
		DestroyWindow ();
		return TRUE;

	case IDHELP:
		ASSERT_VALID (m_pParentWnd);
		m_pParentWnd->SendMessage (BCGM_CUSTOMIZEHELP, GetActiveIndex (), (LPARAM) this);
		return TRUE;
	}
		
	return CPropertySheet::OnCommand(wParam, lParam);
}
//************************************************************************************
void CBCGToolbarCustomize::EnableUserDefinedToolbars (BOOL bEnable)
{
	m_pToolbarsPage->EnableUserDefinedToolbars (bEnable);
}
//******************************************************************************************
void CBCGToolbarCustomize::AddMenuCommands (const CMenu* pMenu, BOOL bPopup, LPCTSTR lpszCategory)
{
	ASSERT (pMenu != NULL);

	int iCount = (int) pMenu->GetMenuItemCount ();
	for (int i = 0; i < iCount; i ++)
	{
		UINT uiCmd = pMenu->GetMenuItemID (i);

		CString strText;
		pMenu->GetMenuString (i, strText, MF_BYPOSITION);

		strText.Remove (_T('&'));

		switch (uiCmd)
		{
		case 0:		// Separator, ignore it.
			break;

		case -1:	// Submenu
			{
				CMenu* pSubMenu = pMenu->GetSubMenu (i);

				CString strCategory = strText;
				if (lpszCategory != NULL)
				{
					strCategory = lpszCategory;
				}

				if (m_bAutoSetFromMenus)
				{
					if (bPopup)
					{
						AddButton (strCategory, 
							CBCGToolbarMenuButton ((UINT) -1, pSubMenu->GetSafeHmenu (),
							-1,
							strText));
					}

					AddMenuCommands (pSubMenu, TRUE, strCategory);
				}
				else
				{
					AddMenuCommands (pSubMenu, TRUE);
				}

			}
			break;

		default:
			AddButton (lpszCategory == NULL ?
						m_strAllCommands : lpszCategory, 
						CBCGToolbarButton (uiCmd, -1, strText));
		}
	}
}
//******************************************************************************************
void CBCGToolbarCustomize::FillCategotiesComboBox (CComboBox& wndCategory) const
{
	CObList* pCategoryButtonsList;

	for (POSITION pos = m_strCategoriesList.GetHeadPosition(); pos != NULL;)
	{
		CString strCategory = m_strCategoriesList.GetNext (pos);

		if (!m_ButtonsByCategory.Lookup (strCategory, pCategoryButtonsList))
		{
			ASSERT (FALSE);
		}

		ASSERT_VALID (pCategoryButtonsList);

		int iIndex = wndCategory.AddString (strCategory);
		wndCategory.SetItemData (iIndex, (DWORD) pCategoryButtonsList);
	}

	// "All" category should be last!
	if (!m_ButtonsByCategory.Lookup (m_strAllCommands, pCategoryButtonsList))
	{
		ASSERT (FALSE);
	}

	ASSERT_VALID (pCategoryButtonsList);

	int iIndex = wndCategory.AddString (m_strAllCommands);
	wndCategory.SetItemData (iIndex, (DWORD) pCategoryButtonsList);
}
//******************************************************************************************
void CBCGToolbarCustomize::FillCategotiesListBox (CListBox& wndCategory) const
{
	CObList* pCategoryButtonsList;

	for (POSITION pos = m_strCategoriesList.GetHeadPosition(); pos != NULL;)
	{
		CString strCategory = m_strCategoriesList.GetNext (pos);

		if (!m_ButtonsByCategory.Lookup (strCategory, pCategoryButtonsList))
		{
			ASSERT (FALSE);
		}

		ASSERT_VALID (pCategoryButtonsList);

		int iIndex = wndCategory.AddString (strCategory);
		wndCategory.SetItemData (iIndex, (DWORD) pCategoryButtonsList);
	}

	// "All" category should be last!
	if (!m_ButtonsByCategory.Lookup (m_strAllCommands, pCategoryButtonsList))
	{
		ASSERT (FALSE);
	}

	ASSERT_VALID (pCategoryButtonsList);

	int iIndex = wndCategory.AddString (m_strAllCommands);
	wndCategory.SetItemData (iIndex, (DWORD) pCategoryButtonsList);
}
//*******************************************************************************************
void CBCGToolbarCustomize::FillAllCommandsList (CListBox& wndListOfCommands) const
{
	wndListOfCommands.ResetContent ();

	CObList* pAllButtonsList;
	if (!m_ButtonsByCategory.Lookup (m_strAllCommands, pAllButtonsList))
	{
		return;
	}

	ASSERT_VALID (pAllButtonsList);

	for (POSITION pos = pAllButtonsList->GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) pAllButtonsList->GetNext (pos);
		ASSERT (pButton != NULL);

		int iIndex = wndListOfCommands.AddString (pButton->m_strText);
		wndListOfCommands.SetItemData (iIndex, (DWORD) pButton->m_nID);
	}
}
//***************************************************************************************
BOOL CBCGToolbarCustomize::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
{
	ASSERT_VALID (m_pParentWnd);
	m_pParentWnd->SendMessage (BCGM_CUSTOMIZEHELP, GetActiveIndex (), (LPARAM) this);
	
	return TRUE;
}
//***************************************************************************************
LPCTSTR CBCGToolbarCustomize::GetCommandName (UINT uiCmd) const
{
	CObList* pAllButtonsList;
	if (!m_ButtonsByCategory.Lookup (m_strAllCommands, pAllButtonsList))
	{
		return NULL;
	}

	ASSERT_VALID (pAllButtonsList);

	for (POSITION pos = pAllButtonsList->GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) pAllButtonsList->GetNext (pos);
		ASSERT (pButton != NULL);

		if (pButton->m_nID == uiCmd)
		{
			return pButton->m_strText;
		}
	}

	return NULL;
}
//***************************************************************************************
void CBCGToolbarCustomize::SetupFromMenus ()
{
	//-------------------------------------------------------------------
	// Find all application document templates and add menu items to the
	// "All commands" category:
	//------------------------------------------------------------------
	CDocManager* pDocManager = AfxGetApp ()->m_pDocManager;
	if (pDocManager != NULL)
	{
		//---------------------------------------
		// Walk all templates in the application:
		//---------------------------------------
		for (POSITION pos = pDocManager->GetFirstDocTemplatePosition (); pos != NULL;)
		{
			CMultiDocTemplate* pTemplate = 
				DYNAMIC_DOWNCAST (	CMultiDocTemplate, 
									pDocManager->GetNextDocTemplate (pos));
			if (pTemplate != NULL)
			{
				CMenu* pDocMenu = CMenu::FromHandle (pTemplate->m_hMenuShared);
				if (pDocMenu != NULL)
				{
					AddMenuCommands (pDocMenu, FALSE);
				}
			}
		}
	}

	//------------------------------------
	// Add commands from the default menu:
	//------------------------------------
	CFrameWnd* pWndMain = DYNAMIC_DOWNCAST (CFrameWnd, AfxGetMainWnd ());
	if (pWndMain != NULL)
	{
		CMenu* pFrameMenu = CMenu::FromHandle (pWndMain->m_hMenuDefault);
		if (pFrameMenu == NULL)
		{
			CBCGMDIFrameWnd* pMainMDIFrame = DYNAMIC_DOWNCAST (CBCGMDIFrameWnd, pWndMain);
			const CBCGMenuBar* pMenuBar = NULL;

			if (pMainMDIFrame != NULL)
			{
				pMenuBar = pMainMDIFrame->GetMenuBar ();
			}
			else
			{
				CBCGFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGFrameWnd, pWndMain);
				if (pMainFrame != NULL)
				{
					pMenuBar = pMainFrame->GetMenuBar ();
				}
			}

			if (pMenuBar != NULL)
			{
				pFrameMenu = CMenu::FromHandle (pMenuBar->GetDefaultMenu ());
			}
		}

		if (pFrameMenu != NULL)
		{
			AddMenuCommands (pFrameMenu, FALSE);
		}
	}
}
