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


#if !defined(AFX_SCOREDLG_H__27C6D341_159A_11D2_9AB6_0060B0CDC13E__INCLUDED_)
#define AFX_SCOREDLG_H__27C6D341_159A_11D2_9AB6_0060B0CDC13E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScoreDlg.h : header file
//
#include "BitmapPropPage.h"
#include <vector>
using namespace std;



struct ScoreTag {
	CString		m_strName;
	UINT		m_uScore;
	UINT		m_uLevel;

	ScoreTag(const CString & name = "", UINT score = 0, UINT level = 0)
		: m_strName(name), m_uScore(score), m_uLevel(level) {}

	ScoreTag & operator=( const ScoreTag & other ) {
		if( &other != this ) {
			m_strName = other.m_strName;
			m_uScore = other.m_uScore;
			m_uLevel = other.m_uLevel;
		}
		return * this;
	}
};
/////////////////////////////////////////////////////////////////////////////
// CScoreDlg dialog

class CScoreDlg : public CBitmapPropPage
{
	typedef vector<ScoreTag>::iterator			iterator;
	typedef vector<ScoreTag>::const_iterator	const_iterator;
	typedef vector<ScoreTag>::size_type			size_type;

	vector<ScoreTag>	m_ScoreArray;
	BOOL				m_bCanEditName;

	CString				m_strName;
	CString				m_strScore;
	CString				m_strLevel;

	enum { MAXSCORE = 10 };

private:
	DECLARE_DYNCREATE(CScoreDlg)

// Construction
public:
	CScoreDlg();
	~CScoreDlg();


	BOOL	IsHiScore(UINT Score) const;
	void	AddHiScore(UINT Score, UINT Level);
	int		AddHiScore(int Index, const CString & Name, UINT Score, UINT Level);
	void	SaveHiScore() const;
	void	RestoreHiScore();
	void	LoadAllStrings();

// Dialog Data
	//{{AFX_DATA(CScoreDlg)
	enum { IDD = IDD_ScoreDlg };
	CListCtrl	m_ctrlScore;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CScoreDlg)
	public:
	virtual BOOL OnKillActive();
	virtual void OnOK();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CScoreDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOREDLG_H__27C6D341_159A_11D2_9AB6_0060B0CDC13E__INCLUDED_)
