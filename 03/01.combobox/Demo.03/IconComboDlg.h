// IconComboDlg.h : header file
//

#if !defined(AFX_ICONCOMBODLG_H__9B4E5997_D255_44DE_9961_24F596AB2FF9__INCLUDED_)
#define AFX_ICONCOMBODLG_H__9B4E5997_D255_44DE_9961_24F596AB2FF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IconCombobox.h" 

/////////////////////////////////////////////////////////////////////////////
// CIconComboDlg dialog

class CIconComboDlg : public CDialog
{
// Construction
public:
	CIconComboDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIconComboDlg)
	enum { IDD = IDD_ICONCOMBO_DIALOG };
	CIconComboBox	m_combo2;
	CIconComboBox	m_combo1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIconComboDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONCOMBODLG_H__9B4E5997_D255_44DE_9961_24F596AB2FF9__INCLUDED_)
