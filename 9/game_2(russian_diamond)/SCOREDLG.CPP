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


// ScoreDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "ScoreDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoreDlg property page

IMPLEMENT_DYNCREATE(CScoreDlg, CBitmapPropPage)

CScoreDlg::CScoreDlg() : CBitmapPropPage(CScoreDlg::IDD, IDS_TitleScorePage)
{
	m_ScoreArray.reserve(MAXSCORE);
	m_bCanEditName = FALSE;
	//{{AFX_DATA_INIT(CScoreDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_psp.dwFlags &= ~PSP_HASHELP;
}

CScoreDlg::~CScoreDlg()
{
}

void CScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScoreDlg)
	DDX_Control(pDX, IDC_ListScore, m_ctrlScore);
	//}}AFX_DATA_MAP
}


BOOL CScoreDlg :: IsHiScore(UINT uScore) const {
	if( m_ScoreArray.size() < (MAXSCORE-1) )
		return TRUE;
	else {
		const_iterator itend(m_ScoreArray.end());
		for(const_iterator it(m_ScoreArray.begin()); it != itend; ++it)
			if( uScore > it->m_uScore )
				return TRUE;
	}
	return FALSE;
}


void CScoreDlg :: AddHiScore(UINT uScore, UINT uLevel) {
	int index = 0;
	const_iterator itend(m_ScoreArray.end());
	iterator it(m_ScoreArray.begin());
	for(; it != itend; ++it, ++index)
		if( uScore > it->m_uScore )
			break;

	CString strName;
	TCHAR name[256];
	DWORD dwSize = 255;
	::ZeroMemory(PVOID(name), 256);
	if( ::GetUserName(name, &dwSize) ) {
		name[dwSize] = TEXT('\0');
		strName = name;
	}

	m_ScoreArray.insert(it, ScoreTag(strName, uScore, uLevel));
	if( m_ScoreArray.size() >= MAXSCORE )
		m_ScoreArray.resize(MAXSCORE);

	VERIFY(AddHiScore(index, strName, uScore, uLevel) == index);

	m_bCanEditName = TRUE;
	CEdit * pEdit =	m_ctrlScore.EditLabel(index);
	ASSERT(pEdit != 0);
	pEdit->LimitText(30);	// that should be enough ...
}


int CScoreDlg :: AddHiScore(int nIndex, const CString & strName, UINT uScore, UINT uLevel) {
	ASSERT(nIndex < MAXSCORE);

	CString strScore, strLevel;
	strScore.Format("%u", uScore);
	strLevel.Format("%u", uLevel);

	VERIFY(m_ctrlScore.InsertItem(LVIF_TEXT, nIndex, strName, 0, 0, 0, 0) == nIndex );
	VERIFY(m_ctrlScore.SetItem(nIndex, 1, LVIF_TEXT, strScore, 0, 0, 0, 0));
	VERIFY(m_ctrlScore.SetItem(nIndex, 2, LVIF_TEXT, strLevel, 0, 0, 0, 0));

	return nIndex;
}


void CScoreDlg :: SaveHiScore() const {
	for( register size_type i = 0; i < m_ScoreArray.size(); ++i )
		theApp.WriteHiScore(int(i), m_ScoreArray[i].m_strName, m_ScoreArray[i].m_uScore, m_ScoreArray[i].m_uLevel);
}

void CScoreDlg :: RestoreHiScore() {
	for( register int i = 0; i < MAXSCORE; ++i ) {
		ScoreTag sc;
		if( ! theApp.GetHiScore(i, sc.m_strName, sc.m_uScore, sc.m_uLevel) )
			break;	// no more scores saved
		m_ScoreArray.push_back(sc);
	}
}


void CScoreDlg :: LoadAllStrings() {
	VERIFY(CLanguage::LoadString(m_strName, IDS_HeaderName));
	VERIFY(CLanguage::LoadString(m_strScore, IDS_HeaderScore));
	VERIFY(CLanguage::LoadString(m_strLevel, IDS_HeaderLevel));

	LV_COLUMN col;
	memset(PVOID(&col), 0, sizeof(LV_COLUMN));

	if( m_ctrlScore.GetColumn(0, &col) ) {
		// columns already exist.
		m_ctrlScore.DeleteColumn(2);
		m_ctrlScore.DeleteColumn(1);
		m_ctrlScore.DeleteColumn(0);
	}
	CRect rect;
	m_ctrlScore.GetClientRect(rect);
	m_ctrlScore.InsertColumn(0, m_strName, LVCFMT_LEFT, rect.Width()/2, 0);
	m_ctrlScore.InsertColumn(1, m_strScore, LVCFMT_LEFT, rect.Width()/4, 1);
	m_ctrlScore.InsertColumn(2, m_strLevel, LVCFMT_LEFT, rect.Width()/4, 2);
}


BEGIN_MESSAGE_MAP(CScoreDlg, CBitmapPropPage)
	//{{AFX_MSG_MAP(CScoreDlg)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_ListScore, OnBeginLabelEdit)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_ListScore, OnEndLabelEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScoreDlg message handlers

BOOL CScoreDlg::OnInitDialog() 
{
	CBitmapPropPage::OnInitDialog();

	LoadAllStrings();

	int index = 0;
	const_iterator itend(m_ScoreArray.end());
	iterator it(m_ScoreArray.begin());
	for(; it != itend; ++it, ++index)
		AddHiScore(index, it->m_strName, it->m_uScore, it->m_uLevel);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CScoreDlg::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = m_bCanEditName ? 0 : 1;
}

void CScoreDlg::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	size_type index = pDispInfo->item.iItem;
	ASSERT(index < MAXSCORE);

	LPCTSTR pszText = pDispInfo->item.pszText;

	if( pszText )
		m_ScoreArray[index].m_strName = pszText;

	m_bCanEditName = FALSE;

#ifdef _DEBUG
	{
		const_iterator itend(m_ScoreArray.end());
		iterator it(m_ScoreArray.begin());
		TRACE("\nscore list:\n");
		index=0;
		for(; it != itend; ++it, ++index)
			TRACE("%u.: %s, %u, %u\n", unsigned(index), LPCTSTR(it->m_strName), it->m_uScore, it->m_uLevel);
		TRACE("-----------------\n");
	}
#endif

	*pResult = pszText ? 1 : 0;
}

BOOL CScoreDlg::OnKillActive() 
{
	SaveHiScore();
	return CBitmapPropPage::OnKillActive();
}

void CScoreDlg::OnOK() 
{
	SaveHiScore();
	CBitmapPropPage::OnOK();
}

void CScoreDlg::OnCancel() 
{
	SaveHiScore();
	CBitmapPropPage::OnCancel();
}
