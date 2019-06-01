// TabProjView.h : interface of the CTabProjView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABPROJVIEW_H__DE90A1AF_3680_11D2_A494_0008C77CF953__INCLUDED_)
#define AFX_TABPROJVIEW_H__DE90A1AF_3680_11D2_A494_0008C77CF953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTabProjView : public CEditView
{
protected: // create from serialization only
	CTabProjView();
	DECLARE_DYNCREATE(CTabProjView)
int m_nCount;
// Attributes
public:
	CTabProjDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabProjView)
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
	virtual ~CTabProjView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabProjView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TabProjView.cpp
inline CTabProjDoc* CTabProjView::GetDocument()
   { return (CTabProjDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABPROJVIEW_H__DE90A1AF_3680_11D2_A494_0008C77CF953__INCLUDED_)
