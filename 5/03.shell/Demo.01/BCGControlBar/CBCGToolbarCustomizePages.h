// CBCGToolbarCustomizePages.h : header file
//

#ifndef __CBCGTOOLBARCUSTOMIZEPAGES_H__
#define __CBCGTOOLBARCUSTOMIZEPAGES_H__

#include "ButtonsList.h"
#include "ButtonsTextList.h"
#include "bcgbarres.h"

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "BCGExCheckList.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomizePage dialog

class CBCGToolbarButton;
class CBCGToolBarImages;
class CBCGToolBar;

class CCustomizePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCustomizePage)

// Construction
public:
	CCustomizePage();
	~CCustomizePage();

// Operations:
	void SetUserCategory (LPCTSTR lpszCategory);
	void SetAllCategory (LPCTSTR lpszCategory);
	void OnChangeSelButton (CBCGToolbarButton* pButton);

protected:

// Dialog Data
	//{{AFX_DATA(CCustomizePage)
	enum { IDD = IDD_BCGBARRES_PROPPAGE1 };
	CListBox	m_wndCategory;
	CButtonsTextList	m_wndTools;
	CString	m_strButtonDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCustomizePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustomizePage)
	afx_msg void OnSelchangeUserTools();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCategory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes:
protected:

	CBCGToolbarButton*	m_pSelButton;
	CString				m_strUserCategory;
	CString				m_strAllCategory;
};

/////////////////////////////////////////////////////////////////////////////
// CToolbarsPage dialog

 class CToolbarsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CToolbarsPage)

// Construction
public:
	CToolbarsPage();
	~CToolbarsPage();

// Dialog Data
	//{{AFX_DATA(CToolbarsPage)
	enum { IDD = IDD_BCGBARRES_PROPPAGE2 };
	CButton	m_wndShowShortcutKeys;
	CButton	m_bntRenameToolbar;
	CButton	m_btnNewToolbar;
	CButton	m_btnDelete;
	CButton	m_btnReset;
	CBCGExCheckList	m_wndToobarList;
    //CCheckListBox m_wndToobarList; 
	BOOL	m_bShowTooltips;
	BOOL	m_bShowShortcutKeys;
	//}}AFX_DATA

// Operations:
public:
	void ShowToolBar (CBCGToolBar* pToolBar, BOOL bShow);
	void EnableUserDefinedToolbars (BOOL bEnable)
	{
		m_bUserDefinedToolbars = bEnable;
	}

protected:
	BOOL IsUserDefinedToolBar (const CBCGToolBar* pToolBar) const;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CToolbarsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CToolbarsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeToolbarList();
	afx_msg void OnDblclkToolbarList();
	afx_msg void OnShowTooltips();
	afx_msg void OnReset();
	afx_msg void OnResetAll();
	afx_msg void OnDeleteToolbar();
	afx_msg void OnNewToolbar();
	afx_msg void OnRenameToolbar();
	afx_msg void OnShowTooltipsWithKeys();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBCGToolBar*	m_pSelectedToolbar;
	BOOL			m_bUserDefinedToolbars;
};



#endif // __CBCGTOOLBARCUSTOMIZEPAGES_H__
