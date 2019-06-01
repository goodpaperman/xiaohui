#if !defined(AFX_GFXFORMATCOLUMNDLG_H__865C7FA2_008E_11D2_83E0_0000B43382FE__INCLUDED_)
#define AFX_GFXFORMATCOLUMNDLG_H__865C7FA2_008E_11D2_83E0_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxFormatColumnDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGfxFormatColumnDlg dialog
class CGfxColumnManager;

class CGfxFormatColumnDlg : public CDialog
{
// Construction
public:
	void SetColumn(const int iId);
	CGfxFormatColumnDlg(CWnd* pParent = NULL);   // standard constructor

	CGfxColumnManager * pManager;
	CGfxColumnManager * pOrigManager;

// Dialog Data
	//{{AFX_DATA(CGfxFormatColumnDlg)
	enum { IDD = IDD_GFX_FORMATCOL };
	CComboBox	wndFormat;
	CListBox	wndCol;
	CString	csLabel;
	CString	csLabelDt;
	int		iWidth;
	CString	csType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxFormatColumnDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGfxFormatColumnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeActcol();
	virtual void OnOK();
	afx_msg void OnRdCenter();
	afx_msg void OnRdLeft();
	afx_msg void OnRdRight();
	afx_msg void OnKillfocusWidth();
	afx_msg void OnKillfocusLabelDt();
	afx_msg void OnKillfocusCdLabel();
	afx_msg void OnKillfocusCbFormat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXFORMATCOLUMNDLG_H__865C7FA2_008E_11D2_83E0_0000B43382FE__INCLUDED_)
