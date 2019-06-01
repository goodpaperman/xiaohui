#include <ddraw.h>
#include <dinput.h>
#include "mmsystem.h"
#include <dsound.h>

#define   WRITEBITMAPS

#define   STACKUP   "StackUp"
#define   SCREEN_XSIZE          640
#define   SCREEN_YSIZE          480

  short g_Options_nPlayerNum;
  short g_Options_nPF_XSize;
  short g_Options_nPF_YSize;
  bool  g_Options_bStartFilled;
  bool  g_Options_nPF_ObjType;
  short g_Options_nPF_ObjNum;
  short g_Options_nPF_ObjXSize;
  short g_Options_nPF_ObjYSize;
  bool  g_Options_bRotateType;
  bool  g_Options_bSoundFX;

// DirectDraw ///////////////////////////////////////////////////////////////

#define DD_BLT(blitting) { while(1) { g_DX_Result = blitting; if(g_DX_Result == DD_OK) break; if(g_DX_Result == DDERR_SURFACELOST) { if(!DD_RestoreAll()) return false; } if(g_DX_Result != DDERR_WASSTILLDRAWING) return false; } if(g_DX_Result != DD_OK) return false; }
#define DD_CHECK_ERROR(ErrorMessage) { if(g_DX_Result != DD_OK) { AfxMessageBox(ErrorMessage); return false; } }
#define WAITFORVB do g_DX_Result = g_lpDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, NULL); while(g_DX_Result != DD_OK);

  HRESULT                 g_DX_Result;
  LPDIRECTDRAW            g_lpDD;                 // DirectDraw object
  LPDIRECTDRAWSURFACE     g_lpDDS_Primary;        // DirectDraw primary surface
  LPDIRECTDRAWSURFACE     g_lpDDS_Secondary;      // BackBuffer

  bool  g_DD_Init();
  bool  g_DD_RestoreAll();
  void  g_DD_Finish();
  void  g_DD_FlipScreens();
  void g_DD_PalleteToBack(LPDIRECTDRAWPALETTE);

// DirectInput //////////////////////////////////////////////////////////////

#define DIRECTINPUTVERSION  0x0300                // version 3.0
#define DINPUT_BUFFERSIZE       16                // Number of buffer elements
#define DI_CHECK_ERROR(ErrorMessage) { if(g_DX_Result != DI_OK) { AfxMessageBox(ErrorMessage); return false; } }

  HRESULT                 g_DI_Result;
  LPDIRECTINPUT           g_lpDI;
  LPDIRECTINPUTDEVICE     g_lpDI_Keyboard;
  DIDEVICEOBJECTDATA      g_DI_rgdod[DINPUT_BUFFERSIZE];   // Receives buffered data
  DWORD                   g_DI_InOut;                      // the number of elements

  bool  g_DI_Init();
  void  g_DI_Finish();
  void  g_DI_GetKeyboardData();

// DirectSound //////////////////////////////////////////////////////////////

#define DS_CHECK_ERROR(ErrorMessage) { if(g_DX_Result != DS_OK) { AfxMessageBox(ErrorMessage); return false; } }
#define DS_CB_ERROR(ErrorMessage) { AfxMessageBox(ErrorMessage); return false; }

  bool                  g_bSoundPresent;
  LPDIRECTSOUND         g_lpDS;

  bool g_DS_Init();
  void g_DS_Finish();

/////////////////////////////////////////////////////////////////////////////

#ifdef WRITEBITMAPS
  HANDLE DDBToDIB(CBitmap&, DWORD, CPalette*);
  BOOL WriteDIB(LPTSTR, HANDLE);
  BOOL WriteWindowToDIB(LPTSTR, CWnd*);
#endif

/////////////////////////////////////////////////////////////////////////////
