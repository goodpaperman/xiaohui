#if !defined(AFX_GFXINCOMBOLIST_H__B8F997D5_E92B_11D1_86F0_000000000000__INCLUDED_)
#define AFX_GFXINCOMBOLIST_H__B8F997D5_E92B_11D1_86F0_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxInComboList.h : header file
//

#define WM_USER_SELENDOK	WM_USER+2

/////////////////////////////////////////////////////////////////////////////
// CGfxInComboList window
class CGfxInCombo;

class CGfxInComboList : public CListBox
{
// Construction
public:
	CGfxInComboList();

// Attributes
public:
	CGfxInCombo * pCombo;
	int			  iLastSel;
	CString		  csLastItem;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxInComboList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGfxInComboList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGfxInComboList)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXINCOMBOLIST_H__B8F997D5_E92B_11D1_86F0_000000000000__INCLUDED_)
