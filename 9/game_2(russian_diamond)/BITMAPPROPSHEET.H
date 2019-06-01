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


#if !defined(AFX_BITMAPPROPSHEET_H__EA8A39F3_1826_11D2_A740_000000000000__INCLUDED_)
#define AFX_BITMAPPROPSHEET_H__EA8A39F3_1826_11D2_A740_000000000000__INCLUDED_

#include "dib256.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BitmapPropSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitmapPropSheet

class CBitmapPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CBitmapPropSheet)

// Construction
public:
	CBitmapPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CBitmapPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

	void	CommonConstruct();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapPropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBitmapPropSheet();

	// Generated message map functions
protected:
	CDIBitmap	m_bmpBackground;
	CBrush		m_HollowBrush;

	//{{AFX_MSG(CBitmapPropSheet)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPPROPSHEET_H__EA8A39F3_1826_11D2_A740_000000000000__INCLUDED_)
