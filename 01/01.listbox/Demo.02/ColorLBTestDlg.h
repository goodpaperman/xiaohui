// ColorLBTestDlg.h : header file
//

#if !defined(AFX_COLORLBTESTDLG_H__766FAF69_5731_11D3_90AF_0020AFBC499D__INCLUDED_)
#define AFX_COLORLBTESTDLG_H__766FAF69_5731_11D3_90AF_0020AFBC499D__INCLUDED_

#include "ColorListBox.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CColorLBTestDlg dialog

class CColorLBTestDlg : public CDialog
{
// Construction
public:
	CColorLBTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CColorLBTestDlg)
	enum { IDD = IDD_COLORLBTEST_DIALOG };
	CColorListBox	m_lbColor;
	BOOL	m_bUseTabStops;
	BOOL	m_bUseColor;
	BOOL	m_bEnabled;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorLBTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CColorLBTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckTabStops();
	afx_msg void OnButtonAddString();
	afx_msg void OnButtonInsertString();
	afx_msg void OnCheckEnabled();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLBTESTDLG_H__766FAF69_5731_11D3_90AF_0020AFBC499D__INCLUDED_)
