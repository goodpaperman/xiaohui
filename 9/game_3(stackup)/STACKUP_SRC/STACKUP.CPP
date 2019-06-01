// StackUp.cpp: implementation of the CStackUp class.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StackUp.h"
#include "Game.h"
#include "Logo.h"
#include "GlobalsExtern.h"

#pragma warning( disable : 4800 )

/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////////////

CStackUp::CStackUp()
{
  m_pLogo = new CLogo;
  m_pGame = new CGame;
}

CStackUp::~CStackUp()
{
  delete m_pLogo;
  delete m_pGame;
}

/////////////////////////////////////////////////////////////////////////////

bool CStackUp::Init()
{
  m_pThisApp = AfxGetApp();

  CString sIniFilePath;     // for INI File
  CString sModFileName;
  GetModuleFileName(NULL, sModFileName.GetBuffer(MAX_PATH), MAX_PATH);
  sModFileName.ReleaseBuffer();

  sModFileName.MakeReverse();
  sIniFilePath = sModFileName.Right(sModFileName.GetLength() - sModFileName.Find('\\'));
  sIniFilePath.MakeReverse();
  sIniFilePath += STACKUP;
  sIniFilePath += ".ini";
  sModFileName.MakeReverse();

  free((void*)m_pThisApp->m_pszProfileName);
  m_pThisApp->m_pszProfileName = _tcsdup(sIniFilePath);

  g_Options_nPlayerNum = m_pThisApp->GetProfileInt(STACKUP, "Number Of Players", 1);
  g_Options_nPF_XSize = m_pThisApp->GetProfileInt(STACKUP, "Playfield Width", 6);
  g_Options_nPF_YSize = m_pThisApp->GetProfileInt(STACKUP, "Playfield Height", 10);
  g_Options_bStartFilled = m_pThisApp->GetProfileInt(STACKUP, "Filled Playfield", 0);
  g_Options_nPF_ObjNum = m_pThisApp->GetProfileInt(STACKUP, "Number Of Objects", 5);
  g_Options_nPF_ObjType = m_pThisApp->GetProfileInt(STACKUP, "Type Of Objects", 0);
  g_Options_nPF_ObjXSize = m_pThisApp->GetProfileInt(STACKUP, "Objects Width", OBJ_XSIZE);
  g_Options_nPF_ObjYSize = m_pThisApp->GetProfileInt(STACKUP, "Objects Height", OBJ_YSIZE);
  g_Options_bRotateType = m_pThisApp->GetProfileInt(STACKUP, "Type Of Rotation", 0);
  g_Options_bSoundFX = m_pThisApp->GetProfileInt(STACKUP, "Sound FX", 1);

  #ifdef USE_DSOUND
    g_bSoundPresent = g_DS_Init();
    if(!g_bSoundPresent)
      g_DS_Finish();
  #endif

  if(!g_DI_Init())
  {
    g_DI_Finish();
    return false;
  }

  if(!g_DD_Init())
  {
    g_DD_Finish();
    return false;
  }

  if(g_lpDI_Keyboard)
    g_lpDI_Keyboard->Acquire();

  m_State = FIRST_INIT_LOGO;

  return true;
}

/////////////////////////////////////////////////////////////////////////////

void CStackUp::Finish()
{
  g_DD_Finish();
  g_DI_Finish();
  #ifdef USE_DSOUND
    g_DS_Finish();
  #endif
  m_pThisApp->WriteProfileInt(STACKUP, "Number Of Players", g_Options_nPlayerNum);
  m_pThisApp->WriteProfileInt(STACKUP, "Playfield Width", g_Options_nPF_XSize);
  m_pThisApp->WriteProfileInt(STACKUP, "Playfield Height", g_Options_nPF_YSize);
  m_pThisApp->WriteProfileInt(STACKUP, "Filled Playfield", g_Options_bStartFilled);
  m_pThisApp->WriteProfileInt(STACKUP, "Number Of Objects", g_Options_nPF_ObjNum);
  m_pThisApp->WriteProfileInt(STACKUP, "Type Of Objects", g_Options_nPF_ObjType);
  m_pThisApp->WriteProfileInt(STACKUP, "Objects Width", g_Options_nPF_ObjXSize);
  m_pThisApp->WriteProfileInt(STACKUP, "Objects Height", g_Options_nPF_ObjYSize);
  m_pThisApp->WriteProfileInt(STACKUP, "Type Of Rotation", g_Options_bRotateType);
  m_pThisApp->WriteProfileInt(STACKUP, "Sound FX", g_Options_bSoundFX);
}

/////////////////////////////////////////////////////////////////////////////

bool CStackUp::Frame()
{
  switch(m_State)
  {
    case FIRST_INIT_LOGO:
      if(!m_pLogo->DD_Init())
        return true;
      m_State = RUNNING_LOGO;
      break;  

    case INIT_LOGO:
      m_pGame->Finish();
      m_pLogo->DD_Init();
      m_State = RUNNING_LOGO;
      break;  

    case RUNNING_LOGO:
      m_State = m_pLogo->UpdateFrame();
      break;  

    case INIT_GAME:
      m_pLogo->DD_Finish();
      m_pGame->Init(true);
      m_State = RUNNING_GAME;
      break;  

    case RUNNING_GAME:
      if(m_pGame->UpdateFrame() == true)
        m_State = INIT_LOGO;
      break;  
  }

  if(m_State == QUIT)
  {
    m_pLogo->DD_Finish();
    return true;
  }
  else
    return false;
}

/////////////////////////////////////////////////////////////////////////////

void CStackUp::Activate()
{
  switch(m_State)
  {
    case RUNNING_LOGO:
      m_pLogo->Activate();
      break;
    case RUNNING_GAME:
      m_pGame->Activate();
      break;  
  }

  if(g_lpDI_Keyboard)
    g_lpDI_Keyboard->Acquire();
}

/////////////////////////////////////////////////////////////////////////////
