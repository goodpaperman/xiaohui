// myothelloDlg.h : header file
//

#if !defined(AFX_MYOTHELLODLG_H__4E7F8E28_D1AB_427D_8D6D_309BECD95EB7__INCLUDED_)
#define AFX_MYOTHELLODLG_H__4E7F8E28_D1AB_427D_8D6D_309BECD95EB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyothelloDlg dialog
#include "chessboard1.h"
class CMyothelloDlg : public CDialog
{
// Construction
public:
	CChessBoard  m_chess;
	CMyothelloDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CMyothelloDlg)
	enum { IDD = IDD_MYOTHELLO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyothelloDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyothelloDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnAboutbox();
	afx_msg void OnNewgame();
	afx_msg void OnEasy();
	afx_msg void OnMid();
	afx_msg void OnAdv();
	afx_msg void OnMoveback();
	//}}AFX_MSG
	afx_msg void OnRecalc(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYOTHELLODLG_H__4E7F8E28_D1AB_427D_8D6D_309BECD95EB7__INCLUDED_)
