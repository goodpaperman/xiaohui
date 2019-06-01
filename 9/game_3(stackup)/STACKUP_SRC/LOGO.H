// Logo.h: interface for the CLogo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGO_H__30F3CA45_E37C_11D1_BF4D_9A2F22A7644A__INCLUDED_)
#define AFX_LOGO_H__30F3CA45_E37C_11D1_BF4D_9A2F22A7644A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ddraw.h>
#include "Options.h"

#define ZOOM_FRAME_NUM    20

#define LOGO_XPOS         (640 - 280) / 2
#define LOGO_YPOS         20
#define LOGO_WIDTH        280
#define LOGO_HEIGHT       128

#define OPTIONS_XPOS      40
#define OPTIONS_YPOS      200
#define OPTIONS_WIDTH     300
#define OPTIONS_HEIGHT    100

#define MENU_XBEG         360
#define MENU_YBEG         200
#define MENU_ITEM_XBEG    MENU_XBEG + 160
#define MENU_ITEM_HEIGHT  20

#define KEY_REPEAT_WAIT   16
#define KEY_REPEAT_DELAY  5

/////////////////////////////////////////////////////////////////////////////

class CLogo  
{
public:
	CLogo();
	virtual ~CLogo();

  CString m_sBitmapLogo;
  CString m_sBitmapOptions;
  bool m_bMenuChanged;

  bool m_bKeyUpFlag;
  bool m_bKeyDownFlag;
  bool m_bKeyLeftFlag;
  bool m_bKeyRightFlag;
  int m_nKeyRepeatCount;

  COptions m_Options;

  void Activate();
  int UpdateFrame();
  void OtherLimits(int);
  bool UpdateItem(bool, short, short);

  void PrintText(bool);

// DirectDraw ///////////////////////////////////////////////////////////////

  bool  DD_Init();
  bool  DD_Finish();
  bool  DD_RestoreAll();
  bool  DD_DrawScreen();

  LPDIRECTDRAWSURFACE     m_lpDDS_Logo;           // Logo
  LPDIRECTDRAWPALETTE     m_lpDDP_Logo;           // palette
  LPDIRECTDRAWSURFACE     m_lpDDS_Options;

// DirectInput //////////////////////////////////////////////////////////////

  int  DI_Frame();

};

#endif // !defined(AFX_LOGO_H__30F3CA45_E37C_11D1_BF4D_9A2F22A7644A__INCLUDED_)
