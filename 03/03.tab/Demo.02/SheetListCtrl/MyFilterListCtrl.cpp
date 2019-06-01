// MyFilterListCtrl.cpp: implementation of the CMyFilterListCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "testdialog.h"
#include "MyFilterListCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyFilterListCtrl::CMyFilterListCtrl()
{

}

CMyFilterListCtrl::~CMyFilterListCtrl()
{

}

BOOL CMyFilterListCtrl::IsEqual(LPCTSTR lpszSource, LPCTSTR lspzDestination)
{
	return CFilterListCtrl::IsEqual(lpszSource, CString(lspzDestination,1));
}
