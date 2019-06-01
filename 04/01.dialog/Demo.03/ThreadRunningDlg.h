#if !defined(AFX_THREADRUNNINGDLG_H__942D1241_B4AD_11D3_9CE3_E7C9978DB001__INCLUDED_)
#define AFX_THREADRUNNINGDLG_H__942D1241_B4AD_11D3_9CE3_E7C9978DB001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThreadRunningDlg.h : header file
//

#include "WndFileBrowse.h"

/////////////////////////////////////////////////////////////////////////////
// CThreadRunningDlg thread

class CThreadRunningDlg : public CWinThread
{
	DECLARE_DYNCREATE(CThreadRunningDlg)
protected:
	CThreadRunningDlg();           // protected constructor used by dynamic creation

// Attributes
public:
	HANDLE	m_hEventCreated;
	HWND		m_hWndParent;
	CWndFileBrowse m_wndFileBrowse;
	CWnd*		m_pAttachedView;
	int		m_nID;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreadRunningDlg)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CThreadRunningDlg();

	// Generated message map functions
	//{{AFX_MSG(CThreadRunningDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREADRUNNINGDLG_H__942D1241_B4AD_11D3_9CE3_E7C9978DB001__INCLUDED_)
