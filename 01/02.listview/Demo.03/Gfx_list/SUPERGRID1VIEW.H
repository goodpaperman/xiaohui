// SuperGrid1View.h : interface of the CSuperGrid1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUPERGRID1VIEW_H__CDC4A642_FED4_11D1_83D4_0000B43382FE__INCLUDED_)
#define AFX_SUPERGRID1VIEW_H__CDC4A642_FED4_11D1_83D4_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GfxListCtrl.h"

class CSuperGrid1View : public CFormView
{
protected: // create from serialization only
	CSuperGrid1View();
	DECLARE_DYNCREATE(CSuperGrid1View)

	CImageList lima, limah;
	CFont ftTimes;

	int iSelBmp;

public:
	//{{AFX_DATA(CSuperGrid1View)
	enum { IDD = IDD_GFXLIST_FORM };
	CGfxListCtrl	wndList;
	//}}AFX_DATA

// Attributes
public:

//	CGfxColumnManager	cManager;

	CSuperGrid1Doc* GetDocument();

	void CategoryCallBack(CGfxCategoryManager * pCatMan, long & lData);
	void GetTextCallback(int iIndex, int iSubItem, long lCode, CString &cs);
	long GetExInfoCallback(LXHDREX * pLx);

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperGrid1View)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSuperGrid1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSuperGrid1View)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetdispinfoList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomheader();
	afx_msg void OnFormatheader();
	afx_msg void OnTestcat();
	afx_msg void OnUpdateTestcat(CCmdUI* pCmdUI);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddanitem();
	afx_msg void OnDestroy();
	afx_msg void OnBlendbmp();
	afx_msg void OnUpdateBlendbmp(CCmdUI* pCmdUI);
	afx_msg void OnTrybitmap1();
	afx_msg void OnUpdateTrybitmap1(CCmdUI* pCmdUI);
	afx_msg void OnTrybitmap2();
	afx_msg void OnUpdateTrybitmap2(CCmdUI* pCmdUI);
	afx_msg void OnDraggablecol();
	afx_msg void OnUpdateDraggablecol(CCmdUI* pCmdUI);
	afx_msg void OnGridh();
	afx_msg void OnUpdateGridh(CCmdUI* pCmdUI);
	afx_msg void OnGridv();
	afx_msg void OnUpdateGridv(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnTestdao();
	afx_msg void OnUpdateTestdao(CCmdUI* pCmdUI);
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAutopreview();
	afx_msg void OnUpdateAutopreview(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnListExNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnListCmdUpdate(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SuperGrid1View.cpp
inline CSuperGrid1Doc* CSuperGrid1View::GetDocument()
   { return (CSuperGrid1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERGRID1VIEW_H__CDC4A642_FED4_11D1_83D4_0000B43382FE__INCLUDED_)
