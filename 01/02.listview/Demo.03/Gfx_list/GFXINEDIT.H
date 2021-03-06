#if !defined(AFX_GFXINEDIT_H__31F5CEAD_E5CA_11D1_86E7_000000000000__INCLUDED_)
#define AFX_GFXINEDIT_H__31F5CEAD_E5CA_11D1_86E7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxInEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGfxInEdit window

class CGfxInEdit : public CRichEditCtrl//CEdit
{
// Construction
public:
	CGfxInEdit(int iItem, int iSubItem, CString sInitText, bool _bMouseSelect = true);

// Attributes
public:
	bool bMouseSelect;

// Operations
public:

private:
	int m_iItem;
	int m_iSubItem;
	CString m_sInitText;
	BOOL m_bESC;// To indicate whether ESC key was pressed

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxInEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void ProcessSelect();
	virtual ~CGfxInEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGfxInEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNcDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	bool UpdateCopy();
	bool UpdatePaste();
	bool UpdateCut();
	bool UpdateUndo();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXINEDIT_H__31F5CEAD_E5CA_11D1_86E7_000000000000__INCLUDED_)
