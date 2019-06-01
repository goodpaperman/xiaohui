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


// TetrisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "TetrisDlg.h"
#include "MainDlg.h"
#include "GameOverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTetrisDlg dialog

CTetrisDlg::CTetrisDlg()
	: CBitmapPropPage(CTetrisDlg::IDD, IDS_TitleGamePage)
{
	//{{AFX_DATA_INIT(CTetrisDlg)
	m_strLevel = _T("");
	m_strLines = _T("");
	m_strScore = _T("");
	//}}AFX_DATA_INIT
	m_psp.dwFlags &= ~PSP_HASHELP;
	m_bInGame = false;
	m_bPaused = false;
	m_pGameBoard = 0;
	m_pPiecePreview = 0;
	m_uScore = 0;
	m_uLevel = 0;
	m_uLines = 0;
}

void CTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CBitmapPropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTetrisDlg)
	DDX_Text(pDX, IDC_TxtLevel, m_strLevel);
	DDX_Text(pDX, IDC_TxtLines, m_strLines);
	DDX_Text(pDX, IDC_TxtScore, m_strScore);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_Pause, m_btnPauseResume);
	DDX_Control(pDX, IDC_BtnStart, m_btnStartStop);
	DDX_Control(pDX, IDC_MoveLeft, m_btnMoveLeft);
	DDX_Control(pDX, IDC_MoveRight, m_btnMoveRight);
	DDX_Control(pDX, IDC_Rotate, m_btnRotate);
	DDX_Control(pDX, IDC_Place, m_btnPlace);

	DDX_Control(pDX, IDC_Score, m_ctrlScore);
	DDX_DigiDisplay(pDX, IDC_Score, m_uScore);
	DDX_Control(pDX, IDC_Lines, m_ctrlLines);
	DDX_DigiDisplay(pDX, IDC_Lines, m_uLines);
	DDX_Control(pDX, IDC_Level, m_ctrlLevel);
	DDX_DigiDisplay(pDX, IDC_Level, m_uLevel);

	if( 0 == m_pGameBoard )
		m_pGameBoard = (CGameBoard*) GetDlgItem(IDC_GameBoard);
	ASSERT(0 != m_pGameBoard);

	if( 0 == m_pPiecePreview )
		m_pPiecePreview = (CPiecePreview*) GetDlgItem(IDC_PiecePreview);
	ASSERT(0 != m_pPiecePreview);

	if( ! pDX->m_bSaveAndValidate ) {
		// display correct text
		m_btnPauseResume.SetWindowText(m_bPaused ? m_strResume : m_strPause);
		m_btnStartStop.SetWindowText(m_bInGame ? m_strStop : m_strStart);
	}
}

