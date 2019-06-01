// DemoClockClassDlg.h : header file
//

#if !defined(AFX_DEMOCLOCKCLASSDLG_H__7217CB66_979D_11D3_A77C_00105AA7390A__INCLUDED_)
#define AFX_DEMOCLOCKCLASSDLG_H__7217CB66_979D_11D3_A77C_00105AA7390A__INCLUDED_

#include "GCClock.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoClockClassDlg dialog

class CDemoClockClassDlg : public CDialog
{
// Construction
public:
	CDemoClockClassDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoClockClassDlg)
	enum { IDD = IDD_DEMOCLOCKCLASS_DIALOG };
	int		m_iFormat;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoClockClassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoClockClassDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadio12hr();
	afx_msg void OnRadio24hr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CGCClock m_Clock;
	CGCClock m_StyleExampleA;
	CGCClock m_StyleExampleB;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOCLOCKCLASSDLG_H__7217CB66_979D_11D3_A77C_00105AA7390A__INCLUDED_)
