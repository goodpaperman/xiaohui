// CustomMoreWindowsView.h : interface of the CCustomMoreWindowsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMMOREWINDOWSVIEW_H__1E39FFF2_EC51_11D3_91A0_20314FC10000__INCLUDED_)
#define AFX_CUSTOMMOREWINDOWSVIEW_H__1E39FFF2_EC51_11D3_91A0_20314FC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCustomMoreWindowsView : public CEditView
{
protected: // create from serialization only
	CCustomMoreWindowsView();
	DECLARE_DYNCREATE(CCustomMoreWindowsView)

// Attributes
public:
	CCustomMoreWindowsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomMoreWindowsView)
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
	virtual ~CCustomMoreWindowsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomMoreWindowsView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CustomMoreWindowsView.cpp
inline CCustomMoreWindowsDoc* CCustomMoreWindowsView::GetDocument()
   { return (CCustomMoreWindowsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMMOREWINDOWSVIEW_H__1E39FFF2_EC51_11D3_91A0_20314FC10000__INCLUDED_)
