// GeneralPrefsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGeneralPrefsDlg dialog

class CGeneralPrefsDlg : public CDialog
{
// Construction
public:
	CGeneralPrefsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGeneralPrefsDlg)
	enum { IDD = IDD_GENERAL };
	BOOL	m_bISee;
	BOOL	m_bDontLike;
	BOOL	m_bLikeBeer;
	int		m_nWhen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneralPrefsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGeneralPrefsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
