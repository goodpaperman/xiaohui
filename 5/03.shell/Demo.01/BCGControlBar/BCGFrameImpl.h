// BCGFrameImpl.h: interface for the CBCGFrameImpl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGFRAMEIMPL_H__829B77B5_FE0E_11D1_8BCB_00A0C9B05590__INCLUDED_)
#define AFX_BCGFRAMEIMPL_H__829B77B5_FE0E_11D1_8BCB_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CBCGToolBar;
class CBCGMenuBar;
class CBCGPopupMenu;

#include "bcgcontrolbar.h"

class BCGCONTROLBARDLLEXPORT CBCGFrameImpl
{
	friend class CBCGMDIFrameWnd;
	friend class CBCGFrameWnd;
	friend class CBCGOleIPFrameWnd;

public:
	CBCGFrameImpl(CFrameWnd* pFrame);
	virtual ~CBCGFrameImpl();

// Attributes:
public:
	const CBCGMenuBar* GetMenuBar () const
	{
		return m_pMenuBar;
	}

protected:
	UINT			m_uiUserToolbarFirst;
	UINT			m_uiUserToolbarLast;
	CObList			m_listUserDefinedToolbars;
	CString			m_strControlBarRegEntry;
	CBCGMenuBar*	m_pMenuBar;
	HMENU			m_hDefaultMenu;
	CFrameWnd*		m_pFrame;
	CBCGPopupMenu*	m_pActivePopupMenu;
	UINT			m_nIDDefaultResource;

// Operations
public:
	void InitUserToobars (LPCTSTR lpszRegEntry, UINT uiUserToolbarFirst, UINT uiUserToolbarLast);
	void LoadUserToolbars ();
	void SaveUserToolbars ();

	BOOL IsDockStateValid (const CDockState& state);
	BOOL IsUserDefinedToolbar (const CBCGToolBar* pToolBar) const;

	void SetMenuBar (CBCGMenuBar* pMenuBar);
	CBCGToolBar* GetUserBarByIndex (int iIndex) const;

protected:

	const CBCGToolBar* CreateNewToolBar (LPCTSTR lpszName);
	BOOL DeleteToolBar (CBCGToolBar* pToolBar);
	BOOL ProcessKeyboard (int nKey);
	BOOL ProcessMouseClick (POINT pt);
	BOOL ProcessMouseMove (POINT pt);

	void FrameEnableDocking(CFrameWnd * pFrame, DWORD dwDockStyle);

	void OnShowPopupMenu (CBCGPopupMenu* pMenuPopup, CFrameWnd* pWndFrame);
};

#endif // !defined(AFX_BCGFRAMEIMPL_H__829B77B5_FE0E_11D1_8BCB_00A0C9B05590__INCLUDED_)
