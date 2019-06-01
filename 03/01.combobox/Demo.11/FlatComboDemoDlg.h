// FlatComboDemoDlg.h : header file
//

#if !defined(AFX_FLATCOMBODEMODLG_H__E5237FC6_2921_11D3_8730_000000000000__INCLUDED_)
#define AFX_FLATCOMBODEMODLG_H__E5237FC6_2921_11D3_8730_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CJColorPicker.h"
#include "CJFlatComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// CFlatComboDemoDlg dialog

class CFlatComboDemoDlg : public CDialog
{
// Construction
public:
	CFlatComboDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFlatComboDemoDlg)
	enum { IDD = IDD_FLATCOMBODEMO_DIALOG };
	CCJColorPicker	m_DLTextColor;
	CCJColorPicker	m_DLBackColor;
	CCJColorPicker	m_DDTextColor;
	CCJColorPicker	m_DDBackColor;
	CCJFlatComboBox	m_DDCombo;
	CCJFlatComboBox	m_DLCombo;
	BOOL	m_bDDAutoComp;
	BOOL	m_bDDDisable;
	BOOL	m_bDLDisable;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatComboDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	COLORREF	m_clrDLText;
	COLORREF	m_clrDLBack;
	COLORREF	m_clrDDText;
	COLORREF	m_clrDDBack;

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFlatComboDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDroplistDisable();
	afx_msg void OnDropdownDisable();
	afx_msg void OnDropdownAutocomp();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg void OnSelEndOK(UINT lParam, LONG wParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATCOMBODEMODLG_H__E5237FC6_2921_11D3_8730_000000000000__INCLUDED_)
