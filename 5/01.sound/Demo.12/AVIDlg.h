// AVIDlg.h : header file
//

#if !defined(AFX_AVIDLG_H__C1C94184_271F_4E1A_B423_4F20EC746B83__INCLUDED_)
#define AFX_AVIDLG_H__C1C94184_271F_4E1A_B423_4F20EC746B83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PicStatic.h" 

/////////////////////////////////////////////////////////////////////////////
// CAVIDlg dialog

class CAVIDlg : public CDialog
{
// Construction
public:
	CAVIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAVIDlg)
	enum { IDD = IDD_AVI_DIALOG };
    CPicStatic m_wndPic; 
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAVIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIDLG_H__C1C94184_271F_4E1A_B423_4F20EC746B83__INCLUDED_)
