#if !defined(AFX_GFXLISTTIP_H__31F5CEAC_E5CA_11D1_86E7_000000000000__INCLUDED_)
#define AFX_GFXLISTTIP_H__31F5CEAC_E5CA_11D1_86E7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxListTip.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGfxListTip window

class CGfxListTip : public CWnd
{
// Construction
public:
	CGfxListTip();

	void Show( CRect rectTitle, LPCTSTR lpszTitleText, int xoffset = 0);
	virtual BOOL Create( CWnd *pParentWnd);
// Attributes
public:
	CWnd *m_pParentWnd;	
	CRect m_rectTitle;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxListTip)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGfxListTip();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGfxListTip)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXLISTTIP_H__31F5CEAC_E5CA_11D1_86E7_000000000000__INCLUDED_)
