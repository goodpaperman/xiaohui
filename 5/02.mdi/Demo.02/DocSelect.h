#if !defined(AFX_DOCSELECTOR_H__C789E26C_DA4B_11D2_BF44_006008085F93__INCLUDED_)
#define AFX_DOCSELECTOR_H__C789E26C_DA4B_11D2_BF44_006008085F93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DocSelector.h : header file
//

#define SWM_SELCHANGE (WM_USER + 137)
#define SWM_UNSELECT (WM_USER + 138)

#include "SwitcherButton.h"
#include "menubutton.h"

/////////////////////////////////////////////////////////////////////////////
// CDocSelector window
class CDocSelector : public CControlBar
{
// Construction
public:
	CDocSelector();

// Attributes
public:
	// Yogesh Jagota
	int				m_cxAvailable;
	UINT			m_nDisplayedButtons;
	CMenuButton		m_btnMenuButton;
	// End Yogesh Jagota

// Operations
public:
	BOOL				AddButton( CWnd* wnd, WORD wIcon = -1 );
	void				ResizeButtons(int NewSize);
	void				RemoveAll();
	BOOL				RemoveButton(CWnd* wnd);
	CSwitcherButton*	GetButtonFromID(int id);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocSelector)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocSelector();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDocSelector)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnDSPopup( WPARAM, LPARAM );
	afx_msg LRESULT OnUnselect(WPARAM, LPARAM);
	afx_msg LRESULT OnSelChange(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

	CPtrArray	m_Buttons;
	int			m_iNextButtonStart;
	int			m_iButtonWidth;
	int			m_iSelectedButton;

	// Yogesh Jagota
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	// End Yogesh Jagota
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCSELECTOR_H__C789E26C_DA4B_11D2_BF44_006008085F93__INCLUDED_)
