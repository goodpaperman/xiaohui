// Logo.cpp: implementation of the CLogo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Logo.h"
#include "ddutil.h"
#include "GlobalsExtern.h"
#include "StackUp.h"
#include "Game.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogo::CLogo()
{
  m_sBitmapLogo = _T("bmp/logo.bmp");
  m_sBitmapOptions = _T("bmp/options.bmp");

  m_Options.Insert(&g_Options_nPlayerNum,   " Number of players ", 1, 1, 2, 1);
  m_Options.Insert(&g_Options_nPF_XSize,    " Playfield width ", 6, 6, 6, 1);
  m_Options.Insert(&g_Options_nPF_YSize,    " Playfield height ", 10, 10, 10, 1);
  m_Options.Insert(&g_Options_bStartFilled, " Filled playfield ", false, "No", "Yes");
  m_Options.Insert(&g_Options_nPF_ObjType,  " Type of objects ", false, "Quadratic", "Any");
  m_Options.Insert(&g_Options_nPF_ObjNum,   " Number of objects ", 5, 1, 5, 1);
  m_Options.Insert(&g_Options_nPF_ObjXSize, " Objects width ", OBJ_XSIZE, OBJ_XSIZE, OBJ_XSIZE, 2);
  m_Options.Insert(&g_Options_nPF_ObjYSize, " Objects height ", OBJ_YSIZE, OBJ_YSIZE, OBJ_YSIZE, 1);
  m_Options.Insert(&g_Options_bRotateType,  " Type of rotation ", false, "Simplex", "Combinative");
  m_Options.Insert(&g_Options_bSoundFX,     " Sound FX ", true, "Off", "On");
  m_Options.Insert(INIT_GAME, "               S   T   A   R   T               ");
  m_Options.Insert(QUIT, "                  Q   U   I   T                  ");

  m_bKeyUpFlag = false;
  m_bKeyDownFlag = false;
  m_bKeyLeftFlag = false;
  m_bKeyRightFlag = false;
}

CLogo::~CLogo()
{

}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//  DIRECT DRAW                                                            //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool CLogo::DD_Init()
{
  WAITFORVB;
  DDBLTFX blt = { 0 };
  blt.dwSize = sizeof(blt);
  blt.dwFillColor = RGB(255, 255, 255);

  DD_BLT(g_lpDDS_Primary->Blt(0, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));

  m_lpDDP_Logo = DDLoadPalette(g_lpDD, m_sBitmapLogo);
  if(m_lpDDP_Logo)
  {
    g_DX_Result = g_lpDDS_Primary->SetPalette(m_lpDDP_Logo);    // make sure to set the palette before loading bitmaps.
    DD_CHECK_ERROR(_T("Error - DD - SetPalette ")  + m_sBitmapLogo);
  }

  m_lpDDS_Logo = DDLoadBitmap(g_lpDD, m_sBitmapLogo, 0, 0);
  if(!m_lpDDS_Logo)
  {
    AfxMessageBox("Error - DD - LoadBitmap " + m_sBitmapLogo);
    return false;
  }

  m_lpDDS_Options = DDLoadBitmap(g_lpDD, m_sBitmapOptions, 0, 0);
  if(!m_lpDDS_Logo)
  {
    AfxMessageBox("Error - DD - LoadBitmap " + m_sBitmapOptions);
    return false;
  }

  OtherLimits(-1);        // all

  return DD_DrawScreen();
}

/////////////////////////////////////////////////////////////////////////////

