// SuperProgressDlg.h : header file
//

#include "SuperProgressCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSuperProgressDlg dialog

class CSuperProgressDlg : public CDialog
{
// Construction
public:
	CSuperProgressDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSuperProgressDlg)
	enum { IDD = IDD_SUPERPROGRESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	int m_nMax;
	int m_nMin;
	int m_nStep;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CSuperProgressCtrl progress;

	// Generated message map functions
	//{{AFX_MSG(CSuperProgressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGo();
	afx_msg void OnStepIt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
