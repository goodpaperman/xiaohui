// CBCGToolbarCustomizePages.cpp : implementation file
//

#include "stdafx.h"
#include <afxpriv.h>
#include "bcgbarres.h"
#include "CBCGToolbarCustomize.h"
#include "CBCGToolbarCustomizePages.h"
#include "BCGtoolbar.h"
#include "BCGToolbarButton.h"
#include "bcglocalres.h"
#include "BCGPopupMenuBar.h"
#include "ToolbarNameDlg.h"
#include "ImageHash.h"
#include "BCGMDIFrameWnd.h"
#include "BCGFrameWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CCustomizePage, CPropertyPage)
IMPLEMENT_DYNCREATE(CToolbarsPage, CPropertyPage)

extern CObList	gAllToolbars;

/////////////////////////////////////////////////////////////////////////////
// CCustomizePage property page

CCustomizePage::CCustomizePage() : CPropertyPage(CCustomizePage::IDD)
{
	//{{AFX_DATA_INIT(CCustomizePage)
	m_strButtonDescription = _T("");
	//}}AFX_DATA_INIT
}

CCustomizePage::~CCustomizePage()
{
}

void CCustomizePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizePage)
	DDX_Control(pDX, IDC_BCGBARRES_CATEGORY, m_wndCategory);
	DDX_Control(pDX, IDC_BCGBARRES_USER_TOOLS, m_wndTools);
	DDX_Text(pDX, IDC_BCGBARRES_BUTTON_DESCR, m_strButtonDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizePage, CPropertyPage)
	//{{AFX_MSG_MAP(CCustomizePage)
	ON_LBN_SELCHANGE(IDC_BCGBARRES_USER_TOOLS, OnSelchangeUserTools)
	ON_LBN_SELCHANGE(IDC_BCGBARRES_CATEGORY, OnSelchangeCategory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCustomizePage::OnSelchangeCategory() 
{
	UpdateData ();

	int iIndex = m_wndCategory.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		ASSERT (FALSE);
		return;
	}

	m_wndTools.ResetContent ();

	//------------------------------------------
	// Only "All commands" list shoud be sorted!
	//------------------------------------------
	CString strCategory;
	m_wndCategory.GetText (iIndex, strCategory);

	BOOL bAllCommands =  (strCategory == m_strAllCategory);

	OnChangeSelButton (NULL);

	CObList* pCategoryButtonsList = 
		(CObList*) m_wndCategory.GetItemData (iIndex);
	ASSERT_VALID (pCategoryButtonsList);

	for (POSITION pos = pCategoryButtonsList->GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) pCategoryButtonsList->GetNext (pos);
		ASSERT (pButton != NULL);

		pButton->m_bUserButton = (g_ImageHash.Get (pButton->m_nID, FALSE) == -1);

		int iIndex = -1;
		
		if (bAllCommands)
		{
			for (int i = 0; iIndex == -1 && i < m_wndTools.GetCount (); i ++)
			{
				CString strCommand;
				m_wndTools.GetText (i, strCommand);

				if (strCommand > pButton->m_strText)
				{
					iIndex = m_wndTools.InsertString (i, pButton->m_strText);
				}
			}
		}

		if (iIndex == -1)	// Not inserted yet
		{
			iIndex = m_wndTools.AddString (pButton->m_strText);
		}

		m_wndTools.SetItemData (iIndex, (DWORD) pButton);
	}

	m_wndTools.EnableWindow ();
}
//**************************************************************************************
void CCustomizePage::OnSelchangeUserTools() 
{
	int iIndex = m_wndTools.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		OnChangeSelButton (NULL);
	}
	else
	{
		OnChangeSelButton ((CBCGToolbarButton*) m_wndTools.GetItemData (iIndex));
	}
}
//**************************************************************************************
BOOL CCustomizePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CBCGToolbarCustomize* pWndParent = DYNAMIC_DOWNCAST (CBCGToolbarCustomize, GetParent ());
	ASSERT (pWndParent != NULL);

	pWndParent->FillCategotiesListBox (m_wndCategory);
	
	m_wndCategory.SetCurSel (0);
	OnSelchangeCategory ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//**********************************************************************************************
