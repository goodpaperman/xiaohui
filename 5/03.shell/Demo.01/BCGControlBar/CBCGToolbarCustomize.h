// CBCGToolbarCustomize.h : header file
//
// CBCGToolbarCustomize is a modeless property sheet that is 
// created once and not destroyed until the application
// closes.  It is initialized and controlled from
// CPropertyFrame.
 
#ifndef __CBCGTOOLBARCUSTOMIZE_H__
#define __CBCGTOOLBARCUSTOMIZE_H__

#include "bcgcontrolbar.h"
#include "CBCGToolbarCustomizePages.h"
#include "MenuPage.h"
#include "MousePage.h"
#include "KeyboardPage.h"

class CBCGToolBarImages;
class CBCGToolbarButton;
class CBCGToolBar;

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarCustomize

class BCGCONTROLBARDLLEXPORT CBCGToolbarCustomize : public CPropertySheet
{
	friend class CBCGToolBar;

	DECLARE_DYNAMIC(CBCGToolbarCustomize)

// Construction
public:
	CBCGToolbarCustomize(CWnd* pWndParent, BOOL bAutoSetFromMenus = FALSE);

// Attributes
protected:
	//------------------------------------------
	// Toolbar+menu items divided by categories:
	//------------------------------------------
	CMap<CString, LPCTSTR, CObList*, CObList*>	m_ButtonsByCategory;
	CStringList									m_strCategoriesList;
													// Need for order!

	//----------------
	// Property pages:
	//----------------	
	CCustomizePage*	m_pCustomizePage;
	CToolbarsPage*	m_pToolbarsPage;
	CKeyboardPage*	m_pKeyboardPage;
	CMenuPage*		m_pMenuPage;
	CMousePage*		m_pMousePage;
	
	CString			m_strAllCommands;

// Operations
public:
	void AddButton (UINT uiCategoryId, const CBCGToolbarButton& button,
					int iInsertAfter = -1);
	void AddButton (LPCTSTR lpszCategory, const CBCGToolbarButton& button,
					int iInsertAfter = -1);

	int RemoveButton (UINT uiCategoryId, UINT uiCmdId);
	int RemoveButton (LPCTSTR lpszCategory, UINT uiCmdId);

	void ReplaceButton (UINT uiCmd, const CBCGToolbarButton& button);

	BOOL AddToolBar (UINT uiCategoryId, UINT uiToolbarResId);
	BOOL AddToolBar (LPCTSTR lpszCategory, UINT uiToolbarResId);
	BOOL AddMenu (UINT uiMenuResId);
	void AddMenuCommands (const CMenu* pMenu, BOOL bPopup, LPCTSTR lpszCategory = NULL);

	BOOL SetUserCategory (LPCTSTR lpszCategory);

	void EnableUserDefinedToolbars (BOOL bEnable = TRUE);

	void FillCategotiesComboBox (CComboBox& wndCategory) const;
	void FillCategotiesListBox (CListBox& wndCategory) const;
	void FillAllCommandsList (CListBox& wndListOfCommands) const;

	LPCTSTR GetCommandName (UINT uiCmd) const;

protected:
	void SetFrameCustMode (BOOL bCustMode);
	void ShowToolBar (CBCGToolBar* pToolBar, BOOL bShow);
	void SetupFromMenus ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGToolbarCustomize)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	virtual BOOL Create();

// Implementation
public:
	 virtual ~CBCGToolbarCustomize();
	 virtual void PostNcDestroy();

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGToolbarCustomize)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes:
protected:
	CWnd*	m_pParentWnd;
	BOOL	m_bAutoSetFromMenus;
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __CBCGTOOLBARCUSTOMIZE_H__
