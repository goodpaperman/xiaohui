// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F0B37D16_D5CF_11D1_B0FA_00A0C94457BF__INCLUDED_)
#define AFX_STDAFX_H__F0B37D16_D5CF_11D1_B0FA_00A0C94457BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxtempl.h>		// MFC templates

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#ifndef TBSTYLE_FLAT
#error "You need an updated commctrl.h to compile this program"
#endif

#include <NGToolbar.h>

#define NGTB_PROJECT
#endif // !defined(AFX_STDAFX_H__F0B37D16_D5CF_11D1_B0FA_00A0C94457BF__INCLUDED_)
