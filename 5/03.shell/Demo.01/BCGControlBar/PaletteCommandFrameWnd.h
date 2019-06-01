#if !defined(AFX_PALETTECOMMANDFRAMEWND_H__052B4BD4_85FD_11D2_8BF9_00A0C9B05590__INCLUDED_)
#define AFX_PALETTECOMMANDFRAMEWND_H__052B4BD4_85FD_11D2_8BF9_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PaletteCommandFrameWnd.h : header file
//

class CImageEditDlg;

/////////////////////////////////////////////////////////////////////////////
// CPaletteCommandFrameWnd frame. "Dummy" class for the CImageEditDlg paletee
// bar routing only!

class CPaletteCommandFrameWnd : public CFrameWnd
{
	friend class CImageEditDlg;

	DECLARE_DYNAMIC(CPaletteCommandFrameWnd)

protected:
	CPaletteCommandFrameWnd();

// Attributes
protected:
	CImageEditDlg*	m_pDlgEdit;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaletteCommandFrameWnd)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CImageEditDlg* pParentWnd);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPaletteCommandFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CPaletteCommandFrameWnd)
	afx_msg void OnBcgToolClear();
	afx_msg void OnBcgToolCopy();
	afx_msg void OnBcgToolPaste();
	afx_msg void OnUpdateBcgToolPaste(CCmdUI* pCmdUI);
	afx_msg void OnBcgToolEllipse();
	afx_msg void OnBcgToolFill();
	afx_msg void OnBcgToolLine();
	afx_msg void OnBcgToolPen();
	afx_msg void OnBcgToolPick();
	afx_msg void OnBcgToolRect();
	afx_msg void OnUpdateBcgToolEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolFill(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolPen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolPick(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBcgToolRect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALETTECOMMANDFRAMEWND_H__052B4BD4_85FD_11D2_8BF9_00A0C9B05590__INCLUDED_)
