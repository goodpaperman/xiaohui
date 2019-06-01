// AlexfHistogramDlg.h : header file
//

#if !defined(AFX_ALEXFHISTOGRAMDLG_H__EE1F7ACB_2661_11D3_9865_868E4C4284CA__INCLUDED_)
#define AFX_ALEXFHISTOGRAMDLG_H__EE1F7ACB_2661_11D3_9865_868E4C4284CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AlexfStaticHistogram.h"

/////////////////////////////////////////////////////////////////////////////
// CAlexfHistogramDlg dialog

class CAlexfHistogramDlg : public CDialog
{
// Construction
public:
	CAlexfHistogramDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAlexfHistogramDlg)
	enum { IDD = IDD_ALEXFHISTOGRAM_DIALOG };
	CAlexfStaticHistogram	m_sHistogram;
	int		m_iRadio1;
	int		m_iRadio3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlexfHistogramDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAlexfHistogramDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALEXFHISTOGRAMDLG_H__EE1F7ACB_2661_11D3_9865_868E4C4284CA__INCLUDED_)
