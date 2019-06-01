#if !defined(AFX_GFXINCOMBO_H__B8F997D3_E92B_11D1_86F0_000000000000__INCLUDED_)
#define AFX_GFXINCOMBO_H__B8F997D3_E92B_11D1_86F0_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxInCombo.h : header file
//
#include "GfxInComboStatic.h"
#include "GfxInComboList.h"
#include "GfxInComboEdit.h"

#define WM_USER_TAB		WM_USER+3

/////////////////////////////////////////////////////////////////////////////
// CGfxInCombo window

class CGfxInCombo : public CWnd
{
// Construction
public:
	CGfxInCombo(int iItem, int iSubItem, CString sInitText, CStringArray * pComboArray, bool _bEditable = false, bool _bMouseSelect = true);

// Attributes
public:
	HFONT hFontHandle;
	bool bProcessed;
	bool bLightBorder;

	bool bMouseSelect;
	int iCurSel;
	bool bEditable;
	int iButtonDx;
	int m_iItem;
	int m_iSubItem;
	CString m_sInitText;
	BOOL m_bESC;// To indicate whether ESC key was pressed
	CStringArray * pArray;

	HBITMAP	hArrow;

	CGfxInComboEdit		wndEdit;
	CGfxInComboStatic	wndStatic;
	CGfxInComboList		wndList;
	bool				m_bAutoComplete;

	COLORREF crColor;

	CFont * pFont;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxInCombo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void PreviousTab();
	void NextTab();
	void DownCell();
	void UpCell();
	void RightCell();
	void LeftCell();
	int FindString( int nStartAfter, CString find);
	void ProcessSelect(const char * cForceText = NULL);
	int SetCurSel(const int iSel);
	CString FindFromCharPressed(char c);
	int FindStringExact(const int iStart, const char * cText);
	void InvalidateButton();
	bool Create(DWORD dwFlag, CRect rc, CWnd * pParent, int id);
	void DrawButton(CDC * pDC, const bool bPressed);
	virtual ~CGfxInCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGfxInCombo)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNcDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnSelendOk(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXINCOMBO_H__B8F997D3_E92B_11D1_86F0_000000000000__INCLUDED_)
