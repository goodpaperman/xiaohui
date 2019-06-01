// TLViewView.h : interface of the CTLViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLVIEWVIEW_H__3C29E711_4823_11D2_980D_004095E0DEFA__INCLUDED_)
#define AFX_TLVIEWVIEW_H__3C29E711_4823_11D2_980D_004095E0DEFA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TreeListView.h"

class CTLViewView : public CTreeListView
{
protected: // create from serialization only
	CTLViewView();
	DECLARE_DYNCREATE(CTLViewView)

// Attributes
public:
	CTLViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTLViewView)
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
	virtual ~CTLViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTLViewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TLViewView.cpp
inline CTLViewDoc* CTLViewView::GetDocument()
   { return (CTLViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TLVIEWVIEW_H__3C29E711_4823_11D2_980D_004095E0DEFA__INCLUDED_)
