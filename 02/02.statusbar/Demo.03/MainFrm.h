// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	CStatusProgress c_StatusProgress;
	CStatusEdit  c_StatusEdit;
	CStatusCombo c_StatusCombo;
	CStatusStatic c_StatusIcon;
	int iconstate;
	int progress;

// Generated message map functions
protected:
        void logEvent(UINT id, CString s = CString(_T("")));
	//{{AFX_MSG(CMainFrame)
        afx_msg void OnSelchangeCombo();
	afx_msg void OnChangeEdit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnStatusCombo();
	afx_msg void OnStatusEdit();
	afx_msg void OnStatusIcon();
	afx_msg void OnStatusProgress();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
