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


// Tetris.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Tetris.h"
#include "MainDlg.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTetrisApp

BEGIN_MESSAGE_MAP(CTetrisApp, CWinApp)
	//{{AFX_MSG_MAP(CTetrisApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrisApp construction

CTetrisApp::CTetrisApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTetrisApp object

CTetrisApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTetrisApp initialization

BOOL CTetrisApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CSplashWnd * pSplash = new CSplashWnd(IDB_Splash);
	pSplash->Create();

	SetRegistryKey(TEXT("Free Games"));

	CMainDlg dlg(AFX_IDS_APP_TITLE);
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CTetrisApp :: GetWantMusic() {
	return GetProfileInt(TEXT("Options"), TEXT("Music"), 1);
}

void CTetrisApp :: WriteWantMusic(BOOL bWant) {
	WriteProfileInt(TEXT("Options"), TEXT("Music"), int(bWant));
}

BOOL CTetrisApp :: GetWantSound() {
	return GetProfileInt(TEXT("Options"), TEXT("Sound"), 1);
}

void CTetrisApp :: WriteWantSound(BOOL bWant) {
	WriteProfileInt(TEXT("Options"), TEXT("Sound"), int(bWant));
}


BOOL CTetrisApp :: GetHiScore(int index, CString & strName, UINT & uScore, UINT & uLevel) {
	CString strSection;
	strSection.Format(TEXT("Score%d"), index);
	strName = GetProfileString(strSection, TEXT("Name"));
	uScore = UINT(GetProfileInt(strSection, TEXT("Score"), 0));
	uLevel = UINT(GetProfileInt(strSection, TEXT("Level"), 0));

	return strName.IsEmpty() ? FALSE : TRUE;
}

void CTetrisApp :: WriteHiScore(int index, const CString & strName, UINT uScore, UINT uLevel) {
	CString strSection;
	strSection.Format(TEXT("Score%d"), index);
	WriteProfileString(strSection, TEXT("Name"), strName);
	WriteProfileInt(strSection, TEXT("Score"), int(uScore));
	WriteProfileInt(strSection, TEXT("Level"), int(uLevel));
}

BOOL CTetrisApp :: GetWantGrid() {
	return GetProfileInt(TEXT("Options"), TEXT("Grid"), 0);
}

void CTetrisApp :: WriteWantGrid(BOOL bWant) {
	WriteProfileInt(TEXT("Options"), TEXT("Grid"), int(bWant));
}

void CTetrisApp :: GetSquareSize( int & nWidth, int & nHeight ) {
	nWidth =  GetProfileInt(TEXT("Options"), TEXT("SquareWidth"),  14);
	nHeight = GetProfileInt(TEXT("Options"), TEXT("SquareHeight"), 14);
}

void CTetrisApp :: WriteSquareSize( int nWidth, int nHeight ) {
	WriteProfileInt(TEXT("Options"), TEXT("SquareWidth"),  nWidth);
	WriteProfileInt(TEXT("Options"), TEXT("SquareHeight"), nHeight);
}


UINT CTetrisApp :: GetMusicType() {
	return UINT(GetProfileInt(TEXT("Options"), TEXT("MusicType"), int(IDM_Kalinka)));
}

void CTetrisApp :: WriteMusicType(UINT uResource) {
	WriteProfileInt(TEXT("Options"), TEXT("MusicType"), int(uResource));
}

BOOL CTetrisApp :: GetWantExFigures() {
	return GetProfileInt(TEXT("Options"), TEXT("ExFigures"), 0);
}

void CTetrisApp :: WriteWantExFigures(BOOL bWant) {
	WriteProfileInt(TEXT("Options"), TEXT("ExFigures"), int(bWant));
}


DWORD CTetrisApp :: GetVolume() {
	return DWORD(GetProfileInt(TEXT("Options"), TEXT("MusicVolume"), 100));
}


void CTetrisApp :: WriteVolume(DWORD dwPercent) {
	WriteProfileInt(TEXT("Options"), TEXT("MusicVolume"), int(dwPercent));
}
