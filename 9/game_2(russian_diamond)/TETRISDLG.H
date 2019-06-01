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


// TetrisDlg.h : header file
//

#if !defined(AFX_TETRISDLG_H__35EAD7E6_009B_11D2_A729_000000000000__INCLUDED_)
#define AFX_TETRISDLG_H__35EAD7E6_009B_11D2_A729_000000000000__INCLUDED_

#include "BitmapPropPage.h"
#include "GameBoard.h"	// Added by ClassView
#include "PiecePreview.h"
#include "DigiDisplay.h"
#include "RoundBmpButton.h"	// Added by ClassView

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTetrisDlg dialog

class CTetrisDlg : public CBitmapPropPage
{
	friend class CMainDlg;

// Construction
public:
	CTetrisDlg();	// standard constructor

	void	LoadAllStrings();

protected:
// Dialog Data
	//{{AFX_DATA(CTetrisDlg)
	enum { IDD = IDD_TETRIS_DIALOG };
	CString	m_strLevel;
	CString	m_strLines;
	CString	m_strScore;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrisDlg)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT			m_uLevel;
	UINT			m_uLines;
	UINT			m_uScore;
	CDigiDisplay	m_ctrlScore;
	CDigiDisplay	m_ctrlLines;
	CDigiDisplay	m_ctrlLevel;

	CRoundButton		m_btnPauseResume;
	CRoundButton		m_btnStartStop;
	CRoundBitmapButton	m_btnMoveLeft;
	CRoundBitmapButton	m_btnMoveRight;
	CRoundBitmapButton	m_btnRotate;
	CRoundBitmapButton	m_btnPlace;

	bool m_bPaused;
	bool m_bInGame;
	CGameBoard * m_pGameBoard;
	CPiecePreview * m_pPiecePreview;

	CString			m_strStart;
	CString			m_strStop;
	CString			m_strPause;
	CString			m_strResume;

	// Generated message map functions
	//{{AFX_MSG(CTetrisDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStart();
	afx_msg void OnPause();
	afx_msg void OnMoveLeft();
	afx_msg void OnMoveRight();
	afx_msg void OnRotate();
	afx_msg void OnPlace();
	//}}AFX_MSG
	afx_msg	void	OnUpdateStatistics(NMHDR*, LRESULT*);
	afx_msg	void	OnGameOver(NMHDR*, LRESULT*);
	afx_msg	void	OnPreview(NMHDR*, LRESULT*);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRISDLG_H__35EAD7E6_009B_11D2_A729_000000000000__INCLUDED_)
