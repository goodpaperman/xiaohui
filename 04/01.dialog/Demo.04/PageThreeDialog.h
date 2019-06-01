#if !defined(AFX_PAGETHREEDIALOG_H__473BDB06_B52B_11D3_9C20_00E09803BB79__INCLUDED_)
#define AFX_PAGETHREEDIALOG_H__473BDB06_B52B_11D3_9C20_00E09803BB79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageThreeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageThreeDialog dialog

class CPageThreeDialog : public TStackedPage
{
// Construction
public:
	CPageThreeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageThreeDialog)
	enum { IDD = IDD_PAGE3 };
	CTreeCtrl	m_Tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageThreeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageThreeDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETHREEDIALOG_H__473BDB06_B52B_11D3_9C20_00E09803BB79__INCLUDED_)
