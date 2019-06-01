#if !defined(AFX_TESTPAGE3_H__5C87DCDC_0E81_11D2_8427_0000B43382FE__INCLUDED_)
#define AFX_TESTPAGE3_H__5C87DCDC_0E81_11D2_8427_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestPage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestPage3 dialog

class CTestPage3 : public CDialog
{
// Construction
public:
	CTestPage3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestPage3)
	enum { IDD = IDD_TESTPAGE3 };
	int		iTestInt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestPage3)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	virtual void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPAGE3_H__5C87DCDC_0E81_11D2_8427_0000B43382FE__INCLUDED_)
