#if !defined(AFX_TESTDIALOG_H__2DB127E2_0DB2_11D2_8423_0000B43382FE__INCLUDED_)
#define AFX_TESTDIALOG_H__2DB127E2_0DB2_11D2_8423_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestDialog dialog
#include "GfxListCtrl.h"

class CTestDialog : public CDialog
{
// Construction
public:
	CTestDialog(CWnd* pParent = NULL);   // standard constructor
	CImageList lima, limah;
	CFont ftTimes;

	void CategoryCallBack(CGfxCategoryManager * pCatMan, long & lData);
	long GetExInfoCallback(LXHDREX * pLx);

// Dialog Data
	//{{AFX_DATA(CTestDialog)
	enum { IDD = IDD_TEST_DIALOG };
	CGfxListCtrl	wndList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDialog)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDIALOG_H__2DB127E2_0DB2_11D2_8423_0000B43382FE__INCLUDED_)
