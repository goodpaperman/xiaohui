// sndView.h : interface of the CSndView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNDVIEW_H__2AAD228D_7424_11D2_8045_540610C10374__INCLUDED_)
#define AFX_SNDVIEW_H__2AAD228D_7424_11D2_8045_540610C10374__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSndView : public CView
{
protected: // create from serialization only
	CSndView();
	DECLARE_DYNCREATE(CSndView)

// Attributes
public:
	CSndDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSndView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSndView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSndView)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in sndView.cpp
inline CSndDoc* CSndView::GetDocument()
   { return (CSndDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNDVIEW_H__2AAD228D_7424_11D2_8045_540610C10374__INCLUDED_)
