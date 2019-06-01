// TPS_DemoView.h : interface of the CTPS_DemoView class
//
/////////////////////////////////////////////////////////////////////////////

class CTPS_DemoView : public CView
{
protected: // create from serialization only
	CTPS_DemoView();
	DECLARE_DYNCREATE(CTPS_DemoView)

// Attributes
public:
	CTPS_DemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPS_DemoView)
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
	virtual ~CTPS_DemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTPS_DemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TPS_DemoView.cpp
inline CTPS_DemoDoc* CTPS_DemoView::GetDocument()
   { return (CTPS_DemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
