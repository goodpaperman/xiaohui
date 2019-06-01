// AutoCompletionDlg.h : header file
//

#if !defined(AFX_AUTOCOMPLETIONDLG_H__A2F51706_7F18_11D2_9B7D_006097F7F4CE__INCLUDED_)
#define AFX_AUTOCOMPLETIONDLG_H__A2F51706_7F18_11D2_9B7D_006097F7F4CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAutoCompletionDlg dialog

#include "AutoCompletionComboBox.h"

class CAutoCompletionDlg : public CDialog
{
// Construction
public:
	CAutoCompletionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAutoCompletionDlg)
	enum { IDD = IDD_AUTOCOMPLETION_DIALOG };
	CAutoCompletionComboBox	m_AutoCompletionComboBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoCompletionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAutoCompletionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOCOMPLETIONDLG_H__A2F51706_7F18_11D2_9B7D_006097F7F4CE__INCLUDED_)
