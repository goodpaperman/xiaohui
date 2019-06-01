// TestViewView.h : interface of the CTestViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEWVIEW_H__CCAACD90_1F93_11D2_864F_0040055C08D9__INCLUDED_)
#define AFX_TESTVIEWVIEW_H__CCAACD90_1F93_11D2_864F_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTestViewView : public CView
{
protected: // create from serialization only
	CTestViewView();
	DECLARE_DYNCREATE(CTestViewView)

// Attributes
public:
	CTestViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestViewView)
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
	virtual ~CTestViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestViewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestViewView.cpp
inline CTestViewDoc* CTestViewView::GetDocument()
   { return (CTestViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEWVIEW_H__CCAACD90_1F93_11D2_864F_0040055C08D9__INCLUDED_)
