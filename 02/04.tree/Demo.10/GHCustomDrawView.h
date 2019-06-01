// GHCustomDrawView.h : interface of the CGHCustomDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GHCUSTOMDRAWVIEW_H__B510B4AD_CA7C_11D2_80FF_00104B346232__INCLUDED_)
#define AFX_GHCUSTOMDRAWVIEW_H__B510B4AD_CA7C_11D2_80FF_00104B346232__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGHCustomDrawView : public CListView
{
protected: // create from serialization only
	CGHCustomDrawView();
	DECLARE_DYNCREATE(CGHCustomDrawView)

// Attributes
public:
	CGHCustomDrawDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGHCustomDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGHCustomDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGHCustomDrawView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GHCustomDrawView.cpp
inline CGHCustomDrawDoc* CGHCustomDrawView::GetDocument()
   { return (CGHCustomDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GHCUSTOMDRAWVIEW_H__B510B4AD_CA7C_11D2_80FF_00104B346232__INCLUDED_)
