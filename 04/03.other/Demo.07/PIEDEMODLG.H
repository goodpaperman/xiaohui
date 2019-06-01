// PieDemoDlg.h : header file
//

#if !defined(AFX_PIEDEMODLG_H__C0A9AE26_30C2_11D2_813C_F042F77F7401__INCLUDED_)
#define AFX_PIEDEMODLG_H__C0A9AE26_30C2_11D2_813C_F042F77F7401__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPieDemoDlg dialog

#include "ColourPicker.h"
#include "PieChartCtrl.h"

class CPieDemoDlg : public CDialog
{
// Construction
public:
	COLORREF m_colorBack, m_colorText;
	CPieChartCtrl m_wndChart;

	CPieDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPieDemoDlg)
	enum { IDD = IDD_PIEDEMO_DIALOG };
	CColourPicker	m_wndTextColor;
	CColourPicker	m_wndBackColor;
	CString	m_strInfo;
	int		m_nAngle;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPieDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPieDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeChartTitle();
	afx_msg void OnAdd();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIEDEMODLG_H__C0A9AE26_30C2_11D2_813C_F042F77F7401__INCLUDED_)
