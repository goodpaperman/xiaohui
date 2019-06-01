// ToolBarExampleView.h : interface of the CToolBarExampleView class
//
/////////////////////////////////////////////////////////////////////////////

class CToolBarExampleView : public CEditView
{
protected: // create from serialization only
	CToolBarExampleView();
	DECLARE_DYNCREATE(CToolBarExampleView)

// Attributes
public:
	CToolBarExampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarExampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolBarExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarExampleView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ToolBarExampleView.cpp
inline CToolBarExampleDoc* CToolBarExampleView::GetDocument()
   { return (CToolBarExampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
