// TestPreviewView.h : interface of the CTestPreviewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPREVIEWVIEW_H__D9C030CE_12DD_11D3_915F_FDE9AD318528__INCLUDED_)
#define AFX_TESTPREVIEWVIEW_H__D9C030CE_12DD_11D3_915F_FDE9AD318528__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestPreviewView : public CView
{
protected: // create from serialization only
	CTestPreviewView();
	DECLARE_DYNCREATE(CTestPreviewView)

// Attributes
public:
	CTestPreviewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPreviewView)
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
	virtual ~CTestPreviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestPreviewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestPreviewView.cpp
inline CTestPreviewDoc* CTestPreviewView::GetDocument()
   { return (CTestPreviewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPREVIEWVIEW_H__D9C030CE_12DD_11D3_915F_FDE9AD318528__INCLUDED_)
