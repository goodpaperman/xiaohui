// TipTestDlg.h : header file
//

#if !defined(AFX_TIPTESTDLG_H__9FDDB2C2_AB73_4882_B3F4_A527B0F1CEF4__INCLUDED_)
#define AFX_TIPTESTDLG_H__9FDDB2C2_AB73_4882_B3F4_A527B0F1CEF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ToolTipEx.h" 

/////////////////////////////////////////////////////////////////////////////
// CTipTestDlg dialog

class CTipTestDlg : public CDialog
{
// Construction
public:
	CTipTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTipTestDlg)
	enum { IDD = IDD_TIPTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipTestDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	CToolTipEx m_tooltip; 

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTipTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPTESTDLG_H__9FDDB2C2_AB73_4882_B3F4_A527B0F1CEF4__INCLUDED_)
