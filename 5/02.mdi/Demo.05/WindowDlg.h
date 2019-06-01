#if !defined(AFX_WINDOWDLG_H__78F7D624_E5F6_11D3_91A0_60354FC10000__INCLUDED_)
#define AFX_WINDOWDLG_H__78F7D624_E5F6_11D3_91A0_60354FC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WindowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWindowDlg dialog
#include "resource.h"

class CWindowDlg : public CDialog
{
// Construction
public:
	CWindowDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWindowDlg)
	enum { IDD = IDD_WINDOWLIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Refresh();

	// Generated message map functions
	//{{AFX_MSG(CWindowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseBtn();
	afx_msg void OnSaveBtn();
	afx_msg void OnActivateBtn();
	afx_msg void OnSelchangeWindowlist();
	afx_msg void OnDblclkWindowlist();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWDLG_H__78F7D624_E5F6_11D3_91A0_60354FC10000__INCLUDED_)
