// SampleDlg.h : header file
//

#if !defined(AFX_SAMPLEDLG_H__2B159559_B4C6_11D3_9C1F_00E09803BB79__INCLUDED_)
#define AFX_SAMPLEDLG_H__2B159559_B4C6_11D3_9C1F_00E09803BB79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg dialog

class CSampleDlg : public TStackedDialog
{
private:
  BOOL m_bTimerActive;

// Construction
public:
	CSampleDlg(CWnd* pParent = NULL);	// standard constructor

  virtual TStackedPage *CreatePage(UINT nId);
  virtual void OnPageChanged(UINT nId, BOOL bActivated);

// Dialog Data
	//{{AFX_DATA(CSampleDlg)
	enum { IDD = IDD_SAMPLE_DIALOG };
	CListBox	m_List;
	CComboBox	m_Combo;
  CButton m_Page1Btn;
  CButton m_Page2Btn;
  CButton m_Page3Btn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnSelchangeList();
	afx_msg void OnPage1();
	afx_msg void OnPage2();
	afx_msg void OnPage3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnScan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEDLG_H__2B159559_B4C6_11D3_9C1F_00E09803BB79__INCLUDED_)
