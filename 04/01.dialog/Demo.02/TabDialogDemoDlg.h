// TabDialogDemoDlg.h : header file
//

#if !defined(AFX_TABDIALOGDEMODLG_H__02A8BC78_DA1A_11D3_83D4_00105ABE120C__INCLUDED_)
#define AFX_TABDIALOGDEMODLG_H__02A8BC78_DA1A_11D3_83D4_00105ABE120C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TabDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CTabDialogDemoDlg dialog

class CTabDialogDemoDlg : public CTabDialog
{
// Construction
public:
	CTabDialogDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTabDialogDemoDlg)
	enum { IDD = IDD_TABDIALOGDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDialogDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTabDialogDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDIALOGDEMODLG_H__02A8BC78_DA1A_11D3_83D4_00105ABE120C__INCLUDED_)