void CCustomizePage::OnChangeSelButton (CBCGToolbarButton* pSelButton)
{
	m_strButtonDescription = _T("");

	if (pSelButton != NULL)
	{
		if (pSelButton->m_nID == 0)
		{
			m_strButtonDescription = pSelButton->m_strText;
		}
		else
		{
			CFrameWnd* pParent = GetParentFrame ();
			if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
			{
				pParent->GetMessageString (pSelButton->m_nID,
							m_strButtonDescription);
			}
		}
	}

	m_pSelButton = pSelButton;
	UpdateData (FALSE);
}
//*************************************************************************************
void CCustomizePage::SetUserCategory (LPCTSTR lpszCategory)
{
	ASSERT (lpszCategory != NULL);
	m_strUserCategory = lpszCategory;
}
//*************************************************************************************
void CCustomizePage::SetAllCategory (LPCTSTR lpszCategory)
{
	ASSERT (lpszCategory != NULL);
	m_strAllCategory = lpszCategory;
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarsPage property page

CToolbarsPage::CToolbarsPage() : 
	CPropertyPage(CToolbarsPage::IDD),
	m_bUserDefinedToolbars (FALSE)
{
	//{{AFX_DATA_INIT(CToolbarsPage)
	m_bShowTooltips = CBCGToolBar::m_bShowTooltips;
	m_bShowShortcutKeys = CBCGToolBar::m_bShowShortcutKeys;
	//}}AFX_DATA_INIT

	m_pSelectedToolbar = NULL;
}

CToolbarsPage::~CToolbarsPage()
{
}

void CToolbarsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolbarsPage)
	DDX_Control(pDX, IDC_BCGBARRES_SHOW_TOOLTIPS_WITH_KEYS, m_wndShowShortcutKeys);
	DDX_Control(pDX, IDC_BCGBARRES_RENAME_TOOLBAR, m_bntRenameToolbar);
	DDX_Control(pDX, IDC_BCGBARRES_NEW_TOOLBAR, m_btnNewToolbar);
	DDX_Control(pDX, IDC_BCGBARRES_DELETE_TOOLBAR, m_btnDelete);
	DDX_Control(pDX, IDC_BCGBARRES_RESET, m_btnReset);
	DDX_Control(pDX, IDC_BCGBARRES_TOOLBAR_LIST, m_wndToobarList);
	DDX_Check(pDX, IDC_BCGBARRES_SHOW_TOOLTIPS, m_bShowTooltips);
	DDX_Check(pDX, IDC_BCGBARRES_SHOW_TOOLTIPS_WITH_KEYS, m_bShowShortcutKeys);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolbarsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CToolbarsPage)
	ON_LBN_SELCHANGE(IDC_BCGBARRES_TOOLBAR_LIST, OnSelchangeToolbarList)
	ON_LBN_DBLCLK(IDC_BCGBARRES_TOOLBAR_LIST, OnDblclkToolbarList)
	ON_BN_CLICKED(IDC_BCGBARRES_SHOW_TOOLTIPS, OnShowTooltips)
	ON_BN_CLICKED(IDC_BCGBARRES_RESET, OnReset)
	ON_BN_CLICKED(IDC_BCGBARRES_RESET_ALL, OnResetAll)
	ON_BN_CLICKED(IDC_BCGBARRES_DELETE_TOOLBAR, OnDeleteToolbar)
	ON_BN_CLICKED(IDC_BCGBARRES_NEW_TOOLBAR, OnNewToolbar)
	ON_BN_CLICKED(IDC_BCGBARRES_RENAME_TOOLBAR, OnRenameToolbar)
	ON_BN_CLICKED(IDC_BCGBARRES_SHOW_TOOLTIPS_WITH_KEYS, OnShowTooltipsWithKeys)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CToolbarsPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if (!m_bUserDefinedToolbars)
	{
		m_btnNewToolbar.EnableWindow (FALSE);

		m_btnNewToolbar.ShowWindow (SW_HIDE);
		m_btnDelete.ShowWindow (SW_HIDE);
		m_bntRenameToolbar.ShowWindow (SW_HIDE);
	}
	
    m_wndToobarList.ResetContent(); 
	for (POSITION pos = gAllToolbars.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (pos);
		ASSERT_VALID(pToolBar);

		if (!pToolBar->IsKindOf (RUNTIME_CLASS (CBCGPopupMenuBar)))
		{
			CString strName;
			pToolBar->GetWindowText (strName);

			if (strName.IsEmpty ())
			{
				CBCGLocalResource locaRes;
				strName.LoadString (IDS_BCGBARRES_UNTITLED_TOOLBAR);
			}

			int iIndex = m_wndToobarList.AddString (strName);
			m_wndToobarList.SetItemData (iIndex, (DWORD) pToolBar);

			if (pToolBar->GetStyle () & WS_VISIBLE)
			{
				m_wndToobarList.SetCheck (iIndex, 1);
			}

			m_wndToobarList.EnableCheck (iIndex, pToolBar->CanBeClosed ());
            //m_wndToobarList.Enable(iIndex, pToolBar->CanBeClosed()); 
		}
	}

	m_wndShowShortcutKeys.EnableWindow (m_bShowTooltips);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//*************************************************************************************
