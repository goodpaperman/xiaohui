// HiColToolBarView.h : interface of the CHiColToolBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HICOLTOOLBARVIEW_H__16F5446B_1B11_11D2_BD39_00A0C945A10E__INCLUDED_)
#define AFX_HICOLTOOLBARVIEW_H__16F5446B_1B11_11D2_BD39_00A0C945A10E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CHiColToolBarView : public CView
{
protected: // create from serialization only
	CHiColToolBarView();
	DECLARE_DYNCREATE(CHiColToolBarView)

// Attributes
public:
	CHiColToolBarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHiColToolBarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHiColToolBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHiColToolBarView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HiColToolBarView.cpp
inline CHiColToolBarDoc* CHiColToolBarView::GetDocument()
   { return (CHiColToolBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HICOLTOOLBARVIEW_H__16F5446B_1B11_11D2_BD39_00A0C945A10E__INCLUDED_)
