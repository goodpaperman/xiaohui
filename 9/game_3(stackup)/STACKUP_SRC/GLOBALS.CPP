#include "stdafx.h"
#include "globals.h"
#include <objbase.h>
#include "ddutil.cpp"

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//  DIRECT DRAW                                                            //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool g_DD_Init()
{
  g_DX_Result = DirectDrawCreate(NULL, &g_lpDD, NULL);   // create the main DirectDraw object
  DD_CHECK_ERROR("Error - DD - Create");

  g_DX_Result = g_lpDD->SetCooperativeLevel(*AfxGetMainWnd(), DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
  DD_CHECK_ERROR("Error - DD - SetCooperativeLevel");

#ifdef _DEBUG
  g_DX_Result = g_lpDD->SetDisplayMode(1024, 768, 8);
#else
  g_DX_Result = g_lpDD->SetDisplayMode(SCREEN_XSIZE, SCREEN_YSIZE, 8);
#endif
  DD_CHECK_ERROR("Error - DD - SetDisplayMode");

  DDSURFACEDESC ddsd;     
  ddsd.dwSize = sizeof(ddsd);                     // Create the primary surface with 1 back buffer
  ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
  ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
  ddsd.dwBackBufferCount = 1;
  g_DX_Result = g_lpDD->CreateSurface(&ddsd, &g_lpDDS_Primary, NULL);
  DD_CHECK_ERROR("Error - DD - CreateSurface");

  DDSCAPS ddscaps;  
  ddscaps.dwCaps = DDSCAPS_BACKBUFFER;              // Get a pointer to the back buffer
  g_DX_Result = g_lpDDS_Primary->GetAttachedSurface(&ddscaps, &g_lpDDS_Secondary);
  DD_CHECK_ERROR("Error - DD - GetAttachedSurface");

  return true;
}

/////////////////////////////////////////////////////////////////////////////

bool g_DD_RestoreAll()
{
  return g_lpDDS_Primary->Restore() == DD_OK &&
         g_lpDDS_Secondary->Restore() == DD_OK;
}

/////////////////////////////////////////////////////////////////////////////

void g_DD_Finish()
{
  if(g_lpDD != NULL)
  {
    if(g_lpDDS_Primary != NULL)
    {
      g_lpDDS_Primary->Release();
      g_lpDDS_Primary = NULL;
    }
    g_lpDD->RestoreDisplayMode();
    g_lpDD->Release();
    g_lpDD = NULL;
  }
}

/////////////////////////////////////////////////////////////////////////////

void g_DD_FlipScreens()
{
  while(1)
  {
    g_DX_Result = g_lpDDS_Primary->Flip(NULL, 0);
    if(g_DX_Result == DD_OK)
      break;
    if(g_DX_Result == DDERR_SURFACELOST)
    {
      g_DX_Result = g_lpDDS_Primary->Restore();
      if(g_DX_Result != DD_OK)
        break;
    }
    if(g_DX_Result != DDERR_WASSTILLDRAWING)
      break;
  }
}

/////////////////////////////////////////////////////////////////////////////

void g_DD_PalleteToBack(LPDIRECTDRAWPALETTE lpDDP)
{
  PALETTEENTRY  PalEntry_Background[256];
  if(lpDDP->GetEntries(0, 0, 256, PalEntry_Background) != DD_OK)
    AfxMessageBox("Error - Get Palette Entries");

  PALETTEENTRY  PalEntry_Work[256];
  for(int i = 0; i < 256; i++)
  {
    PalEntry_Work[i].peRed = PalEntry_Background[0].peRed;
    PalEntry_Work[i].peGreen = PalEntry_Background[0].peGreen;
    PalEntry_Work[i].peBlue = PalEntry_Background[0].peBlue;
    PalEntry_Work[i].peFlags = 0;
  }
  if(lpDDP->SetEntries(0, 0, 256, PalEntry_Work) != DD_OK)
    AfxMessageBox("Error - Set Palette Entries");
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//  DIRECT INPUT                                                           //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool g_DI_Init()
{
  g_DX_Result = DirectInputCreate(AfxGetInstanceHandle(), DIRECTINPUTVERSION, &g_lpDI, NULL);
  DI_CHECK_ERROR("Error - DirectInputCreate");

  g_DX_Result = g_lpDI->CreateDevice(GUID_SysKeyboard, &g_lpDI_Keyboard, NULL);
  DI_CHECK_ERROR("Error - DI - CreateDevice");

  g_DX_Result = g_lpDI_Keyboard->SetDataFormat(&c_dfDIKeyboard);
  DI_CHECK_ERROR("Error - DI - SetDataFormat");

  g_DX_Result = g_lpDI_Keyboard->SetCooperativeLevel(*AfxGetMainWnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
  DI_CHECK_ERROR("Error - DI - SetCooperativeLevel");

  DIPROPDWORD dipdw =
  {
    {
      sizeof(DIPROPDWORD),        // diph.dwSize
      sizeof(DIPROPHEADER),       // diph.dwHeaderSize
      0,                          // diph.dwObj
      DIPH_DEVICE,                // diph.dwHow
    },
    DINPUT_BUFFERSIZE,            // dwData
  };

  g_DX_Result = g_lpDI_Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
  DI_CHECK_ERROR("Error - DI - Set buffer size");

  return true;
}

/////////////////////////////////////////////////////////////////////////////

void g_DI_Finish()
{
  if(g_lpDI_Keyboard)
  {
    g_lpDI_Keyboard->Unacquire();
    g_lpDI_Keyboard->Release();
    g_lpDI_Keyboard = NULL;
  }

  if(g_lpDI)
  {
    g_lpDI->Release();
    g_lpDI = NULL;
  }
}

/////////////////////////////////////////////////////////////////////////////

void g_DI_GetKeyboardData()
{
again:
  g_DI_InOut = DINPUT_BUFFERSIZE;
  g_DX_Result = g_lpDI_Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), g_DI_rgdod, &g_DI_InOut, 0);

  if(g_DX_Result != DI_OK)
  {
    if(g_DX_Result == DIERR_INPUTLOST)
    {
      g_DX_Result = g_lpDI_Keyboard->Acquire();
      if(SUCCEEDED(g_DX_Result))
      {
        goto again;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
//  DIRECT SOUND                                                           //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

bool g_DS_Init()
{
  g_DX_Result = DirectSoundCreate(NULL, &g_lpDS, NULL);
  DS_CHECK_ERROR("Error - DS - Create\nAudio cannot be used");

  g_DX_Result = g_lpDS->SetCooperativeLevel(*AfxGetMainWnd(), DSSCL_NORMAL);
  DS_CHECK_ERROR("Error - DS - SetCooperativeLevel");

  return true;
}

/////////////////////////////////////////////////////////////////////////////

void g_DS_Finish()
{
  if(g_lpDS != NULL)
  {
    g_lpDS->Release();
    g_lpDS = NULL;
  }
}

/////////////////////////////////////////////////////////////////////////////

#ifdef WRITEBITMAPS

/////////////////////////////////////////////////////////////////////////////
// DDBToDIB             - Creates a DIB from a DDB
// bitmap               - Device dependent bitmap
// dwCompression        - Type of compression - see BITMAPINFOHEADER
// pPal                 - Logical palette

HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal ) 
{
        BITMAP                  bm;
        BITMAPINFOHEADER        bi;
        LPBITMAPINFOHEADER      lpbi;
        DWORD                   dwLen;
        HANDLE                  hDIB;
        HANDLE                  handle;
        HDC                     hDC;
        HPALETTE                hPal;


        ASSERT( bitmap.GetSafeHandle() );

        // The function has no arg for bitfields
        if( dwCompression == BI_BITFIELDS )
                return NULL;

        // If a palette has not been supplied use defaul palette
        hPal = (HPALETTE) pPal->GetSafeHandle();
        if (hPal==NULL)
                hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

        // Get bitmap information
        bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

        // Initialize the bitmapinfoheader
        bi.biSize               = sizeof(BITMAPINFOHEADER);
        bi.biWidth              = bm.bmWidth;
        bi.biHeight             = bm.bmHeight;
        bi.biPlanes             = 1;
        bi.biBitCount           = bm.bmPlanes * bm.bmBitsPixel;
        bi.biCompression        = dwCompression;
        bi.biSizeImage          = 0;
        bi.biXPelsPerMeter      = 0;
        bi.biYPelsPerMeter      = 0;
        bi.biClrUsed            = 0;
        bi.biClrImportant       = 0;

        // Compute the size of the  infoheader and the color table
        int nColors = (1 << bi.biBitCount);
        if( nColors > 256 ) 
                nColors = 0;
        dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

        // We need a device context to get the DIB from
        hDC = GetDC(NULL);
        hPal = SelectPalette(hDC,hPal,FALSE);
        RealizePalette(hDC);

        // Allocate enough memory to hold bitmapinfoheader and color table
        hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

        if (!hDIB){
                SelectPalette(hDC,hPal,FALSE);
                ReleaseDC(NULL,hDC);
                return NULL;
        }

        lpbi = (LPBITMAPINFOHEADER)hDIB;

        *lpbi = bi;

        // Call GetDIBits with a NULL lpBits param, so the device driver 
        // will calculate the biSizeImage field 
        GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
                        (LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

        bi = *lpbi;

        // If the driver did not fill in the biSizeImage field, then compute it
        // Each scan line of the image is aligned on a DWORD (32bit) boundary
        if (bi.biSizeImage == 0){
                bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
                                                * bi.biHeight;

                // If a compression scheme is used the result may infact be larger
                // Increase the size to account for this.
                if (dwCompression != BI_RGB)
                        bi.biSizeImage = (bi.biSizeImage * 3) / 2;
        }

        // Realloc the buffer so that it can hold all the bits
        dwLen += bi.biSizeImage;
        if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
                hDIB = handle;
        else{
                GlobalFree(hDIB);

                // Reselect the original palette
                SelectPalette(hDC,hPal,FALSE);
                ReleaseDC(NULL,hDC);
                return NULL;
        }

        // Get the bitmap bits
        lpbi = (LPBITMAPINFOHEADER)hDIB;

        // FINALLY get the DIB
        BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
                                0L,                             // Start scan line
                                (DWORD)bi.biHeight,             // # of scan lines
                                (LPBYTE)lpbi                    // address for bitmap bits
                                + (bi.biSize + nColors * sizeof(RGBQUAD)),
                                (LPBITMAPINFO)lpbi,             // address of bitmapinfo
                                (DWORD)DIB_RGB_COLORS);         // Use RGB for color table

        if( !bGotBits )
        {
                GlobalFree(hDIB);
                
                SelectPalette(hDC,hPal,FALSE);
                ReleaseDC(NULL,hDC);
                return NULL;
        }

        SelectPalette(hDC,hPal,FALSE);
        ReleaseDC(NULL,hDC);
        return hDIB;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDIB             - Writes a DIB to file
// Returns              - TRUE on success
// szFile               - Name of file to write to
// hDIB                 - Handle of the DIB

BOOL WriteDIB( LPTSTR szFile, HANDLE hDIB)
{
        BITMAPFILEHEADER        hdr;
        LPBITMAPINFOHEADER      lpbi;

        if (!hDIB)
                return FALSE;

        CFile file;
        if( !file.Open( szFile, CFile::modeWrite|CFile::modeCreate) )
                return FALSE;

        lpbi = (LPBITMAPINFOHEADER)hDIB;

        int nColors = 1 << lpbi->biBitCount;

        // Fill in the fields of the file header 
        hdr.bfType              = ((WORD) ('M' << 8) | 'B');    // is always "BM"
        hdr.bfSize              = GlobalSize (hDIB) + sizeof( hdr );
        hdr.bfReserved1         = 0;
        hdr.bfReserved2         = 0;
        hdr.bfOffBits           = (DWORD) (sizeof( hdr ) + lpbi->biSize +
                                                nColors * sizeof(RGBQUAD));

        // Write the file header 
        file.Write( &hdr, sizeof(hdr) );

        // Write the DIB header and the bits 
        file.Write( lpbi, GlobalSize(hDIB) );

        return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

BOOL WriteWindowToDIB( LPTSTR szFile, CWnd *pWnd )
{
        CBitmap         bitmap;
        CWindowDC       dc(pWnd);
        CDC             memDC;
        CRect           rect;

        memDC.CreateCompatibleDC(&dc); 

        pWnd->GetWindowRect(rect);

        bitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height() );
        
        CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
        memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc, 0, 0, SRCCOPY); 

        // Create logical palette if device support a palette
        CPalette pal;
        if( dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE )
        {
                UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);
                LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
                pLP->palVersion = 0x300;

                pLP->palNumEntries = 
                        GetSystemPaletteEntries( dc, 0, 255, pLP->palPalEntry );

                // Create the palette
                pal.CreatePalette( pLP );

                delete[] pLP;
        }

        memDC.SelectObject(pOldBitmap);

        // Convert the bitmap to a DIB
        HANDLE hDIB = DDBToDIB( bitmap, BI_RGB, &pal );

        if( hDIB == NULL )
                return FALSE;

        // Write it to file
        WriteDIB( szFile, hDIB );

        // Free the memory allocated by DDBToDIB for the DIB
        GlobalFree( hDIB );
        return TRUE;
}

#endif

/////////////////////////////////////////////////////////////////////////////
