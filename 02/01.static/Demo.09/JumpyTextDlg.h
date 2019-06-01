// JumpyTextDlg.h : header file
//

#if !defined(AFX_JUMPYTEXTDLG_H__E1E3B9A9_5E9C_11D3_A785_0000214D19D7__INCLUDED_)
#define AFX_JUMPYTEXTDLG_H__E1E3B9A9_5E9C_11D3_A785_0000214D19D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CJumpyTextDlg dialog
#include "jumpyDraw.h"
#include "colourpicker.h"

class CJumpyTextDlg : public CDialog
{
// Construction
public:
	CJumpyTextDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CJumpyTextDlg)
	enum { IDD = IDD_JUMPYTEXT_DIALOG };
	CJumpyDraw	m_jumpyDraw;
    CColourPicker    m_GradientStart;
	CColourPicker    m_GradientEnd;
	CColourPicker    m_ColourText;
	CColourPicker    m_ColourShaddow;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJumpyTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CJumpyTextDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton2();
	afx_msg void OnButtonCustomAnimation();
	afx_msg void OnChangeEditText();
	afx_msg void OnChangeEditFont();
	afx_msg void OnChangeEditSizeFont();
	afx_msg void OnChangeEditTime();
	//}}AFX_MSG

    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUMPYTEXTDLG_H__E1E3B9A9_5E9C_11D3_A785_0000214D19D7__INCLUDED_)
