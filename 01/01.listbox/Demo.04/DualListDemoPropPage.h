///////////////////////////////////////////////////////////////////////////////
//
//  Filename:       DualListPropPage.h
//  Description:    Demo property page that uses the DualListManager class.
//
//  AUTHOR     :    Copyright (C) Steve Aube, February 2000
//                  SteveAube@yahoo.com
//
//                  You can reuse and redistribute this code, provided this 
//                  header is kept as is.
//
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUALLISTDEMOPROPPAGE_H__6B858D5F_DFC4_11D3_8664_0050DA15E05C__INCLUDED_)
#define AFX_DUALLISTDEMOPROPPAGE_H__6B858D5F_DFC4_11D3_8664_0050DA15E05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DualListManager.h"

class CDualListDemoPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDualListDemoPropPage)

// Construction
public:
	CDualListDemoPropPage();
	~CDualListDemoPropPage();

// Dialog Data
	//{{AFX_DATA(CDualListDemoPropPage)
	enum { IDD = IDD_PROP_PAGE_DUAL_LIST_DEMO };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDualListDemoPropPage)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDualListDemoPropPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CDualListManager    m_DualListManager;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUALLISTDEMOPROPPAGE_H__6B858D5F_DFC4_11D3_8664_0050DA15E05C__INCLUDED_)

