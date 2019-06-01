///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//       ______  _______  _______   ______   __   __      __   __   _______  //
//      / ____/\/__  __/\/ ___  /\ / ____/\ / /\ / /\ ®  / /\ / /\ / ___  /\ //
//     / /\___\/\_/ /\_\/ /\_/ / // /\___\// / // / /   / / // / // /\_/ / / //
//    / /_/_     / / / / /_// / // / /    / /_//_/ /   / / // / // /_// / /  //
//    \__  /\   / / / / ___  / // / /    /    ____/   / / // / // _____/ /   //
//  ____/ / /  / / / / /\_/ / // /_/_   / /\  \_     / /_// / // /\____\/    //
// /_____/ /  / / / /_/ //_/ //_____/\ /_/ /\__/\   /______/ //_/ /          //
// \_____\/   \_\/  \_\/ \_\/ \_____\/ \_\/  \_\/   \______\/ \_\/           //
//                                                                           //
//                                                                           //
//                    V1.0 © Tool@theWaterCooler.com 1998                    //
//                    http://www.theWaterCooler.com/Tool                     //
//                        also Petr.Stejskal@vslib.cz                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Game.h"
#include "GlobalsExtern.h"
#include "ddutil.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Game dialog

CGame::CGame()
{
  m_sBitmapObjects    = "bmp/objects.bmp";
  m_sBitmapBackground = "bmp/backgrnd.bmp";

  #ifdef USE_DSOUND
  m_cWavRotate        = "wav/rotate.wav";
  m_cWavSpeedup       = "wav/speedup.wav"; 
  m_cWavPlace         = "wav/place.wav"; 
  m_cWavSignalizing   = "wav/signal.wav"; 
  m_cWavFalling       = "wav/falling.wav"; 
  #endif
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//                                                                         //
//              G A M E   I N I T                                          //
//                                                                         //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool CGame::Init(bool bFirst)
{
  if(bFirst)
  {
    m_nPF_XSize = g_Options_nPF_XSize + 2;
    m_nPF_YSize = g_Options_nPF_YSize + 2;

    #ifdef USE_DSOUND
    if((m_bSoundPresent = g_bSoundPresent) == true)
      m_bSoundPresent = DS_Init();
    #endif

    if(!DD_Init())
    {
      DD_Finish();
      return false;
    }

    srand((unsigned)time(NULL));
  }

// new game /////////////////////////////////////////////////////////////////

  m_bPause = false;
  m_bQuit = false;
	
  g_DD_PalleteToBack(m_lpDDP_Background);

  #ifdef _DEBUG
    DD_ClearScreen();
    g_DD_FlipScreens();
    DD_ClearScreen();
  #endif

  DD_CopyBackground();

  short nScore_XBeg;
  short nPF_XBeg;
  short nPF_YBeg = ((SCREEN_YSIZE - FONT_HEIGHT) - (g_Options_nPF_YSize + 2) * g_Options_nPF_ObjYSize) / 2;

  if(g_Options_nPlayerNum == 1)
  {
    nScore_XBeg = SCREEN_XSIZE / 2;
    nPF_XBeg = (SCREEN_XSIZE - (g_Options_nPF_XSize + 2) * g_Options_nPF_ObjXSize) / 2;
  }
  else
  {
    nScore_XBeg = SCREEN_XSIZE / 4;
    nPF_XBeg = (SCREEN_XSIZE / 2 - (g_Options_nPF_XSize + 2) * g_Options_nPF_ObjXSize) / 2;
  }

  m_pPlayer = &m_PlayerOne;
  ClearFallingTab();
  InitPlayer(1, nPF_XBeg, nPF_YBeg, nScore_XBeg);

  if(g_Options_nPlayerNum == 2)
  {
    m_pPlayer = &m_PlayerTwo;
    ClearFallingTab();
    nPF_XBeg += SCREEN_XSIZE / 2;
    InitPlayer(2, nPF_XBeg, nPF_YBeg, SCREEN_XSIZE / 4 * 3);
  }

  m_pPlayer = &m_PlayerOne;

  g_DD_FlipScreens();
  DD_CopyPrimaryToSecondary();

  FadeIn();

  return true;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//                                                                         //
//              G A M E   L O O P                                          //
//                                                                         //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool CGame::UpdateFrame() 
{
  DI_Frame();

  if(!m_bPause)
  {
    g_DD_FlipScreens();

    m_pPlayer = &m_PlayerOne;
    PlayPlayer();
    if(g_Options_nPlayerNum == 2)
    {
      m_pPlayer = &m_PlayerTwo;
      PlayPlayer();
    }
  }
  return m_bQuit;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//                                                                         //
//              G A M E   F I N I S H                                      //
//                                                                         //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool CGame::Finish() 
{
  FadeOut();

  m_pPlayer = &m_PlayerOne;
  FinishPlayer();
  if(g_Options_nPlayerNum == 2)
  {
    m_pPlayer = &m_PlayerTwo;
    FinishPlayer();
  }

  #ifdef USE_DSOUND
  if(m_bSoundPresent)
    DS_Finish();
  #endif

  DD_Finish();
  return true;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//                       G A M E   R O U T I N E S                         //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void CGame::InitPlayer(short nWhich, short nXBeg, short nYBeg, short nScoreXBeg)
{
  m_pPlayer->nWhich = nWhich;
  m_pPlayer->nPF_XBeginning = nXBeg;
  m_pPlayer->nPF_YBeginning = nYBeg;
  m_pPlayer->nScoreXBeg = nScoreXBeg;
  m_pPlayer->nScore = 0;
  m_pPlayer->bSignalizingFlag = false;
  m_pPlayer->bSignalizingState = false;
  m_pPlayer->bYSpd = false;
  m_pPlayer->bNewObj = false;

  m_pPlayer->bControlRotateFlag = false;
  m_pPlayer->bControlDownFlag = false;
  m_pPlayer->bControlLeftFlag = false;
  m_pPlayer->bControlRightFlag = false;
  MakeNewPlayfield();
  m_pPlayer->nGameState = GS_PLAYING;
  NewObjects(true);
  AddScore(0);
}

/////////////////////////////////////////////////////////////////////////////

void CGame::PlayPlayer()
{
  switch(m_pPlayer->nGameState)
  {
    case GS_PLAYING:
      Playing();
      break;
    case GS_SIGNALIZING:
      #ifdef USE_DSOUND
        DS_PlaySound(DS_SOUND_SIGNALIZING, NULL);
      #endif
      UpdateObjects(false);
      Signalizing();
      break;
    case GS_FALLING:
      #ifdef USE_DSOUND
        DS_PlaySound(DS_SOUND_FALLING, NULL);
      #endif
      Falling();
      UpdateObjects(false);
      break;
    case GS_NOTHING:
      break;
  }
}

/////////////////////////////////////////////////////////////////////////////

void CGame::FinishPlayer()
{
  ClearFallingTab();
}

/////////////////////////////////////////////////////////////////////////////

void CGame::Activate() 
{
//  DD_RestoreAll();

  #ifdef _DEBUG
    DD_ClearScreen();
  #endif
  DD_CopyBackground();

  m_pPlayer = &m_PlayerOne;
  if(m_pPlayer->nGameState == GS_FALLING)
    ClearFallingTab();
  DrawPlayfield();
  AddScore(0);
  if(m_pPlayer->Object1.nY >= g_Options_nPF_ObjYSize)
    DrawNewObjects();

  if(g_Options_nPlayerNum == 2)
  {
    m_pPlayer = &m_PlayerTwo;
    if(m_pPlayer->nGameState == GS_FALLING)
      ClearFallingTab();
    DrawPlayfield();
    AddScore(0);
    if(m_pPlayer->Object1.nY >= g_Options_nPF_ObjYSize)
      DrawNewObjects();
  }

  g_DD_FlipScreens();
  #ifdef _DEBUG
    DD_ClearScreen();
  #endif
  DD_CopyPrimaryToSecondary();
}

/////////////////////////////////////////////////////////////////////////////

void CGame::MakeNewPlayfield() 
{
  for(short nY = 0; nY < m_nPF_YSize; nY++)
  {
    for(short nX = 0; nX < m_nPF_XSize; nX++)
    {  
      if(nX == 0 || nY == 0 || nX == m_nPF_XSize - 1 || nY == m_nPF_YSize - 1)
        m_pPlayer->Playfield[nX][nY] = '@';
      else
      {
        if(nY < 2 || !g_Options_bStartFilled)
          m_pPlayer->Playfield[nX][nY] = ' ';
        else
        {
          m_pPlayer->Playfield[nX][nY] = (rand() % g_Options_nPF_ObjNum + 'a');
          m_pPlayer->Playfield_Frames[nX][nY] = rand() % OBJ_ANIM_FRAMES_NUM;
        }
      }
    }
  }
  DrawPlayfield();
}

/////////////////////////////////////////////////////////////////////////////

void CGame::DrawPlayfield()
{
  for(short nY = 0; nY < m_nPF_YSize - 0; nY++)
  {
    for(short nX = 0; nX < m_nPF_XSize - 0; nX++)
      DD_SetObject(nX, nY, m_pPlayer->Playfield[nX][nY], m_pPlayer->Playfield_Frames[nX][nY]);
  }
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::Testing(bool bSign)
{
  char A, B, C;
  short nChain;
  short nX;
  short nY;

  // looking up "-" /////////////////////////////////////////////////////////

  for(nY = 1; nY < m_nPF_YSize; nY++)
  {
    for(nX = 0; nX < m_nPF_XSize - 2; nX++)
    {
      A = m_pPlayer->Playfield[nX    ][nY] & 0x0f;
      B = m_pPlayer->Playfield[nX + 1][nY] & 0x0f;
      C = m_pPlayer->Playfield[nX + 2][nY] & 0x0f;
      if(A == B && A == C && A != 0)
      {
        if(bSign)
        {
          m_pPlayer->Playfield[nX    ][nY] = A + '@';
          m_pPlayer->Playfield[nX + 1][nY] = A + '@';
          m_pPlayer->Playfield[nX + 2][nY] = A + '@';
          nChain = 3;

          while(A == (m_pPlayer->Playfield[nX + nChain][nY] & 0x0f))
            nChain++;
          while(nChain > 3)
          {
            m_pPlayer->Playfield[nX + nChain - 1][nY] = A + '@';
            nChain--;
          }
        }
        else
          return true;
      }
    }
  }

  // looking up "|" /////////////////////////////////////////////////////////

  for(nX = 0; nX < m_nPF_XSize; nX++)
  {
    for(nY = 1; nY < m_nPF_YSize - 2; nY++)
    {
      A = m_pPlayer->Playfield[nX][nY    ] & 0x0f;
      B = m_pPlayer->Playfield[nX][nY + 1] & 0x0f;
      C = m_pPlayer->Playfield[nX][nY + 2] & 0x0f;
      if(A == B && A == C && A != 0)
      {
        if(bSign)
        {
          m_pPlayer->Playfield[nX][nY    ] = A + '@';
          m_pPlayer->Playfield[nX][nY + 1] = A + '@';
          m_pPlayer->Playfield[nX][nY + 2] = A + '@';
          nChain = 3;

          while(A == (m_pPlayer->Playfield[nX][nY + nChain] & 0x0f))
            nChain++;
          while(nChain > 3)
          {
            m_pPlayer->Playfield[nX][nY + nChain - 1] = A + '@';
            nChain--;
          }
        }
        else
          return true;
      }
    }
  }

// looking up "\" ///////////////////////////////////////////////////////////

  for(nY = 1; nY < m_nPF_YSize - 2; nY++)
  {
    for(nX = 0; nX < m_nPF_XSize - 2; nX++)
    {
      A = m_pPlayer->Playfield[nX    ][nY    ] & 0x0f;
      B = m_pPlayer->Playfield[nX + 1][nY + 1] & 0x0f;
      C = m_pPlayer->Playfield[nX + 2][nY + 2] & 0x0f;
      if(A == B && A == C && A != 0)
      {
        if(bSign)
        {
          m_pPlayer->Playfield[nX    ][nY    ] = A + '@';
          m_pPlayer->Playfield[nX + 1][nY + 1] = A + '@';
          m_pPlayer->Playfield[nX + 2][nY + 2] = A + '@';
          nChain = 3;

          while(A == (m_pPlayer->Playfield[nX + nChain][nY + nChain] & 0x0f))
            nChain++;
          while(nChain > 3)
          {
            m_pPlayer->Playfield[nX + nChain - 1][nY + nChain - 1] = A + '@';
            nChain--;
          }
        }
        else
          return true;
      }
    }
  }

// looking up "/" ///////////////////////////////////////////////////////////

  for(nY = 1; nY < m_nPF_YSize - 2; nY++)
  {
    for(nX = m_nPF_XSize - 1; nX != 1; nX--)
    {
      A = m_pPlayer->Playfield[nX    ][nY    ] & 0x0f;
      B = m_pPlayer->Playfield[nX - 1][nY + 1] & 0x0f;
      C = m_pPlayer->Playfield[nX - 2][nY + 2] & 0x0f;
      if(A == B && A == C && A != 0)
      {
        if(bSign)
        {
          m_pPlayer->Playfield[nX    ][nY    ] = A + '@';
          m_pPlayer->Playfield[nX - 1][nY + 1] = A + '@';
          m_pPlayer->Playfield[nX - 2][nY + 2] = A + '@';
          nChain = 3;

          while(A == (m_pPlayer->Playfield[nX - nChain][nY + nChain] & 0x0f))
            nChain++;
          while(nChain > 3)
          {
            m_pPlayer->Playfield[nX - nChain + 1][nY + nChain - 1] = A + '@';
            nChain--;
          }
        }
        else
          return true;
      }
    }
  }

  if(bSign)
  {
    bool bSignalizingFlag = false;
    for(nY = 1; nY < m_nPF_YSize - 1; nY++)
    {
      for(nX = 1; nX < m_nPF_XSize - 1; nX++)
      {
        if(m_pPlayer->Playfield[nX][nY] < 'a' && m_pPlayer->Playfield[nX][nY] != ' ')
          bSignalizingFlag = true;
      }
    }
    return bSignalizingFlag;
  }
  else
    return false;
}

// Signalizing //////////////////////////////////////////////////////////////

void CGame::Signalize(bool bState)
{
  short nZ;
  for(short nY = 1; nY < m_nPF_YSize - 1; nY++)
  {
    for(short nX = 1; nX < m_nPF_XSize - 1; nX++)
    {
      nZ = m_pPlayer->Playfield[nX][nY];
      if(nZ < 'a' && nZ != ' ')
      {
        if(bState)
          DD_SetObject(nX, nY, nZ + ('a' - 'A'), m_pPlayer->Playfield_Frames[nX][nY]);
        else
          DD_SetObject(nX, nY, ' ', 0);
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//   N E W   O B J E C T S                                                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void CGame::NewObjects(bool bFirst)
{
  m_pPlayer->bNewObj = false;
  m_pPlayer->bRotateState = false;

  m_pPlayer->Object1.nState = 0;
  m_pPlayer->Object2.nState = 0;
  m_pPlayer->Object3.nState = 0;

  m_pPlayer->Object1.nAnimFrame = 0;
  m_pPlayer->Object2.nAnimFrame = 0;
  m_pPlayer->Object3.nAnimFrame = 0;

  if(bFirst)
  {
    m_pPlayer->Object1.nZ_Next = (rand() % g_Options_nPF_ObjNum + 'a');
    m_pPlayer->Object2.nZ_Next = (rand() % g_Options_nPF_ObjNum + 'a');
    m_pPlayer->Object3.nZ_Next = (rand() % g_Options_nPF_ObjNum + 'a');
  }

  m_pPlayer->Object1.nZ = m_pPlayer->Object1.nZ_Next;
  m_pPlayer->Object2.nZ = m_pPlayer->Object2.nZ_Next;
  m_pPlayer->Object3.nZ = m_pPlayer->Object3.nZ_Next;

  m_pPlayer->Object1.nZ_Next = (rand() % g_Options_nPF_ObjNum + 'a');
  m_pPlayer->Object2.nZ_Next = (rand() % g_Options_nPF_ObjNum + 'a');
  m_pPlayer->Object3.nZ_Next = (rand() % g_Options_nPF_ObjNum + 'a');

  m_pPlayer->Playfield[(m_nPF_XSize / 2 - 1 + 0)][0] = (char)m_pPlayer->Object1.nZ_Next;
  m_pPlayer->Playfield[(m_nPF_XSize / 2 - 1 + 1)][0] = (char)m_pPlayer->Object2.nZ_Next;
  m_pPlayer->Playfield[(m_nPF_XSize / 2 - 1 + 2)][0] = (char)m_pPlayer->Object3.nZ_Next;

  m_pPlayer->Object1.nX = (m_nPF_XSize / 2 - 1 + 0) * g_Options_nPF_ObjXSize;
  m_pPlayer->Object2.nX = (m_nPF_XSize / 2 - 1 + 1) * g_Options_nPF_ObjXSize;
  m_pPlayer->Object3.nX = (m_nPF_XSize / 2 - 1 + 2) * g_Options_nPF_ObjXSize;

  m_pPlayer->Object1.nY = 0;
  m_pPlayer->Object2.nY = 0;
  m_pPlayer->Object3.nY = 0;

  m_pPlayer->Object1.nX_Last = m_pPlayer->Object1.nX;
  m_pPlayer->Object2.nX_Last = m_pPlayer->Object2.nX;
  m_pPlayer->Object3.nX_Last = m_pPlayer->Object3.nX;

  m_pPlayer->Object1.nY_Last = m_pPlayer->Object1.nY;
  m_pPlayer->Object2.nY_Last = m_pPlayer->Object2.nY;
  m_pPlayer->Object3.nY_Last = m_pPlayer->Object3.nY;

  m_pPlayer->Object1.nX_Speed = 0;
  m_pPlayer->Object2.nX_Speed = 0;
  m_pPlayer->Object3.nX_Speed = 0;

  m_pPlayer->Playfield_Frames[(m_nPF_XSize / 2 - 1 + 0)][0] = rand() % OBJ_ANIM_FRAMES_NUM;
  m_pPlayer->Playfield_Frames[(m_nPF_XSize / 2 - 1 + 1)][0] = rand() % OBJ_ANIM_FRAMES_NUM;
  m_pPlayer->Playfield_Frames[(m_nPF_XSize / 2 - 1 + 2)][0] = rand() % OBJ_ANIM_FRAMES_NUM;
}

/////////////////////////////////////////////////////////////////////////////

void CGame::DrawNewObjects()
{
  m_pPlayer->bNewObj = true;
  short nXBeg = (m_nPF_XSize / 2 - 1) * g_Options_nPF_ObjXSize;
  short nAnimFrame1 = m_pPlayer->Playfield_Frames[(m_nPF_XSize / 2 - 1 + 0)][0];
  short nAnimFrame2 = m_pPlayer->Playfield_Frames[(m_nPF_XSize / 2 - 1 + 1)][0];
  short nAnimFrame3 = m_pPlayer->Playfield_Frames[(m_nPF_XSize / 2 - 1 + 2)][0];
  DD_DrawObject(false, nXBeg + 0 * g_Options_nPF_ObjXSize, 0, m_pPlayer->Object1.nZ_Next, nAnimFrame1);
  DD_DrawObject(false, nXBeg + 1 * g_Options_nPF_ObjXSize, 0, m_pPlayer->Object2.nZ_Next, nAnimFrame2);
  DD_DrawObject(false, nXBeg + 2 * g_Options_nPF_ObjXSize, 0, m_pPlayer->Object3.nZ_Next, nAnimFrame3);
  DD_DrawObject(true, nXBeg + 0 * g_Options_nPF_ObjXSize, 0, m_pPlayer->Object1.nZ_Next, nAnimFrame1);
  DD_DrawObject(true, nXBeg + 1 * g_Options_nPF_ObjXSize, 0, m_pPlayer->Object2.nZ_Next, nAnimFrame2);
  DD_DrawObject(true, nXBeg + 2 * g_Options_nPF_ObjXSize, 0, m_pPlayer->Object3.nZ_Next, nAnimFrame3);
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//   P L A Y I N G                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool CGame::Playing()
{
  // new objects ////////////////////////////////////////////////////////////

  if(m_pPlayer->Object1.nState == 2 && m_pPlayer->Object2.nState == 2 && m_pPlayer->Object3.nState == 2)
  {
    if(m_pPlayer->Playfield[m_nPF_XSize / 2 - 1 + 0][1] != ' '
    || m_pPlayer->Playfield[m_nPF_XSize / 2 - 1 + 1][1] != ' '
    || m_pPlayer->Playfield[m_nPF_XSize / 2 - 1 + 2][1] != ' ')
    {
      m_pPlayer->nGameState = GS_NOTHING;
      HDC hdc;
      if(g_lpDDS_Primary->GetDC(&hdc) == DD_OK)
      {
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(255, 255, 255));
        CString sText = "Game Over - Press ESC or F1";
        TextOut(hdc, SCREEN_XSIZE / 2 - 100, SCREEN_YSIZE - FONT_HEIGHT, sText, sText.GetLength());
        g_lpDDS_Primary->ReleaseDC(hdc);

        RECT rcSrc;
        rcSrc.left   = 0;
        rcSrc.right  = SCREEN_XSIZE;
        rcSrc.top    = SCREEN_YSIZE - FONT_HEIGHT;
        rcSrc.bottom = SCREEN_YSIZE;
        DD_BLT(g_lpDDS_Secondary->Blt(&rcSrc, g_lpDDS_Primary, &rcSrc, 0, NULL));

        return true;
      }
    }
    else
      NewObjects(false);
  }

  // clear previous position ////////////////////////////////////////////////

  if(!m_pPlayer->Object1.nState)
    DD_DrawObject(false, m_pPlayer->Object1.nX_Last, m_pPlayer->Object1.nY_Last, 0, 0);
  if(!m_pPlayer->Object2.nState)
    DD_DrawObject(false, m_pPlayer->Object2.nX_Last, m_pPlayer->Object2.nY_Last, 0, 0);
  if(!m_pPlayer->Object3.nState)
    DD_DrawObject(false, m_pPlayer->Object3.nX_Last, m_pPlayer->Object3.nY_Last, 0, 0);

  if(m_pPlayer->bYSpd ^= true)
  {
    m_pPlayer->Object1.nY_Speed = 0;
    m_pPlayer->Object2.nY_Speed = 0;
    m_pPlayer->Object3.nY_Speed = 0;
  }
  else
  {
    m_pPlayer->Object1.nY_Speed = 1;
    m_pPlayer->Object2.nY_Speed = 1;
    m_pPlayer->Object3.nY_Speed = 1;
  }

  if(m_pPlayer->Object1.nY >= g_Options_nPF_ObjYSize && !m_pPlayer->bNewObj)
    DrawNewObjects();

  // rotation ///////////////////////////////////////////////////////////////

  if(m_pPlayer->bControlRotateFlag)
  {
    m_pPlayer->bControlRotateFlag = false;

    short nWork;
    bool bPlayRotateSound = false;
    if(!m_pPlayer->Object1.nState && !m_pPlayer->Object2.nState && !m_pPlayer->Object3.nState)
    {
      if(!g_Options_bRotateType)
      {
        if(!(m_pPlayer->Object1.nZ == m_pPlayer->Object2.nZ == m_pPlayer->Object3.nZ))
        {
          bPlayRotateSound = true;
          nWork = m_pPlayer->Object1.nZ;
          m_pPlayer->Object1.nZ = m_pPlayer->Object2.nZ;
          m_pPlayer->Object2.nZ = m_pPlayer->Object3.nZ;
          m_pPlayer->Object3.nZ = nWork;
        }
      }
      else
      {
        if(m_pPlayer->bRotateState ^= true)
        {
          if(!(m_pPlayer->Object1.nZ == m_pPlayer->Object2.nZ))
          {
            bPlayRotateSound = true;
            nWork = m_pPlayer->Object1.nZ;
            m_pPlayer->Object1.nZ = m_pPlayer->Object2.nZ;
            m_pPlayer->Object2.nZ = nWork;
          }
          else
          {
            m_pPlayer->bRotateState = false;
            bPlayRotateSound = true;
            nWork = m_pPlayer->Object2.nZ;
            m_pPlayer->Object2.nZ = m_pPlayer->Object3.nZ;
            m_pPlayer->Object3.nZ = nWork;
          }
        }
        else
        {
          if(!(m_pPlayer->Object2.nZ == m_pPlayer->Object3.nZ))
          {
            bPlayRotateSound = true;
            nWork = m_pPlayer->Object2.nZ;
            m_pPlayer->Object2.nZ = m_pPlayer->Object3.nZ;
            m_pPlayer->Object3.nZ = nWork;
          }
          else
          {
            m_pPlayer->bRotateState = true;
            bPlayRotateSound = true;
            nWork = m_pPlayer->Object1.nZ;
            m_pPlayer->Object1.nZ = m_pPlayer->Object2.nZ;
            m_pPlayer->Object2.nZ = nWork;
          }
        }
      }
    }

    if(!m_pPlayer->Object1.nState && !m_pPlayer->Object2.nState && m_pPlayer->Object3.nState)
    {
      if(m_pPlayer->Object1.nZ != m_pPlayer->Object2.nZ)
      {
        bPlayRotateSound = true;
        nWork = m_pPlayer->Object1.nZ;
        m_pPlayer->Object1.nZ = m_pPlayer->Object2.nZ;
        m_pPlayer->Object2.nZ = nWork;
      }
    }
    if(m_pPlayer->Object1.nState && !m_pPlayer->Object2.nState && !m_pPlayer->Object3.nState)
    {
      if(m_pPlayer->Object2.nZ != m_pPlayer->Object3.nZ)
      {
        bPlayRotateSound = true;
        nWork = m_pPlayer->Object2.nZ;
        m_pPlayer->Object2.nZ = m_pPlayer->Object3.nZ;
        m_pPlayer->Object3.nZ = nWork;
      }
    }
    if(!m_pPlayer->Object1.nState && m_pPlayer->Object2.nState && !m_pPlayer->Object3.nState)
    {
      if(m_pPlayer->Object1.nZ != m_pPlayer->Object3.nZ)
      {
        bPlayRotateSound = true;
        nWork = m_pPlayer->Object1.nZ;
        m_pPlayer->Object1.nZ = m_pPlayer->Object3.nZ;
        m_pPlayer->Object3.nZ = nWork;
      }
    }

    #ifdef USE_DSOUND
    if(bPlayRotateSound)
      DS_PlaySound(DS_SOUND_ROTATE, NULL);
    #endif
  }

  // object moving //////////////////////////////////////////////////////////

  if(m_pPlayer->bControlLeftFlag)
  {
    m_pPlayer->Object1.nX_Speed = -OBJ_XSPEED;
    m_pPlayer->Object2.nX_Speed = -OBJ_XSPEED;
    m_pPlayer->Object3.nX_Speed = -OBJ_XSPEED;
  }
  else if(m_pPlayer->bControlRightFlag)
  {
    m_pPlayer->Object1.nX_Speed = OBJ_XSPEED;
    m_pPlayer->Object2.nX_Speed = OBJ_XSPEED;
    m_pPlayer->Object3.nX_Speed = OBJ_XSPEED;
  }
  else
  {
    if((m_pPlayer->Object1.nX % g_Options_nPF_ObjXSize) == 0 || (m_pPlayer->Object1.nX % g_Options_nPF_ObjXSize) == 1)
      m_pPlayer->Object1.nX_Speed = 0;
    if((m_pPlayer->Object2.nX % g_Options_nPF_ObjXSize) == 0 || (m_pPlayer->Object2.nX % g_Options_nPF_ObjXSize) == 1)
      m_pPlayer->Object2.nX_Speed = 0;
    if((m_pPlayer->Object3.nX % g_Options_nPF_ObjXSize) == 0 || (m_pPlayer->Object3.nX % g_Options_nPF_ObjXSize) == 1)
      m_pPlayer->Object3.nX_Speed = 0;
  }

  if(m_pPlayer->bControlDownFlag)
  {
    m_pPlayer->Object1.nY_Speed = OBJ_YSPEED;
    m_pPlayer->Object2.nY_Speed = OBJ_YSPEED;
    m_pPlayer->Object3.nY_Speed = OBJ_YSPEED;
  }

  if(m_pPlayer->Object1.nX_Speed == -OBJ_XSPEED)
  {
    ObjectMoving(&m_pPlayer->Object1);           // left
    ObjectMoving(&m_pPlayer->Object2);
    ObjectMoving(&m_pPlayer->Object3);
  }
  else
  {
    ObjectMoving(&m_pPlayer->Object3);           // right
    ObjectMoving(&m_pPlayer->Object2);
    ObjectMoving(&m_pPlayer->Object1);
  }

  // left collision /////////////////////////////////////////////////////////

  if(!m_pPlayer->Object1.nState)                     // 2. -> 1.
  {
    if(m_pPlayer->Object2.nX_Speed == -OBJ_XSPEED)
    {
      if(((m_pPlayer->Object2.nX + m_pPlayer->Object2.nX_Speed) - (m_pPlayer->Object1.nX + m_pPlayer->Object1.nX_Speed) < g_Options_nPF_ObjXSize)
        && (m_pPlayer->Object2.nY - m_pPlayer->Object1.nY < g_Options_nPF_ObjYSize))
        m_pPlayer->Object2.nX_Speed = 0;
    }
  }

  if(!m_pPlayer->Object2.nState)                     // 3. -> 2.
  {
    if(m_pPlayer->Object3.nX_Speed == -OBJ_XSPEED)
    {
      if(((m_pPlayer->Object3.nX + m_pPlayer->Object3.nX_Speed) - (m_pPlayer->Object2.nX + m_pPlayer->Object2.nX_Speed) < g_Options_nPF_ObjXSize)
        && (m_pPlayer->Object3.nY - m_pPlayer->Object2.nY < g_Options_nPF_ObjYSize))
        m_pPlayer->Object3.nX_Speed = 0;
    }
  }

  if(!m_pPlayer->Object1.nState)                     // 3. -> 1.
  {
    if(m_pPlayer->Object3.nX_Speed == -OBJ_XSPEED)
    {
      if(((m_pPlayer->Object3.nX + m_pPlayer->Object3.nX_Speed) - (m_pPlayer->Object1.nX + m_pPlayer->Object1.nX_Speed) < g_Options_nPF_ObjXSize)
        && (m_pPlayer->Object3.nY - m_pPlayer->Object1.nY < g_Options_nPF_ObjYSize))
        m_pPlayer->Object3.nX_Speed = 0;
    }
  }

  // right collision ////////////////////////////////////////////////////////

  if(!m_pPlayer->Object3.nState)                     // 2. -> 3.
  {
    if(m_pPlayer->Object2.nX_Speed == OBJ_XSPEED)
    {
      if(((m_pPlayer->Object3.nX + m_pPlayer->Object3.nX_Speed) - (m_pPlayer->Object2.nX + m_pPlayer->Object2.nX_Speed) < g_Options_nPF_ObjXSize)
        && (m_pPlayer->Object3.nY - m_pPlayer->Object2.nY < g_Options_nPF_ObjYSize))
        m_pPlayer->Object2.nX_Speed = 0;
    }
  }

  if(!m_pPlayer->Object2.nState)                     // 1. -> 2.
  {
    if(m_pPlayer->Object1.nX_Speed == OBJ_XSPEED)
    {
      if(((m_pPlayer->Object2.nX + m_pPlayer->Object2.nX_Speed) - (m_pPlayer->Object1.nX + m_pPlayer->Object1.nX_Speed) < g_Options_nPF_ObjXSize)
        && (m_pPlayer->Object2.nY - m_pPlayer->Object1.nY < g_Options_nPF_ObjYSize))
        m_pPlayer->Object1.nX_Speed = 0;
    }
  }

  if(!m_pPlayer->Object3.nState)                     // 1. -> 3.
  {
    if(m_pPlayer->Object1.nX_Speed == OBJ_XSPEED)
    {
      if(((m_pPlayer->Object3.nX + m_pPlayer->Object3.nX_Speed) - (m_pPlayer->Object1.nX + m_pPlayer->Object1.nX_Speed) < g_Options_nPF_ObjXSize)
        && (m_pPlayer->Object3.nY - m_pPlayer->Object1.nY < g_Options_nPF_ObjYSize))
        m_pPlayer->Object1.nX_Speed = 0;
    }
  }

  UpdateObjects(true);

  return true;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//   U P D A T E   O B J E C T S                                           //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void CGame::UpdateObjects(bool bWhilePlaying)
{
  if(m_pPlayer->Object1.nState != 2)
  {
    if(!m_pPlayer->Object1.nState)
    {
      if(bWhilePlaying)
      {
        m_pPlayer->Object1.nX_Last = m_pPlayer->Object1.nX;
        m_pPlayer->Object1.nY_Last = m_pPlayer->Object1.nY;
        m_pPlayer->Object1.nX += m_pPlayer->Object1.nX_Speed;
        m_pPlayer->Object1.nY += m_pPlayer->Object1.nY_Speed;
      }
      m_pPlayer->Object1.nAnimFrame++;
      if(m_pPlayer->Object1.nAnimFrame == OBJ_ANIM_FRAMES_NUM * OBJ_ANIM_DELAY)
        m_pPlayer->Object1.nAnimFrame = 0;
    }
    DD_DrawObject(false, m_pPlayer->Object1.nX, m_pPlayer->Object1.nY, m_pPlayer->Object1.nZ, m_pPlayer->Object1.nAnimFrame / OBJ_ANIM_DELAY);
  }
  if(m_pPlayer->Object2.nState != 2)
  {
    if(!m_pPlayer->Object2.nState)
    {
      if(bWhilePlaying)
      {
        m_pPlayer->Object2.nX_Last = m_pPlayer->Object2.nX;
        m_pPlayer->Object2.nY_Last = m_pPlayer->Object2.nY;
        m_pPlayer->Object2.nX += m_pPlayer->Object2.nX_Speed;
        m_pPlayer->Object2.nY += m_pPlayer->Object2.nY_Speed;
      }
      m_pPlayer->Object2.nAnimFrame++;
      if(m_pPlayer->Object2.nAnimFrame == OBJ_ANIM_FRAMES_NUM * OBJ_ANIM_DELAY)
        m_pPlayer->Object2.nAnimFrame = 0;
    }
    DD_DrawObject(false, m_pPlayer->Object2.nX, m_pPlayer->Object2.nY, m_pPlayer->Object2.nZ, m_pPlayer->Object2.nAnimFrame / OBJ_ANIM_DELAY);
  }

  if(m_pPlayer->Object3.nState != 2)
  {
    if(!m_pPlayer->Object3.nState)
    {
      if(bWhilePlaying)
      {
        m_pPlayer->Object3.nX_Last = m_pPlayer->Object3.nX;
        m_pPlayer->Object3.nY_Last = m_pPlayer->Object3.nY;
        m_pPlayer->Object3.nX += m_pPlayer->Object3.nX_Speed;
        m_pPlayer->Object3.nY += m_pPlayer->Object3.nY_Speed;
      }
      m_pPlayer->Object3.nAnimFrame++;
      if(m_pPlayer->Object3.nAnimFrame == OBJ_ANIM_FRAMES_NUM * OBJ_ANIM_DELAY)
        m_pPlayer->Object3.nAnimFrame = 0;
    }
    DD_DrawObject(false, m_pPlayer->Object3.nX, m_pPlayer->Object3.nY, m_pPlayer->Object3.nZ, m_pPlayer->Object3.nAnimFrame / OBJ_ANIM_DELAY);
  }
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//    O B J E C T   M O V I N G                                            //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void CGame::ObjectMoving(OBJECT* pObject)
{
  if(!pObject->nState)
  {
    // move down ////////////////////////////////////////////////////////////

    if(pObject->nY_Speed != 0)
    {
      if(m_pPlayer->Playfield[pObject->nX / g_Options_nPF_ObjXSize]
                    [((pObject->nY + pObject->nY_Speed + (g_Options_nPF_ObjYSize - 1)) / g_Options_nPF_ObjYSize)] != ' '
      || m_pPlayer->Playfield[((pObject->nX + (g_Options_nPF_ObjXSize - 1)) / g_Options_nPF_ObjXSize)]
                    [((pObject->nY + pObject->nY_Speed + (g_Options_nPF_ObjYSize - 1)) / g_Options_nPF_ObjYSize)] != ' ')
      {
        pObject->nY_Speed = 0;
        if((pObject->nY % g_Options_nPF_ObjYSize) != 0)
        {
          short nSpeed = g_Options_nPF_ObjYSize - (pObject->nY % g_Options_nPF_ObjYSize);
          if(nSpeed < OBJ_YSPEED)
            pObject->nY_Speed = nSpeed;
        }
      }
    }

    // move left ////////////////////////////////////////////////////////////

    if(pObject->nX_Speed == -OBJ_XSPEED)
    {
      if(m_pPlayer->Playfield[((pObject->nX - OBJ_XSPEED) / g_Options_nPF_ObjXSize)]
                    [(pObject->nY / g_Options_nPF_ObjYSize)] != ' '
      || m_pPlayer->Playfield[((pObject->nX - OBJ_XSPEED) / g_Options_nPF_ObjXSize)]
                    [((pObject->nY + (g_Options_nPF_ObjYSize - 1)) / g_Options_nPF_ObjYSize)] != ' ')
        pObject->nX_Speed = 0;
    }

    // move left down ///////////////////////////////////////////////////////

    if(pObject->nX_Speed == -OBJ_XSPEED && pObject->nY_Speed != 0)
    {
      if(m_pPlayer->Playfield[((pObject->nX - OBJ_XSPEED) / g_Options_nPF_ObjXSize)]
                    [((pObject->nY + pObject->nY_Speed + (g_Options_nPF_ObjYSize - 1)) / g_Options_nPF_ObjYSize)] != ' ')
        pObject->nX_Speed = 0;
    }

    // move right ///////////////////////////////////////////////////////////

    if(pObject->nX_Speed == OBJ_XSPEED)
    {
      if(m_pPlayer->Playfield[((pObject->nX + OBJ_XSPEED + (g_Options_nPF_ObjXSize - 1)) / g_Options_nPF_ObjXSize)]
                    [(pObject->nY / g_Options_nPF_ObjYSize)] != ' '
      || m_pPlayer->Playfield[((pObject->nX + OBJ_XSPEED + (g_Options_nPF_ObjXSize - 1)) / g_Options_nPF_ObjXSize)]
                    [((pObject->nY + (g_Options_nPF_ObjYSize - 1)) / g_Options_nPF_ObjYSize)] != ' ')
        pObject->nX_Speed = 0;
    }

    // move right down //////////////////////////////////////////////////////

    if(pObject->nX_Speed == OBJ_XSPEED && pObject->nY_Speed != 0)
    {
      if(m_pPlayer->Playfield[((pObject->nX + OBJ_XSPEED + (g_Options_nPF_ObjXSize - 1)) / g_Options_nPF_ObjXSize)]
                    [((pObject->nY + pObject->nY_Speed + (g_Options_nPF_ObjYSize - 1)) / g_Options_nPF_ObjYSize)] != ' ')
        pObject->nX_Speed = 0;

    }

    // lay down the object //////////////////////////////////////////////////

    if((pObject->nX % g_Options_nPF_ObjXSize) == 0
      && m_pPlayer->Playfield[pObject->nX / g_Options_nPF_ObjXSize][(pObject->nY / g_Options_nPF_ObjYSize) + 1] != ' ')
    {
      pObject->nState = 1;
      short nX = pObject->nX / g_Options_nPF_ObjXSize;
      short nY = pObject->nY / g_Options_nPF_ObjYSize;
      m_pPlayer->Playfield[nX][nY] = (char)pObject->nZ;
      m_pPlayer->Playfield_Frames[nX][nY] = pObject->nAnimFrame / OBJ_ANIM_DELAY;

      AddScore(1);

      if(Testing(false) == true)    // only the test (no initialization)
      {
        m_pPlayer->Object1.nY_Speed = 0;     // stop all
        m_pPlayer->Object2.nY_Speed = 0;
        m_pPlayer->Object3.nY_Speed = 0;
        m_pPlayer->Object1.nX_Speed = 0;
        m_pPlayer->Object2.nX_Speed = 0;
        m_pPlayer->Object3.nX_Speed = 0;
      }
    }
  }
  else
  {
    if(pObject->nState == 1)
    {
      pObject->nState = 2;          // no move and animation

      #ifdef USE_DSOUND
        DS_PlaySound(DS_SOUND_PLACE, NULL);
      #endif

      if((m_pPlayer->bSignalizingFlag = Testing(true)) == true)
      {
        m_pPlayer->bSignalizingFlag = false;
        m_pPlayer->nGameState = GS_SIGNALIZING;
        m_pPlayer->nSignalizingTimeCounter = SIGNALIZING_TIME;
        m_pPlayer->Object1.nY_Speed = 0;     // stop all
        m_pPlayer->Object2.nY_Speed = 0;
        m_pPlayer->Object3.nY_Speed = 0;
        m_pPlayer->Object1.nX_Speed = 0;
        m_pPlayer->Object2.nX_Speed = 0;
        m_pPlayer->Object3.nX_Speed = 0;
      }
    }
  }
}

// Signalizing //////////////////////////////////////////////////////////////

void CGame::Signalizing() 
{
//  g_DD_FlipScreens();

  if(--(m_pPlayer->nSignalizingTimeCounter) == 1)
  {
    Signalize(false);
  }
  else if(m_pPlayer->nSignalizingTimeCounter == 0)
  {
    Signalize(false);

    int nNum = 0;
    for(short nY = 1; nY < m_nPF_YSize - 1; nY++)
    {
      for(short nX = 1; nX < m_nPF_XSize - 1; nX++)
      {
        if(m_pPlayer->Playfield[nX][nY] < 'a' && m_pPlayer->Playfield[nX][nY] != ' ')
        {
          m_pPlayer->Playfield[nX][nY] = ' ';              // clean up
          nNum++;
        }
      }
    }
    AddScore(10 * nNum);

    FallingInit();
  }
  else
  {
    if(m_pPlayer->nSignalizingTimeCounter % SIGNALIZING_DELAY == 1)
    {
      m_pPlayer->bSignalizingState ^= true;
      Signalize(m_pPlayer->bSignalizingState);
    }
    if(m_pPlayer->nSignalizingTimeCounter % SIGNALIZING_DELAY == 0)
    {
      Signalize(m_pPlayer->bSignalizingState);
    }
  }	
}

// Falling /////////////////////////////////////////////////////////////////

void CGame::Falling() 
{
  bool bShiftingFlag = false;
  SHIFTING_BLOCK* pShiftingBlock;
  ARRAY_SHIFTING_BLOCKS* paShiftingColumn;
  short nBlockNum;
  short nCulNum = m_pPlayer->aShifting.GetSize();

  for(short nX = 0; nX < nCulNum; nX++)
  {
    paShiftingColumn = m_pPlayer->aShifting[nX];

    nBlockNum = paShiftingColumn->GetSize();
    for(short nY = 0; nY < nBlockNum; nY++)
    {
      pShiftingBlock = paShiftingColumn->GetAt(nY);
      if(!pShiftingBlock->bState)
      {
        bShiftingFlag = true;
        DD_ShiftBlock(pShiftingBlock->nY_Counter,
                      pShiftingBlock->nX,
                      pShiftingBlock->nY_Beg,
                      pShiftingBlock->nY_Size,
                      pShiftingBlock->nY_DownRate
                      );
        pShiftingBlock->nY_Counter++;
        if(pShiftingBlock->nY_Counter == pShiftingBlock->nY_DownRate)
          pShiftingBlock->bState = true;
      }
    }
  }

  if(!bShiftingFlag)    // finished?
  {
    m_pPlayer->nGameState = GS_PLAYING;

    ClearFallingTab();

    if(Testing(true))
    {
      m_pPlayer->nGameState = GS_SIGNALIZING;
      m_pPlayer->nSignalizingTimeCounter = SIGNALIZING_TIME;
    }
  }
}

// Clear the table //////////////////////////////////////////////////////////

void CGame::ClearFallingTab()
{
  ARRAY_SHIFTING_BLOCKS* paShiftingColumn;
  short nX_Size = m_pPlayer->aShifting.GetSize();
  short nY_Size;
  for(short nX = 0; nX < nX_Size; nX++)
  {
    paShiftingColumn = m_pPlayer->aShifting[0];
    nY_Size = paShiftingColumn->GetSize();
    for(short nY = 0; nY < nY_Size; nY++)
    {
      delete paShiftingColumn->GetAt(0);
      paShiftingColumn->RemoveAt(0);
    }
    ASSERT(paShiftingColumn->GetSize() == 0);
    m_pPlayer->aShifting.RemoveAt(0);
    delete paShiftingColumn;
  }
  ASSERT(m_pPlayer->aShifting.GetSize() == 0);
}

// Fill the table for shifting //////////////////////////////////////////////

void CGame::FallingInit()
{
  m_pPlayer->nGameState = GS_PLAYING;
  SHIFTING_BLOCK* pShiftingBlock;
  ARRAY_SHIFTING_BLOCKS* paShiftingColumn;
  short nX;
  short nY;
  short nY_Space;
  short nY_Block;
  short nY_Offset;
  short nY_Work;
  bool bColumn;

  for(nX = 1; nX < m_nPF_XSize - 1; nX++)
  {
    bColumn = false;
    nY_Offset = 0;
    for(nY = m_nPF_YSize - 2; nY >= 2; nY--)
    {
      if(m_pPlayer->Playfield[nX][nY] == ' ')
      {
        nY_Space = 0;
        nY_Work = nY;
        while(m_pPlayer->Playfield[nX][nY_Work] == ' ')
        {
          nY_Space++;
          nY_Work--;
          if(nY_Work <= 1)
            break;
        }

        nY_Block = 0;
        nY_Work = nY - nY_Space;
        while(m_pPlayer->Playfield[nX][nY_Work] != ' ')
        {
          nY_Block++;
          nY_Work--;
          if(nY_Work < 1)
            break;
        }

        if(nY_Block > 0)
        {
          m_pPlayer->nGameState = GS_FALLING;
          pShiftingBlock = new SHIFTING_BLOCK;
          pShiftingBlock->bState = false;
          pShiftingBlock->nY_Counter = 0;
          pShiftingBlock->nY_DownRate = (nY_Space + nY_Offset) * g_Options_nPF_ObjYSize + 1;
          pShiftingBlock->nX = nX * g_Options_nPF_ObjXSize;
          pShiftingBlock->nY_Beg = (nY_Work + 1) * g_Options_nPF_ObjYSize;
          pShiftingBlock->nY_Size = nY_Block * g_Options_nPF_ObjYSize;

          if(!bColumn)
            paShiftingColumn = new ARRAY_SHIFTING_BLOCKS;
          bColumn = true;
          paShiftingColumn->Add(pShiftingBlock);

          nY_Offset += nY_Space;
          nY -= (nY_Space + nY_Block - 1);
        }
      }
    }
    if(bColumn)
      m_pPlayer->aShifting.Add(paShiftingColumn);
  }

// Falling //////////////////////////////////////////////////////////////////

  char WorkPf[PF_MAX_XSIZE][PF_MAX_YSIZE];
  short WorkPf_Frames[PF_MAX_XSIZE][PF_MAX_YSIZE];

  for(nX = 1; nX < m_nPF_XSize - 1; nX++)
  {
    for(nY = 1; nY < m_nPF_YSize - 1; nY++)
    {
      WorkPf[nX][nY] = m_pPlayer->Playfield[nX][nY];
      WorkPf_Frames[nX][nY] = m_pPlayer->Playfield_Frames[nX][nY];
      m_pPlayer->Playfield[nX][nY] = ' ';
      m_pPlayer->Playfield_Frames[nX][nY] = 0;
    }
  }

  short nYDest;
  for(nX = 1; nX < m_nPF_XSize - 1; nX++)
  {
    nYDest = m_nPF_YSize - 2;
    for(nY = m_nPF_YSize - 2; nY >= 1; nY--)
    {
      if(WorkPf[nX][nY] != ' ')
      {
        m_pPlayer->Playfield[nX][nYDest] = WorkPf[nX][nY];
        m_pPlayer->Playfield_Frames[nX][nYDest] = WorkPf_Frames[nX][nY];
        nYDest--;
      }
    }
  }

  if(g_Options_nPF_ObjType)
  {
    ClearFallingTab();
    DrawPlayfield();
    DD_CopySecondaryToPrimary();
  }
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//  DIRECT DRAW                                                            //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool CGame::DD_Init()
{
  m_lpDDP_Background = DDLoadPalette(g_lpDD, m_sBitmapBackground);
  if(m_lpDDP_Background)
  {
    g_DX_Result = g_lpDDS_Primary->SetPalette(m_lpDDP_Background);    // make sure to set the palette before loading bitmaps.
    DD_CHECK_ERROR("Error - DD - SetPalette "  + m_sBitmapBackground);
  }

  m_lpDDS_Objects = DDLoadBitmap(g_lpDD, m_sBitmapObjects, 0, 0);
  if(!m_lpDDS_Objects)
  {
    AfxMessageBox("Error - DD - LoadBitmap " + m_sBitmapObjects);
    return false;
  }

  m_lpDDS_Background = DDLoadBitmap(g_lpDD, m_sBitmapBackground, 0, 0);
  if(!m_lpDDS_Background)
  {
    AfxMessageBox("Error - DD - LoadBitmap " + m_sBitmapBackground);
    return false;
  }

  if(m_lpDDP_Background->GetEntries(0, 0, 256, m_PalEntry_Background) != DD_OK)
    AfxMessageBox("Error - DD - Get Palette Entries");

	g_DX_Result = DDSetColorKey(m_lpDDS_Objects, CLR_INVALID);
  DD_CHECK_ERROR("Error - DD - SetColorKey");

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DD_RestoreAll()
{
  return g_lpDDS_Primary->Restore() == DD_OK &&
         g_lpDDS_Secondary->Restore() == DD_OK &&
         m_lpDDS_Objects->Restore() == DD_OK &&
         m_lpDDS_Background->Restore() == DD_OK &&

         DDLoadPalette(g_lpDD, m_sBitmapBackground) &&
         g_lpDDS_Primary->SetPalette(m_lpDDP_Background) == DD_OK &&

         DDReLoadBitmap(m_lpDDS_Objects, m_sBitmapObjects) == DD_OK &&
         DDReLoadBitmap(m_lpDDS_Background, m_sBitmapBackground) == DD_OK;
}

/////////////////////////////////////////////////////////////////////////////

void CGame::DD_Finish()
{
  if(m_lpDDS_Objects != NULL)
  {
    m_lpDDS_Objects->Release();
    m_lpDDS_Objects = NULL;
  }
  if(m_lpDDP_Background != NULL)
  {
    m_lpDDP_Background->Release();
    m_lpDDP_Background = NULL;
  }
}

/////////////////////////////////////////////////////////////////////////////

void CGame::FadeIn()
{
  int nLoops = 25;
  PALETTEENTRY peAnimate[256];
  PALETTEENTRY peOriginal[256];
  memcpy(&peOriginal, &m_PalEntry_Background, 256 * sizeof(PALETTEENTRY));
  memcpy(&peAnimate, &m_PalEntry_Background, 256 * sizeof(PALETTEENTRY));

  BYTE clrRValue = peOriginal[0].peBlue;
  BYTE clrGValue = peOriginal[0].peGreen;
  BYTE clrBValue = peOriginal[0].peBlue;
  for(int i = 0; i < 256; i++)
  {
    peAnimate[i].peRed = clrRValue;
    peAnimate[i].peGreen = clrGValue;
    peAnimate[i].peBlue = clrBValue;
  }

  for(i = 1; i <= nLoops; i++)
  {
    for (int j = 0; j < 256; j++) 
    {  
      peAnimate[j].peRed   = clrRValue - ((clrRValue - peOriginal[j].peRed)   * i) / nLoops;
      peAnimate[j].peGreen = clrGValue - ((clrGValue - peOriginal[j].peGreen) * i) / nLoops;
      peAnimate[j].peBlue  = clrBValue - ((clrBValue - peOriginal[j].peBlue)  * i) / nLoops;
    }
    WAITFORVB;
    if(m_lpDDP_Background->SetEntries(0, 0, 256, peAnimate) != DD_OK)
      AfxMessageBox("Error - DD - Set Palette Entry");
  }
  ASSERT(memcmp(peOriginal, peAnimate, 256) == 0);
}

/////////////////////////////////////////////////////////////////////////////

void CGame::FadeOut()
{
  int nLoops = 25;
  PALETTEENTRY peAnimate[256];
  PALETTEENTRY peOriginal[256];
  memcpy(&peOriginal, &m_PalEntry_Background, 256 * sizeof(PALETTEENTRY));

  BYTE clrRValue = peOriginal[0].peBlue;
  BYTE clrGValue = peOriginal[0].peGreen;
  BYTE clrBValue = peOriginal[0].peBlue;

  for(int i = 0; i < 256; i++)
  {
    peAnimate[i].peRed = peOriginal[i].peRed;
    peAnimate[i].peGreen = peOriginal[i].peGreen;
    peAnimate[i].peBlue = peOriginal[i].peBlue;
  }

  for(i = 1; i <= nLoops; i++)
  {
    for (int j = 0; j < 256; j++) 
    {  
      peAnimate[j].peRed   = peOriginal[j].peRed   - ((peOriginal[j].peRed   - clrRValue) * i) / nLoops;
      peAnimate[j].peGreen = peOriginal[j].peGreen - ((peOriginal[j].peGreen - clrGValue) * i) / nLoops;
      peAnimate[j].peBlue  = peOriginal[j].peBlue  - ((peOriginal[j].peBlue  - clrBValue) * i) / nLoops;
    }
    WAITFORVB;
    if(m_lpDDP_Background->SetEntries(0, 0, 256, peAnimate) != DD_OK)
      AfxMessageBox("Error - DD - Set Palette Entry");
  }
}

/////////////////////////////////////////////////////////////////////////////

void CGame::FadeColorToGray() 
{
  int nLoops = 25;
  PALETTEENTRY peAnimate[256];
  PALETTEENTRY peGray[256];
  PALETTEENTRY peOriginal[256];

  m_lpDDP_Background->GetEntries(0, 0, 256, peOriginal);

  for(int i = 0; i < 256; i++)
  {
    long lSquareSum = peOriginal[i].peRed 
                            * peOriginal[i].peRed
                            + peOriginal[i].peGreen 
                            * peOriginal[i].peGreen
                            + peOriginal[i].peBlue 
                            * peOriginal[i].peBlue;
    int nGray = (int)sqrt(((double)lSquareSum) / 3);

    peGray[i].peRed = nGray;
    peGray[i].peGreen = nGray;
    peGray[i].peBlue = nGray;
  }

  for(i = 1; i <= nLoops; i++)
  {
    for (int j = 0; j < 256; j++) 
    {  
      peAnimate[j].peRed   = peOriginal[j].peRed   - ((peOriginal[j].peRed   - peGray[j].peRed)   * i) / nLoops;
      peAnimate[j].peGreen = peOriginal[j].peGreen - ((peOriginal[j].peGreen - peGray[j].peGreen) * i) / nLoops;
      peAnimate[j].peBlue  = peOriginal[j].peBlue  - ((peOriginal[j].peBlue  - peGray[j].peBlue)  * i) / nLoops;
      peAnimate[j].peFlags = peOriginal[j].peFlags;
    }

    WAITFORVB;
    m_lpDDP_Background->SetEntries(0, 0, 256, peAnimate);
  }
}

/////////////////////////////////////////////////////////////////////////////

void CGame::FadeGrayToColor() 
{
  int nLoops = 25;
  PALETTEENTRY peAnimate[256];
  PALETTEENTRY peGray[256];
  PALETTEENTRY peOriginal[256];
  memcpy(&peOriginal, &m_PalEntry_Background, 256 * sizeof(PALETTEENTRY));

  m_lpDDP_Background->GetEntries(0, 0, 256, peGray);

  for(int i = 1; i <= nLoops; i++)
  {
    for (int j = 0; j < 256; j++) 
    {  
      peAnimate[j].peRed   = peGray[j].peRed   - ((peGray[j].peRed   - peOriginal[j].peRed)   * i) / nLoops;
      peAnimate[j].peGreen = peGray[j].peGreen - ((peGray[j].peGreen - peOriginal[j].peGreen) * i) / nLoops;
      peAnimate[j].peBlue  = peGray[j].peBlue  - ((peGray[j].peBlue  - peOriginal[j].peBlue)  * i) / nLoops;
      peAnimate[j].peFlags = peGray[j].peFlags;
    }

    WAITFORVB;
    m_lpDDP_Background->SetEntries(0, 0, 256, peAnimate);
  }
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DD_ClearScreen()
{
  DDBLTFX blt = { 0 };
  blt.dwSize = sizeof(blt);
  blt.dwFillColor = RGB(0, 0, 0);

  DD_BLT(g_lpDDS_Secondary->Blt(0, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &blt));
  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DD_CopyBackground()
{
  RECT rcRect;
  rcRect.left   = 0;
  rcRect.top    = 0;
  rcRect.right  = SCREEN_XSIZE;
  rcRect.bottom = SCREEN_YSIZE;

  DD_BLT(g_lpDDS_Secondary->BltFast(0, 0, m_lpDDS_Background, &rcRect, DDBLTFAST_NOCOLORKEY));
  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DD_CopyPrimaryToSecondary()
{
  RECT rcRect;
  rcRect.left   = 0;
  rcRect.top    = 0;
  rcRect.right  = SCREEN_XSIZE;
  rcRect.bottom = SCREEN_YSIZE;

  DD_BLT(g_lpDDS_Secondary->BltFast(0, 0, g_lpDDS_Primary, &rcRect, DDBLTFAST_NOCOLORKEY));
  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DD_CopySecondaryToPrimary()
{
  if(g_Options_nPlayerNum == 1)
  {
    RECT rcRect;
    rcRect.left   = 0;
    rcRect.top    = 0;
    rcRect.right  = SCREEN_XSIZE;
    rcRect.bottom = SCREEN_YSIZE;

    DD_BLT(g_lpDDS_Primary->BltFast(0, 0, g_lpDDS_Secondary, &rcRect, DDBLTFAST_NOCOLORKEY));
  }
  else
  {
    if(m_pPlayer->nWhich == 1)    // player one?
    {
      RECT rcRect;
      rcRect.left   = 0;
      rcRect.top    = 0;
      rcRect.right  = SCREEN_XSIZE / 2;
      rcRect.bottom = SCREEN_YSIZE;

      DD_BLT(g_lpDDS_Primary->BltFast(0, 0, g_lpDDS_Secondary, &rcRect, DDBLTFAST_NOCOLORKEY));
    }
    else
    {
      RECT rcRect;
      rcRect.left   = SCREEN_XSIZE / 2;
      rcRect.top    = 0;
      rcRect.right  = SCREEN_XSIZE;
      rcRect.bottom = SCREEN_YSIZE;

      DD_BLT(g_lpDDS_Primary->BltFast(SCREEN_XSIZE / 2, 0, g_lpDDS_Secondary, &rcRect, DDBLTFAST_NOCOLORKEY));
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DD_SetObject(short nX, short nY, short nZ, short nAnimFrame)
{
  RECT    rcSrc;
  RECT    rcDest;

  DWORD dwFlags = 0;

  LPDIRECTDRAWSURFACE lpDD_SrcSurface = m_lpDDS_Objects;

  if(nZ == '@')
  {
    rcSrc.left   = 640 - OBJ_XSIZE;
    rcSrc.right  = 640;
    rcSrc.top    = 0 * OBJ_YSIZE;
    rcSrc.bottom = 0 * OBJ_YSIZE + OBJ_YSIZE;
    dwFlags = DDBLT_KEYSRC;
  }
  else if(nZ == ' ')
  {
    lpDD_SrcSurface = m_lpDDS_Background;
    rcSrc.left   = m_pPlayer->nPF_XBeginning + nX * g_Options_nPF_ObjXSize;
    rcSrc.right  = m_pPlayer->nPF_XBeginning + nX * g_Options_nPF_ObjXSize + g_Options_nPF_ObjXSize;
    rcSrc.top    = m_pPlayer->nPF_YBeginning + nY * g_Options_nPF_ObjYSize;
    rcSrc.bottom = m_pPlayer->nPF_YBeginning + nY * g_Options_nPF_ObjYSize + g_Options_nPF_ObjYSize;
  }
  else
  {
    nZ -= 'a';
    rcSrc.left   = nAnimFrame * OBJ_XSIZE;
    rcSrc.right  = nAnimFrame * OBJ_XSIZE + OBJ_XSIZE;
    rcSrc.top    = nZ * OBJ_YSIZE;
    rcSrc.bottom = nZ * OBJ_YSIZE + OBJ_YSIZE;

    if(g_Options_nPF_ObjType)
      dwFlags = DDBLT_KEYSRC;
  }

  rcDest.left   = m_pPlayer->nPF_XBeginning + nX * g_Options_nPF_ObjXSize;
  rcDest.right  = m_pPlayer->nPF_XBeginning + nX * g_Options_nPF_ObjXSize + g_Options_nPF_ObjXSize;
  rcDest.top    = m_pPlayer->nPF_YBeginning + nY * g_Options_nPF_ObjYSize;
  rcDest.bottom = m_pPlayer->nPF_YBeginning + nY * g_Options_nPF_ObjYSize + g_Options_nPF_ObjYSize;

  DD_BLT(g_lpDDS_Secondary->Blt(&rcDest, lpDD_SrcSurface, &rcSrc, dwFlags, NULL));

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DD_DrawObject(bool bPrimary, short nX, short nY, short nZ, short nAnimFrame)
{
  RECT rcSrc;
  RECT rcDest;
  LPDIRECTDRAWSURFACE lpDD_SrcSurface = m_lpDDS_Objects;
  DWORD dwFlags = 0;

  rcDest.left   = m_pPlayer->nPF_XBeginning + nX;
  rcDest.right  = m_pPlayer->nPF_XBeginning + nX + g_Options_nPF_ObjXSize;
  rcDest.top    = m_pPlayer->nPF_YBeginning + nY;
  rcDest.bottom = m_pPlayer->nPF_YBeginning + nY + g_Options_nPF_ObjYSize;

  if(nZ != 0)
  {
    nZ -= 'a';
    rcSrc.left   = nAnimFrame * OBJ_XSIZE;
    rcSrc.right  = nAnimFrame * OBJ_XSIZE + OBJ_XSIZE;
    rcSrc.top    = nZ * OBJ_YSIZE;
    rcSrc.bottom = nZ * OBJ_YSIZE + OBJ_YSIZE;

    if(g_Options_nPF_ObjType)
      dwFlags = DDBLT_KEYSRC;
  }
  else
  {
    lpDD_SrcSurface = m_lpDDS_Background;
    rcSrc = rcDest;
  }

  if(bPrimary)
  {
    DD_BLT(g_lpDDS_Primary->Blt(&rcDest, lpDD_SrcSurface, &rcSrc, dwFlags, NULL));
  }
  else
  {
    DD_BLT(g_lpDDS_Secondary->Blt(&rcDest, lpDD_SrcSurface, &rcSrc, dwFlags, NULL));
  }

  return true;
}

// Fall one block (in a Column) /////////////////////////////////////////////

bool CGame::DD_ShiftBlock(short nY_Counter, short nX, short nY_Beg, short nY_Size, short nY_DownRate)
{
  RECT rcSrc;
  RECT rcDest;

  short nShiftOffset = 2;

  if(nY_Counter == 0)
  {
    nY_Counter = 1;
    nShiftOffset = 1;
  }
  if(nY_Counter == nY_DownRate - 1)
    nShiftOffset = 1;

  nY_Counter--;

  rcSrc.left   = m_pPlayer->nPF_XBeginning + nX;
  rcSrc.right  = m_pPlayer->nPF_XBeginning + nX + g_Options_nPF_ObjXSize;
  rcSrc.top    = m_pPlayer->nPF_YBeginning + nY_Beg + nY_Counter;
  rcSrc.bottom = m_pPlayer->nPF_YBeginning + nY_Beg + nY_Counter + nY_Size;

  rcDest.left   = m_pPlayer->nPF_XBeginning + nX;
  rcDest.right  = m_pPlayer->nPF_XBeginning + nX + g_Options_nPF_ObjXSize;
  rcDest.top    = m_pPlayer->nPF_YBeginning + nY_Beg + nY_Counter + nShiftOffset;
  rcDest.bottom = m_pPlayer->nPF_YBeginning + nY_Beg + nY_Counter + nShiftOffset + nY_Size;

  DD_BLT(g_lpDDS_Secondary->Blt(&rcDest, g_lpDDS_Secondary, &rcSrc, 0, NULL));

  // complete the background

  rcSrc.left   = m_pPlayer->nPF_XBeginning + nX;
  rcSrc.right  = m_pPlayer->nPF_XBeginning + nX + g_Options_nPF_ObjXSize;
  rcSrc.top    = m_pPlayer->nPF_YBeginning + nY_Beg + nY_Counter;
  rcSrc.bottom = m_pPlayer->nPF_YBeginning + nY_Beg + nY_Counter + nShiftOffset;

  DD_BLT(g_lpDDS_Secondary->Blt(&rcSrc, m_lpDDS_Background, &rcSrc, 0, NULL));

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::AddScore(int nPlus)
{
  m_pPlayer->nScore += nPlus;
  HDC hdc;
  if(g_lpDDS_Secondary->GetDC(&hdc) == DD_OK)
  {
    SetBkColor(hdc, RGB(0, 0, 0));
    SetTextColor(hdc, RGB(255, 255, 255));

    CString sValue;
    sValue.Format("%d", m_pPlayer->nScore);

    TextOut(hdc, m_pPlayer->nScoreXBeg, SCREEN_YSIZE - FONT_HEIGHT, sValue, lstrlen(sValue));
    g_lpDDS_Secondary->ReleaseDC(hdc);
  }

  RECT rcSrc;
  rcSrc.left   = 0;
  rcSrc.right  = SCREEN_XSIZE;
  rcSrc.top    = SCREEN_YSIZE - FONT_HEIGHT;
  rcSrc.bottom = SCREEN_YSIZE;
  DD_BLT(g_lpDDS_Primary->Blt(&rcSrc, g_lpDDS_Secondary, &rcSrc, 0, NULL));
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//  DIRECT INPUT                                                           //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool CGame::DI_Frame()
{
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
            WriteWindowToDIB("c:\\temp\\game.bmp", AfxGetMainWnd());
            break;
          #endif
          case DIK_ESCAPE:
            if(!(g_DI_rgdod[iod].dwData & 0x80))
              m_bQuit = true;
            break;

          case DIK_F1:
            if(!(g_DI_rgdod[iod].dwData & 0x80))
            {
              FadeOut();
              Init(false);
            }
            break;

          case DIK_P:
            if(g_DI_rgdod[iod].dwData & 0x80)
            {
              m_bPause ^= true;
              if(m_bPause)
                FadeColorToGray();
              else
                FadeGrayToColor();
            }
            break;

          case DIK_S:
            if(g_DI_rgdod[iod].dwData & 0x80)
            {
            #ifdef USE_DSOUND
              g_Options_bSoundFX ^= true;
            #endif
            }
            break;

          // player 1

          case DIK_UP:
            if(g_DI_rgdod[iod].dwData & 0x80)
              m_PlayerOne.bControlRotateFlag = true;
            break;

          case DIK_DOWN:
            if(g_DI_rgdod[iod].dwData & 0x80)
            {
              m_PlayerOne.bControlDownFlag = true;
              #ifdef USE_DSOUND
                DS_PlaySound(DS_SOUND_SPEEDUP, NULL);
              #endif
            }
            else
              m_PlayerOne.bControlDownFlag = false;
            break;

          case DIK_LEFT:
            if(g_DI_rgdod[iod].dwData & 0x80)
              m_PlayerOne.bControlLeftFlag = true;
            else
              m_PlayerOne.bControlLeftFlag = false;
            break;

          case DIK_RIGHT:
            if(g_DI_rgdod[iod].dwData & 0x80)
              m_PlayerOne.bControlRightFlag = true;
            else
              m_PlayerOne.bControlRightFlag = false;
            break;

          // player 2

          case DIK_NUMPAD8:
            if(g_DI_rgdod[iod].dwData & 0x80)
              m_PlayerTwo.bControlRotateFlag = true;
            break;

          case DIK_NUMPAD5:
            if(g_DI_rgdod[iod].dwData & 0x80)
            {
              m_PlayerTwo.bControlDownFlag = true;
              #ifdef USE_DSOUND
                DS_PlaySound(DS_SOUND_SPEEDUP, NULL);
              #endif
            }
            else
              m_PlayerTwo.bControlDownFlag = false;
            break;

          case DIK_NUMPAD4:
            if(g_DI_rgdod[iod].dwData & 0x80)
              m_PlayerTwo.bControlLeftFlag = true;
            else
              m_PlayerTwo.bControlLeftFlag = false;
            break;

          case DIK_NUMPAD6:
            if(g_DI_rgdod[iod].dwData & 0x80)
              m_PlayerTwo.bControlRightFlag = true;
            else
              m_PlayerTwo.bControlRightFlag = false;
            break;
        }
      }
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//  DIRECT SOUND                                                           //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool CGame::DS_Init()
{
  for(int i = 0; i < DS_SOUNDS_NUM; i ++)      // Null out all the sound pointers
    m_lpDS_Sounds[i] = NULL;

  if(!DS_CreateBufferFromWaveFile(m_cWavRotate, DS_SOUND_ROTATE))
    DS_CB_ERROR("Error - DS - Loading .WAV file");

  if(!DS_CreateBufferFromWaveFile(m_cWavSpeedup, DS_SOUND_SPEEDUP))
    DS_CB_ERROR("Error - DS - Loading .WAV file");

  if(!DS_CreateBufferFromWaveFile(m_cWavPlace, DS_SOUND_PLACE))
    DS_CB_ERROR("Error - DS - Loading .WAV file");

  if(!DS_CreateBufferFromWaveFile(m_cWavSignalizing, DS_SOUND_SIGNALIZING))
    DS_CB_ERROR("Error - DS - Loading .WAV file");

  if(!DS_CreateBufferFromWaveFile(m_cWavFalling, DS_SOUND_FALLING))
    DS_CB_ERROR("Error - DS - Loading .WAV file");

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DS_CreateBufferFromWaveFile(char* FileName, DWORD dwBuf)
{
  struct WaveHeader
  {
    BYTE        RIFF[4];          // "RIFF"
    DWORD       dwSize;           // Size of data to follow
    BYTE        WAVE[4];          // "WAVE"
    BYTE        fmt_[4];          // "fmt "
    DWORD       dw16;             // 16
    WORD        wOne_0;           // 1
    WORD        wChnls;           // Number of Channels
    DWORD       dwSRate;          // Sample Rate
    DWORD       BytesPerSec;      // Sample Rate
    WORD        wBlkAlign;        // 1
    WORD        BitsPerSample;    // Sample size
    BYTE        DATA[4];          // "DATA"
    DWORD       dwDSize;          // Number of Samples
  };

  // Open the wave file       
  FILE* pFile = fopen(FileName, "rb");
  if(!pFile)
    return false;

  // Read in the wave header          
  WaveHeader wavHdr;
  if (fread(&wavHdr, sizeof(wavHdr), 1, pFile) != 1) 
  {
    fclose(pFile);
    return NULL;
  }

  // Figure out the size of the data region
  DWORD dwSize = wavHdr.dwDSize;

  // Is this a stereo or mono file?
  BOOL bStereo = wavHdr.wChnls > 1 ? true : false;

  // Create the sound buffer for the wave file
  if(DS_CreateSoundBuffer(dwBuf, dwSize, wavHdr.dwSRate, wavHdr.BitsPerSample, wavHdr.wBlkAlign, bStereo) != TRUE)
  {
    // Close the file
    fclose(pFile);
    
    return false;
  }

  // Read the data for the wave file into the sound buffer
  if (!DS_ReadData(m_lpDS_Sounds[dwBuf], pFile, dwSize, sizeof(wavHdr))) 
  {
    fclose(pFile);
    return false;
  }
  fclose(pFile);
  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DS_CreateSoundBuffer(DWORD dwBuf, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo)
{
  PCMWAVEFORMAT pcmwf;
  DSBUFFERDESC dsbdesc;
  
  // Set up wave format structure.
  memset( &pcmwf, 0, sizeof(PCMWAVEFORMAT) );
  pcmwf.wf.wFormatTag         = WAVE_FORMAT_PCM;      
  pcmwf.wf.nChannels          = bStereo ? 2 : 1;
  pcmwf.wf.nSamplesPerSec     = dwFreq;
  pcmwf.wf.nBlockAlign        = (WORD)dwBlkAlign;
  pcmwf.wf.nAvgBytesPerSec    = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
  pcmwf.wBitsPerSample        = (WORD)dwBitsPerSample;

  // Set up DSBUFFERDESC structure.
  memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));  // Zero it out. 
  dsbdesc.dwSize              = sizeof(DSBUFFERDESC);
  dsbdesc.dwFlags             = DSBCAPS_CTRLDEFAULT;  // Need default controls (pan, volume, frequency).
  dsbdesc.dwBufferBytes       = dwBufSize; 
  dsbdesc.lpwfxFormat         = (LPWAVEFORMATEX)&pcmwf;

  g_DX_Result = g_lpDS->CreateSoundBuffer(&dsbdesc, &m_lpDS_Sounds[dwBuf], NULL);
  DS_CHECK_ERROR("Error - DS - CreateSoundBuffer");

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DS_ReadData(LPDIRECTSOUNDBUFFER lpDSB, FILE* pFile, DWORD dwSize, DWORD dwPos) 
{
  // Seek to correct position in file (if necessary)
  if (dwPos != 0xffffffff) 
  {
    if (fseek(pFile, dwPos, SEEK_SET) != 0) 
    {
      return false;
    }
  }

  // Lock data in buffer for writing
  LPVOID pData1;
  DWORD  dwData1Size;
  LPVOID pData2;
  DWORD  dwData2Size;
  HRESULT rval;

  rval = lpDSB->Lock(0, dwSize, &pData1, &dwData1Size, &pData2, &dwData2Size, DSBLOCK_FROMWRITECURSOR);
  if (rval != DS_OK)
  {
    return false;
  }

  // Read in first chunk of data
  if (dwData1Size > 0) 
  {
    if (fread(pData1, dwData1Size, 1, pFile) != 1) 
    {               
      return false;
    }
  }

  // read in second chunk if necessary
  if (dwData2Size > 0) 
  {
    if (fread(pData2, dwData2Size, 1, pFile) != 1) 
    {
      return false;
    }
  }

  // Unlock data in buffer
  rval = lpDSB->Unlock(pData1, dwData1Size, pData2, dwData2Size);
  if (rval != DS_OK)
  {
    return false;
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DS_StopAllSounds()
{
  // Make sure we have a valid sound buffer
  for (int i = 0; i < DS_SOUNDS_NUM; i++)
  {
    if(m_lpDS_Sounds[i])
    {
      DWORD dwStatus;
      g_DX_Result = m_lpDS_Sounds[i]->GetStatus(&dwStatus);
      DS_CHECK_ERROR("Error - DS - GetStatus");

      if ((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
      {  
        g_DX_Result = m_lpDS_Sounds[i]->Stop();     // Play the sound
        DS_CHECK_ERROR("Error - DS - Stop");
      }
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool CGame::DS_PlaySound(int nSound, DWORD dwFlags)
{
  if(!g_Options_bSoundFX)
    return true;
  if(!m_bSoundPresent)
    return true;

  if(m_lpDS_Sounds[nSound])  // Make sure we have a valid sound buffer
  {
    DWORD dwStatus;
    g_DX_Result = m_lpDS_Sounds[nSound]->GetStatus(&dwStatus);
    DS_CHECK_ERROR("Error - DS - GetStatus");

    if((dwStatus & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
    {
      g_DX_Result = m_lpDS_Sounds[nSound]->Play(0, 0, dwFlags);    // Play the sound
      DS_CHECK_ERROR("Error - DS - Play");
    }
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////

void CGame::DS_Finish()
{
  if(g_lpDS != NULL)
  {
    for(int i = 0; i < DS_SOUNDS_NUM; i ++)
    {
      if(m_lpDS_Sounds[i])
      {       
        m_lpDS_Sounds[i]->Release();
        m_lpDS_Sounds[i] = NULL;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
