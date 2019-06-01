// StatusBarView.h : interface of the CStatusBarView class
//
/////////////////////////////////////////////////////////////////////////////

class CStatusBarView : public CListView
{
protected: // create from serialization only
	CStatusBarView();
	DECLARE_DYNCREATE(CStatusBarView)

// Attributes
public:
	CStatusBarDoc* GetDocument();

// Operations
public:
        int AddString(UINT id, CString s);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusBarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStatusBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStatusBarView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StatusBarView.cpp
inline CStatusBarDoc* CStatusBarView::GetDocument()
   { return (CStatusBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
