#if !defined(AFX_WNDFILEBROWSE_H__946CEB96_BABA_11D3_AEB4_000000000000__INCLUDED_)
#define AFX_WNDFILEBROWSE_H__946CEB96_BABA_11D3_AEB4_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndFileBrowse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWndFileBrowse window

class CWndFileBrowse : public CWnd
{
DECLARE_DYNAMIC(CWndFileBrowse)
// Construction
public:
	CWndFileBrowse();

// Attributes
public:

// Operations
public:
	void SetListSize();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndFileBrowse)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWndFileBrowse();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndFileBrowse)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//private:
//	HWND	m_hwndList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDFILEBROWSE_H__946CEB96_BABA_11D3_AEB4_000000000000__INCLUDED_)
