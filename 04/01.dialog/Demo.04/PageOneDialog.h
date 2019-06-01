#if !defined(AFX_PAGEONEDIALOG_H__473BDB04_B52B_11D3_9C20_00E09803BB79__INCLUDED_)
#define AFX_PAGEONEDIALOG_H__473BDB04_B52B_11D3_9C20_00E09803BB79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageOneDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageOneDialog dialog

class CPageOneDialog : public TStackedPage
{
// Construction
public:
	CPageOneDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageOneDialog)
	enum { IDD = IDD_PAGE1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageOneDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageOneDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEONEDIALOG_H__473BDB04_B52B_11D3_9C20_00E09803BB79__INCLUDED_)
