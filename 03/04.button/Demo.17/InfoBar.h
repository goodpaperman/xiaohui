#if !defined(AFX_INFOBAR_H__2EC7BF33_ED05_11D3_B07F_0050DAB826FF__INCLUDED_)
#define AFX_INFOBAR_H__2EC7BF33_ED05_11D3_B07F_0050DAB826FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoBar.h : header file
//
#define WM_DESTROYINFOBAR WM_USER + 5

/////////////////////////////////////////////////////////////////////////////
// CInfoBar dialog

class CInfoBar : public CDialog
{
	CWnd* pParentDlg; 
// Construction
public:
	CInfoBar(CWnd* pParent = NULL);   // standard constructor
	BOOL  Create();
	CWnd* GetWnd(){ return this; };

// Dialog Data
	//{{AFX_DATA(CInfoBar)
	enum { IDD = IDD_INFO_BAR };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfoBar)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOBAR_H__2EC7BF33_ED05_11D3_B07F_0050DAB826FF__INCLUDED_)
