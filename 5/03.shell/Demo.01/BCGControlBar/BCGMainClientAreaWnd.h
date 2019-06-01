#if !defined(AFX_BCGMAINCLIENTAREAWND_H__08B9EC05_DCE3_11D1_A64F_00A0C93A70EC__INCLUDED_)
#define AFX_BCGMAINCLIENTAREAWND_H__08B9EC05_DCE3_11D1_A64F_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGMainClientAreaWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBCGMainClientAreaWnd window

class CBCGMainClientAreaWnd : public CWnd
{
// Construction
public:
	CBCGMainClientAreaWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGMainClientAreaWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGMainClientAreaWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGMainClientAreaWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LRESULT OnSetMenu (WPARAM wp, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGMAINCLIENTAREAWND_H__08B9EC05_DCE3_11D1_A64F_00A0C93A70EC__INCLUDED_)
