/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Jörg König
// All rights reserved
//
// This file is part of the completely free tetris clone "CGTetris".
//
// This is free software.
// You may redistribute it by any means providing it is not sold for profit
// without the authors written consent.
//
// No warrantee of any kind, expressed or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_MAINDLG_H__35EAD7EE_009B_11D2_A729_000000000000__INCLUDED_)
#define AFX_MAINDLG_H__35EAD7EE_009B_11D2_A729_000000000000__INCLUDED_

#include "BitmapPropSheet.h"
#include "TetrisDlg.h"	// Added by ClassView
#include "OptionsDlg.h"	// Added by ClassView
#include "AboutDlg.h"	// Added by ClassView
#include "RoundButton.h"	// Added by ClassView
#include "ScoreDlg.h"	// Added by ClassView
#include "PropSheetTab.h"	// Added by ClassView
#include "HelpDlg.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainDlg

class CMainDlg : public CBitmapPropSheet
{
	DECLARE_DYNAMIC(CMainDlg)

// Construction
public:
	CMainDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMainDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

	void	LoadAllStrings();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void	SetHiScore(UINT uScore, UINT uLevel);

	virtual ~CMainDlg();

protected:
	void	SetPageTitle(CBitmapPropPage & page, UINT uResID);

	// Generated message map functions
protected:
	CHelpDlg m_HelpDlg;
	CPropSheetTab m_Tab;
	CScoreDlg m_ScoreDlg;
	CRoundButton m_btnEndGame;
	CAboutDlg m_AboutDlg;
	COptionsDlg m_OptionsDlg;
	void CommonConstruct();
	CTetrisDlg m_TetrisDlg;
	HICON m_hIcon;
	CString m_strEndGame;

	//{{AFX_MSG(CMainDlg)
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__35EAD7EE_009B_11D2_A729_000000000000__INCLUDED_)
