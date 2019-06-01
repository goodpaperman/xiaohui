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


// Language.cpp: implementation of the CLanguage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tetris.h"
#include "Language.h"

#include <winnls.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


HMODULE	CLanguage::m_hLangDLL;
HMODULE	CLanguage::m_hLocalResource;


static struct LangDLL {
	WORD		wPrimaryLang;
	LPCTSTR		pszDLL;
} gLangDLL[] = {
	{LANG_AFRIKAANS, TEXT("AFRIKAANS.lng")},
	{LANG_ALBANIAN, TEXT("ALBANIAN.lng")},
	{LANG_ARABIC, TEXT("ARABIC.lng")},
	{LANG_BASQUE, TEXT("BASQUE.lng")},
	{LANG_BELARUSIAN, TEXT("BELARUSIAN.lng")},
	{LANG_BULGARIAN, TEXT("BULGARIAN.lng")},
	{LANG_CATALAN, TEXT("CATALAN.lng")},
	{LANG_CHINESE, TEXT("CHINESE.lng")},
	{LANG_CROATIAN, TEXT("CROATIAN.lng")},
	{LANG_CZECH, TEXT("CZECH.lng")},
	{LANG_DANISH, TEXT("DANISH.lng")},
	{LANG_DUTCH, TEXT("DUTCH.lng")},
	{LANG_ESTONIAN, TEXT("ESTONIAN.lng")},
	{LANG_FAEROESE, TEXT("FAEROESE.lng")},
	{LANG_FARSI, TEXT("FARSI.lng")},
	{LANG_FINNISH, TEXT("FINNISH.lng")},
	{LANG_FRENCH, TEXT("FRENCH.lng")},
	{LANG_GERMAN, TEXT("GERMAN.lng")},
	{LANG_GREEK, TEXT("GREEK.lng")},
	{LANG_HEBREW, TEXT("HEBREW.lng")},
	{LANG_HUNGARIAN, TEXT("HUNGARIAN.lng")},
	{LANG_ICELANDIC, TEXT("ICELANDIC.lng")},
	{LANG_INDONESIAN, TEXT("INDONESIAN.lng")},
	{LANG_ITALIAN, TEXT("ITALIAN.lng")},
	{LANG_JAPANESE, TEXT("JAPANESE.lng")},
	{LANG_KOREAN, TEXT("KOREAN.lng")},
	{LANG_LATVIAN, TEXT("LATVIAN.lng")},
	{LANG_LITHUANIAN, TEXT("LITHUANIAN.lng")},
	{LANG_NORWEGIAN, TEXT("NORWEGIAN.lng")},
	{LANG_POLISH, TEXT("POLISH.lng")},
	{LANG_PORTUGUESE, TEXT("PORTUGUESE.lng")},
	{LANG_ROMANIAN, TEXT("ROMANIAN.lng")},
	{LANG_RUSSIAN, TEXT("RUSSIAN.lng")},
	{LANG_SERBIAN, TEXT("SERBIAN.lng")},
	{LANG_SLOVAK, TEXT("SLOVAK.lng")},
	{LANG_SLOVENIAN, TEXT("SLOVENIAN.lng")},
	{LANG_SPANISH, TEXT("SPANISH.lng")},
	{LANG_SWEDISH, TEXT("SWEDISH.lng")},
	{LANG_THAI, TEXT("THAI.lng")},
	{LANG_TURKISH, TEXT("TURKISH.lng")},
	{LANG_UKRAINIAN, TEXT("UKRAINIAN.lng")},
	{LANG_VIETNAMESE, TEXT("VIETNAMESE.lng")}
};

#define ENDVEC( vector )	(vector-1+sizeof(vector)/sizeof(vector[0]))

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLanguage::CLanguage()
{
	m_LangID = ::GetUserDefaultLangID();

	LPCTSTR pszLangDll = 0;

	LangDLL	* low = gLangDLL;
	LangDLL * high = ENDVEC(gLangDLL);

	WORD wLang = PRIMARYLANGID(m_LangID);

	while( low <= high ) {
		if( low->wPrimaryLang == wLang ) {
			pszLangDll = low->pszDLL;
			break;
		}
		++low;
	}

	if( pszLangDll )
		m_hLangDLL = ::LoadLibrary(pszLangDll);

	m_hLocalResource = ::GetModuleHandle(0);
}

CLanguage::~CLanguage()
{
	if( m_hLangDLL )
		::FreeLibrary(m_hLangDLL);
	m_hLangDLL = 0;
}


BOOL CLanguage :: LoadString(CString & str, UINT uResource) {
	BOOL bRet = FALSE;
	int bufsize = 512;
	LPTSTR buf = str.GetBufferSetLength(bufsize);
	if( m_hLangDLL )
		bRet = ::LoadString(m_hLangDLL, uResource, buf, bufsize);
	if( ! bRet )
		bRet = ::LoadString(m_hLocalResource, uResource, buf, bufsize);
	str.ReleaseBuffer();
	return bRet;
}
