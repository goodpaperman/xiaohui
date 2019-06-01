///////////////////////////////////////////////////////////////////////////////
//
//  Filename:       DualListDemoDialog.h
//  Description:    Demo dialog box that uses the DualListManager class.
//
//  AUTHOR     :    Copyright (C) Steve Aube, February 2000
//                  SteveAube@yahoo.com
//
//                  You can reuse and redistribute this code, provided this 
//                  header is kept as is.
//
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUALLISTDEMODIALOG_H__6B858D5E_DFC4_11D3_8664_0050DA15E05C__INCLUDED_)
#define AFX_DUALLISTDEMODIALOG_H__6B858D5E_DFC4_11D3_8664_0050DA15E05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DualListManager.h"

/////////////////////////////////////////////////////////////////////////////
// CDualListDemoDialog dialog

class CDualListDemoDialog : public CDialog
{
// Construction
public:
	CDualListDemoDialog(CWnd* pParent = NULL);   // standard constructor
    ~CDualListDemoDialog(void);

// Dialog Data
	//{{AFX_DATA(CDualListDemoDialog)
	enum { IDD = IDD_DIALOG_DUAL_LIST_DEMO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDualListDemoDialog)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDualListDemoDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CDualListManager    m_DualListManager;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUALLISTDEMODIALOG_H__6B858D5E_DFC4_11D3_8664_0050DA15E05C__INCLUDED_)

