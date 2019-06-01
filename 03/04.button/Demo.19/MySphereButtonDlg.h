// MySphereButtonDlg.h : header file
//

#if !defined(AFX_MYSPHEREBUTTONDLG_H__44648A96_9ABA_11D2_9E44_0020182F735A__INCLUDED_)
#define AFX_MYSPHEREBUTTONDLG_H__44648A96_9ABA_11D2_9E44_0020182F735A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UniButton.h"

/////////////////////////////////////////////////////////////////////////////
// CMySphereButtonDlg dialog

class CMySphereButtonDlg : public CDialog
{
// Construction
public:
	enum {MY_BTN1 = 1001, MY_BTN2 = 1002, MY_BTN3 = 1003, MY_BTN4 = 1004, MY_BTN5 = 1005, MY_BTN6 = 1006, MY_BTN7 = 1007, MY_BTN8 = 1008};
	enum {MY_BTN9 = 1009, MY_BTN10 = 1010, MY_BTN11 = 1011, MY_BTN12 = 1012, MY_BTN13 = 1013, MY_BTN14 = 1014, MY_BTN15 = 10015, MY_BTN16=1016};
	enum {MY_BTN17 = 1017, MY_BTN18 = 1018};
	CMySphereButtonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMySphereButtonDlg)
	enum { IDD = IDD_MYSPHEREBUTTON_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySphereButtonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CUniButton m_Btn1, m_Btn2, m_Btn3, m_Btn4, m_Btn5, m_Btn6, m_Btn7, m_Btn8, m_Btn9, m_Btn10;
	CUniButton m_Btn11, m_Btn12, m_Btn13, m_Btn14, m_Btn15, m_Btn16, m_Btn17, m_Btn18;

	// Generated message map functions
	//{{AFX_MSG(CMySphereButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPHEREBUTTONDLG_H__44648A96_9ABA_11D2_9E44_0020182F735A__INCLUDED_)
