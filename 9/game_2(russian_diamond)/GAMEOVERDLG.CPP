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


// GameOverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "GameOverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameOverDlg dialog


CGameOverDlg::CGameOverDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CGameOverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGameOverDlg)
	m_strGameOver = _T("");
	//}}AFX_DATA_INIT

	SetBitmap(IDB_RedPlace, CBitmapDialog::BITMAP_STRETCH);
}


void CGameOverDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameOverDlg)
	DDX_Control(pDX, IDC_GameOver, m_ctrlGameOver);
	DDX_Text(pDX, IDC_GameOver, m_strGameOver);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CGameOverDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CGameOverDlg)
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameOverDlg message handlers

BOOL CGameOverDlg::OnInitDialog() 
{
	VERIFY(CLanguage::LoadString(m_strGameOver,IDS_GameOver));

	CBitmapDialog::OnInitDialog();

	CFont * pFont = m_ctrlGameOver.GetFont();
	LOGFONT lgfont;
	pFont->GetLogFont(&lgfont);
	lgfont.lfHeight = 48;
	lgfont.lfWidth = 0;		// let windows compute this;
	lgfont.lfQuality = PROOF_QUALITY;
	lgfont.lfPitchAndFamily = DEFAULT_PITCH | FF_ROMAN;
	lgfont.lfFaceName[0] = '\0';
	VERIFY(m_Font.CreateFontIndirect(&lgfont));
	m_ctrlGameOver.SetFont(&m_Font);

	return TRUE;  // return TRUE unless you set the focus to a control
}

UINT CGameOverDlg::OnNcHitTest(CPoint point) 
{
	// This allows to drag the dialog by clicking anywhere in it.
	return HTCAPTION;
}
