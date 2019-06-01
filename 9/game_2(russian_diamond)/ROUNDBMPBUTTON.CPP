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


// RoundBmpButton.cpp: implementation of the CRoundBitmapButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tetris.h"
#include "RoundBmpButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CRoundBitmapButton, CRoundButton)
	//{{AFX_MSG_MAP(CRoundBitmapButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CRoundBitmapButton::CRoundBitmapButton()
	: m_hIcon(0)
{

}

CRoundBitmapButton::~CRoundBitmapButton()
{

}


BOOL CRoundBitmapButton::SetIcon(LPCTSTR pszResource, const CSize & size) {
	m_hIcon = ::LoadIcon(HINSTANCE(GetModuleHandle(0)), pszResource);
	if( m_hIcon ) {
		SetWindowText(TEXT(""));
		if( size == CSize(0,0) )
			m_SizeIcon = CSize(::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
		else
			m_SizeIcon = size;
	}
	return m_hIcon ? TRUE : FALSE;
}

void CRoundBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
	ASSERT(lpDrawItemStruct != NULL);

	// first do default processing
	CRoundButton::DrawItem(lpDrawItemStruct);
	
	CDC* pDC   = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT state = lpDrawItemStruct->itemState;

	if( m_hIcon ) {
		CRgn rgn;

		if( m_bStretch ) {
			rgn.CreateRectRgn(m_ptLeft.x-m_nRadius/2, m_ptCentre.y-m_nRadius, 
				m_ptRight.x+m_nRadius/2, m_ptCentre.y+m_nRadius);
		} else {
			rgn.CreateEllipticRgn(m_ptCentre.x-m_nRadius, m_ptCentre.y-m_nRadius, 
				m_ptCentre.x+m_nRadius, m_ptCentre.y+m_nRadius);
		}

		pDC->SelectClipRgn(&rgn);

		CPoint pt = CPoint( m_ptCentre.x - m_SizeIcon.cx/2, m_ptCentre.y - m_SizeIcon.cy/2 );

		if( state & ODS_SELECTED )
			pt.Offset(1,1);

		pDC->SetBkMode(TRANSPARENT);

		::DrawIconEx(
			pDC->GetSafeHdc(),
			pt.x, pt.y,
			m_hIcon,
			m_SizeIcon.cx,
			m_SizeIcon.cy,
			0, 0,
			DI_NORMAL
		);

		pDC->SelectClipRgn(NULL);
		rgn.DeleteObject();
	}
}