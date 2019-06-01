#if !defined(AFX_BCGMDIFRAMEWND_H__08B9EC04_DCE3_11D1_A64F_00A0C93A70EC__INCLUDED_)
#define AFX_BCGMDIFRAMEWND_H__08B9EC04_DCE3_11D1_A64F_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGMDIFrameWnd.h : header file
//

#include "bcgcontrolbar.h"
#include "BCGFrameImpl.h"
#include "BCGMainClientAreaWnd.h"

class CBCGPopupMenu;
class CBCGToolBar;
class CBCGToolbarMenuButton;

/////////////////////////////////////////////////////////////////////////////
// CBCGMDIFrameWnd frame

class BCGCONTROLBARDLLEXPORT CBCGMDIFrameWnd : public CMDIFrameWnd
{
	friend class CBCGMainClientAreaWnd;
	friend class CBCGMenuBar;
	friend class CToolbarsPage;

	DECLARE_DYNCREATE(CBCGMDIFrameWnd)

protected:
	CBCGMDIFrameWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	BOOL IsMenuBarAvailable () const
	{
		return m_Impl.GetMenuBar () != NULL;
	}

	const CBCGMenuBar* GetMenuBar () const
	{
		return m_Impl.GetMenuBar ();
	}

	UINT GetDefaultResId () const
	{
		return m_Impl.m_nIDDefaultResource;
	}

protected:
	BOOL					m_bIsTlbCustMode;
	CBCGMainClientAreaWnd	m_wndClientArea;
	HMENU					m_hmenuWindow;
	CBCGFrameImpl			m_Impl;
	BOOL					m_bContextHelp;

// Operations
public:
	void EnableDocking (DWORD dwDockStyle);

protected:
	void OnSetMenu (HMENU hmenu);

// Implementation:
	void InitUserToobars (LPCTSTR lpszRegEntry, UINT uiUserToolbarFirst, UINT uiUserToolbarLast)
	{
		m_Impl.InitUserToobars (lpszRegEntry, uiUserToolbarFirst, uiUserToolbarLast);
	}

	void LoadUserToolbars ()
	{
		m_Impl.LoadUserToolbars ();
	}

	void SaveUserToolbars ()
	{
		m_Impl.SaveUserToolbars ();
	}

	BOOL IsDockStateValid (const CDockState& state)
	{
		return m_Impl.IsDockStateValid (state);
	}


	CBCGToolBar* GetUserBarByIndex (int iIndex) const
	{
		return m_Impl.GetUserBarByIndex (iIndex);
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGMDIFrameWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	virtual HMENU GetWindowMenuPopup (HMENU hMenuBar);

public:
	virtual void OnShowPopupMenu (CBCGPopupMenu* pMenuPopup);
	virtual void OnClosePopupMenu (CBCGPopupMenu* pMenuPopup);
	virtual BOOL OnDrawMenuImage (	CDC* /*pDC*/, 
									const CBCGToolbarMenuButton* /*pMenuButton*/, 
									const CRect& /*rectImage*/)
	{
		return FALSE;
	}

// Implementation
protected:
	virtual ~CBCGMDIFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CBCGMDIFrameWnd)
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	afx_msg LRESULT OnToolbarCreateNew(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarDelete(WPARAM,LPARAM);
	afx_msg void OnContextHelp ();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGMDIFRAMEWND_H__08B9EC04_DCE3_11D1_A64F_00A0C93A70EC__INCLUDED_)
