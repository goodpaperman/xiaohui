// ExampleDlg.h : header file
//

#if !defined(AFX_EXAMPLEDLG_H__73B46E69_01FB_11D3_8647_00105AC69564__INCLUDED_)
#define AFX_EXAMPLEDLG_H__73B46E69_01FB_11D3_8647_00105AC69564__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BounceButton.h"

/////////////////////////////////////////////////////////////////////////////
// CExampleDlg dialog

class CExampleDlg : public CDialog
{
// Construction
public:
	CExampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExampleDlg)
	enum { IDD = IDD_EXAMPLE_DIALOG };
	CBounceButton	m_Btn3;
	CBounceButton	m_Btn2;
	CBounceButton	m_Btn1;
	CToolTipCtrl	m_ToolTip;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLEDLG_H__73B46E69_01FB_11D3_8647_00105AC69564__INCLUDED_)
