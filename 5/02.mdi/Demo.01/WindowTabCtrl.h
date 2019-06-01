#if !defined(AFX_WINDOWTABCTRL_H__C67D43AA_F890_11D1_83BA_0000B43382FE__INCLUDED_)
#define AFX_WINDOWTABCTRL_H__C67D43AA_F890_11D1_83BA_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WindowTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWindowTabCtrl window

class CWindowTabCtrl : public CTabCtrl
{
private:
	BOOL m_bDisplayIcons;
// Construction
public:
	CWindowTabCtrl();

// Attributes
public:

// Operations
public:
	void SetFonts(CFont* pSelFont, CFont* pUnselFont);
	void SetFonts(int nSelWeight = FW_SEMIBOLD, BOOL bSelItalic = FALSE,   
		BOOL bSelUnderline = FALSE, int nUnselWeight = FW_MEDIUM, 
		BOOL bUnselItalic = FALSE, BOOL bUnselUnderline = FALSE);

	void SetColors(COLORREF bSelColor, COLORREF bUnselColor, COLORREF rcDocModified);

	void SetIconDisplay(BOOL bDisplayIt = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowTabCtrl)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWindowTabCtrl();

// Implementation
protected:
	COLORREF m_crSelColor, m_crUnselColor, m_rcDocModified;
	CFont    m_SelFont,	m_UnselFont;

	// Generated message map functions
protected:
	//{{AFX_MSG(CWindowTabCtrl)
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWTABCTRL_H__C67D43AA_F890_11D1_83BA_0000B43382FE__INCLUDED_)
