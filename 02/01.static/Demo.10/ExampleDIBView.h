// ExampleDIBView.h : interface of the CExampleDIBView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLEDIBVIEW_H__A69F7E0C_69CD_11D3_9AB9_0008C7728E19__INCLUDED_)
#define AFX_EXAMPLEDIBVIEW_H__A69F7E0C_69CD_11D3_9AB9_0008C7728E19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExampleDIBView : public CFormView
{
protected: // create from serialization only
	CExampleDIBView();
	DECLARE_DYNCREATE(CExampleDIBView)

public:
	//{{AFX_DATA(CExampleDIBView)
	enum{ IDD = IDD_EXAMPLEDIB_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CExampleDIBDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleDIBView)
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
	virtual ~CExampleDIBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExampleDIBView)
	afx_msg void OnBtn1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ExampleDIBView.cpp
inline CExampleDIBDoc* CExampleDIBView::GetDocument()
   { return (CExampleDIBDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLEDIBVIEW_H__A69F7E0C_69CD_11D3_9AB9_0008C7728E19__INCLUDED_)
