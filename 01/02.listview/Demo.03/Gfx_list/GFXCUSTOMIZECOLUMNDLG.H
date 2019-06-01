#if !defined(AFX_GFXCUSTOMIZECOLUMNDLG_H__A9703E02_FFCA_11D1_83DC_0000B43382FE__INCLUDED_)
#define AFX_GFXCUSTOMIZECOLUMNDLG_H__A9703E02_FFCA_11D1_83DC_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxCustomizeColumnDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGfxCustomizeColumnDlg dialog
class CGfxColumnManager;


class CGfxCustomizeColumnDlg : public CDialog
{
// Construction
public:
	CGfxCustomizeColumnDlg(CWnd* pParent = NULL);   // standard constructor

	CGfxColumnManager * pManager;

// Dialog Data
	//{{AFX_DATA(CGfxCustomizeColumnDlg)
	enum { IDD = IDD_GFX_CUSTOMIZECOL };
	CListBox	wndFreeCol;
	CListBox	wndCol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxCustomizeColumnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGfxCustomizeColumnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnMovedown();
	afx_msg void OnMoveup();
	virtual void OnOK();
	afx_msg void OnSelchangeActcol();
	afx_msg void OnSelchangeFreecol();
	afx_msg void OnDblclkActcol();
	afx_msg void OnDblclkFreecol();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXCUSTOMIZECOLUMNDLG_H__A9703E02_FFCA_11D1_83DC_0000B43382FE__INCLUDED_)
