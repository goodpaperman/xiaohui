#if !defined(AFX_MAINTOOLBAR_H__F83C8E1B_F33E_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_MAINTOOLBAR_H__F83C8E1B_F33E_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainToolBar.h : header file
//

#include "BCGToolBar.h"

/////////////////////////////////////////////////////////////////////////////
// CMainToolBar window

class CMainToolBar : public CBCGToolBar
{
// Construction
public:
	CMainToolBar();

// Attributes
public:

// Operations
public:
	void TogglePen ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainToolBar)
	//}}AFX_VIRTUAL

	virtual BOOL CanBeRestored () const
	{
		return TRUE;
	}

	virtual BOOL RestoreOriginalstate ();

// Implementation
public:
	virtual ~CMainToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainToolBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTOOLBAR_H__F83C8E1B_F33E_11D2_A713_0090274409AC__INCLUDED_)
