#if !defined(AFX_BACKPROPDLG_H__F3752A66_DB89_11D2_989F_204C4F4F5020__INCLUDED_)
#define AFX_BACKPROPDLG_H__F3752A66_DB89_11D2_989F_204C4F4F5020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackPropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackPropDlg dialog

class CMainFrame;
class CBackPropDlg : public CDialog
{
// Construction
public:
	CBackPropDlg(CWnd* pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackPropDlg)
	enum { IDD = IDD_BACKGROUND };
	CSpinButtonCtrl	m_ctlSpin2;
	CSpinButtonCtrl	m_ctlSpin1;
    CString	m_strFileName;
	int	m_nMode;
	UINT	m_nX;
	UINT	m_nY;
	BOOL	m_bAutoSave;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBackPropDlg)
	afx_msg void OnBrowse();
	afx_msg void OnBkcolor();
	afx_msg void OnReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnDisplay();
	afx_msg void OnChangeEditx();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()   

   CMainFrame* m_pFrame;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKPROPDLG_H__F3752A66_DB89_11D2_989F_204C4F4F5020__INCLUDED_)
