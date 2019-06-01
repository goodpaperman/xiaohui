// TestAppView.h : interface of the CTestAppView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTAPPVIEW_H__9FD1E411_D97C_11D2_989A_204C4F4F5020__INCLUDED_)
#define AFX_TESTAPPVIEW_H__9FD1E411_D97C_11D2_989A_204C4F4F5020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestAppView : public CView
{
protected: // create from serialization only
	CTestAppView();
	DECLARE_DYNCREATE(CTestAppView)

// Attributes
public:
	CTestAppDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAppView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestAppView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestAppView.cpp
inline CTestAppDoc* CTestAppView::GetDocument()
   { return (CTestAppDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAPPVIEW_H__9FD1E411_D97C_11D2_989A_204C4F4F5020__INCLUDED_)
