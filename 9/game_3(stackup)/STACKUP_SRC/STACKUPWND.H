// PageWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStackUpWnd window

class CStackUpWnd : public CWnd
{
// Construction
public:
	CStackUpWnd();

// Attributes
public:
  CStackUpApp* m_pApp;

// Operations
public:
  BOOL Create();
 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStackUpWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStackUpWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStackUpWnd)
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
