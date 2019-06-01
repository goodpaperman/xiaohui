// SwitchTBView.h : interface of the CSwitchTBView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWITCHTBVIEW_H__22E84081_DBB1_11D2_9145_0060082BE95D__INCLUDED_)
#define AFX_SWITCHTBVIEW_H__22E84081_DBB1_11D2_9145_0060082BE95D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSwitchTBView : public CView
{
protected: // create from serialization only
	CSwitchTBView();
	DECLARE_DYNCREATE(CSwitchTBView)

// Attributes
public:
	CSwitchTBDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchTBView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSwitchTBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSwitchTBView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SwitchTBView.cpp
inline CSwitchTBDoc* CSwitchTBView::GetDocument()
   { return (CSwitchTBDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHTBVIEW_H__22E84081_DBB1_11D2_9145_0060082BE95D__INCLUDED_)
