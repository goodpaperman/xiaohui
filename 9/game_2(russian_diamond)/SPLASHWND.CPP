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


// SplashWnd.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashWnd

CSplashWnd::CSplashWnd(UINT nBitmapID, UINT nDuration /*= 3500*/)
	: m_nBitmapID(nBitmapID)
	, m_nDuration(nDuration)
{
}


BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CSplashWnd message handlers

BOOL CSplashWnd::Create()
{
	m_bitmap.LoadBitmap(m_nBitmapID);

	// First create an invisible window
	m_wndInvisible.CreateEx(
		WS_EX_TOPMOST, 
		AfxRegisterWndClass(CS_CLASSDC), 
		_T("Splash"), WS_POPUP, 0, 0, 
		m_bitmap.GetWidth(), m_bitmap.GetHeight(), 0, 0
	);

	// Create the the splash window with invisible one as parent
	BOOL bRetVal = CWnd::CreateEx(
		WS_EX_TOPMOST, 
		AfxRegisterWndClass(CS_CLASSDC), 
		_T("Splash"), WS_POPUP, 0, 0, 
		m_bitmap.GetWidth(), m_bitmap.GetHeight(), m_wndInvisible.m_hWnd, 0
	);

	CenterWindow();
	ShowWindow(SW_SHOW);
	UpdateWindow();

	//Create the timer.
	m_nTimerID = SetTimer(1, m_nDuration, 0);
	ASSERT(m_nTimerID);

	return bRetVal;
}

void CSplashWnd::OnPaint() 
{
	CPaintDC dc(this);
	m_bitmap.DrawDIB(&dc);
}

void CSplashWnd::OnTimer(UINT nIDEvent) 
{
	if (m_nTimerID == nIDEvent) {       
		//Destroy the timer and splash window
		KillTimer(m_nTimerID);
		m_wndInvisible.DestroyWindow();         
		delete this;
		return;
	}        

	CWnd::OnTimer(nIDEvent);
}

BOOL CSplashWnd::PreTranslateMessage(MSG* pMsg) 
{
	ASSERT(pMsg != 0);

	if (pMsg->message == WM_KEYDOWN ||
		pMsg->message == WM_SYSKEYDOWN ||
		pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_RBUTTONDOWN ||
		pMsg->message == WM_MBUTTONDOWN )
	{
		//Destroy the timer and splash window
		KillTimer(m_nTimerID);
		m_wndInvisible.DestroyWindow();         
		delete this;
		return TRUE;
	}        

	return CWnd::PreTranslateMessage(pMsg);
}
