// CButtonXDlg.h : header file
//

#if !defined(AFX_CBUTTONXDLG_H__EDD5DCD9_4629_11D4_AB66_005004CF7A2A__INCLUDED_)
#define AFX_CBUTTONXDLG_H__EDD5DCD9_4629_11D4_AB66_005004CF7A2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HotButton.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CCButtonXDlg dialog

class CCButtonXDlg : public CDialog
{
// Construction
public:
	CCButtonXDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCButtonXDlg)
	enum { IDD = IDD_HOTBUTTON_DIALOG };
	CHotButton	m_btnx;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCButtonXDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCButtonXDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnContacts();
	afx_msg void OnHot();
	afx_msg void OnUseBitmap();
	afx_msg void OnXBmp();
	afx_msg void OnCheckBmp();
	afx_msg void OnFolderBmp();
	afx_msg void OnPaperBmp();
	afx_msg void OnPrinterBmp();
	afx_msg void OnRarrow();
	afx_msg void OnLarrow();
	afx_msg void OnLed();
	afx_msg void OnEllipse();
	afx_msg void OnBinoc();
	afx_msg void OnClockBmp();
	afx_msg void OnRedflagBmp();
	afx_msg void OnBannedBmp();
	afx_msg void OnAppDefined();
	afx_msg void OnAbout();
	//}}AFX_MSG
	afx_msg void OnContactHotClicked();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBUTTONXDLG_H__EDD5DCD9_4629_11D4_AB66_005004CF7A2A__INCLUDED_)
