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


// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString gstrCopyright = TEXT("Copyright (C) 1998|by Jörg König|Joerg.Koenig@rhein-neckar.de||");


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg property page

IMPLEMENT_DYNCREATE(CAboutDlg, CBitmapPropPage)

CAboutDlg::CAboutDlg() : CBitmapPropPage(CAboutDlg::IDD, IDS_TitleAboutPage)
{
	//{{AFX_DATA_INIT(CAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_psp.dwFlags &= ~PSP_HASHELP;
}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::LoadAllStrings() {
	CString strLicense;
	VERIFY(CLanguage::LoadString(strLicense, IDS_License));
	CString strConcept;
	VERIFY(CLanguage::LoadString(strConcept, IDS_Concept));
	CString strWarrantee;
	VERIFY(CLanguage::LoadString(strWarrantee, IDS_Warrantee));
	CString strDisclosure;
	VERIFY(CLanguage::LoadString(strDisclosure, IDS_Disclosure));
	CString strSplashImage;
	VERIFY(CLanguage::LoadString(strSplashImage, IDS_SplashImage));
	CString strCredits;
	VERIFY(CLanguage::LoadString(strCredits, IDS_Credits));

	VERIFY(CLanguage::LoadString(m_strCredits, AFX_IDS_APP_TITLE));

	m_strCredits +=TEXT("\t|") 
				 + gstrCopyright
				 + TEXT("SHIELD^||")
				 + strLicense
				 + TEXT("PARAGRAPH^||")
				 + strConcept
				 + TEXT("PARAGRAPH^||")
				 + strWarrantee
				 + TEXT("PARAGRAPH^||")
				 + strDisclosure
				 + TEXT("PARAGRAPH^||")
				 + strSplashImage
				 + TEXT("PARAGRAPH^||")
				 + strCredits
				 + TEXT("PARAGRAPH^|||||||||||||||||||||||")
				 ;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	
	if( ! pDX->m_bSaveAndValidate )
		m_Credits.SetCredits(m_strCredits, '|');
}


BEGIN_MESSAGE_MAP(CAboutDlg, CBitmapPropPage)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CBitmapPropPage::OnInitDialog();

	LoadAllStrings();

	m_Credits.SubclassDlgItem(IDC_Credits, this);
	m_Credits.SetSpeed(DISPLAY_MEDIUM);
	m_Credits.SetTransparent();
	m_Credits.SetBkImage(IDB_Background);
	return TRUE;
}

BOOL CAboutDlg::OnSetActive() 
{
	UpdateData(FALSE);
	m_Credits.StartScrolling();
	return CBitmapPropPage::OnSetActive();
}

BOOL CAboutDlg::OnKillActive() 
{
	m_Credits.EndScrolling();
	return CBitmapPropPage::OnKillActive();
}
