// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F83C8E0F_F33E_11D2_A713_0090274409AC__INCLUDED_)
#define AFX_MAINFRM_H__F83C8E0F_F33E_11D2_A713_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CFrameWnd CBCGFrameWnd

#include "MainToolBar.h"
#include "LinksBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CStringArray						m_astrFavoriteURLs;
	CMap<CString, LPCTSTR, int, int>	m_URLIcons;

	CMenu m_menuFavotites;

	HIMAGELIST	m_himSystem;
	CSize		m_SysImageSize;

// Operations
public:
	int BuildFavoritesMenu(LPCTSTR pszPath, int nStartPos, CMenu* pMenu);
	void SetAddress(LPCTSTR lpszUrl);
	void StartAnimation();
	BOOL IsFavoritesMenu (const CBCGToolbarMenuButton* pMenuButton);

	virtual void OnShowPopupMenu (CBCGPopupMenu* pMenuPopup);
	virtual BOOL OnDrawMenuImage (CDC* pDC,
									const CBCGToolbarMenuButton* pMenuButton, 
									const CRect& rectImage);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGMenuBar		m_wndMenuBar;
	CStatusBar		m_wndStatusBar;
	CMainToolBar	m_wndToolBar;
	CLinksBar		m_wndLinksBar;
	CReBar			m_wndReBar;
	CAnimateCtrl	m_wndAnimate;
	CComboBoxEx		m_wndAddress;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnLink1();
	afx_msg void OnViewAddressBar();
	afx_msg void OnUpdateViewAddressBar(CCmdUI* pCmdUI);
	afx_msg void OnViewLinksBar();
	afx_msg void OnUpdateViewLinksBar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	afx_msg LRESULT OnHelpCustomizeToolbars(WPARAM wp, LPARAM lp);
	afx_msg void OnNewAddress();
	afx_msg void OnNewAddressEnter();
	afx_msg void OnFavorite(UINT nID);
	afx_msg void OnHistory(UINT nID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F83C8E0F_F33E_11D2_A713_0090274409AC__INCLUDED_)
