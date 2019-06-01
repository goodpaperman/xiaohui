// PropListBoxDlg.h : header file
//

#if !defined(AFX_PROPLISTBOXDLG_H__B8AE534A_3892_11D4_BC48_00105AA2186F__INCLUDED_)
#define AFX_PROPLISTBOXDLG_H__B8AE534A_3892_11D4_BC48_00105AA2186F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PropertyList.h"

/////////////////////////////////////////////////////////////////////////////
// CPropListBoxDlg dialog

class CPropListBoxDlg : public CDialog
{
// Construction
public:
	CPropListBoxDlg(CWnd* pParent = NULL);	// standard constructor

	~CPropListBoxDlg();

// Dialog Data
	//{{AFX_DATA(CPropListBoxDlg)
	enum { IDD = IDD_PROPLISTBOX_DIALOG };
	CPropertyList	m_propList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropListBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	CPropertyItem *propItem1,*propItem2,*propItem3,*propItem4,*propItem5;
	CPropertyItem *propItem6,*propItem7,*propItem8,*propItem9,*propItem10;
	CPropertyItem *propItem11,*propItem12,*propItem13,*propItem14,*propItem15;
	CPropertyItem *propItem16,*propItem17;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPropListBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPLISTBOXDLG_H__B8AE534A_3892_11D4_BC48_00105AA2186F__INCLUDED_)
