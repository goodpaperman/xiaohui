///////////////////////////////////////////////////////////////////////////////
//
//  Filename:       DualListDemoPropSheet.h
//  Description:    Demo Property Sheet that uses a property page that uses 
//                  the DualListManager class.
//
//  AUTHOR     :    Copyright (C) Steve Aube, February 2000
//                  SteveAube@yahoo.com
//
//                  You can reuse and redistribute this code, provided this 
//                  header is kept as is.
//
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUALLISTDEMOPROPSHEET_H__6B858D60_DFC4_11D3_8664_0050DA15E05C__INCLUDED_)
#define AFX_DUALLISTDEMOPROPSHEET_H__6B858D60_DFC4_11D3_8664_0050DA15E05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DualListDemoPropSheet.h : header file
//

#include "DualListDemoPropPage.h"

class CDualListDemoPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CDualListDemoPropSheet)

// Construction
public:
	CDualListDemoPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDualListDemoPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDualListDemoPropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDualListDemoPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDualListDemoPropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CDualListDemoPropPage   m_DualListPP;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUALLISTDEMOPROPSHEET_H__6B858D60_DFC4_11D3_8664_0050DA15E05C__INCLUDED_)

