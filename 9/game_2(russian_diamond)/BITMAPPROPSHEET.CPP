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


// BitmapPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "BitmapPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapPropSheet

IMPLEMENT_DYNAMIC(CBitmapPropSheet, CPropertySheet)

CBitmapPropSheet::CBitmapPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	CommonConstruct();
}

CBitmapPropSheet::CBitmapPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	CommonConstruct();
}

CBitmapPropSheet::~CBitmapPropSheet()
{
}


void CBitmapPropSheet::CommonConstruct()
{
	VERIFY(m_bmpBackground.LoadBitmap(IDB_Background));
	VERIFY(m_HollowBrush.CreateStockObject(HOLLOW_BRUSH));
}

BEGIN_MESSAGE_MAP(CBitmapPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CBitmapPropSheet)
	ON_WM_ERASEBKGND()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapPropSheet message handlers

BOOL CBitmapPropSheet::OnEraseBkgnd(CDC* pDC) 
{
	if(m_bmpBackground.GetPixelPtr() != 0)
		m_bmpBackground.DrawDIB(pDC);
	else
		// no bitmap set. behave like a normal property sheet
		return CPropertySheet::OnEraseBkgnd(pDC);

	return TRUE;
}

BOOL CBitmapPropSheet::OnQueryNewPalette() 
{
	CPalette * pPal = m_bmpBackground.GetPalette();
	if( pPal != 0 && GetSafeHwnd() != 0 ) {
		CClientDC dc(this);
		CPalette * pOldPalette = dc.SelectPalette(pPal, FALSE);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if (nChanged == 0)
			return FALSE;

		Invalidate();
		return TRUE;
	}
	return CPropertySheet::OnQueryNewPalette();
}

void CBitmapPropSheet::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CPalette * pPal = m_bmpBackground.GetPalette();
	if( pPal != 0 && GetSafeHwnd() != 0 && pFocusWnd != this && ! IsChild(pFocusWnd) ) {
		CClientDC dc(this);
		CPalette * pOldPalette = dc.SelectPalette(pPal, TRUE);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if( nChanged )
			Invalidate();
	} else
		CPropertySheet::OnPaletteChanged(pFocusWnd);
}

HBRUSH CBitmapPropSheet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if(m_bmpBackground.GetPixelPtr() != 0) {
		switch(nCtlColor) {
			case CTLCOLOR_STATIC:
			case CTLCOLOR_BTN:
				// let static controls shine through
				pDC->SetBkMode(TRANSPARENT);
				return HBRUSH(m_HollowBrush);

			default:
				break;
		}
	}
	
	// if we reach that line, we haven't set a brush so far
	return CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);
}
