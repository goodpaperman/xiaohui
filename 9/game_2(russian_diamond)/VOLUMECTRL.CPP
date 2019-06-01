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


// VolumeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "VolumeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVolumeCtrl dialog


CVolumeCtrl::CVolumeCtrl(CMIDI * pMusic)
	: CDialog(CVolumeCtrl::IDD, 0)
	, m_pMusic(pMusic)
{
	//{{AFX_DATA_INIT(CVolumeCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVolumeCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVolumeCtrl)
	DDX_Control(pDX, IDC_Volume, m_ctrlSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVolumeCtrl, CDialog)
	//{{AFX_MSG_MAP(CVolumeCtrl)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeCtrl message handlers

BOOL CVolumeCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ASSERT(m_pMusic != 0);

	m_ctrlSlider.SetRange(0, 10);
	m_dwVolume = m_pMusic->GetVolume();
	m_ctrlSlider.SetPos(m_dwVolume / 10);

	m_uTimer = SetTimer(1, 750, 0);

	return TRUE;
}


void CVolumeCtrl::OnTimer(UINT nIDEvent) 
{
	ASSERT(nIDEvent == m_uTimer);
	ASSERT(m_pMusic != 0);
	m_dwVolume = m_ctrlSlider.GetPos() * 10;
	m_pMusic->SetVolume(m_dwVolume);
	KillTimer(m_uTimer);
	EndDialog(IDOK);
}


BOOL CVolumeCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_CHAR ) {
		if( TCHAR(pMsg->wParam) == TCHAR('+') ||
			TCHAR(pMsg->wParam) == TCHAR('-') ||
			TCHAR(pMsg->wParam) == VK_ADD     ||
			TCHAR(pMsg->wParam) == VK_SUBTRACT ) {

			int nPos = m_ctrlSlider.GetPos();
			if( TCHAR(pMsg->wParam) == TEXT('+') ||
				TCHAR(pMsg->wParam) == VK_ADD ) {
				if( nPos < 10 )
					++nPos;
			} else {
				if( nPos > 0 )
					--nPos;
			}
			m_ctrlSlider.SetPos(nPos);
			KillTimer(m_uTimer);
			m_uTimer = SetTimer(1, 750, 0);
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
