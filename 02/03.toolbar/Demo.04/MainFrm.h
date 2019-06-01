// MainFrm.h : interface of the CMainFrame class
// Matthew Angel mangel@uniserve.com
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

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

// Example of creating extra toolbars , dialog bars
// and floating toolbars... 

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
    CToolBar    m_wndToolBar1;

protected: // create a Dialog Bar
    CDialogBar  m_dlgBar1;
    CDialogBar  m_dlgBar2;
    // To produce a Shareware screen or Freeware Screen. 
	// A nag screen
	CDialogBar  m_dlgBar3;
    
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	afx_msg  void OnBarOne();
	afx_msg  void OnBarTwo();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
