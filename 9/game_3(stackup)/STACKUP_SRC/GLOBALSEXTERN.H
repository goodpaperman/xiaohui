#include <ddraw.h>
#include <dinput.h>
#include "mmsystem.h"
#include <dsound.h>

#define   WRITEBITMAPS

#define   STACKUP   "StackUp"
#define   SCREEN_XSIZE          640
#define   SCREEN_YSIZE          480

  extern  short g_Options_nPlayerNum;
  extern  short g_Options_nPF_XSize;
  extern  short g_Options_nPF_YSize;
  extern  bool  g_Options_bStartFilled;
  extern  bool  g_Options_nPF_ObjType;
  extern  short g_Options_nPF_ObjNum;
  extern  short g_Options_nPF_ObjXSize;
  extern  short g_Options_nPF_ObjYSize;
  extern  bool  g_Options_bRotateType;
  extern  bool  g_Options_bSoundFX;

// DirectDraw ///////////////////////////////////////////////////////////////

#define DD_BLT(blitting) { while(1) { g_DX_Result = blitting; if(g_DX_Result == DD_OK) break; if(g_DX_Result == DDERR_SURFACELOST) { if(!DD_RestoreAll()) return false; } if(g_DX_Result != DDERR_WASSTILLDRAWING) return false; } if(g_DX_Result != DD_OK) return false; }
#define DD_CHECK_ERROR(ErrorMessage) { if(g_DX_Result != DD_OK) { AfxMessageBox(ErrorMessage); return false; } }
#define WAITFORVB do g_DX_Result = g_lpDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, NULL); while(g_DX_Result != DD_OK);

  extern HRESULT                 g_DX_Result;
  extern LPDIRECTDRAW            g_lpDD;                 // DirectDraw object
  extern LPDIRECTDRAWSURFACE     g_lpDDS_Primary;        // DirectDraw primary surface
  extern LPDIRECTDRAWSURFACE     g_lpDDS_Secondary;      // BackBuffer

  extern bool g_DD_Init();
  extern bool g_DD_RestoreAll();
  extern void g_DD_Finish();
  extern void g_DD_FlipScreens();
  extern void g_DD_PalleteToBack(LPDIRECTDRAWPALETTE);

// DirectInput //////////////////////////////////////////////////////////////

#define DIRECTINPUTVERSION  0x0300                // version 3.0
#define DINPUT_BUFFERSIZE       16                // Number of buffer elements
#define DI_CHECK_ERROR(ErrorMessage) { if(g_DX_Result != DI_OK) { AfxMessageBox(ErrorMessage); return false; } }

  extern HRESULT                 g_DI_Result;
  extern LPDIRECTINPUT           g_lpDI;
  extern LPDIRECTINPUTDEVICE     g_lpDI_Keyboard;
  extern DIDEVICEOBJECTDATA      g_DI_rgdod[DINPUT_BUFFERSIZE];   // Receives buffered data
  extern DWORD                   g_DI_InOut;                      // the number of elements

  extern bool  g_DI_Init();
  extern void  g_DI_Finish();
  extern void  g_DI_GetKeyboardData();

// DirectSound //////////////////////////////////////////////////////////////

#define DS_CHECK_ERROR(ErrorMessage) { if(g_DX_Result != DS_OK) { AfxMessageBox(ErrorMessage); return false; } }
#define DS_CB_ERROR(ErrorMessage) { AfxMessageBox(ErrorMessage); return false; }

  extern  bool                  g_bSoundPresent;
  extern  LPDIRECTSOUND         g_lpDS;

  extern  bool g_DS_Init();
  extern  void g_DS_Finish();

/////////////////////////////////////////////////////////////////////////////

#ifdef WRITEBITMAPS
  extern  HANDLE DDBToDIB(CBitmap&, DWORD, CPalette*);
  extern  BOOL WriteDIB(LPTSTR, HANDLE);
  extern  BOOL WriteWindowToDIB(LPTSTR, CWnd*);
#endif

////////////////////////////////////////////////////////////////////////////