BEGIN_MESSAGE_MAP(CTetrisDlg, CBitmapPropPage)
	//{{AFX_MSG_MAP(CTetrisDlg)
	ON_BN_CLICKED(IDC_BtnStart, OnBtnStart)
	ON_BN_CLICKED(IDC_Pause, OnPause)
	ON_BN_CLICKED(IDC_MoveLeft, OnMoveLeft)
	ON_BN_CLICKED(IDC_MoveRight, OnMoveRight)
	ON_BN_CLICKED(IDC_Rotate, OnRotate)
	ON_BN_CLICKED(IDC_Place, OnPlace)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NMB_STATISTICS, IDC_GameBoard, OnUpdateStatistics)
	ON_NOTIFY(NMB_GAMEOVER, IDC_GameBoard, OnGameOver)
	ON_NOTIFY(NMB_PREVIEW, IDC_GameBoard, OnPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrisDlg message handlers

BOOL CTetrisDlg::OnInitDialog()
{
	CBitmapPropPage::OnInitDialog();

	LoadAllStrings();

	GetDlgItem(IDC_Pause)->EnableWindow(FALSE);
	ASSERT(m_pGameBoard != 0);
	m_pGameBoard->EnableSound(theApp.GetWantSound());
	m_pGameBoard->EnableMusic(theApp.GetWantMusic());
	m_pGameBoard->ShowGrid(theApp.GetWantGrid());
	m_pGameBoard->SetMusicType(theApp.GetMusicType());
	m_pGameBoard->UseExFigureSet(theApp.GetWantExFigures());
	m_pGameBoard->SetVolume(theApp.GetVolume());
	int w, h;
	theApp.GetSquareSize(w, h);
	m_pGameBoard->SetDimension(w, h);

	m_btnMoveLeft.SetIcon(IDI_MoveLeft, CSize(10, 10));
	m_btnMoveRight.SetIcon(IDI_MoveRight, CSize(10, 10));
	m_btnPlace.SetIcon(IDI_Place, CSize(10, 10));
	m_btnRotate.SetIcon(IDI_Rotate, CSize(10, 10));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CTetrisDlg::OnSetActive() 
{
	m_pGameBoard->InitBoard();
	return CBitmapPropPage::OnSetActive();
}

void CTetrisDlg::OnBtnStart() 
{
	if( m_bInGame )
		m_pGameBoard->StopGame();
	else {
		// Starting the game requires loading the music.
		// This may take 2 seconds (more or less :-)
		CWaitCursor curs;
		m_pGameBoard->StartGame();
	}
	m_bInGame = !m_bInGame;

	if( m_bInGame ) {
		m_btnPauseResume.EnableWindow();
		GotoDlgCtrl(GetDlgItem(IDC_Pause));
		if( m_bPaused )
			OnPause();	// reset the pause flag
	} else {
		m_pPiecePreview->ViewPiece(0);
		m_btnPauseResume.EnableWindow(FALSE);
		GotoDlgCtrl(GetDlgItem(IDC_BtnStart));
	}

	UpdateData(FALSE);
}

void CTetrisDlg::OnPause() 
{
	m_bPaused = ! m_bPaused;
	if( !m_bPaused ) {
		// Starting the game requires loading the music.
		// This may take 2 seconds (more or less :-)
		CWaitCursor curs;
		m_pGameBoard->ResumeGame();
	} else
		m_pGameBoard->PauseGame();

	UpdateData(FALSE);

	GotoDlgCtrl(GetDlgItem(IDC_Pause));
}

BOOL CTetrisDlg::OnKillActive() 
{
	if( m_bInGame )
		OnBtnStart();	// simulate a stop request
	return CBitmapPropPage::OnKillActive();
}


void CTetrisDlg :: OnUpdateStatistics(NMHDR * pNMHDR, LRESULT * )
{
	NMBOARD * pBoard = (NMBOARD*)pNMHDR;
	m_uScore = pBoard->points;
	m_uLines = pBoard->lines;
	m_uLevel = pBoard->level;
	UpdateData(FALSE);
}

void CTetrisDlg :: OnGameOver(NMHDR *, LRESULT * )
{
	CGameOverDlg dlg;
	dlg.DoModal();
	ASSERT(m_bInGame);
	OnBtnStart();	// simulate a stop request
	ASSERT(m_pPiecePreview != 0);
	m_pPiecePreview->ViewPiece(0);
	((CMainDlg *)GetParent())->SetHiScore(m_uScore, m_uLevel);
}

void CTetrisDlg :: OnPreview(NMHDR * pNMHDR, LRESULT * )
{
	NMPREVIEW * pPreview = (NMPREVIEW*)pNMHDR;
	ASSERT(m_pPiecePreview != 0);
	ASSERT(pPreview->piece != 0);
	m_pPiecePreview->ViewPiece(pPreview->piece);
}

BOOL CTetrisDlg::PreTranslateMessage(MSG* pMsg) 
{
	// We handle the key in a different way only if the CTRL key isn't
	// down in the moment.
	if( ! (::GetAsyncKeyState(VK_CONTROL) & (1<<(sizeof(SHORT)*8-1))) ) {
		if(pMsg->message == WM_KEYDOWN) {
			if( pMsg->wParam == VK_RETURN ) {
				if( m_bInGame ) {
					// simulate a "Pause Game" request
					OnPause();
				} else {
					// simulate a "Start Game" request
					OnBtnStart();
				}
				return TRUE;
			}
		}

		// Maybe the game board has usage for the key ...
		if( pMsg->message == WM_KEYDOWN ||
			pMsg->message == WM_KEYUP   ||
			pMsg->message == WM_CHAR )
				if( m_pGameBoard && m_pGameBoard->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam) == 0 )
				return TRUE;
	}

	return CBitmapPropPage::PreTranslateMessage(pMsg);
}

void CTetrisDlg::OnMoveLeft() 
{
	if( m_bInGame )
		m_pGameBoard->MoveLeft();
}

void CTetrisDlg::OnMoveRight() 
{
	if( m_bInGame )
		m_pGameBoard->MoveRight();
}

void CTetrisDlg::OnRotate() 
{
	if( m_bInGame )
		m_pGameBoard->Rotate();
}

void CTetrisDlg::OnPlace() 
{
	if( m_bInGame )
		m_pGameBoard->StartFall();
		// Note that you cannot stop falling the piece if you're
		// using the mouse. You really should use your keyboard.
}

void CTetrisDlg :: LoadAllStrings() {
	VERIFY(CLanguage::LoadString(m_strScore, IDS_TxtScore));
	VERIFY(CLanguage::LoadString(m_strLines, IDS_TxtLines));
	VERIFY(CLanguage::LoadString(m_strLevel, IDS_TxtLevel));
	VERIFY(CLanguage::LoadString(m_strStart, IDS_TxtStart));
	VERIFY(CLanguage::LoadString(m_strStop, IDS_TxtStop));
	VERIFY(CLanguage::LoadString(m_strPause, IDS_TxtPause));
	VERIFY(CLanguage::LoadString(m_strResume, IDS_TxtResume));

	UpdateData(FALSE);
}

void CTetrisDlg::OnOK() 
{
	if(m_pGameBoard)
		theApp.WriteVolume(m_pGameBoard->GetVolume());
	CBitmapPropPage::OnOK();
}

void CTetrisDlg::OnCancel() 
{
	if(m_pGameBoard)
		theApp.WriteVolume(m_pGameBoard->GetVolume());
	CBitmapPropPage::OnCancel();
}
