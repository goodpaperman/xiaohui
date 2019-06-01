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


// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlg

IMPLEMENT_DYNAMIC(CMainDlg, CBitmapPropSheet)

CMainDlg::CMainDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CBitmapPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	CommonConstruct();
}

CMainDlg::CMainDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CBitmapPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	CommonConstruct();
}

CMainDlg::~CMainDlg()
{
}


void CMainDlg::LoadAllStrings() {
	VERIFY(CLanguage::LoadString(m_strEndGame, IDS_TxtEndGame));
}


BEGIN_MESSAGE_MAP(CMainDlg, CBitmapPropSheet)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

void CMainDlg::CommonConstruct()
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	AddPage(&m_TetrisDlg);
	AddPage(&m_ScoreDlg);
	AddPage(&m_OptionsDlg);
	AddPage(&m_AboutDlg);
	AddPage(&m_HelpDlg);

	m_ScoreDlg.RestoreHiScore();

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CMainDlg::OnInitDialog() 
{
	BOOL bResult = CBitmapPropSheet::OnInitDialog();

	LoadAllStrings();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CButton * pOK = (CButton*)GetDlgItem(IDOK);
	pOK->ShowWindow(SW_HIDE);

	m_btnEndGame.SubclassDlgItem(IDCANCEL, this);
	m_btnEndGame.SetWindowText(m_strEndGame);
	VERIFY(m_Tab.SubclassWindow(GetTabControl()->GetSafeHwnd()));

	return bResult;
}

void CMainDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBitmapPropSheet::OnPaint();
	}
}

HCURSOR CMainDlg::OnQueryDragIcon() 
{
	return (HCURSOR) m_hIcon;
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg) 
{
	if( GetActivePage() == &m_TetrisDlg ) {
		if( pMsg->message == WM_KEYDOWN ||
			pMsg->message == WM_KEYUP ||
			pMsg->message == WM_CHAR ) {
			if( GetFocus() != &m_TetrisDlg )
				m_TetrisDlg.SetFocus();
			
			// Make sure the CTRL key is not down. If so, we have to process
			// the key by ourself!
			if( ! (::GetAsyncKeyState(VK_CONTROL) & (1<<(sizeof(SHORT)*8-1))) )
				if( m_TetrisDlg.SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam) == 0 )
					return TRUE;
		}
	}
	// default processing

	return CBitmapPropSheet::PreTranslateMessage(pMsg);
}

void CMainDlg::SetHiScore(UINT uScore, UINT uLevel)
{
	if(m_ScoreDlg.IsHiScore(uScore)) {
		VERIFY(SetActivePage(&m_ScoreDlg));
		m_ScoreDlg.AddHiScore(uScore, uLevel);
	}
}

void CMainDlg::SetPageTitle(CBitmapPropPage & page, UINT uID)
{
	CString strCaption;
	VERIFY(CLanguage::LoadString(strCaption, uID));

	page.SetCaption(strCaption);

	CTabCtrl * pCtrl = GetTabControl();
	ASSERT(pCtrl != 0);
	int nIndex = GetPageIndex(&page);
	ASSERT(nIndex >= 0);
	TC_ITEM tab;
	memset(PVOID(&tab), 0, sizeof(TC_ITEM));
	tab.mask = TCIF_TEXT;

	// ATTENTION: the following paragraph is still not UNICODE clean:
	char * pszBuf = new char [strCaption.GetLength()+1];
	#ifdef UNICODE
		#pragma message( __FILE__ ": Tetris is not completely UNICODE clean.")
	#else
		strcpy(pszBuf, LPCTSTR(strCaption));
	#endif
	tab.pszText = pszBuf;
	VERIFY(pCtrl->SetItem(nIndex, &tab));
	pCtrl->Invalidate();
	delete [] pszBuf;
}