bool CLogo::DD_DrawScreen()
{
  m_bMenuChanged = true;
  m_Options.SetCurrentItem(10);              // initial selection - S T A R T

  // clear screen

  DDBLTFX blt = { 0 };
  blt.dwSize = sizeof(blt);
  blt.dwFillColor = RGB(255, 255, 255);

  DD_BLT(g_lpDDS_Secondary->Blt(0, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));
  g_DD_FlipScreens();
  DD_BLT(g_lpDDS_Secondary->Blt(0, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));

  // logo

  RECT rcLogoSrc;
  rcLogoSrc.left   = 0;
  rcLogoSrc.top    = 0;
  rcLogoSrc.right  = LOGO_WIDTH;
  rcLogoSrc.bottom = LOGO_HEIGHT;

  RECT rcOptionsSrc;
  rcOptionsSrc.left   = 0;
  rcOptionsSrc.top    = 0;
  rcOptionsSrc.right  = OPTIONS_WIDTH;
  rcOptionsSrc.bottom = OPTIONS_HEIGHT;

  RECT rcLogoDest;
  RECT rcOptionsDest;

  int x;
  int y;
  for(int i = 1; i <= ZOOM_FRAME_NUM; i++)
  {
    x = LOGO_WIDTH * i / ZOOM_FRAME_NUM;
    y = LOGO_HEIGHT * i / ZOOM_FRAME_NUM;

    rcLogoDest.left   = LOGO_XPOS + (LOGO_WIDTH / 2) - x / 2;
    rcLogoDest.top    = LOGO_YPOS + (LOGO_HEIGHT / 2) - y / 2;
    rcLogoDest.right  = LOGO_XPOS + (LOGO_WIDTH / 2) - x / 2 + x;
    rcLogoDest.bottom = LOGO_YPOS + (LOGO_HEIGHT / 2) - y / 2 + y;

    x = OPTIONS_WIDTH / ZOOM_FRAME_NUM * i;
    y = OPTIONS_HEIGHT / ZOOM_FRAME_NUM * i;

    rcOptionsDest.left   = OPTIONS_XPOS + (OPTIONS_WIDTH / 2) - x / 2;
    rcOptionsDest.top    = OPTIONS_YPOS + (OPTIONS_HEIGHT / 2) - y / 2;
    rcOptionsDest.right  = OPTIONS_XPOS + (OPTIONS_WIDTH / 2) - x / 2 + x;
    rcOptionsDest.bottom = OPTIONS_YPOS + (OPTIONS_HEIGHT / 2) - y / 2 + y;

    WAITFORVB;
    g_DD_FlipScreens();
    DD_BLT(g_lpDDS_Secondary->Blt(&rcLogoDest, m_lpDDS_Logo, &rcLogoSrc, 0, NULL));
    DD_BLT(g_lpDDS_Secondary->Blt(&rcOptionsDest, m_lpDDS_Options, &rcOptionsSrc, 0, NULL));
  }

  WAITFORVB;
  g_DD_FlipScreens();
  DD_BLT(g_lpDDS_Secondary->Blt(&rcLogoDest, m_lpDDS_Logo, &rcLogoSrc, 0, NULL));
  DD_BLT(g_lpDDS_Secondary->Blt(&rcOptionsDest, m_lpDDS_Options, &rcOptionsSrc, 0, NULL));

  PrintText(true);    // print logo text

  return true;
}

/////////////////////////////////////////////////////////////////////////////
// text

void CLogo::PrintText(bool bShow)
{
  HDC hDC;
  if(g_lpDDS_Primary->GetDC(&hDC) == DD_OK)
  {
    SetBkColor(hDC, RGB(255, 255, 255));
    if(bShow)
      SetTextColor(hDC, RGB(0, 128, 255));
    else
      SetTextColor(hDC, RGB(255, 255, 255));

    CString sItem;
    CString sItemValue;
    int j = m_Options.GetItemNum();
    for(int i = 0; i < j; i++)
    {
      WAITFORVB;
      WAITFORVB;
      m_Options.GetItem(i, sItem, sItemValue);
      TextOut(hDC, MENU_XBEG, MENU_YBEG + i * MENU_ITEM_HEIGHT, sItem, lstrlen(sItem));
      TextOut(hDC, MENU_ITEM_XBEG, MENU_YBEG + i * MENU_ITEM_HEIGHT, sItemValue, lstrlen(sItemValue));
    }

    CString sText;
    sText = _T("©1998 Code: Tool - Petr Stejskal, Liberec, Logo: Ventor  Home: http://www.theWaterCooler.com/Tool");
    TextOut(hDC, 0, SCREEN_YSIZE - MENU_ITEM_HEIGHT, sText, lstrlen(sText));

    g_lpDDS_Primary->ReleaseDC(hDC);
  }
}
/////////////////////////////////////////////////////////////////////////////

void CLogo::Activate()
{
  DD_RestoreAll();
  DD_DrawScreen();
}

