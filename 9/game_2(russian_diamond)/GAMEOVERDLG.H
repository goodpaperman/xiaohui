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


#if !defined(AFX_GAMEOVERDLG_H__97537103_176C_11D2_A73F_000000000000__INCLUDED_)
#define AFX_GAMEOVERDLG_H__97537103_176C_11D2_A73F_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GameOverDlg.h : header file
//

#include "BitmapDialog.h"
#include "RoundButton.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CGameOverDlg dialog

class CGameOverDlg : public CBitmapDialog
{
// Construction
public:
	CGameOverDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGameOverDlg)
	enum { IDD = IDD_GameOverDlg };
	CStatic	m_ctrlGameOver;
	CString	m_strGameOver;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameOverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRoundButton	m_btnOK;
	CFont			m_Font;

	// Generated message map functions
	//{{AFX_MSG(CGameOverDlg)
	virtual BOOL OnInitDialog();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEOVERDLG_H__97537103_176C_11D2_A73F_000000000000__INCLUDED_)
