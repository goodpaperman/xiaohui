// JMultiColSampleDlg.h : header file
//

#if !defined(AFX_JMULTICOLSAMPLEDLG_H__2AF0C2AA_09E9_11D2_B3DF_00104B307E8C__INCLUDED_)
#define AFX_JMULTICOLSAMPLEDLG_H__2AF0C2AA_09E9_11D2_B3DF_00104B307E8C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "JComboBx.h"
/////////////////////////////////////////////////////////////////////////////
// CJMultiColSampleDlg dialog

class CJMultiColSampleDlg : public CDialog
{
// Construction
public:
	//CWnd * m_pWndPopDown;
	//void DisplayPopdownWindow();
	void OnInitShowTitletip();
	void OnInitCheckBox();
	void OnInitHideColumn();
	void OnInitSearchComboBox();
	CJMultiColSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CJMultiColSampleDlg)
	enum { IDD = IDD_JMULTICOLSAMPLE_DIALOG };
	CJComboBox	m_jcbCheckBox;
	CJComboBox	m_jcbShowTitletip;
	CJComboBox	m_jcbHideColumn;
	CJComboBox	m_jcbSearch;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJMultiColSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CJMultiColSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdit1();
	afx_msg void OnButton1();
	//afx_msg void OnDropdownCombo2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JMULTICOLSAMPLEDLG_H__2AF0C2AA_09E9_11D2_B3DF_00104B307E8C__INCLUDED_)
