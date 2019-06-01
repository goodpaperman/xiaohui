// DocumentBarView.h : interface of the CDocumentBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENTBARVIEW_H__822331B2_F2C5_11D3_91A0_303D4FC10000__INCLUDED_)
#define AFX_DOCUMENTBARVIEW_H__822331B2_F2C5_11D3_91A0_303D4FC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDocumentBarView : public CEditView
{
protected: // create from serialization only
	CDocumentBarView();
	DECLARE_DYNCREATE(CDocumentBarView)

// Attributes
public:
	CDocumentBarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocumentBarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocumentBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDocumentBarView)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DocumentBarView.cpp
inline CDocumentBarDoc* CDocumentBarView::GetDocument()
   { return (CDocumentBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCUMENTBARVIEW_H__822331B2_F2C5_11D3_91A0_303D4FC10000__INCLUDED_)
