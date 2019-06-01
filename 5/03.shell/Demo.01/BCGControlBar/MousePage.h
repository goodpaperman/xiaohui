#if !defined(AFX_MOUSEPAGE_H__0A141F64_E9CA_11D1_90D2_00A0C9B05590__INCLUDED_)
#define AFX_MOUSEPAGE_H__0A141F64_E9CA_11D1_90D2_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MousePage.h : header file
//

#include "bcgbarres.h"

/////////////////////////////////////////////////////////////////////////////
// CMousePage dialog

class CMousePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMousePage)

// Construction
public:
	CMousePage();
	~CMousePage();

// Operations:
protected:
	void EnableDblClickControls (BOOL bEnable = TRUE);
	BOOL SelectCommand (UINT uiCmd);

// Attributes:
protected:
	int									m_iCurrViewId;
	CImageList							m_ViewsImages;

// Dialog Data
	//{{AFX_DATA(CMousePage)
	enum { IDD = IDD_BCGBARRES_PROPPAGE4 };
	CListCtrl	m_wndListOfViews;
	CListBox	m_wndListOfCommands;
	CStatic	m_wndCommandDescription;
	CString	m_strCommandDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMousePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMousePage)
	afx_msg void OnNoDblcliick();
	afx_msg void OnUseDblcliick();
	afx_msg void OnSelchangeListOfCommands();
	afx_msg void OnItemchangedListViews(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSEPAGE_H__0A141F64_E9CA_11D1_90D2_00A0C9B05590__INCLUDED_)
