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


#if !defined(AFX_GAMEBOARD_H__35EAD7F1_009B_11D2_A729_000000000000__INCLUDED_)
#define AFX_GAMEBOARD_H__35EAD7F1_009B_11D2_A729_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GameBoard.h : header file
//

#include "DirectSound.h"
#include "MIDI.h"
#include <vector>
using std::vector;


class CPiece;

/////////////////////////////////////////////////////////////////////////////
// CGameBoard window


typedef struct NMBoard_tag {
	NMHDR	hdr;
	UINT	level;
	UINT	lines;
	UINT	points;
	UINT	pieces;
} NMBOARD;

typedef struct NMPreview_tag {
	NMHDR		hdr;
	CPiece *	piece;
} NMPREVIEW;


#define	NMB_PREVIEW			(0U-1997U)
#define	NMB_GAMEOVER		(0U-1998U)
#define	NMB_STATISTICS		(0U-1999U)


class CGameBoard : public CWnd
{
	friend class CTetrisDlg;
	friend class COptionsDlg;

	DECLARE_DYNAMIC(CGameBoard);

// Construction/Destruction
public:
	CGameBoard();
	virtual	~CGameBoard();

public:
	void	StopGame();
	void	StartGame();
	void	PauseGame();
	void	ResumeGame();
	void	InitBoard();
	int		Height(LPCRECT pRect = 0) const;
	int		Width(LPCRECT pRect = 0) const;
	void	GetDimension(int & uWidth, int & uHeight);
	void	SetDimension(int uWidth, int uHeight);
	void	ShowGrid( BOOL bShow = TRUE );
	BOOL	IsGridEnabled() const { return m_bShowGrid; }
	ULONG	GetCompleteLines() const { return m_ulCompleteLines; }
	USHORT	GetLevel() const { return m_usLevel; }
	ULONG	GetPieceCount() const { return m_ulPieces; }
	void	EnableSound(BOOL bEnable = TRUE);
	void	EnableMusic(BOOL bEnable = TRUE);
	void	SetMusicType(UINT uResource);
	void	UseExFigureSet(BOOL bUse) { m_bExFigures = bUse; }
	BOOL	UseExFigureSet() const { return m_bExFigures; }
	void	SetVolume(DWORD dwPercent);
	DWORD	GetVolume() const { return m_dwVolume; }

	void	MoveLeft();
	void	MoveRight();
	void	Rotate();
	void	BackRotate();
	void	StartFall();
	void	StopFall();

protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameBoard)
	//}}AFX_VIRTUAL

protected:	// member data
	vector< vector<COLORREF> >		m_Board;
	CPiece *	m_pCurPiece;
	CPiece *	m_pNextPiece;
	COLORREF	m_clrCurPiece;
	USHORT		m_usLevel;
	ULONG		m_ulCompleteLines;
	ULONG		m_ulPieces;
	UINT		m_uTimer;
	UINT		m_uPoints;
	NMBOARD		m_BoardNotifier;
	NMPREVIEW	m_PreviewNotifier;

	CDirectSound	m_SndKey;
	CDirectSound	m_SndPlace;
	CDirectSound	m_SndLevelWarp;
	CDirectSound	m_SndGameOver;
	CDirectSound	m_SndLineComplete;
	CMIDI *			m_pMusic;

	DWORD			m_dwVolume;		// volume of background music
	
	// the lower left corner of the current shape
	int				m_nCurCol;
	int				m_nCurLine;

	COLORREF		m_clrBackground;
	int				m_nSquareHeight;
	int				m_nSquareWidth;
	BOOL			m_bShowGrid;
	BOOL			m_bExFigures;

	static BOOL		m_bRegistered;

protected:
	void		ResetTimer(BOOL bSpeed = FALSE);
	CPiece *	SelectPiece();
	void		Paint();
	void		OnLineComplete();
	void		OnNewPiece();
	void		OnGameOver();
	void		CheckBoard();
	void		FixPiece();
	bool		CanPlace(int nLine, int nCol);
	void		NotifyParent(BOOL bStatistics = TRUE);	// if FALSE, then send Preview request

	static BOOL	Register();

	// Generated message map functions
	//{{AFX_MSG(CGameBoard)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LONG	OnVolumeChanged(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

LRESULT CALLBACK GameBoardWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

CGameBoard * TetrisGetGameBoard();

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEBOARD_H__35EAD7F1_009B_11D2_A729_000000000000__INCLUDED_)
