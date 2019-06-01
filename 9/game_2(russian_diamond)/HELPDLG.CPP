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


// HelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "HelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg property page

IMPLEMENT_DYNCREATE(CHelpDlg, CBitmapPropPage)

CHelpDlg::CHelpDlg() : CBitmapPropPage(CHelpDlg::IDD, IDS_HelpPageDlg)
{
	//{{AFX_DATA_INIT(CHelpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_psp.dwFlags &= ~PSP_HASHELP;
}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	if( ! pDX->m_bSaveAndValidate )
		m_Help.SetCredits(m_strHelp, '|');
}


void CHelpDlg::LoadAllStrings() {
	CString strPrelude;
	VERIFY(CLanguage::LoadString(strPrelude, IDS_HelpPrelude));
	CString strKeys;
	VERIFY(CLanguage::LoadString(strKeys, IDS_HelpKeys));
	VERIFY(CLanguage::LoadString(m_strHelp, AFX_IDS_APP_TITLE));

	m_strHelp	 +=TEXT("\t|")
				 + strPrelude
				 + TEXT("KEYBOARD^||")
				 + strKeys
				 + TEXT("PARAGRAPH^|||||||||||||||||||||||")
				 ;
}


BEGIN_MESSAGE_MAP(CHelpDlg, CBitmapPropPage)
	//{{AFX_MSG_MAP(CHelpDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg message handlers

BOOL CHelpDlg::OnInitDialog() 
{
	CBitmapPropPage::OnInitDialog();

	LoadAllStrings();

	m_Help.SubclassDlgItem(IDC_Help, this);
	m_Help.SetSpeed(DISPLAY_MEDIUM);
	m_Help.SetTransparent();
	m_Help.SetBkImage(IDB_Background);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CHelpDlg::OnSetActive() 
{
	UpdateData(FALSE);
	m_Help.StartScrolling();
	return CBitmapPropPage::OnSetActive();
}

BOOL CHelpDlg::OnKillActive() 
{
	m_Help.EndScrolling();
	return CBitmapPropPage::OnKillActive();
}
