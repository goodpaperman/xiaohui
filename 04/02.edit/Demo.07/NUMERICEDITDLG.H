// NumericEditDlg.h : header file
//

#if !defined(AFX_NUMERICEDITDLG_H__95933459_3D26_11D2_A321_00609761A58B__INCLUDED_)
#define AFX_NUMERICEDITDLG_H__95933459_3D26_11D2_A321_00609761A58B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CNumericEditDlg dialog

class CNumericEditDlg : public CDialog
{
// Construction
public:
	CNumericEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNumericEditDlg)
	enum { IDD = IDD_NUMERICEDIT_DIALOG };
	CNumEdit	m_num;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumericEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNumericEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMERICEDITDLG_H__95933459_3D26_11D2_A321_00609761A58B__INCLUDED_)
