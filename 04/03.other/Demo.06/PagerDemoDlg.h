// PagerDemoDlg.h : header file
//

#if !defined(AFX_PAGERDEMODLG_H__F07F030A_61EC_11D2_9582_0040053E0F5B__INCLUDED_)
#define AFX_PAGERDEMODLG_H__F07F030A_61EC_11D2_9582_0040053E0F5B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CJPagerCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPagerDemoDlg dialog

class CPagerDemoDlg : public CDialog
{
// Construction
public:
	CPagerDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPagerDemoDlg)
	enum { IDD = IDD_PAGERDEMO_DIALOG };
	CCJPagerCtrl m_Pager;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPagerDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CToolBar     m_wndToolBar;

	// Generated message map functions
	//{{AFX_MSG(CPagerDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGERDEMODLG_H__F07F030A_61EC_11D2_9582_0040053E0F5B__INCLUDED_)
