// TestBedSmartEditDlg.h : header file
//

#if !defined(AFX_TESTBEDSMARTEDITDLG_H__0B514388_CADB_11D3_BD1E_0060520365FB__INCLUDED_)
#define AFX_TESTBEDSMARTEDITDLG_H__0B514388_CADB_11D3_BD1E_0060520365FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "AFEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CTestBedSmartEditDlg dialog

class CTestBedSmartEditDlg : public CDialog
{
// Construction
public:
	CTestBedSmartEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestBedSmartEditDlg)
	enum { IDD = IDD_TESTBEDSMARTEDIT_DIALOG };
	CAFEdit	m_edtEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBedSmartEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestBedSmartEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBEDSMARTEDITDLG_H__0B514388_CADB_11D3_BD1E_0060520365FB__INCLUDED_)
