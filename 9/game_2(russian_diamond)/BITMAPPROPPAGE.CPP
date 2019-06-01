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


// BitmapPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "BitmapPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapPropPage property page

IMPLEMENT_DYNCREATE(CBitmapPropPage, CPropertyPage)

CBitmapPropPage::CBitmapPropPage()
{
	CommonConstruct();
}


CBitmapPropPage::CBitmapPropPage(UINT uResource, UINT nIDCaption /*=0*/)
	: CPropertyPage(uResource, nIDCaption)
{
	CommonConstruct(nIDCaption);
}


CBitmapPropPage::CBitmapPropPage(LPCTSTR pszResource, UINT nIDCaption /*=0*/)
	: CPropertyPage(pszResource, nIDCaption)
{
	CommonConstruct(nIDCaption);
}


void CBitmapPropPage::CommonConstruct(UINT nIDCaption)
{
	if( nIDCaption != 0 ) {
		VERIFY(CLanguage::LoadString(m_strCaption, nIDCaption));
		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;
	}

	VERIFY(m_bmpBackground.LoadBitmap(IDB_Background));
	VERIFY(m_HollowBrush.CreateStockObject(HOLLOW_BRUSH));

	// use white text because of the dark background bitmap
	m_clrText = RGB(255, 255, 255);

	//{{AFX_DATA_INIT(CBitmapPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


CBitmapPropPage::~CBitmapPropPage()
{
}

void CBitmapPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitmapPropPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBitmapPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CBitmapPropPage)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapPropPage message handlers

BOOL CBitmapPropPage::OnEraseBkgnd(CDC* pDC) 
{
	if(m_bmpBackground.GetPixelPtr() != 0) {
		CRect rc;
		GetClientRect(rc);
		CRect rcClient(rc);
		ClientToScreen(rc);
		CWnd * pParent = GetParent();
		ASSERT(pParent != 0);
		pParent->ScreenToClient(rc);

		m_bmpBackground.DrawDIB(pDC, rcClient, rc);
	} else
		// no bitmap set. behave like a normal dialog
		return CPropertyPage::OnEraseBkgnd(pDC);

	return TRUE;
}

HBRUSH CBitmapPropPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if(m_bmpBackground.GetPixelPtr() != 0) {
		switch(nCtlColor) {
			case CTLCOLOR_STATIC:
			case CTLCOLOR_BTN:
				pDC->SetTextColor(m_clrText);
				// let static controls shine through
				pDC->SetBkMode(TRANSPARENT);
				return HBRUSH(m_HollowBrush);

			default:
				break;
		}
	}
	
	// if we reach this line, we haven't set a brush so far
	return CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CBitmapPropPage::OnPaletteChanged(CWnd* pFocusWnd) 
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
		CPropertyPage::OnPaletteChanged(pFocusWnd);
}

BOOL CBitmapPropPage::OnQueryNewPalette() 
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
	return CPropertyPage::OnQueryNewPalette();
}
