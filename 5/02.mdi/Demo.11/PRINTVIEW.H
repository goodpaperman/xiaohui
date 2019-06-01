// PrintView.h : interface of the CPrintView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTVIEW_H__015023DE_F3FD_11D1_BF9F_0020AFF340CF__INCLUDED_)
#define AFX_PRINTVIEW_H__015023DE_F3FD_11D1_BF9F_0020AFF340CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPrintView : public CFormView
{
protected: // create from serialization only
	CPrintView();
	DECLARE_DYNCREATE(CPrintView)

public:
	CRect m_rect;
	CBitmap * m_pBm;
	CDC * m_pMemDC;
	//{{AFX_DATA(CPrintView)
	enum{ IDD = IDD_PRINT_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CPrintDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrintView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PrintView.cpp
inline CPrintDoc* CPrintView::GetDocument()
   { return (CPrintDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTVIEW_H__015023DE_F3FD_11D1_BF9F_0020AFF340CF__INCLUDED_)
