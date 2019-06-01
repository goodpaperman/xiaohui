/****************************************************************************************
//	Copyright (c) 1999, Huang Shansong (╩фи╫ки)
//	Department of Automation, Tsinghua University, Beijing, P.R.China
//	hsssp@263.net or pingersoft@263.net
//	You may freely use or modify this code provided this 
//	copyright is included in all derived versions.
//	If you enhance it, please mail one copy to me. Thanks.
****************************************************************************************/

#if !defined(AFX_OPTIONTREECTRL_H__C422DA81_B1D3_11D2_9CCB_000021001339__INCLUDED_)
#define AFX_OPTIONTREECTRL_H__C422DA81_B1D3_11D2_9CCB_000021001339__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Optionstreectrl.h : header file
//
class COptions;
/////////////////////////////////////////////////////////////////////////////
// COptionsTreeCtrl window

class COptionsTreeCtrl : public CTreeCtrl
{
// Construction
public:
	COptionsTreeCtrl();

// Attributes
public:
	COptions* m_pOptions;
// Operations
public:
	void Initialize(char* strExpand);
	void ExpandItem(HTREEITEM hItem);
	void EnableItem(HTREEITEM hItem, BOOL enable, BOOL self);
	void InvalidateItem(HTREEITEM hItem, BOOL self);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptionsTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(COptionsTreeCtrl)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONTREECTRL_H__C422DA81_B1D3_11D2_9CCB_000021001339__INCLUDED_)
