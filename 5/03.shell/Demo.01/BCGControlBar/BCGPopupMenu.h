#if !defined(AFX_BCGPOPUPMENU_H__A6E1AD75_D511_11D1_A64D_00A0C93A70EC__INCLUDED_)
#define AFX_BCGPOPUPMENU_H__A6E1AD75_D511_11D1_A64D_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGPopupMenu.h : header file
//

#include "bcgcontrolbar.h"
#include "BCGPopupMenuBar.h"

class CBCGToolbarMenuButton;
class CBCGMenuBar;
class CMenuPage;

/////////////////////////////////////////////////////////////////////////////
// CBCGPopupMenu frame

class BCGCONTROLBARDLLEXPORT CBCGPopupMenu : public CMiniFrameWnd
{
	friend CBCGToolbarMenuButton;
	friend CMenuPage;

	DECLARE_SERIAL(CBCGPopupMenu)

public:
	CBCGPopupMenu();
	virtual ~CBCGPopupMenu();

protected:
	CBCGPopupMenu(CMenuPage* pCustPage, LPCTSTR lpszTitle);	// For customization only

// Attributes
public:
	enum ANIMATION_TYPE
	{
		NO_ANIMATION,
		UNFOLD,
		SLIDE
	};

	BOOL m_bAutoDestroyParent;
	HMENU GetMenu () const
	{
		return m_hMenu;
	}

	virtual CBCGPopupMenuBar* GetMenuBar ()
	{
		return &m_wndMenuBar;
	}

	void SetAutoDestroy (BOOL bAutoDestroy = TRUE)
	{
		m_bAutoDestroy = bAutoDestroy;
	}

	CBCGToolbarMenuButton* GetParentButton () const
	{
		return m_pParentBtn;
	}

	static CBCGPopupMenu::ANIMATION_TYPE GetAnimationType ()
	{
		return m_AnimationType;
	}

	static SetAnimationType (CBCGPopupMenu::ANIMATION_TYPE type)
	{
		m_AnimationType = type;
	}

	BOOL IsScrollable () const
	{
		return m_bScrollable;
	}

	void EnableScrolling (BOOL bEnable = TRUE)
	{
		m_bScrollable = bEnable;
	}

protected:
	CBCGToolbarMenuButton*	m_pParentBtn;
	CBCGPopupMenuBar		m_wndMenuBar;
	HMENU					m_hMenu;
	int						m_x;
	int						m_y;
	CSize					m_FinalSize;
	CSize					m_AnimSize;
	BOOL					m_bIsAnimate;
	BOOL					m_bAutoDestroy;

	CMenuPage* const		m_pMenuCustomizationPage;
	CString					m_strCaption;

	static ANIMATION_TYPE	m_AnimationType;

	BOOL					m_bScrollable;
	CRect					m_rectScrollUp;
	CRect					m_rectScrollDn;
	int						m_iScrollMode;	// -1 - Up, 0 - None, 1 - Down

	static CImageList		m_MenuImages;
	static CString			m_strClassName;

// Operations
public:
	void SaveState ();

	CBCGPopupMenu* GetParentPopupMenu () const;
	CBCGToolBar* GetParentToolBar () const;

	CBCGToolbarMenuButton* GetSelItem ();

	int InsertItem (const CBCGToolbarMenuButton& button, int iInsertAt = -1);
	int InsertSeparator (int iInsertAt = -1);
	
	BOOL RemoveItem (int iIndex);
	void RemoveAllItems ();

	static void ActivatePopupMenu (CBCGPopupMenu* pPopupMenu);
	void CloseMenu (BOOL bSetFocusToBar = FALSE);

protected:
	void Initialize ();

	BOOL IsScrollUpAvailable ();
	BOOL IsScrollDnAvailable ();

	void CollapseSubmenus ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPopupMenu)
	public:
	virtual BOOL Create(CWnd* pWndParent, int x, int y, HMENU hMenu, BOOL bLocked = FALSE);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBCGPopupMenu)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPOPUPMENU_H__A6E1AD75_D511_11D1_A64D_00A0C93A70EC__INCLUDED_)
