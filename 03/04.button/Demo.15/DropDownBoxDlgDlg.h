// DropDownBoxDlgDlg.h : header file
//

#if !defined(AFX_DROPDOWNBOXDLGDLG_H__58EB9227_27DF_11D3_B296_006097BEAB13__INCLUDED_)
#define AFX_DROPDOWNBOXDLGDLG_H__58EB9227_27DF_11D3_B296_006097BEAB13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDropDownBoxDlgDlg dialog

#include "ChoiceWindowBtn.h"


class CDropDownBoxDlgDlg : public CDialog
{
// Construction
public:
	CChoiceWindowBtn m_btnDropDown;
	CDropDownBoxDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDropDownBoxDlgDlg)
	enum { IDD = IDD_DROPDOWNBOXDLG_DIALOG };
	CString	m_strNewValue;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropDownBoxDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDropDownBoxDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeValue();
	afx_msg void OnAdd();
	afx_msg void OnCheckall();
	afx_msg void OnRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPDOWNBOXDLGDLG_H__58EB9227_27DF_11D3_B296_006097BEAB13__INCLUDED_)
