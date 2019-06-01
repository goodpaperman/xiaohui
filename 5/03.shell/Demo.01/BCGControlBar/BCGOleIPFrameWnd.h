#if !defined(AFX_BCGOLEIPFRAMEWND_H__1E1CDCA3_DD9E_11D2_A70E_0090274409AC__INCLUDED_)
#define AFX_BCGOLEIPFRAMEWND_H__1E1CDCA3_DD9E_11D2_A70E_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGOleIPFrameWnd.h : header file
//

#include "BCGFrameImpl.h"
#include "bcgcontrolbar.h"

class CBCGMenuBar;
class CBCGToolbarMenuButton;

/////////////////////////////////////////////////////////////////////////////
// CBCGOleIPFrameWnd window

class BCGCONTROLBARDLLEXPORT CBCGOleIPFrameWnd : public COleIPFrameWnd
{
	friend class CBCGMenuBar;
	friend class CToolbarsPage;

	DECLARE_DYNCREATE(CBCGOleIPFrameWnd)

// Construction
protected:
	CBCGOleIPFrameWnd();           // protected constructor used by dynamic creation

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
	BOOL			m_bIsTlbCustMode;
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
	//{{AFX_VIRTUAL(CBCGOleIPFrameWnd)
	public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBCGOleIPFrameWnd();

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
protected:
	//{{AFX_MSG(CBCGOleIPFrameWnd)
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	//}}AFX_MSG
	afx_msg LRESULT OnSetMenu (WPARAM wp, LPARAM);
	afx_msg LRESULT OnToolbarCreateNew(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarDelete(WPARAM,LPARAM);
	afx_msg void OnContextHelp ();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGOLEIPFRAMEWND_H__1E1CDCA3_DD9E_11D2_A70E_0090274409AC__INCLUDED_)
