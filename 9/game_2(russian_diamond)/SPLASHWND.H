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


#if !defined(AFX_SPLASHWND_H__B00C23E0_04EE_11D2_9AA3_0060B0CDC13E__INCLUDED_)
#define AFX_SPLASHWND_H__B00C23E0_04EE_11D2_9AA3_0060B0CDC13E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SplashWnd.h : header file
//

#include "dib256.h"

/////////////////////////////////////////////////////////////////////////////
// CSplashWnd window

class CSplashWnd : public CWnd
{
// Construction
public:
	CSplashWnd(UINT nBitmapID, UINT nDuration = 3500);

// Attributes
public:
	BOOL Create();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySplashWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:

// Generated message map functions
protected:
	//{{AFX_MSG(CMySplashWnd)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	UINT		m_nBitmapID;
	UINT		m_nDuration;
	UINT		m_nTimerID;
	CDIBitmap	m_bitmap;
	CWnd		m_wndInvisible;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHWND_H__B00C23E0_04EE_11D2_9AA3_0060B0CDC13E__INCLUDED_)
