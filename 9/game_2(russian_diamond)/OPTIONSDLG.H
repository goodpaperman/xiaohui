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


#if !defined(AFX_OPTIONSDLG_H__35EAD7F2_009B_11D2_A729_000000000000__INCLUDED_)
#define AFX_OPTIONSDLG_H__35EAD7F2_009B_11D2_A729_000000000000__INCLUDED_

#include "BitmapPropPage.h"
#include "RoundButton.h"	// Added by ClassView

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

class COptionsDlg : public CBitmapPropPage
{
	DECLARE_DYNCREATE(COptionsDlg)

// Construction
public:
	COptionsDlg();
	~COptionsDlg();

	void	LoadAllStrings();

protected:
// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_OptionsDlg };
	CComboBox	m_ctrlMusicBox;
	CButton	m_ctrlWantMusic;
	CButton	m_ctrlWantSound;
	CSpinButtonCtrl	m_spinWidth;
	CSpinButtonCtrl	m_spinHeight;
	BOOL	m_bGrid;
	int		m_nSquareHeight;
	int		m_nSquareWidth;
	BOOL	m_bWantSound;
	BOOL	m_bWantMusic;
	int		m_nMusicType;
	BOOL	m_bExFigures;
	CString	m_strSoundCard;
	CString	m_strSquareHeight;
	CString	m_strSquareWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	public:
	virtual BOOL OnKillActive();
	virtual void OnOK();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRoundButton	m_btnSplash;
	CString			m_strGrid;
	CString			m_strSplashAgain;
	CString			m_strEnableSound;
	CString			m_strEnableMusic;
	CString			m_strBoard;
	CString			m_strSound;
	CString			m_strExFigureSet;
	CString			m_strChaikovsky;
	CString			m_strScorpions;
	CString			m_strKalinka;

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSplash();
	afx_msg void OnChkMusic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SaveSettings();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__35EAD7F2_009B_11D2_A729_000000000000__INCLUDED_)