void CToolbarsPage::OnSelchangeToolbarList() 
{
	int iIndex = m_wndToobarList.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		m_pSelectedToolbar = NULL;
		m_btnReset.EnableWindow (FALSE);
		m_btnDelete.EnableWindow (FALSE);
		m_bntRenameToolbar.EnableWindow (FALSE);

		return;
	}

	m_pSelectedToolbar = (CBCGToolBar*) m_wndToobarList.GetItemData (iIndex);
	ASSERT_VALID(m_pSelectedToolbar);

	m_btnReset.EnableWindow (m_pSelectedToolbar->CanBeRestored ());
	m_btnDelete.EnableWindow (IsUserDefinedToolBar (m_pSelectedToolbar));
	m_bntRenameToolbar.EnableWindow (IsUserDefinedToolBar (m_pSelectedToolbar));
}
//*************************************************************************************
void CToolbarsPage::OnDblclkToolbarList() 
{
	int iIndex = m_wndToobarList.GetCurSel ();
	if (iIndex != LB_ERR)
	{
		m_pSelectedToolbar = (CBCGToolBar*) m_wndToobarList.GetItemData (iIndex);
		ASSERT_VALID(m_pSelectedToolbar);

		if (m_pSelectedToolbar->CanBeClosed ())
		{
			m_wndToobarList.SetCheck (iIndex, !m_wndToobarList.GetCheck (iIndex));
		}
		else
		{
			MessageBeep ((UINT) -1);
		}
	}

	OnSelchangeToolbarList ();
}
//*************************************************************************************
void CToolbarsPage::ShowToolBar (CBCGToolBar* pToolBar, BOOL bShow)
{
	if (m_wndToobarList.GetSafeHwnd () == NULL)
	{
		return;
	}

	for (int i = 0; i < m_wndToobarList.GetCount (); i ++)
	{
		CBCGToolBar* pListToolBar = (CBCGToolBar*) m_wndToobarList.GetItemData (i);
		ASSERT_VALID(pListToolBar);

		if (pListToolBar == pToolBar)
		{
			m_wndToobarList.SetCheck (i, bShow);
			break;
		}
	}
}
//**************************************************************************************
void CToolbarsPage::OnShowTooltips() 
{
	UpdateData ();

	CBCGToolBar::m_bShowTooltips = m_bShowTooltips;
	m_wndShowShortcutKeys.EnableWindow (m_bShowTooltips);
}
//**************************************************************************************
void CToolbarsPage::OnReset() 
{
	ASSERT (m_pSelectedToolbar != NULL);
	ASSERT (m_pSelectedToolbar->CanBeRestored ());

	{
		CBCGLocalResource locaRes;

		CString strName;
		m_pSelectedToolbar->GetWindowText (strName);

		CString strPrompt;
		strPrompt.Format (IDS_BCGBARRES_RESET_TOOLBAR_FMT, strName);

		if (MessageBox (strPrompt, NULL, MB_YESNO | MB_ICONQUESTION) != IDYES)
		{
			return;
		}
	}

	m_pSelectedToolbar->RestoreOriginalstate ();
}
//**************************************************************************************
void CToolbarsPage::OnResetAll() 
{
	{
		CBCGLocalResource locaRes;
		if (AfxMessageBox (IDS_BCGBARRES_RESET_ALL_TOOLBARS, MB_YESNO | MB_ICONQUESTION) != IDYES)
		{
			return;
		}
	}

	g_ImageHash.ClearAll ();

	for (int i = 0; i < m_wndToobarList.GetCount (); i ++)
	{
		CBCGToolBar* pListToolBar = (CBCGToolBar*) m_wndToobarList.GetItemData (i);
		ASSERT_VALID(pListToolBar);

		if (pListToolBar->CanBeRestored ())
		{
			pListToolBar->RestoreOriginalstate ();
		}
	}
}
//**********************************************************************************
void CToolbarsPage::OnDeleteToolbar() 
{
	ASSERT (m_pSelectedToolbar != NULL);
	ASSERT (IsUserDefinedToolBar (m_pSelectedToolbar));

	CFrameWnd* pParentFrame = GetParentFrame ();
	if (pParentFrame == NULL)
	{
		MessageBeep (MB_ICONASTERISK);
		return;
	}

	{
		CBCGLocalResource locaRes;

		CString strName;
		m_pSelectedToolbar->GetWindowText (strName);

		CString strPrompt;
		strPrompt.Format (IDS_BCGBARRES_DELETE_TOOLBAR_FMT, strName);

		if (MessageBox (strPrompt, NULL, MB_YESNO | MB_ICONQUESTION) != IDYES)
		{
			return;
		}
	}

	if (pParentFrame->SendMessage (BCGM_DELETETOOLBAR, 0, (LPARAM) m_pSelectedToolbar)
		== 0)
	{
		MessageBeep (MB_ICONASTERISK);
		return;
	}

	m_wndToobarList.DeleteString (m_wndToobarList.GetCurSel ());
	m_wndToobarList.SetCurSel (0);
	OnSelchangeToolbarList ();
}
//**********************************************************************************
void CToolbarsPage::OnNewToolbar()
{
	CString strToolbarName;
	{
		CBCGLocalResource locaRes;

		CToolbarNameDlg dlg (this);
		if (dlg.DoModal () != IDOK)
		{
			return;
		}

		strToolbarName = dlg.m_strToolbarName;
	}

	CFrameWnd* pParentFrame = GetParentFrame ();
	if (pParentFrame == NULL)
	{
		MessageBeep (MB_ICONASTERISK);
		return;
	}

	CBCGToolBar* pNewToolbar = 
		(CBCGToolBar*)pParentFrame->SendMessage (BCGM_CREATETOOLBAR, 0,
			(LPARAM) (LPCTSTR) strToolbarName);
	if (pNewToolbar == NULL)
	{
		return;
	}

	ASSERT_VALID (pNewToolbar);

	int iIndex = m_wndToobarList.AddString (strToolbarName);
	m_wndToobarList.SetItemData (iIndex, (DWORD) pNewToolbar);

	m_wndToobarList.SetCheck (iIndex, 1);
	m_wndToobarList.SetCurSel (iIndex);
	m_wndToobarList.SetTopIndex (iIndex);

	OnSelchangeToolbarList ();
}
//**********************************************************************************
void CToolbarsPage::OnRenameToolbar() 
{
	ASSERT (m_pSelectedToolbar != NULL);
	ASSERT (IsUserDefinedToolBar (m_pSelectedToolbar));

	CString strToolbarName;
	{
		CBCGLocalResource locaRes;

		CToolbarNameDlg dlg (this);
		m_pSelectedToolbar->GetWindowText (dlg.m_strToolbarName);

		if (dlg.DoModal () != IDOK)
		{
			return;
		}

		strToolbarName = dlg.m_strToolbarName;
	}

	m_pSelectedToolbar->SetWindowText (strToolbarName);
	if (m_pSelectedToolbar->IsFloating ())
	{
		//-----------------------------
		// Change floating frame title:
		//-----------------------------
		CFrameWnd* pParent = m_pSelectedToolbar->GetParentFrame();

		CMiniDockFrameWnd* pDockFrame =
			DYNAMIC_DOWNCAST (CMiniDockFrameWnd, pParent);
		if (pDockFrame != NULL)
		{
			pDockFrame->m_wndDockBar.SetWindowText (strToolbarName);
		}
	}

	m_wndToobarList.DeleteString (m_wndToobarList.GetCurSel ());

	int iIndex = m_wndToobarList.AddString (strToolbarName);
	m_wndToobarList.SetItemData (iIndex, (DWORD) m_pSelectedToolbar);

	if (m_pSelectedToolbar->GetStyle () & WS_VISIBLE)
	{
		m_wndToobarList.SetCheck (iIndex, 1);
	}

	m_wndToobarList.SetCurSel (iIndex);
	m_wndToobarList.SetTopIndex (iIndex);

	OnSelchangeToolbarList ();
}
//*************************************************************************************
BOOL CToolbarsPage::IsUserDefinedToolBar (const CBCGToolBar* pToolBar) const
{
	CBCGMDIFrameWnd* pMainMDIFrame = DYNAMIC_DOWNCAST (CBCGMDIFrameWnd, AfxGetMainWnd ());
	if (pMainMDIFrame != NULL)
	{
		return pMainMDIFrame->m_Impl.IsUserDefinedToolbar (pToolBar);
	}

	CBCGFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGFrameWnd, AfxGetMainWnd ());
	if (pMainFrame != NULL)
	{
		return pMainFrame->m_Impl.IsUserDefinedToolbar (pToolBar);
	}

	return FALSE;
}
//*******************************************************************
void CToolbarsPage::OnShowTooltipsWithKeys() 
{
	UpdateData ();
	CBCGToolBar::m_bShowShortcutKeys = m_bShowShortcutKeys;
}
//*******************************************************************
BOOL CToolbarsPage::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	UINT uiCode = HIWORD (wParam);
	UINT uiID = LOWORD (wParam);

	if (uiCode == CLBN_CHKCHANGE && uiID == IDC_BCGBARRES_TOOLBAR_LIST)
	{
		int iIndex = m_wndToobarList.GetCurSel ();
		if (iIndex != LB_ERR)
		{
			CBCGToolBar* pToolbar = (CBCGToolBar*) m_wndToobarList.GetItemData (iIndex);
			ASSERT_VALID (pToolbar);

			CFrameWnd* pParentFrame = (pToolbar->m_pDockSite == NULL) ?
				pToolbar->GetDockingFrame() : pToolbar->m_pDockSite;
			ASSERT_VALID(pParentFrame);

			if (pToolbar->CanBeClosed ())
			{
				//-------------------
				// Show/hide toolbar:
				//-------------------
				pParentFrame->ShowControlBar (pToolbar,
					m_wndToobarList.GetCheck (iIndex), FALSE);
			}
			else if (m_wndToobarList.GetCheck (iIndex) == 0)
			{
				//----------------------------------
				// Toolbar should be visible always!
				//----------------------------------
				m_wndToobarList.SetCheck (iIndex, TRUE);
				MessageBeep ((UINT) -1);
			}
		}
	}
	
	return CPropertyPage::OnCommand(wParam, lParam);
}
