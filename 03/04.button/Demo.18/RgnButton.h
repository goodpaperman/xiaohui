/********************************************* 
 REVISION LOG ENTRY 
 Revision By: Noam Rathaus
 Revised on 26/5/1999 14:57:00
 Comments: RgnButton.h : implementation file 
**********************************************/ 

#if !defined(AFX_RGNBUTTON_H__A60F9873_1365_11D3_A817_0090271A0C11__INCLUDED_)
#define AFX_RGNBUTTON_H__A60F9873_1365_11D3_A817_0090271A0C11__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RgnButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRgnButton window

class CRgnButton : public CButton
{
// Construction
public:
	CRgnButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRgnButton)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRgnButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRgnButton)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGNBUTTON_H__A60F9873_1365_11D3_A817_0090271A0C11__INCLUDED_)
