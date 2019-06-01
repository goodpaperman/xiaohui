// TreeListView.h : interface of the CTreeListView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREELISTVIEW_H__5FA5FACF_89C9_11D1_980B_004095E0DEFA__INCLUDED_)
#define AFX_TREELISTVIEW_H__5FA5FACF_89C9_11D1_980B_004095E0DEFA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TLFrame.h"
//#include "LantivUIDoc.h" 

class CTreeListView : public CFormView
{
protected: // create from serialization only
	CTreeListView();
	DECLARE_DYNCREATE(CTreeListView)

// Form Data
public:
	CImageList m_cImageList;

	//{{AFX_DATA(CMainView)
	enum { IDD = IDD_TREE_LIST_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CTLFrame m_wndTreeList;
private:
	BOOL m_TLInitialized;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeListView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
    //CLantivUIDoc* GetDocument(); 
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTreeListView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREELISTVIEW_H__5FA5FACF_89C9_11D1_980B_004095E0DEFA__INCLUDED_)
