// ListViewDemoView.h : interface of the CListViewDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTVIEWDEMOVIEW_H__6AB8B06D_0F98_11D2_8560_00A024068C2F__INCLUDED_)
#define AFX_LISTVIEWDEMOVIEW_H__6AB8B06D_0F98_11D2_8560_00A024068C2F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CListViewDemoView : public CView
{
protected: // create from serialization only
	CListViewDemoView();
	DECLARE_DYNCREATE(CListViewDemoView)

// Attributes
public:
	CListViewDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListViewDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListViewDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CListViewDemoView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ListViewDemoView.cpp
inline CListViewDemoDoc* CListViewDemoView::GetDocument()
   { return (CListViewDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTVIEWDEMOVIEW_H__6AB8B06D_0F98_11D2_8560_00A024068C2F__INCLUDED_)
