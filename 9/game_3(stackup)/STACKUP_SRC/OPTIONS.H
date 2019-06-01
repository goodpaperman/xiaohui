// Options.h: interface for the COptions class.
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONS_H__5EFA3043_EFB6_11D1_BF86_A5D5D09E834A__INCLUDED_)
#define AFX_OPTIONS_H__5EFA3043_EFB6_11D1_BF86_A5D5D09E834A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define OI_COMMAND  1
#define OI_BOOL     2 
#define OI_NUMBER   3

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////

class COptions  
{
public:
	COptions();
	virtual ~COptions();

  int m_nCurrentItem;
  int m_nItemNum;

  struct OPTIONS_ITEM
  {
    int     oi_nType;
    CString oi_sName;

    int     oi_nReturnValue;

    bool*   oi_pbValue;
//    bool    oi_bDefault;
    CString oi_sMinValue;
    CString oi_sMaxValue;

    short*  oi_pnValue;
    short   oi_nDefault;
    short   oi_nMinValue;
    short   oi_nMaxValue;
    short   oi_nDiffValue;
  };

  CArray<OPTIONS_ITEM*, OPTIONS_ITEM*&> m_apOptionsItems;

  void  Insert(short*, CString, short, short, short, short);
  void  Insert(bool*, CString, bool, CString, CString);
  void  Insert(int, CString);
  void  GetItem(int, CString&, CString&);
  bool  GoUp();
  bool  GoDown();
  int   ChangeItem(bool&);
  int   IncreaseItem(bool&);
  int   DecreaseItem(bool&);
  void  SetCurrentItem(int nItem) { m_nCurrentItem = nItem; };
  int   GetCurrentItem() { return m_nCurrentItem; };
  int   GetItemNum() { return m_nItemNum; };
  void  SetItemLimits(short, short, short);
};

#endif // !defined(AFX_OPTIONS_H__5EFA3043_EFB6_11D1_BF86_A5D5D09E834A__INCLUDED_)
