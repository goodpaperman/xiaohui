#if !defined(AFX_VIEWMANAGER_H__2A1E6B81_0BC9_11D3_933D_0000F0510AC9__INCLUDED_)
#define AFX_VIEWMANAGER_H__2A1E6B81_0BC9_11D3_933D_0000F0510AC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewManager.h : header file
//

#include <afxcoll.h>
#include "WindowTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CViewManager window

class CViewManager : public CControlBar
{
	DECLARE_DYNAMIC(CViewManager)

private:
	CSize m_sizeDefault;
	CSize m_sizeMRU;
	int   m_nLMargin;
	UINT  m_nDockID;

// Construction
public:
	CViewManager();

// Attributes
public:

// Operations
public:
    virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
        CSize sizeDefault, UINT nID,
        DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP);
	
	void OnActivateView(const BOOL bActivate, CView* pView);
	int  GetWindowNum();
	void SetViewName(const TCHAR* cs, CView* pView);
	void RemoveAll();
	void RemoveView(CView* pView);
	void AddView(const TCHAR* csName, CView* pView);

	CPtrArray	 m_arViews;
	CStringArray m_arViewTitles;
	BOOL		 m_bClosing;

// Overrides
	virtual void DoPaint(CDC* pDC);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewManager)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CViewManager();
	BOOL CreateViewManager(CMDIFrameWnd* pMDIFrameWnd, UINT uID);
	CWindowTabCtrl m_ViewTabCtrl;
    CImageList     m_ViewTabImages;

	// Generated message map functions
protected:

	void DrawGripper(CDC* pDC);

	//{{AFX_MSG(CViewManager)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
    BOOL OnViewManagerToolTip(UINT id, NMHDR* pTTTStruct, LRESULT * pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWMANAGER_H__2A1E6B81_0BC9_11D3_933D_0000F0510AC9__INCLUDED_)
