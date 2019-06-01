// Game.h : header file
//

#if !defined(AFX_STACKUP_H__5BCBB708_B46C_11D1_82C0_444553540000__INCLUDED_)
#define AFX_STACKUP_H__5BCBB708_B46C_11D1_82C0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _DEBUG
#define USE_DSOUND
#endif

#include <ddraw.h>
#include "mmsystem.h"
#include <dsound.h>
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CStackUpDlg dialog

#define   GS_NOTHING            0
#define   GS_PLAYING            1
#define   GS_SIGNALIZING        2
#define   GS_FALLING            4

#define   SIGNALIZING_DELAY     5                          // one blink
#define   SIGNALIZING_TIME      SIGNALIZING_DELAY * 10     // its number

#define   PF_MIN_XSIZE          3
#define   PF_MAX_XSIZE          30 + 2
#define   PF_MIN_YSIZE          3
#define   PF_MAX_YSIZE          30 + 2
#define   PF_MIN_OBJNUM         1
#define   PF_MAX_OBJNUM         5

#define   OBJ_XSPEED            2
#define   OBJ_YSPEED            6

#define   OBJ_XSIZE             32      // means the size in source bitmap!
#define   OBJ_YSIZE             29
#define   OBJ_MIN_XSIZE         10
#define   OBJ_MIN_YSIZE         10
#define   OBJ_ANIM_FRAMES_NUM   15
#define   OBJ_ANIM_DELAY        5

#define   FONT_HEIGHT 16

/////////////////////////////////////////////////////////////////////////////

class CGame
{
public:
	CGame();
  bool Init(bool);
  bool UpdateFrame();
  bool Finish();
  void Activate();

protected:
  CString   m_sBitmapObjects;
  CString   m_sBitmapBackground;

  short m_nPF_XSize;
  short m_nPF_YSize;

  bool  m_bPause;
  bool  m_bQuit;

  struct OBJECT
  {
    short   nState;           // false -> inactive (no moving)
    short   nX;               // x-position
    short   nY;               // y-position
    short   nX_Last;          // x-position (one frame back)
    short   nY_Last;          // y-position (one frame back)
    short   nX_Speed;         // x-speed
    short   nY_Speed;         // y-speed
    short   nAnimFrame;       // current animation frame
    short   nZ;               // current object 
    short   nZ_Next;          // next object
  };

  struct SHIFTING_BLOCK
  {
    bool  bState;           // 0...finished
    short nY_Counter;       // counter in pixels
    short nY_DownRate;      // offset for shift
    short nX;               // which column
    short nY_Beg;           // beginning
    short nY_Size;          // block y-size
  };

typedef CArray<SHIFTING_BLOCK*, SHIFTING_BLOCK*&> ARRAY_SHIFTING_BLOCKS;
typedef CArray<ARRAY_SHIFTING_BLOCKS*, ARRAY_SHIFTING_BLOCKS*&> ARRAY_SHIFTING;

  struct PLAYER
  {
    short     nWhich;
    int       nScore;
    short     nScoreXBeg;
    short     nNextXBeg;
    short     nPF_XBeginning;
    short     nPF_YBeginning;
    short     nGameState;
    char      Playfield[PF_MAX_XSIZE][PF_MAX_YSIZE];         // main playfield
    short     Playfield_Frames[PF_MAX_XSIZE][PF_MAX_YSIZE];  // for animation frames
    short     nSignalizingTimeCounter;
    bool      bSignalizingState;
    bool      bSignalizingFlag;
    ARRAY_SHIFTING aShifting;          // table for shifting
    OBJECT    Object1;
    OBJECT    Object2;
    OBJECT    Object3;
    bool      bControlRotateFlag;
    bool      bControlDownFlag;
    bool      bControlLeftFlag;
    bool      bControlRightFlag;
    bool      bRotateState;
    bool      bYSpd;
    bool      bNewObj;
  };

  void InitPlayer(short, short, short, short);
  void PlayPlayer();
  void FinishPlayer();

  PLAYER* m_pPlayer;  
  PLAYER m_PlayerOne;
  PLAYER m_PlayerTwo;

  void  MakeNewPlayfield();
  void  DrawPlayfield();
  bool  Playing();
  bool  Testing(bool);
  void  Signalizing();
  void  Falling();
  void  FallingInit();
  void  Signalize(bool);
  void  NewObjects(bool);
  void  ObjectMoving(OBJECT*);
  void  UpdateObjects(bool);
  bool  AddScore(int);
  void  ClearFallingTab();

// DirectDraw

  void  FadeIn();
  void  FadeOut();
  void  FadeColorToGray();
  void  FadeGrayToColor();

  bool  DD_Init();
  void  DD_Finish();
  bool  DD_RestoreAll();
  bool  DD_SetObject(short, short, short, short);
  bool  DD_DrawObject(bool, short, short, short, short);
  bool  DD_ClearScreen();
  bool  DD_CopyBackground();
  bool  DD_CopyPrimaryToSecondary();
  bool  DD_CopySecondaryToPrimary();
  bool  DD_ShiftBlock(short, short, short, short, short);
  void  DrawNewObjects();

  LPDIRECTDRAWSURFACE     m_lpDDS_Objects;        // Objects
  LPDIRECTDRAWSURFACE     m_lpDDS_Background;     // Game Background
  LPDIRECTDRAWPALETTE     m_lpDDP_Background;     // palette
  PALETTEENTRY            m_PalEntry_Background[256];

  bool DI_Frame();

// DirectSound

#define DS_SOUNDS_NUM         5
#define DS_SOUND_ROTATE       0
#define DS_SOUND_SPEEDUP      1
#define DS_SOUND_PLACE        2
#define DS_SOUND_SIGNALIZING  3
#define DS_SOUND_FALLING      4

  char*                 m_cWavRotate;
  char*                 m_cWavSpeedup;
  char*                 m_cWavPlace;
  char*                 m_cWavSignalizing;
  char*                 m_cWavFalling;
  LPDIRECTSOUNDBUFFER   m_lpDS_Sounds[DS_SOUNDS_NUM];         // Sound buffers
  HRESULT               m_DS_Result;
  bool                  m_bSoundPresent;

  bool   DS_Init();
  void   DS_Finish();
  bool   DS_StopAllSounds();
  bool   DS_CreateBufferFromWaveFile(char* FileName, DWORD dwBuf);
  bool   DS_PlaySound(int nSound, DWORD dwFlags);
  bool   DS_CreateSoundBuffer(DWORD dwBuf, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo);
  bool   DS_ReadData(LPDIRECTSOUNDBUFFER lpDSB, FILE* pFile, DWORD dwSize, DWORD dwPos);

};

#endif
