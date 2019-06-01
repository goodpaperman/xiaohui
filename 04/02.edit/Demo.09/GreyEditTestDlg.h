#pragma once

#include "GreyEdit.h"

class CGreyEditTestDlg : public CDialog
{
// Construction
public:
	CGreyEditTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGreyEditTestDlg)
	enum { IDD = IDD_GREYEDITTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGreyEditTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

protected:
	CGreyEdit m_editName;
	CGreyEdit m_editAddr1;
	CGreyEdit m_editAddr2;
	CGreyEdit m_editCity;
	CGreyEdit m_editState;
	CGreyEdit m_editZip;

	// Generated message map functions
	//{{AFX_MSG(CGreyEditTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
