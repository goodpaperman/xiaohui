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


// RoundBmpButton.h: interface for the CRoundBitmapButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROUNDBMPBUTTON_H__B30E61F2_157E_11D2_9AB5_0060B0CDC13E__INCLUDED_)
#define AFX_ROUNDBMPBUTTON_H__B30E61F2_157E_11D2_9AB5_0060B0CDC13E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RoundButton.h"

class CRoundBitmapButton : public CRoundButton  
{
	HICON	m_hIcon;
	CSize	m_SizeIcon;

public:
	CRoundBitmapButton();
	virtual ~CRoundBitmapButton();

	BOOL	SetIcon(LPCTSTR pszResource, const CSize & size = CSize(0,0));
	BOOL	SetIcon(UINT uResource, const CSize & size = CSize(0,0)) {
				return SetIcon(MAKEINTRESOURCE(uResource), size);
			}

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

protected:
	//{{AFX_MSG(CRoundButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP();
};

#endif // !defined(AFX_ROUNDBMPBUTTON_H__B30E61F2_157E_11D2_9AB5_0060B0CDC13E__INCLUDED_)
