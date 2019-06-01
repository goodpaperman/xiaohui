// MenuHash.h: interface for the CMenuHash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUHASH_H__6DC611B4_D93A_11D1_A64E_00A0C93A70EC__INCLUDED_)
#define AFX_MENUHASH_H__6DC611B4_D93A_11D1_A64E_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

class CBCGToolBar;

class CMenuHash
{
public:
	CMenuHash();
	virtual ~CMenuHash();

	BOOL SaveMenuBar (HMENU hMenu, CBCGToolBar* pBar);
	BOOL LoadMenuBar (HMENU hMenu, CBCGToolBar* pBar) const;

protected:
	CMap<HMENU, HMENU&, HANDLE, HANDLE&>	m_StoredMenues;
};

extern CMenuHash	g_menuHash;

#endif // !defined(AFX_MENUHASH_H__6DC611B4_D93A_11D1_A64E_00A0C93A70EC__INCLUDED_)
