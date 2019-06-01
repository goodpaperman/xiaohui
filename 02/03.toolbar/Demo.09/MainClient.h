#if !defined(AFX_MAINCLIENT_H__0ED95743_DBDF_11D2_9146_0060082BE95D__INCLUDED_)
#define AFX_MAINCLIENT_H__0ED95743_DBDF_11D2_9146_0060082BE95D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainClient.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainClient window

class CMainClient : public CWnd
/***************************************************************\
| This class implements the MDI client window. It goes to work	|
| after subbclaess in CMainFrams::OnCreate.						|
| It's goal is to notify the frame window when a menu is changed|
| ot when there are no open windows.							|
| Changed menu is notified with the message 'WM_MDISETMENU',	|
| implemented in 'DefWindowProc'.								|
| Closed (and opened) windows is notified in 'OnParentNotify'.	|
\***************************************************************/
{
// Construction
public:
	CMainClient();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainClient)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainClient();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainClient)
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nChilds;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINCLIENT_H__0ED95743_DBDF_11D2_9146_0060082BE95D__INCLUDED_)
