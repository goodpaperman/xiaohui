// SeparatorDemoDlg.h : header file
//

#if !defined(AFX_SEPARATORDEMODLG_H__D41D6FA6_6F88_11D2_9506_A0C64BC100C2__INCLUDED_)
#define AFX_SEPARATORDEMODLG_H__D41D6FA6_6F88_11D2_9506_A0C64BC100C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "separator.h"

/////////////////////////////////////////////////////////////////////////////
// CSeparatorDemoDlg dialog

class CSeparatorDemoDlg : public CDialog
{
// Construction
public:
	CSeparatorDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSeparatorDemoDlg)
	enum { IDD = IDD_SEPARATORDEMO_DIALOG };
	CSeparator  m_wndSep4;
	CSeparator  m_wndSep3;
	CSeparator	m_wndSep2;
	CSeparator	m_wndSep1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeparatorDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSeparatorDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEPARATORDEMODLG_H__D41D6FA6_6F88_11D2_9506_A0C64BC100C2__INCLUDED_)
