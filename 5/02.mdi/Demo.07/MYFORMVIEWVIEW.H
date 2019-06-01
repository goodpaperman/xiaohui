// MyFormViewView.h : interface of the CMyFormViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFORMVIEWVIEW_H__F9BB0CCC_3D20_11D2_BC46_0060970A2B51__INCLUDED_)
#define AFX_MYFORMVIEWVIEW_H__F9BB0CCC_3D20_11D2_BC46_0060970A2B51__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ColorFormView.h"

class CMyFormViewView : public CColorFormView
{
protected: // create from serialization only
	CMyFormViewView();
	DECLARE_DYNCREATE(CMyFormViewView)

public:
	//{{AFX_DATA(CMyFormViewView)
	enum{ IDD = IDD_MYFORMVIEW_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CMyFormViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFormViewView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyFormViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyFormViewView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChangeBkColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyFormViewView.cpp
inline CMyFormViewDoc* CMyFormViewView::GetDocument()
   { return (CMyFormViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFORMVIEWVIEW_H__F9BB0CCC_3D20_11D2_BC46_0060970A2B51__INCLUDED_)
