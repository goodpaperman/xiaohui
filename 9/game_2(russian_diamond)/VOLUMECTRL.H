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


#if !defined(AFX_VOLUMECTRL_H__853CBCF3_2320_11D2_A74B_000000000000__INCLUDED_)
#define AFX_VOLUMECTRL_H__853CBCF3_2320_11D2_A74B_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VolumeCtrl.h : header file
//

#include "MIDI.h"


/////////////////////////////////////////////////////////////////////////////
// CVolumeCtrl dialog

class CVolumeCtrl : public CDialog
{
// Construction
public:
	CVolumeCtrl(CMIDI * pMusic);   // standard constructor

	DWORD	GetVolume() const { return m_dwVolume; }

// Dialog Data
	//{{AFX_DATA(CVolumeCtrl)
	enum { IDD = IDD_VolumeCtrl };
	CSliderCtrl	m_ctrlSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVolumeCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMIDI *	m_pMusic;
	UINT	m_uTimer;
	DWORD	m_dwVolume;

	// Generated message map functions
	//{{AFX_MSG(CVolumeCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLUMECTRL_H__853CBCF3_2320_11D2_A74B_000000000000__INCLUDED_)
