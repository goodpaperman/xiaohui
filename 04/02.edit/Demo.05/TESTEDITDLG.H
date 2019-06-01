#if !defined(AFX_TESTEDITDLG_H__978AA09D_2DDE_11D2_BE76_0080ADB7F1BB__INCLUDED_)
#define AFX_TESTEDITDLG_H__978AA09D_2DDE_11D2_BE76_0080ADB7F1BB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestEditDlg.h : header file
//
#include "Masked.h"
/////////////////////////////////////////////////////////////////////////////
// CTestEditDlg dialog

class CTestEditDlg : public CDialog
{
// Construction
public:
	CTestEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestEditDlg)
	enum { IDD = IDD_TESTEDIT_DIALOG };
	CMaskEdit	m_EditPCodeCtrl;
	CMaskEdit	m_EditIPCtrl;
	CMaskEdit	m_EditPhoneCtrl;
	CDateEdit	m_DateEditCtrl;
	CTimeEdit	m_TimeEditCtrl;
	CString		m_EditMaxH;
	CString		m_EditMaxM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestEditDlg)
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTEDITDLG_H__978AA09D_2DDE_11D2_BE76_0080ADB7F1BB__INCLUDED_)
