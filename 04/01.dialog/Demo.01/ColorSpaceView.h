// ColorSpaceView.h : interface of the CColorSpaceView class
//
/////////////////////////////////////////////////////////////////////////////

class CColorSpaceView : public CView
{
protected: // create from serialization only
	CColorSpaceView();
	DECLARE_DYNCREATE(CColorSpaceView)

// Attributes
public:
	CColorSpaceDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorSpaceView)
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
	virtual ~CColorSpaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CColorSpaceView)
	afx_msg void OnViewColorspace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	COLORREF m_Color;
};

#ifndef _DEBUG  // debug version in ColorSpaceView.cpp
inline CColorSpaceDoc* CColorSpaceView::GetDocument()
   { return (CColorSpaceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
