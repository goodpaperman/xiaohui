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


// PiecePreview.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "PiecePreview.h"
#include "Piece.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPiecePreview

IMPLEMENT_DYNAMIC(CPiecePreview, CWnd);


BOOL	CPiecePreview :: m_bRegistered = Register();

CPiecePreview::CPiecePreview()
{
	m_pPiece = 0;
	m_clrPiece = RGB(0,0,255);
}

CPiecePreview::~CPiecePreview()
{
}

BOOL CPiecePreview :: Register()
{
	WNDCLASS wc;
	wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = PiecePreviewWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = 0;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = 0;
	wc.lpszClassName = TEXT("TetrisPreview");
	VERIFY(RegisterClass(&wc));
	return TRUE;
}

LRESULT CALLBACK PiecePreviewWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)									// Dispatch on message type
	{
	case WM_NCCREATE:								// On WM_NCCREATE we create a C++ object and attach it to the control
		{
			CPiecePreview * pCtl = new CPiecePreview();
			ASSERT(pCtl);							// Better not fail!
			BOOL b = pCtl->SubclassWindow(hWnd);	// Attach the window handle to the new object
			ASSERT(b);								// Better not fail!
			return b;								// Return result to continue/abort window creation
			break;
		}
	default:										// All other messages go through default window processor
		return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}
}


BEGIN_MESSAGE_MAP(CPiecePreview, CWnd)
	//{{AFX_MSG_MAP(CPiecePreview)
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPiecePreview message handlers

void CPiecePreview::OnNcDestroy() 
{
	CWnd::OnNcDestroy();

	// Make sure the window was destroyed
	ASSERT(NULL == m_hWnd);

	delete this;
}

int CPiecePreview::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Set the styles for the parent control
	ModifyStyleEx(0, WS_EX_CLIENTEDGE | WS_EX_NOPARENTNOTIFY);

	return 0;
}

void CPiecePreview::ViewPiece(CPiece * pPiece)
{
	m_pPiece = pPiece;
	Invalidate();
}

void CPiecePreview::OnPaint() 
{
	if( m_pPiece ) {
		CPaintDC dc(this);

		CRect rect;
		GetClientRect(rect);

		COLORREF clrTopLeft = ::GetSysColor(COLOR_BTNHILIGHT);
		COLORREF clrBottomRight = ::GetSysColor(COLOR_BTNSHADOW);

		register const int nLines = m_pPiece->GetLines();
		register const int nCols  = m_pPiece->GetColumns();

		register const int nSquareWidth  = (rect.Width()  / nCols)  - 1;
		register const int nSquareHeight = (rect.Height() / nLines) - 1;

		register const int nHOffset = (rect.Width()  - (nSquareWidth  * nCols )) / 2;
		register const int nVOffset = (rect.Height() - (nSquareHeight * nLines)) / 2;

		for( register int l = nLines-1 ; l >= 0 ; --l )
			for( register int c = 0 ; c < nCols ; ++c )
				if( m_pPiece->IsSquare(nLines-1-l, c) )	{ // have to mirror horizontal ...
					dc.FillSolidRect(nHOffset+(c*nSquareWidth), nVOffset+(l*nSquareHeight), nSquareWidth, nSquareHeight, m_clrPiece);
					dc.Draw3dRect(nHOffset+(c*nSquareWidth), nVOffset+(l*nSquareHeight), nSquareWidth, nSquareHeight, clrTopLeft, clrBottomRight);
				}
	} else
		CWnd::OnPaint();
}

void CPiecePreview::OnMouseMove(UINT nFlags, CPoint point) 
{
	::SetCursor(0);
	CWnd::OnMouseMove(nFlags, point);
}
