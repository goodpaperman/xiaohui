// Options.cpp: implementation of the COptions class.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Options.h"

/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////////////

COptions::COptions()
{
  m_nItemNum = 0;
}

COptions::~COptions()
{

}

/////////////////////////////////////////////////////////////////////////////
// inserts number-type item

void COptions::Insert(short* pnItemValue, CString sItemName, short nItemDefault, short nItemMin, short nItemMax, short nItemDiff)
{
  OPTIONS_ITEM* pOptionsItem = new OPTIONS_ITEM;
  pOptionsItem->oi_pnValue = pnItemValue;

  pOptionsItem->oi_nType = OI_NUMBER;
  pOptionsItem->oi_sName = sItemName;
  *(pOptionsItem->oi_pnValue) = nItemDefault;
  pOptionsItem->oi_nDefault = nItemDefault;
  pOptionsItem->oi_nMinValue = nItemMin;
  pOptionsItem->oi_nMaxValue = nItemMax;
  pOptionsItem->oi_nDiffValue = nItemDiff;
  m_apOptionsItems.Add(pOptionsItem);
  m_nItemNum++;
}

/////////////////////////////////////////////////////////////////////////////
// inserts bool-type item

void COptions::Insert(bool* pbItemValue, CString sItemName, bool bItemDefault, CString sItemMin, CString sItemMax)
{
  OPTIONS_ITEM* pOptionsItem = new OPTIONS_ITEM;
  pOptionsItem->oi_pbValue = pbItemValue;

  pOptionsItem->oi_nType = OI_BOOL;
  pOptionsItem->oi_sName = sItemName;
  *(pOptionsItem->oi_pbValue) = bItemDefault;
  pOptionsItem->oi_sMinValue = sItemMin;
  pOptionsItem->oi_sMaxValue = sItemMax;

  m_apOptionsItems.Add(pOptionsItem);
  m_nItemNum++;
}

/////////////////////////////////////////////////////////////////////////////
// inserts command-type item

void COptions::Insert(int nReturnValue, CString sItemName)
{
  OPTIONS_ITEM* pOptionsItem = new OPTIONS_ITEM;
  pOptionsItem->oi_nType = OI_COMMAND;
  pOptionsItem->oi_sName = sItemName;
  pOptionsItem->oi_nReturnValue = nReturnValue;

  m_apOptionsItems.Add(pOptionsItem);
  m_nItemNum++;
}

/////////////////////////////////////////////////////////////////////////////
/*
int COptions::GetItemValue(short nItem)
{
  OPTIONS_ITEM* pOptionsItem = m_apOptionsItems.GetAt(nItem);
  return pOptionsItem->oi_nValue;
}
*/
/////////////////////////////////////////////////////////////////////////////

void COptions::SetItemLimits(short nItem, short nMin, short nMax)
{
  OPTIONS_ITEM* pOptionsItem = m_apOptionsItems.GetAt(nItem);

  pOptionsItem->oi_nMinValue = nMin;
  pOptionsItem->oi_nMaxValue = nMax;

  if(*(pOptionsItem->oi_pnValue) > nMax || *(pOptionsItem->oi_pnValue) < nMin)
    *(pOptionsItem->oi_pnValue) = nMax; //pOptionsItem->oi_nDefault;
}

/////////////////////////////////////////////////////////////////////////////

bool COptions::GoUp()
{
  if(m_nCurrentItem > 0)
    m_nCurrentItem--;
  else
    m_nCurrentItem = m_nItemNum - 1;

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool COptions::GoDown()
{
  if(m_nCurrentItem < m_nItemNum - 1)
    m_nCurrentItem++;
  else
    m_nCurrentItem = 0;

  return true;
}

/////////////////////////////////////////////////////////////////////////////

int COptions::ChangeItem(bool& bChanged)
{
  OPTIONS_ITEM* pOptionsItem = m_apOptionsItems.GetAt(m_nCurrentItem);

  switch(pOptionsItem->oi_nType)
  {
    case OI_COMMAND:
      return pOptionsItem->oi_nReturnValue;
      break;

    case OI_BOOL:
      bChanged = true;
      *(pOptionsItem->oi_pbValue) ^= true;
      break;

    case OI_NUMBER:
      if(*(pOptionsItem->oi_pnValue) + pOptionsItem->oi_nDiffValue <= pOptionsItem->oi_nMaxValue)
        (*(pOptionsItem->oi_pnValue)) += pOptionsItem->oi_nDiffValue;
      else
        (*(pOptionsItem->oi_pnValue)) = pOptionsItem->oi_nMinValue;
      bChanged = true;
      break;
  }

  return 0;
}

/////////////////////////////////////////////////////////////////////////////

int COptions::IncreaseItem(bool& bChanged)
{
  OPTIONS_ITEM* pOptionsItem = m_apOptionsItems.GetAt(m_nCurrentItem);

  switch(pOptionsItem->oi_nType)
  {
    case OI_COMMAND:
      return pOptionsItem->oi_nReturnValue;
      break;

    case OI_BOOL:
      bChanged = true;
      *(pOptionsItem->oi_pbValue) ^= true;
      break;

    case OI_NUMBER:
      if(*(pOptionsItem->oi_pnValue) + pOptionsItem->oi_nDiffValue <= pOptionsItem->oi_nMaxValue)
      {
        bChanged = true;
        (*(pOptionsItem->oi_pnValue)) += pOptionsItem->oi_nDiffValue;
      }
      break;
  }

  return 0;
}

/////////////////////////////////////////////////////////////////////////////

int COptions::DecreaseItem(bool& bChanged)
{
  OPTIONS_ITEM* pOptionsItem = m_apOptionsItems.GetAt(m_nCurrentItem);

  switch(pOptionsItem->oi_nType)
  {
    case OI_COMMAND:
      return pOptionsItem->oi_nReturnValue;
      break;

    case OI_BOOL:
      bChanged = true;
      *(pOptionsItem->oi_pbValue) ^= true;
      break;

    case OI_NUMBER:
      if(*(pOptionsItem->oi_pnValue) - pOptionsItem->oi_nDiffValue >= pOptionsItem->oi_nMinValue)
      {
        bChanged = true;
        (*(pOptionsItem->oi_pnValue)) -= pOptionsItem->oi_nDiffValue;
      }
      break;
  }

  return 0;
}

/////////////////////////////////////////////////////////////////////////////

void COptions::GetItem(int nItem, CString& sItem, CString& sValue)
{
  OPTIONS_ITEM* pOptionsItem = m_apOptionsItems.GetAt(nItem);
  sItem = pOptionsItem->oi_sName;

  switch(pOptionsItem->oi_nType)
  {
    case OI_COMMAND:
      sValue = "";
      break;

    case OI_BOOL:
      if(*(pOptionsItem->oi_pbValue))
        sValue = pOptionsItem->oi_sMaxValue;
      else
        sValue = pOptionsItem->oi_sMinValue;
      break;

    case OI_NUMBER:
      sValue = "";
      sValue.Format("%d", *(pOptionsItem->oi_pnValue));
      break;
  }
}

/////////////////////////////////////////////////////////////////////////////
