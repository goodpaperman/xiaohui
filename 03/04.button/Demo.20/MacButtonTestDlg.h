// MacButtonTestDlg.h : header file
//

#if !defined(AFX_MACBUTTONTESTDLG_H__994F45CD_C9CC_11D3_910F_0020AFBC499D__INCLUDED_)
#define AFX_MACBUTTONTESTDLG_H__994F45CD_C9CC_11D3_910F_0020AFBC499D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MacButtons.h"

/////////////////////////////////////////////////////////////////////////////
// CMacButtonTestDlg dialog

class CMacButtonTestDlg : public CDialog
{
// Construction
public:
	CFont Font;
	CMacButtonTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMacButtonTestDlg)
	enum { IDD = IDD_MACBUTTONTEST_DIALOG };
	CMacButton	m_buttonOK;
	CMacMoreButton	m_buttonMoreButton;
	CMacMoreButton	m_buttonMoreRadio;
	CMacMoreButton	m_buttonMoreCheckbox;
	CMacCheckBox	m_checkDisable;
	CMacRadioButton	m_radioNone;
	CMacRadioButton	m_radioCheck;
	CMacRadioButton	m_radioIcon;
	CMacRadioButton	m_radio1;
	CMacCheckBox	m_check1;
	CMacCheckBox	m_check2;
	CMacCheckBox	m_check3;
	CMacCheckBox	m_check4;
	CMacCheckBox	m_check5;
	CMacButton	m_button1;
	CMacButton	m_button2;
	CMacButton	m_button3;
	CMacButton	m_button4;
	CMacButton	m_button5;
	CMacButton	m_button6;
	//}}AFX_DATA
	CMacRadioButton	m_radio2;
	CMacRadioButton	m_radio3;
	CMacRadioButton	m_radio4;
	CMacRadioButton	m_radio5;
	CMacRadioButton	m_radioBitmap;
	CMacRadioButton	m_radioText;
	CMacRadioButton	m_radioRaised;
	CMacRadioButton	m_radioSunken;
	CMacRadioButton	m_radioCross;
	CMacRadioButton	m_radioTri;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMacButtonTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRect m_rectWindow;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMacButtonTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadioBitmap();
	afx_msg void OnRadioIcon();
	afx_msg void OnRadioText();
	afx_msg void OnRadioCheck();
	afx_msg void OnRadioCross();
	afx_msg void OnRadioRaised();
	afx_msg void OnRadioSunken();
	afx_msg void OnRadioNone();
	afx_msg void OnCheckEnable();
	//afx_msg void OnButtonSetFont();
	afx_msg void OnButtonMorebutton();
	afx_msg void OnButtonMorecheckbox();
	afx_msg void OnButtonMoreradio();
	afx_msg void OnRadioTristate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACBUTTONTESTDLG_H__994F45CD_C9CC_11D3_910F_0020AFBC499D__INCLUDED_)
