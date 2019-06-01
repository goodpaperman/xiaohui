#if !defined(AFX_CHESSBOARD1_H__B4258483_0326_42B7_A043_C0299D0A89D3__INCLUDED_)
#define AFX_CHESSBOARD1_H__B4258483_0326_42B7_A043_C0299D0A89D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChessBoard1.h : header file
//
#include "othello.h"
/////////////////////////////////////////////////////////////////////////////
// CChessBoard window
#define COL_WIDTH 45
#define ROW_WIDTH 45

#define UM_RECALC  (WM_USER+100)
#define UM_COMRUN   (UM_RECALC +1)  
class CChessBoard : public CWnd
{
private:
	CBitmap  m_bitBlackChess, m_bitWhiteChess;
	CBitmap  m_bitChessBoard;
	CBitmap  m_motive[8]; 
	int      m_iMotiveNumber;
	bool     m_bPlayMotive;
	int      m_iMotivex, m_iMotivey;
// Construction
public:
	board_type m_oChessBoard;
	CChessBoard()
	{
		//	m_iCurColor = CHESS_BLACK;
		m_iMotiveNumber=0;
		m_iMotivex = m_iMotivey=0;
		m_bPlayMotive = FALSE; 
		init_board(&m_oChessBoard);
	}

// Attributes
public:
  
// Operations
public:
    void NewGame();
	void MoveBack();
	void PlayMotive(int row, int col, UINT8 obcolor);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChessBoard)
	public:
	  virtual BOOL Create(RECT &rect, CWnd * pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChessBoard();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChessBoard)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnComRun(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTranChess(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHESSBOARD1_H__B4258483_0326_42B7_A043_C0299D0A89D3__INCLUDED_)
