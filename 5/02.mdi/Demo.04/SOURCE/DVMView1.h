// DVMView1.h : interface of the CDVMView1 class
//
/////////////////////////////////////////////////////////////////////////////

class CDVMView1 : public CScrollView
{
protected: // create from serialization only
	CDVMView1();
	DECLARE_DYNCREATE(CDVMView1)

// Attributes
public:
	CDVMDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDVMView1)
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
	virtual ~CDVMView1();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDVMView1)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DVMView1.cpp
inline CDVMDoc* CDVMView1::GetDocument()
   { return (CDVMDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
