#if !defined(AFX_GFXINCOMBOSTATIC_H__B8F997D4_E92B_11D1_86F0_000000000000__INCLUDED_)
#define AFX_GFXINCOMBOSTATIC_H__B8F997D4_E92B_11D1_86F0_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxInComboStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGfxInComboStatic window
class CGfxInCombo;

class CGfxInComboStatic : public CStatic
{
// Construction
public:
	CGfxInComboStatic();

// Attributes
public:
	CGfxInCombo * pCombo;

// Operations
public:
	COLORREF crColor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxInComboStatic)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGfxInComboStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGfxInComboStatic)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXINCOMBOSTATIC_H__B8F997D4_E92B_11D1_86F0_000000000000__INCLUDED_)
