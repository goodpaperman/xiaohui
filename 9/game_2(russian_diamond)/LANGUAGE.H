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


// Language.h: interface for the CLanguage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGE_H__98EE40A3_1A7C_11D2_A742_000000000000__INCLUDED_)
#define AFX_LANGUAGE_H__98EE40A3_1A7C_11D2_A742_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CLanguage  
{
public:
	CLanguage();
	virtual ~CLanguage();


	static BOOL		LoadString(CString &, UINT);

protected:
	LANGID				m_LangID;
	static HMODULE		m_hLangDLL;
	static HMODULE		m_hLocalResource;
};

#endif // !defined(AFX_LANGUAGE_H__98EE40A3_1A7C_11D2_A742_000000000000__INCLUDED_)
