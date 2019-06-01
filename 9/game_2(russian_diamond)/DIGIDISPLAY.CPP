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


// CDigiDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "tetris.h"
#include "DigiDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDigiDisplay

CDigiDisplay::CDigiDisplay(int NumOfDigits /* = 8 */)
	: m_nNumOfDigits(NumOfDigits)
	, m_strNumber("0")
{
	VERIFY(m_bmpDigit[0].LoadBitmap(IDB_Digit0));
	VERIFY(m_bmpDigit[1].LoadBitmap(IDB_Digit1));
	VERIFY(m_bmpDigit[2].LoadBitmap(IDB_Digit2));
	VERIFY(m_bmpDigit[3].LoadBitmap(IDB_Digit3));
	VERIFY(m_bmpDigit[4].LoadBitmap(IDB_Digit4));
	VERIFY(m_bmpDigit[5].LoadBitmap(IDB_Digit5));
	VERIFY(m_bmpDigit[6].LoadBitmap(IDB_Digit6));
	VERIFY(m_bmpDigit[7].LoadBitmap(IDB_Digit7));
	VERIFY(m_bmpDigit[8].LoadBitmap(IDB_Digit8));
	VERIFY(m_bmpDigit[9].LoadBitmap(IDB_Digit9));
	VERIFY(m_bmpDigit[BLANK].LoadBitmap(IDB_DigitBlank));

	// assuming all bitmaps are same sized.
	m_bmpDigit[0].GetObject(sizeof(BITMAP), &m_BM);
}

CDigiDisplay::~CDigiDisplay()
{
}


BEGIN_MESSAGE_MAP(CDigiDisplay, CStatic)
	//{{AFX_MSG_MAP(CDigiDisplay)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDigiDisplay message handlers

void CDigiDisplay::SetNumber(UINT uNumber)
{
	m_strNumber.Format("%u", uNumber);
	Invalidate();
}

void CDigiDisplay::GetNumber(UINT & uNumber)
{
	GetWindowText(m_strNumber);
	uNumber = UINT(_ttol(m_strNumber));
}

void CDigiDisplay::OnPaint() 
{
	CPaintDC dc(this);
	CDC dcMem;
	VERIFY(dcMem.CreateCompatibleDC(0));

	CRect rect;
	GetClientRect(rect);
	CString str(m_strNumber);

	const int nHeight = rect.Height();
	const int nWidth  = rect.Width() / m_nNumOfDigits;

	const BOOL bLeft = !(GetStyle() & SS_RIGHT);

	register const int len = str.GetLength();

	for( register int i = 0; i < m_nNumOfDigits; ++i ) {
		CBitmap * pBmp = 0;
		if( bLeft ) {
			// left aligned
			if( i < len && str[i] >= '0' && str[i] <= '9' )
				pBmp = &m_bmpDigit[str[i]-'0'];
			else
				pBmp = &m_bmpDigit[BLANK];
		} else {
			// right aligned
			const int nSpaceLeft = (m_nNumOfDigits - len < 0) ? 0 : (m_nNumOfDigits - len);
			if( i >= nSpaceLeft && str[i-nSpaceLeft] >= '0' && str[i-nSpaceLeft] <= '9' )
				pBmp = &m_bmpDigit[str[i-nSpaceLeft]-'0'];
			else
				pBmp = &m_bmpDigit[BLANK];
		}
		ASSERT(pBmp != 0);

		CBitmap* pBmpOld = dcMem.SelectObject(pBmp);
		dc.StretchBlt(nWidth*i, 0, nWidth, nHeight,
				&dcMem, 0, 0, m_BM.bmWidth, m_BM.bmHeight, SRCCOPY);
 		dcMem.SelectObject(pBmpOld);
	}
	dcMem.DeleteDC();
}


void DDX_DigiDisplay(CDataExchange* pDX, int nIDC, UINT & uNumber)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	ASSERT(hWndCtrl);
	CDigiDisplay * pCtrl = (CDigiDisplay*) CWnd::FromHandle(hWndCtrl);
	ASSERT(pCtrl);

	if( pDX->m_bSaveAndValidate ) {
		pCtrl->GetNumber(uNumber);
	} else {
		pCtrl->SetNumber(uNumber);
	}
}
