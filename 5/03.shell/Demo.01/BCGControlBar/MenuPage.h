#if !defined(AFX_MENUPAGE_H__385604B4_DDC0_11D1_A64F_00A0C93A70EC__INCLUDED_)
#define AFX_MENUPAGE_H__385604B4_DDC0_11D1_A64F_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MenuPage.h : header file
//
#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "bcgbarres.h"

class CBCGMenuBar;
class CBCGPopupMenu;

/////////////////////////////////////////////////////////////////////////////
// CMenuPage dialog

class CMenuPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMenuPage)

// Construction
public:
	CMenuPage();
	~CMenuPage();

// Operations
public:
	void CloseContextMenu (CBCGPopupMenu* pMenu);

// Dialog Data
	//{{AFX_DATA(CMenuPage)
	enum { IDD = IDD_BCGBARRES_PROPPAGE3 };
	CButton	m_wndContextFrame;
	CStatic	m_wndContextHint;
	CButton	m_wndResetMenuButton;
	CStatic	m_wndContextMenuCaption;
	CComboBox	m_wndContextMenus;
	CStatic	m_wndIcon;
	CComboBox	m_wndMenuesList;
	CString	m_strMenuDescr;
	CString	m_strContextMenuName;
	CString	m_strMenuName;
	int		m_iMenuAnimationType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMenuPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMenuPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMenuList();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeContextMenuList();
	afx_msg void OnResetMenu();
	afx_msg void OnBcgbarresResetFrameMenu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void SaveMenu ();

// Attributes:
protected:
	CBCGMenuBar*	m_pMenuBar;
	HMENU			m_hmenuCurr;
	HMENU			m_hmenuSelected;
	CBCGPopupMenu*	m_pContextMenu;

	static CPoint	m_ptMenuLastPos;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUPAGE_H__385604B4_DDC0_11D1_A64F_00A0C93A70EC__INCLUDED_)
