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


#if !defined(AFX_BITMAPPROPPAGE_H__EA8A39F4_1826_11D2_A740_000000000000__INCLUDED_)
#define AFX_BITMAPPROPPAGE_H__EA8A39F4_1826_11D2_A740_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BitmapPropPage.h : header file
//

#include "dib256.h"

/////////////////////////////////////////////////////////////////////////////
// CBitmapPropPage dialog

class CBitmapPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBitmapPropPage)

// Construction
public:
	CBitmapPropPage(UINT uResourceID, UINT nIDCaption = 0);
	CBitmapPropPage(LPCTSTR pszResourceID, UINT nIDCaption = 0);
	CBitmapPropPage();
	~CBitmapPropPage();

	void	SetCaption( LPCTSTR pszCaption ) {
				if(pszCaption) {
					m_strCaption = pszCaption;
					m_psp.pszTitle = m_strCaption;
					m_psp.dwFlags |= PSP_USETITLE;
				}
			}

	void	SetTextColor(COLORREF clr) { m_clrText = clr; }

	virtual void	LoadAllStrings() {}

protected:
	void	CommonConstruct(UINT nIDCaption = 0);

// Dialog Data
	//{{AFX_DATA(CBitmapPropPage)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBitmapPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDIBitmap	m_bmpBackground;
	CBrush		m_HollowBrush;
	COLORREF	m_clrText;

	// Generated message map functions
	//{{AFX_MSG(CBitmapPropPage)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPPROPPAGE_H__EA8A39F4_1826_11D2_A740_000000000000__INCLUDED_)
