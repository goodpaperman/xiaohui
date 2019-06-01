// MyFilterListCtrl.h: interface for the CMyFilterListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFILTERLISTCTRL_H__7D098183_21F3_11D2_8652_0040055C08D9__INCLUDED_)
#define AFX_MYFILTERLISTCTRL_H__7D098183_21F3_11D2_8652_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "FilterListCtrl.h"

class CMyFilterListCtrl : public CFilterListCtrl  
{
public:
	CMyFilterListCtrl();
	virtual ~CMyFilterListCtrl();
protected:
	BOOL IsEqual(LPCTSTR lpszSource, LPCTSTR lspzDestination);

};

#endif // !defined(AFX_MYFILTERLISTCTRL_H__7D098183_21F3_11D2_8652_0040055C08D9__INCLUDED_)
