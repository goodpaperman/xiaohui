// ListEditView.h : interface of the CListEditView class
//
// Reg Anderson June 5 1998.

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTEDITVIEW_H__DEDB8F30_1417_11D2_AF14_0000C06B6ED6__INCLUDED_)
#define AFX_LISTEDITVIEW_H__DEDB8F30_1417_11D2_AF14_0000C06B6ED6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CLVEdit 

class CLVEdit : public CEdit
{
// Construction
public:
	CLVEdit() :m_x(0),m_y(0) {}

// Attributes
public:
	int m_x;
	int m_y;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLVEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLVEdit() {};

	// Generated message map functions
protected:
	//{{AFX_MSG(CLVEdit)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CListEditView 

class CListEditView : public CListView
{
protected: // create from serialization only
	CListEditView();
	DECLARE_DYNCREATE(CListEditView)

// Attributes
protected:
	int		m_cx;
	int m_nColEdit;
    int m_nRowEdit; 
	CLVEdit	m_LVEdit;

// Operations
protected:
	virtual void RepaintSelectedItems();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual LPCTSTR MakeShortString(CDC* pDC,LPCTSTR lpszLong,int nColumnLen);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListEditView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CListEditView)
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR,LRESULT* pResult);
	afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR,LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTEDITVIEW_H__DEDB8F30_1417_11D2_AF14_0000C06B6ED6__INCLUDED_)
