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


#if !defined(AFX_CDigiDisplay_H__84DF3FA2_067D_11D2_9AA5_0060B0CDC13E__INCLUDED_)
#define AFX_CDigiDisplay_H__84DF3FA2_067D_11D2_9AA5_0060B0CDC13E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CDigiDisplay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDigiDisplay window

class CDigiDisplay : public CStatic
{
// Construction
public:
	CDigiDisplay(int NumOfDigits = 8);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigiDisplay)
	//}}AFX_VIRTUAL

// Implementation
public:
	void	SetNumber(UINT uNumber);
	void	GetNumber(UINT & uNumber);
	virtual ~CDigiDisplay();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDigiDisplay)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	int			m_nNumOfDigits;
	CString		m_strNumber;
	CBitmap		m_bmpDigit[11];
	#define		BLANK	10		/*special index for m_bmpDigit[]*/
	BITMAP		m_BM;
};

void DDX_DigiDisplay(CDataExchange* pDX, int nIDC, UINT & uNumber);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDigiDisplay_H__84DF3FA2_067D_11D2_9AA5_0060B0CDC13E__INCLUDED_)
