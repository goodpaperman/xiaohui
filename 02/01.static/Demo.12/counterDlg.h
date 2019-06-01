// counterDlg.h : header file
//

#if !defined(AFX_COUNTERDLG_H__C012E028_AB9E_11D1_A717_AC9DD64C3607__INCLUDED_)
#define AFX_COUNTERDLG_H__C012E028_AB9E_11D1_A717_AC9DD64C3607__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "cdxCDynamicDialog.h"

#include "Digiutil.h"
/////////////////////////////////////////////////////////////////////////////
// CCounterDlg dialog

class CCounterDlg : public cdxCDynamicDialog
{
// Construction
public:
	CCounterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCounterDlg)
	enum { IDD = IDD_COUNTER_DIALOG };
	CStatic	m_Frame;
	CDigistring	m_Text2;
	CDigiScroll	m_ScrollText;
	CDigiClock	m_TheTime;
	CDigistring	m_Digistring;
	BOOL	m_bSmooth;
	int		m_14Status;
	BOOL	m_bProportional;
	CString	m_LedEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCounterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCounterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSmoothCheck();
	afx_msg void On14Radio();
	afx_msg void On7Radio();
	afx_msg void OnPropCheck();
	afx_msg void OnChangeLedEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		// Text, meters and counters...
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COUNTERDLG_H__C012E028_AB9E_11D1_A717_AC9DD64C3607__INCLUDED_)
