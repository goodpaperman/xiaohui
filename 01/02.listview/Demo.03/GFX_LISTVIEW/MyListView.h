#if !defined(AFX_MYLISTVIEW_H__B4FCAE2D_2092_11D2_8476_0000B43382FE__INCLUDED_)
#define AFX_MYLISTVIEW_H__B4FCAE2D_2092_11D2_8476_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListView view
#include "GfxListView.h"

class CCGfxListViewDoc;

class CMyListView : public CGfxListView
{
protected:
	CMyListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyListView)

// Attributes
public:
	CCGfxListViewDoc* GetDocument();


	CImageList lima, limah;
	void CategoryCallBack(CGfxCategoryManager * pCatMan, long & lData);
	void GetTextCallback(int iIndex, int iSubItem, long lCode, CString &cs);
	long GetExInfoCallback(LXHDREX * pLx);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListView)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTestCat();
	afx_msg void OnUpdateTestCat(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _DEBUG  // debug version in GfxListView.cpp
inline CCGfxListViewDoc* CMyListView::GetDocument()
   { return (CCGfxListViewDoc*)m_pDocument; }
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTVIEW_H__B4FCAE2D_2092_11D2_8476_0000B43382FE__INCLUDED_)
