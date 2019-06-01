#if !defined(AFX_BCGMENUBAR_H__644FE23B_D1DB_11D1_A649_00A0C93A70EC__INCLUDED_)
#define AFX_BCGMENUBAR_H__644FE23B_D1DB_11D1_A649_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGMenuBar.h : header file
//

#include "BCGToolBar.h"
#include "bcgcontrolbar.h"

class CBCGToolbarMenuButton;

#define BCG_IDW_MENUBAR               0xE806  // CBCGMenuBar

/////////////////////////////////////////////////////////////////////////////
// CBCGMenuBar window

class BCGCONTROLBARDLLEXPORT CBCGMenuBar : public CBCGToolBar
{
	DECLARE_SERIAL(CBCGMenuBar)

// Construction
public:
	CBCGMenuBar();

// Attributes
public:

protected:
	CWnd*	m_pParentWnd;
	BOOL	m_bMaximizeMode;
	BOOL	m_bActualMaximizeMode;
	HMENU	m_hMenu;
	HMENU	m_hDefaultMenu;
	HMENU	m_hSysMenu;
	HICON	m_hSysIcon;
	UINT	m_uiDefMenuResId;
	int		m_nSystemButtonsNum;
	int		m_nSystemButtonsNumSaved;
	BOOL	m_bHaveButtons;

	static HHOOK		m_hookMouseDrag;
	static CBCGMenuBar*	m_pDraggedMenuBar;

// Operations
public:
	BOOL TranslateChar (UINT nChar);

	void CreateFromMenu (HMENU hMenu, BOOL bDefaultMenu = FALSE);
	void SetMaximizeMode (BOOL bMax, CWnd* pWnd = NULL);

	void SetDefaultMenuResId (UINT uiResId);
	UINT GetDefaultMenuResId () const
	{
		return m_uiDefMenuResId;
	}

	HMENU GetMenu () const
	{
		return m_hMenu;
	}

	HMENU GetDefaultMenu () const
	{
		return m_hDefaultMenu;
	}

protected:
	void RestoreMaximizeMode ();
	void SetDragMode (BOOL bOn);

	static LRESULT CALLBACK BCGMenuBarMouseProc (int nCode, WPARAM wParam, LPARAM lParam);
	static BOOL FindMenuItemText (HMENU hMenu, const UINT nID, CString& strText);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGMenuBar)
	//}}AFX_VIRTUAL

public:
	virtual BOOL Create(CWnd* pParentWnd,
			DWORD dwStyle = dwDefaultToolbarStyle,
			UINT nID = BCG_IDW_MENUBAR);

	virtual CSize CalcDynamicLayout (int nLength, DWORD dwMode);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcLayout(DWORD dwMode, int nLength = -1);

	virtual void AdjustLocations ();
	virtual BOOL OnSendCommand (const CBCGToolbarButton* pButton);

	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

	virtual BOOL LoadState (LPCTSTR lpszProfileName, int nIndex = -1);
	virtual BOOL SaveState (LPCTSTR lpszProfileName, int nIndex = -1);

	virtual void OnCustomizeMode (BOOL bSet);

	virtual BOOL CanBeRestored () const
	{
		return TRUE;
	}

	virtual BOOL CanBeClosed () const
	{
		return FALSE;
	}

	virtual BOOL RestoreOriginalstate ();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual int GetRowHeight () const
	{
		return m_bHaveButtons || m_sizeMenuButton.cy <= 0 ? 
			m_sizeButton.cy : m_sizeMenuButton.cy - 2;
	}

	virtual int GetColumnWidth () const
	{
		return m_bHaveButtons || m_sizeMenuButton.cx <= 0 ? 
			m_sizeButton.cx : m_sizeMenuButton.cx - 2;
	}

	virtual BOOL OnSetDefaultButtonText (CBCGToolbarButton* pButton);
	virtual BOOL PrevMenu ();
	virtual BOOL NextMenu ();

protected:
	virtual int FindDropIndex (const CPoint point, CRect& rectDrag) const;

	// Implementation
public:
	virtual ~CBCGMenuBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGMenuBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGMENUBAR_H__644FE23B_D1DB_11D1_A649_00A0C93A70EC__INCLUDED_)
