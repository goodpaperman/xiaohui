#if !defined(AFX_ACTIVESTATUSBAR_H__04B11A86_B5B7_11D2_8398_26DCA8000000__INCLUDED_)
#define AFX_ACTIVESTATUSBAR_H__04B11A86_B5B7_11D2_8398_26DCA8000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ActiveStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CActiveStatusBar window

class CActiveStatusBar : public CStatusBar
{
// Construction
public:
	CActiveStatusBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveStatusBar)
        virtual BOOL OnCommand(WPARAM, LPARAM);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CActiveStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CActiveStatusBar)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVESTATUSBAR_H__04B11A86_B5B7_11D2_8398_26DCA8000000__INCLUDED_)
