// WFDemoView.h : interface of the CWFDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WFDEMOVIEW_H__284419AD_4050_11D4_AE95_00A024E8EE6B__INCLUDED_)
#define AFX_WFDEMOVIEW_H__284419AD_4050_11D4_AE95_00A024E8EE6B__INCLUDED_

#include "Chart.h"	// Added by ClassView
#include "Chart3d.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWFDemoView : public CFormView
{
protected: // create from serialization only
	CWFDemoView();
	DECLARE_DYNCREATE(CWFDemoView)

public:
	//{{AFX_DATA(CWFDemoView)
	enum{ IDD = IDD_WFDEMO_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CWFDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWFDemoView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CChart3d m_Chart3d;
	CChart m_Chart2d ;
	virtual ~CWFDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL bTimerCreate;
	//{{AFX_MSG(CWFDemoView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStart();
	afx_msg void OnDestroy();
	afx_msg void OnView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WFDemoView.cpp
inline CWFDemoDoc* CWFDemoView::GetDocument()
   { return (CWFDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WFDEMOVIEW_H__284419AD_4050_11D4_AE95_00A024E8EE6B__INCLUDED_)
