#if !defined(AFX_BCGFRAMEWND_H__829B77B4_FE0E_11D1_8BCB_00A0C9B05590__INCLUDED_)
#define AFX_BCGFRAMEWND_H__829B77B4_FE0E_11D1_8BCB_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGFrameWnd.h : header file
//

#include "BCGFrameImpl.h"
#include "bcgcontrolbar.h"

class CBCGMenuBar;
class CBCGToolbarMenuButton;

/////////////////////////////////////////////////////////////////////////////
// CBCGFrameWnd frame

class BCGCONTROLBARDLLEXPORT CBCGFrameWnd : public CFrameWnd
{
	friend class CBCGMenuBar;
	friend class CToolbarsPage;

	DECLARE_DYNCREATE(CBCGFrameWnd)

protected:
	CBCGFrameWnd();           // protected constructor used by dynamic creation

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
	//BOOL			m_bIsTlbCustMode;
	HMENU			m_hmenuWindow;
	CBCGFrameImpl	m_Impl;
	BOOL			m_bContextHelp;

// Operations
public:
	void EnableDocking (DWORD dwDockStyle);

protected:

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
	//{{AFX_VIRTUAL(CBCGFrameWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBCGFrameWnd();

	void OnSetMenu (HMENU hmenu);

public:
	virtual void OnShowPopupMenu (CBCGPopupMenu* pMenuPopup);
	virtual void OnClosePopupMenu (CBCGPopupMenu* pMenuPopup);
	virtual BOOL OnDrawMenuImage (	CDC* /*pDC*/, 
									const CBCGToolbarMenuButton* /*pMenuButton*/, 
									const CRect& /*rectImage*/)
	{
		return FALSE;
	}

	// Generated message map functions
	//{{AFX_MSG(CBCGFrameWnd)
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	//}}AFX_MSG
    //afx_msg LRESULT OnSetMenu (WPARAM wp, LPARAM);
	afx_msg LRESULT OnToolbarCreateNew(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarDelete(WPARAM,LPARAM);
	afx_msg void OnContextHelp ();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGFRAMEWND_H__829B77B4_FE0E_11D1_8BCB_00A0C9B05590__INCLUDED_)
