#if !defined(AFX_TESTPAGE1_H__5C87DCDA_0E81_11D2_8427_0000B43382FE__INCLUDED_)
#define AFX_TESTPAGE1_H__5C87DCDA_0E81_11D2_8427_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestPage1 dialog

class CTestPage1 : public CDialog
{
// Construction
public:
	CTestPage1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestPage1)
	enum { IDD = IDD_TESTPAGE1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestPage1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	virtual void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPAGE1_H__5C87DCDA_0E81_11D2_8427_0000B43382FE__INCLUDED_)
