#if !defined(AFX_PAGETWODIALOG_H__473BDB05_B52B_11D3_9C20_00E09803BB79__INCLUDED_)
#define AFX_PAGETWODIALOG_H__473BDB05_B52B_11D3_9C20_00E09803BB79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTwoDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageTwoDialog dialog

class CPageTwoDialog : public TStackedPage
{
// Construction
public:
	CPageTwoDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageTwoDialog)
	enum { IDD = IDD_PAGE2 };
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageTwoDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageTwoDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETWODIALOG_H__473BDB05_B52B_11D3_9C20_00E09803BB79__INCLUDED_)
