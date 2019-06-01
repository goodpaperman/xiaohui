// ClrWellDemoDlg.h : header file
//

#if !defined(AFX_CLRWELLDEMODLG_H__D13C6689_9EED_11D2_8DF1_00104B2A8A87__INCLUDED_)
#define AFX_CLRWELLDEMODLG_H__D13C6689_9EED_11D2_8DF1_00104B2A8A87__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ColorBtn.h"
/////////////////////////////////////////////////////////////////////////////
// CClrWellDemoDlg dialog

class CClrWellDemoDlg : public CDialog
{
// Construction
public:
	CClrWellDemoDlg(CWnd* pParent = NULL);	// standard constructor
   CColorBtn m_ColorButton;

// Dialog Data
	//{{AFX_DATA(CClrWellDemoDlg)
	enum { IDD = IDD_CLRWELLDEMO_DIALOG };
	CSpinButtonCtrl	m_OuterBorderSpin;
	CSpinButtonCtrl	m_NumColsSpin;
	CSpinButtonCtrl	m_InnerBorderSpin;
	CButton	m_Update;
	CSpinButtonCtrl	m_WellHeightSpin;
	CEdit	m_WellHeightEdit;
	CSliderCtrl	m_SliderControl;
	BOOL	m_Aqua;
	BOOL	m_Black;
	BOOL	m_Blue;
	BOOL	m_Fuschia;
	BOOL	m_Gray;
	BOOL	m_Green;
	BOOL	m_Lime;
	BOOL	m_Maroon;
	BOOL	m_Navy;
	BOOL	m_Olive;
	BOOL	m_Purple;
	BOOL	m_Red;
	BOOL	m_Silver;
	BOOL	m_Teal;
	BOOL	m_White;
	BOOL	m_Yellow;
	BOOL	m_IsotropicWells;
	int		m_OuterBorder;
	int		m_InnerBorder;
	int		m_NumCols;
	int		m_WellHeight;
	int		m_Shape;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClrWellDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClrWellDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnIsotropicwells();
	afx_msg void OnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLRWELLDEMODLG_H__D13C6689_9EED_11D2_8DF1_00104B2A8A87__INCLUDED_)