/////////////////////////////////////////////////////////////////////////////

bool CLogo::DD_RestoreAll()
{
  return g_lpDDS_Primary->Restore() == DD_OK &&
         g_lpDDS_Secondary->Restore() == DD_OK &&
         m_lpDDS_Logo->Restore() == DD_OK &&
         m_lpDDS_Options->Restore() == DD_OK &&
         DDLoadPalette(g_lpDD, m_sBitmapLogo) &&
         g_lpDDS_Primary->SetPalette(m_lpDDP_Logo) == DD_OK &&
         DDReLoadBitmap(m_lpDDS_Logo, m_sBitmapLogo) == DD_OK &&
         DDReLoadBitmap(m_lpDDS_Options, m_sBitmapOptions) == DD_OK;
}

/////////////////////////////////////////////////////////////////////////////

bool CLogo::DD_Finish()
{
  DDBLTFX blt = { 0 };
  blt.dwSize = sizeof(blt);
  blt.dwFillColor = RGB(255, 255, 255);

  PrintText(false);    // clear logo text

  // logo

  RECT rcClear;
  RECT rcLogoSrc;
  rcLogoSrc.left   = 0;
  rcLogoSrc.top    = 0;
  rcLogoSrc.right  = LOGO_WIDTH;
  rcLogoSrc.bottom = LOGO_HEIGHT;

  RECT rcOptionsSrc;
  rcOptionsSrc.left   = 0;
  rcOptionsSrc.top    = 0;
  rcOptionsSrc.right  = OPTIONS_WIDTH;
  rcOptionsSrc.bottom = OPTIONS_HEIGHT;

  RECT rcLogoDest;
  RECT rcOptionsDest;

  int x;
  int y;
  for(int i = ZOOM_FRAME_NUM; i > 0; i--)
  {
    x = LOGO_WIDTH * i / ZOOM_FRAME_NUM;
    y = LOGO_HEIGHT * i / ZOOM_FRAME_NUM;

    rcLogoDest.left   = LOGO_XPOS + (LOGO_WIDTH / 2) - x / 2;
    rcLogoDest.top    = LOGO_YPOS + (LOGO_HEIGHT / 2) - y / 2;
    rcLogoDest.right  = LOGO_XPOS + (LOGO_WIDTH / 2) - x / 2 + x;
    rcLogoDest.bottom = LOGO_YPOS + (LOGO_HEIGHT / 2) - y / 2 + y;

    x = OPTIONS_WIDTH / ZOOM_FRAME_NUM * i;
    y = OPTIONS_HEIGHT / ZOOM_FRAME_NUM * i;

    rcOptionsDest.left   = OPTIONS_XPOS + (OPTIONS_WIDTH / 2) - x / 2;
    rcOptionsDest.top    = OPTIONS_YPOS + (OPTIONS_HEIGHT / 2) - y / 2;
    rcOptionsDest.right  = OPTIONS_XPOS + (OPTIONS_WIDTH / 2) - x / 2 + x;
    rcOptionsDest.bottom = OPTIONS_YPOS + (OPTIONS_HEIGHT / 2) - y / 2 + y;

    WAITFORVB;
    g_DD_FlipScreens();

    rcClear.left   = LOGO_XPOS;
    rcClear.top    = LOGO_YPOS;
    rcClear.right  = LOGO_XPOS + LOGO_WIDTH;
    rcClear.bottom = LOGO_YPOS + LOGO_HEIGHT;
    DD_BLT(g_lpDDS_Secondary->Blt(&rcClear, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));

    rcClear.left   = OPTIONS_XPOS;
    rcClear.top    = OPTIONS_YPOS;
    rcClear.right  = OPTIONS_XPOS + OPTIONS_WIDTH;
    rcClear.bottom = OPTIONS_YPOS + OPTIONS_HEIGHT;
    DD_BLT(g_lpDDS_Secondary->Blt(&rcClear, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));

    DD_BLT(g_lpDDS_Secondary->Blt(&rcLogoDest, m_lpDDS_Logo, &rcLogoSrc, 0, NULL));
    DD_BLT(g_lpDDS_Secondary->Blt(&rcOptionsDest, m_lpDDS_Options, &rcOptionsSrc, 0, NULL));
  }

  rcClear.left   = LOGO_XPOS;
  rcClear.top    = LOGO_YPOS;
  rcClear.right  = LOGO_XPOS + LOGO_WIDTH;
  rcClear.bottom = LOGO_YPOS + LOGO_HEIGHT;
  DD_BLT(g_lpDDS_Secondary->Blt(&rcClear, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));

  rcClear.left   = OPTIONS_XPOS;
  rcClear.top    = OPTIONS_YPOS;
  rcClear.right  = OPTIONS_XPOS + OPTIONS_WIDTH;
  rcClear.bottom = OPTIONS_YPOS + OPTIONS_HEIGHT;
  DD_BLT(g_lpDDS_Secondary->Blt(&rcClear, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));

  g_DD_FlipScreens();

  rcClear.left   = LOGO_XPOS;
  rcClear.top    = LOGO_YPOS;
  rcClear.right  = LOGO_XPOS + LOGO_WIDTH;
  rcClear.bottom = LOGO_YPOS + LOGO_HEIGHT;
  DD_BLT(g_lpDDS_Secondary->Blt(&rcClear, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));

  rcClear.left   = OPTIONS_XPOS;
  rcClear.top    = OPTIONS_YPOS;
  rcClear.right  = OPTIONS_XPOS + OPTIONS_WIDTH;
  rcClear.bottom = OPTIONS_YPOS + OPTIONS_HEIGHT;
  DD_BLT(g_lpDDS_Secondary->Blt(&rcClear, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));

  if(m_lpDDS_Logo != NULL)
  {
    m_lpDDS_Logo->Release();
    m_lpDDS_Logo = NULL;
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////

int CLogo::UpdateFrame()
{
  int nOldItem = m_Options.GetCurrentItem();
  int nReturnValue = DI_Frame();

//WAITFORVB;
  Sleep(10);

  if(m_bKeyUpFlag)
  {
    m_nKeyRepeatCount--;
    if(m_nKeyRepeatCount == 0 || m_nKeyRepeatCount == (KEY_REPEAT_WAIT - 1))
    {
      if(m_nKeyRepeatCount == 0)
        m_nKeyRepeatCount = KEY_REPEAT_DELAY;
      m_bMenuChanged = true;
      m_Options.GoUp();
    }
  }

  if(m_bKeyDownFlag)
  {
    m_nKeyRepeatCount--;
    if(m_nKeyRepeatCount == 0 || m_nKeyRepeatCount == (KEY_REPEAT_WAIT - 1))
    {
      if(m_nKeyRepeatCount == 0)
        m_nKeyRepeatCount = KEY_REPEAT_DELAY;
      m_bMenuChanged = true;
      m_Options.GoDown();
    }
  }

  if(m_bKeyLeftFlag)
  {
    m_nKeyRepeatCount--;
    if(m_nKeyRepeatCount == 0 || m_nKeyRepeatCount == (KEY_REPEAT_WAIT - 1))
    {
      if(m_nKeyRepeatCount == 0)
        m_nKeyRepeatCount = KEY_REPEAT_DELAY;
      m_Options.DecreaseItem(m_bMenuChanged);
    }
  }

  if(m_bKeyRightFlag)
  {
    m_nKeyRepeatCount--;
    if(m_nKeyRepeatCount == 0 || m_nKeyRepeatCount == (KEY_REPEAT_WAIT - 1))
    {
      if(m_nKeyRepeatCount == 0)
        m_nKeyRepeatCount = KEY_REPEAT_DELAY;
      m_Options.IncreaseItem(m_bMenuChanged);
    }
  }

  int nCurrentItem = m_Options.GetCurrentItem();

  // other defined limits

  if(m_bMenuChanged)
    OtherLimits(nCurrentItem);

  // change the current selection

  if(m_bMenuChanged)
  {
    m_bMenuChanged = false;
    UpdateItem(true, nOldItem, nCurrentItem);
  }

  return nReturnValue;
}

/////////////////////////////////////////////////////////////////////////////

void CLogo::OtherLimits(int nCurrentItem)
{
  switch(nCurrentItem)
  {
    case -1:
    case 0:   // number of players changed
    {
      short nPFXMax = SCREEN_XSIZE / (g_Options_nPlayerNum * g_Options_nPF_ObjXSize);
      m_Options.SetItemLimits(1, PF_MIN_XSIZE, nPFXMax - 2);
      if(nCurrentItem != -1)
        UpdateItem(false, 1, 1);

      if((g_Options_nPlayerNum * g_Options_nPF_ObjXSize * (g_Options_nPF_XSize) > SCREEN_XSIZE))
      {
        m_Options.SetItemLimits(6, OBJ_MIN_XSIZE, g_Options_nPF_ObjXSize);
        if(nCurrentItem != -1)
          UpdateItem(false, 6, 6);
      }
    }
    if(nCurrentItem != -1)
      break;

    case 1:   // playfield width changed
    {
      if((g_Options_nPlayerNum * g_Options_nPF_ObjXSize * (g_Options_nPF_XSize) > SCREEN_XSIZE))
      {
        m_Options.SetItemLimits(1, PF_MIN_XSIZE, g_Options_nPF_XSize);
        if(nCurrentItem != -1)
          UpdateItem(false, 1, 1);
      }
      short nObjXMax = SCREEN_XSIZE / (g_Options_nPlayerNum * (g_Options_nPF_XSize + 2));
      m_Options.SetItemLimits(6, OBJ_MIN_XSIZE, nObjXMax);
      if(nCurrentItem != -1)
        UpdateItem(false, 6, 6);
    }
    if(nCurrentItem != -1)
      break;

    case 6:   // objects width changed
    {
      if((g_Options_nPlayerNum * g_Options_nPF_ObjXSize * (g_Options_nPF_XSize) > SCREEN_XSIZE))
      {
        m_Options.SetItemLimits(6, OBJ_MIN_XSIZE, g_Options_nPF_ObjXSize);
        if(nCurrentItem != -1)
          UpdateItem(false, 6, 6);
      }
      short nPFXMax = SCREEN_XSIZE / (g_Options_nPlayerNum * g_Options_nPF_ObjXSize);
      m_Options.SetItemLimits(1, PF_MIN_XSIZE, nPFXMax - 2);
      if(nCurrentItem != -1)
        UpdateItem(false, 1, 1);
    }
    if(nCurrentItem != -1)
      break;

    case 2:   // playfield height changed
    {
      if((g_Options_nPF_ObjYSize * g_Options_nPF_YSize) > (SCREEN_YSIZE - 16))
      {
        m_Options.SetItemLimits(2, PF_MIN_YSIZE, g_Options_nPF_YSize);
        if(nCurrentItem != -1)
          UpdateItem(false, 2, 2);
      }
      short nObjYMax = (SCREEN_YSIZE - 16) / (g_Options_nPF_YSize + 2);
      m_Options.SetItemLimits(7, OBJ_MIN_YSIZE, nObjYMax);
      if(nCurrentItem != -1)
        UpdateItem(false, 7, 7);
    }
    if(nCurrentItem != -1)
      break;

    case 7:   // objects height changed
    {    
      if((g_Options_nPF_ObjYSize * g_Options_nPF_YSize) > (SCREEN_YSIZE - 16))
      {
        m_Options.SetItemLimits(7, OBJ_MIN_YSIZE, g_Options_nPF_ObjYSize);
        if(nCurrentItem != -1)
          UpdateItem(false, 7, 7);
      }
      short nPFYMax = (SCREEN_YSIZE - 16) / g_Options_nPF_ObjYSize;
      m_Options.SetItemLimits(2, PF_MIN_YSIZE, nPFYMax - 2);
      if(nCurrentItem != -1)
        UpdateItem(false, 2, 2);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////

bool CLogo::UpdateItem(bool bIsCurrent, short nOldItem, short nCurrentItem)
{
    CString sItem;
    CString sItemValue;

    DDBLTFX blt = { 0 };
    blt.dwSize = sizeof(blt);
    blt.dwFillColor = RGB(255, 255, 255);

    RECT rcClear;
    rcClear.left   = MENU_ITEM_XBEG;
    rcClear.top    = MENU_YBEG + nCurrentItem * MENU_ITEM_HEIGHT;
    rcClear.right  = SCREEN_XSIZE;
    rcClear.bottom = MENU_YBEG + nCurrentItem * MENU_ITEM_HEIGHT + MENU_ITEM_HEIGHT;
    WAITFORVB;
    DD_BLT(g_lpDDS_Primary->Blt(&rcClear, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));

    HDC hDC;
    if(g_lpDDS_Primary->GetDC(&hDC) == DD_OK)
    {
      m_Options.GetItem(nOldItem, sItem, sItemValue);       // clear old
      SetTextColor(hDC, RGB(0, 128, 255));
      SetBkColor(hDC, RGB(255, 255, 255));
      TextOut(hDC, MENU_XBEG, MENU_YBEG + nOldItem * MENU_ITEM_HEIGHT, sItem, sItem.GetLength());
      TextOut(hDC, MENU_ITEM_XBEG, MENU_YBEG + nOldItem * MENU_ITEM_HEIGHT, sItemValue, lstrlen(sItemValue));

      m_Options.GetItem(nCurrentItem, sItem, sItemValue);       // new selection

      if(bIsCurrent)
      {
        SetTextColor(hDC, RGB(0, 0, 0));
        SetBkColor(hDC, RGB(238, 170, 170));
      }
      TextOut(hDC, MENU_XBEG, MENU_YBEG + nCurrentItem * MENU_ITEM_HEIGHT, sItem, lstrlen(sItem));
      TextOut(hDC, MENU_ITEM_XBEG, MENU_YBEG + nCurrentItem * MENU_ITEM_HEIGHT, sItemValue, lstrlen(sItemValue));

      g_lpDDS_Primary->ReleaseDC(hDC);
    }
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//  DIRECT INPUT                                                           //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

int CLogo::DI_Frame()
{
  int nReturnValue;
  if(g_lpDI_Keyboard)
  {
    g_DI_GetKeyboardData();

    if(SUCCEEDED(g_DX_Result) && g_DI_InOut > 0)
    {
      DWORD iod;
      for (iod = 0; iod < g_DI_InOut; iod++)
      {
        switch(g_DI_rgdod[iod].dwOfs)
        {
          #ifdef WRITEBITMAPS
          case DIK_W:
            WriteWindowToDIB("c:\\temp\\logo.bmp", AfxGetMainWnd());
            break;
          #endif

          case DIK_ESCAPE:
            return QUIT;
            break;

          case DIK_F1:
            if(!(g_DI_rgdod[iod].dwData & 0x80))
            {
              return INIT_GAME;
            }
            else
            {
            }
            break;

          case DIK_UP:
            if(g_DI_rgdod[iod].dwData & 0x80)
            {
              m_nKeyRepeatCount = KEY_REPEAT_WAIT;
              m_bKeyUpFlag = true;
            }
            else
            {
              m_bKeyUpFlag = false;
            }
            break;

          case DIK_DOWN:
            if(g_DI_rgdod[iod].dwData & 0x80)
            {
              m_nKeyRepeatCount = KEY_REPEAT_WAIT;
              m_bKeyDownFlag = true;
            }
            else
            {
              m_bKeyDownFlag = false;
            }
            break;

          case DIK_SPACE:
          case DIK_RETURN:
            if(g_DI_rgdod[iod].dwData & 0x80)
            {
              nReturnValue = m_Options.ChangeItem(m_bMenuChanged);
              if(nReturnValue)
                return nReturnValue;
            }
            break;

          case DIK_SUBTRACT:
          case DIK_LEFT:
            if(g_DI_rgdod[iod].dwData & 0x80)
            {
              m_nKeyRepeatCount = KEY_REPEAT_WAIT;
              m_bKeyLeftFlag = true;
            }
            else
            {
              m_bKeyLeftFlag = false;
            }
            break;

          case DIK_ADD:
          case DIK_RIGHT:
            if(g_DI_rgdod[iod].dwData & 0x80)
            {
              m_nKeyRepeatCount = KEY_REPEAT_WAIT;
              m_bKeyRightFlag = true;
            }
            else
            {
              m_bKeyRightFlag = false;
            }
            break;
        }
      }
    }
  }
  else
    return QUIT;

  return RUNNING_LOGO;
}

/////////////////////////////////////////////////////////////////////////////
