// TestTipDayView.h : interface of the CTestTipDayView class
//
/////////////////////////////////////////////////////////////////////////////

class CTestTipDayView : public CView
{
protected: // create from serialization only
	CTestTipDayView();
	DECLARE_DYNCREATE(CTestTipDayView)

// Attributes
public:
	CTestTipDayDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTipDayView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestTipDayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestTipDayView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestTipDayView.cpp
inline CTestTipDayDoc* CTestTipDayView::GetDocument()
   { return (CTestTipDayDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
