// BtnTestDlg.h : header file
//

#if !defined(AFX_BTNTESTDLG_H__513213E5_B771_4FDA_A793_4C0126868A19__INCLUDED_)
#define AFX_BTNTESTDLG_H__513213E5_B771_4FDA_A793_4C0126868A19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BtnMenu.h" 
#include "HiButton.h" 
#include "SXButton.h" 
#include "MyTextButton.h" 

/////////////////////////////////////////////////////////////////////////////
// CBtnTestDlg dialog

class CBtnTestDlg : public CDialog
{
// Construction
public:
	CBtnTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBtnTestDlg)
	enum { IDD = IDD_BTNTEST_DIALOG };
    CBtnMenu m_btn; 
    CHiButton m_btn2; 
    CSXButton m_btn3; 
    CMyTextButton m_btn4; 
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBtnTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBtnTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtn2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BTNTESTDLG_H__513213E5_B771_4FDA_A793_4C0126868A19__INCLUDED_)
