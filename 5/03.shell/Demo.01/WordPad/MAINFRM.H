// mainfrm.h : interface of the CMainFrame class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "formatba.h"
#include "ruler.h"
#include "BCGToolBar.h"
#include "BCGMenuBar.h"
#include "BCGFrameWnd.h"

class CMainFrame : public CBCGFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	HICON m_hIconDoc;
	HICON m_hIconText;
	HICON m_hIconWrite;
	HICON GetIcon(int nDocType);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	virtual void OnShowPopupMenu (CBCGPopupMenu* pMenuPopup);

protected:
	void AdjustObjectSubmenu (CBCGPopupMenu* pMenuPopup);
	void AdjustColorsMenu (CBCGPopupMenu* pMenuPopup, UINT uiId);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CBCGMenuBar		m_wndMenuBar;
	CBCGToolBar		m_wndToolBar;
	CStatusBar		m_wndStatusBar;
	CFormatBar		m_wndFormatBar;
	CRulerBar		m_wndRulerBar;
protected:  // control bar embedded members
	BOOL CreateMenuBar();
	BOOL CreateToolBar();
	BOOL CreateFormatBar();
	BOOL CreateStatusBar();
	BOOL CreateRulerBar();
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnHelpFinder();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnFontChange();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnDevModeChange(LPTSTR lpDeviceName);
	afx_msg void OnViewCustomize();
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LONG OnBarState(UINT wParam, LONG lParam);
	afx_msg LONG OnOpenMsg(UINT wParam, LONG lParam);
	void OnToolsViewUserToolbar (UINT id);
	void OnUpdateToolsViewUserToolbar (CCmdUI* pCmdUI);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg LRESULT OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnChangeColor(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};
