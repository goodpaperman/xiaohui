// DualListDemoView.h : interface of the CDualListDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUALLISTDEMOVIEW_H__E6FFDCDC_DF3B_11D3_8664_0050DA15E05C__INCLUDED_)
#define AFX_DUALLISTDEMOVIEW_H__E6FFDCDC_DF3B_11D3_8664_0050DA15E05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DualListManager.h"

class CDualListDemoView : public CFormView
{
protected: // create from serialization only
	CDualListDemoView();
	DECLARE_DYNCREATE(CDualListDemoView)

public:
	//{{AFX_DATA(CDualListDemoView)
	enum{ IDD = IDD_FORM_DUAL_LIST_DEMO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CDualListDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDualListDemoView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
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
	virtual ~CDualListDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDualListDemoView)
	afx_msg void OnDuallisttestsDuallistdialog();
	afx_msg void OnDuallisttestsDuallistpropertypage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CDualListManager    m_DualListManager;
};

#ifndef _DEBUG  // debug version in DualListDemoView.cpp
inline CDualListDemoDoc* CDualListDemoView::GetDocument()
   { return (CDualListDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUALLISTDEMOVIEW_H__E6FFDCDC_DF3B_11D3_8664_0050DA15E05C__INCLUDED_)
