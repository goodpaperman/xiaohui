#if !defined(AFX_GFXHEADERCTRL_H__31F5CEA9_E5CA_11D1_86E7_000000000000__INCLUDED_)
#define AFX_GFXHEADERCTRL_H__31F5CEA9_E5CA_11D1_86E7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxHeaderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGfxHeaderCtrl window

class CGfxHeaderCtrl : public CHeaderCtrl
{
// Construction
public:
	CGfxHeaderCtrl();

// Attributes
public:
	DWORD	dwSortUp;
	DWORD	dwDontShowSortArrow, dwNoResizeColumn;
	int		m_nSortCol;	
	BOOL	m_bSortAsc;
	CImageList * pImageList;

	int SetSortImage(int nCol, BOOL bAsc);
	void SetSortOrder(const int iCol, const bool bAscending);
	bool GetSortOrder(const int iCol);

// Column dragging
	bool	bEnableDrag;
	BOOL	m_bCheckForDrag;	
	BOOL	m_bDragging;	
	int	*	m_pWidth;	
	int		m_nDragCol;
	int		m_nDropPos;	
	CRect	marker_rect;	
	void	(CWnd::*m_fpDragCol)(int &, int &);
//	CWnd	*m_pOwnerWnd;
	void	SetCallback(void (CWnd::*fpDragCol)(int &, int &));

	CBitmap bDragColumn;
	CRect	rcDragColumn, rcLastDragColumn;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxHeaderCtrl)
	//}}AFX_VIRTUAL
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Implementation
public:
	void DrawDragColumn(const int iCol);
	bool bIsDragAllowed;
	bool IsDragAllowed(CPoint point);
	virtual ~CGfxHeaderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGfxHeaderCtrl)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXHEADERCTRL_H__31F5CEA9_E5CA_11D1_86E7_000000000000__INCLUDED_)
