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


// Tetris.h : main header file for the TETRIS application
//

#if !defined(AFX_TETRIS_H__35EAD7E4_009B_11D2_A729_000000000000__INCLUDED_)
#define AFX_TETRIS_H__35EAD7E4_009B_11D2_A729_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "StringRes.h"		// string symbols
#include "Language.h"

/////////////////////////////////////////////////////////////////////////////
// CTetrisApp:
// See Tetris.cpp for the implementation of this class
//

class CTetrisApp : public CWinApp
{
public:
	CTetrisApp();

	// profile wrappers:
	BOOL	GetWantMusic();
	void	WriteWantMusic(BOOL bWant);
	BOOL	GetWantSound();
	void	WriteWantSound(BOOL bWant);
	BOOL	GetWantGrid();
	void	WriteWantGrid(BOOL bWant);
	BOOL	GetHiScore(int index, CString & strName, UINT & uScore, UINT & uLevel);
	void	WriteHiScore(int index, const CString & strName, UINT uScore, UINT uLevel);
	void	GetSquareSize( int & nWidth, int & nHeight );
	void	WriteSquareSize( int nWidth, int nHeight );
	UINT	GetMusicType();
	void	WriteMusicType(UINT uResource);
	BOOL	GetWantExFigures();
	void	WriteWantExFigures(BOOL bWant);
	DWORD	GetVolume();
	void	WriteVolume(DWORD dwPercent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrisApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTetrisApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CLanguage m_Language;
};

extern CTetrisApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRIS_H__35EAD7E4_009B_11D2_A729_000000000000__INCLUDED_)
