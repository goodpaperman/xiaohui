// CRgnedButtonDlg.h : header file
//

#if !defined(AFX_CRGNEDBUTTONDLG_H__A60F986B_1365_11D3_A817_0090271A0C11__INCLUDED_)
#define AFX_CRGNEDBUTTONDLG_H__A60F986B_1365_11D3_A817_0090271A0C11__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RgnButton.h"
/////////////////////////////////////////////////////////////////////////////
// CCRgnedButtonDlg dialog

class CCRgnedButtonDlg : public CDialog
{
// Construction
public:
	CCRgnedButtonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCRgnedButtonDlg)
	enum { IDD = IDD_CRGNEDBUTTON_DIALOG };
	CRgnButton	m_Btn3;
	CRgnButton	m_Btn2;
	CRgnButton	m_Btn1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCRgnedButtonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCRgnedButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRGNEDBUTTONDLG_H__A60F986B_1365_11D3_A817_0090271A0C11__INCLUDED_)
