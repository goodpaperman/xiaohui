// titleAnimView.h : interface of the CTitleAnimView class
//
/////////////////////////////////////////////////////////////////////////////

class CTitleAnimView : public CView
{
protected: // create from serialization only
	CTitleAnimView();
	DECLARE_DYNCREATE(CTitleAnimView)

// Attributes
public:
	CTitleAnimDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitleAnimView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTitleAnimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTitleAnimView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in titleAnimView.cpp
inline CTitleAnimDoc* CTitleAnimView::GetDocument()
   { return (CTitleAnimDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
