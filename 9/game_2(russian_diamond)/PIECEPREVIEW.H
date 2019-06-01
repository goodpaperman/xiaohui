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


#if !defined(AFX_PIECEPREVIEW_H__B00C23E3_04EE_11D2_9AA3_0060B0CDC13E__INCLUDED_)
#define AFX_PIECEPREVIEW_H__B00C23E3_04EE_11D2_9AA3_0060B0CDC13E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PiecePreview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPiecePreview window

class CPiece;


class CPiecePreview : public CWnd
{
	DECLARE_DYNAMIC(CPiecePreview);

// Construction
public:
	CPiecePreview();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPiecePreview)
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF &	PieceColor() { return m_clrPiece; }
	void ViewPiece(CPiece * pPiece);
	virtual ~CPiecePreview();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPiecePreview)
	afx_msg void OnNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	static BOOL		Register();

protected:
	COLORREF		m_clrPiece;
	CPiece *		m_pPiece;
	static BOOL		m_bRegistered;
};

LRESULT CALLBACK PiecePreviewWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIECEPREVIEW_H__B00C23E3_04EE_11D2_9AA3_0060B0CDC13E__INCLUDED_)
