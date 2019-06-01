class CDlg_TTBarDlg : public CDialog
{
// Construction
public:
	CDlg_TTBarDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CDlg_TTBarDlg() ; // standard destructor

// Dialog Data
	//{{AFX_DATA(CDlg_TTBarDlg)
	enum { IDD = IDD_DLG_TTBAR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

private:
	CToolBarCtrl *m_toolbarCtrl ;
	TBBUTTON btn[5];
	BOOL NotifyFunction( UINT id, NMHDR * pTTTStruct, LRESULT * pResult );
	void SetToolBarPosition(int pos);
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_TTBarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlg_TTBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBottom();
	afx_msg void OnTop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
