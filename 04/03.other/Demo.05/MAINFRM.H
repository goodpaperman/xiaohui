// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__28FA2C98_11B7_11D2_8437_0000B43382FE__INCLUDED_)
#define AFX_MAINFRM_H__28FA2C98_11B7_11D2_8437_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GfxSplitterWnd.h"
#include "GfxOutBarCtrl.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CGfxSplitterWnd	wndSplitter;
    //CSplitterWnd wndSplitter; 
	CGfxOutBarCtrl	wndBar;

	CImageList		imaLarge, imaSmall;

	CTreeCtrl		wndTree;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGfxLargeicon();
	afx_msg void OnUpdateGfxLargeicon(CCmdUI* pCmdUI);
	afx_msg void OnGfxSmallicon();
	afx_msg void OnUpdateGfxSmallicon(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg long OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__28FA2C98_11B7_11D2_8437_0000B43382FE__INCLUDED_)
