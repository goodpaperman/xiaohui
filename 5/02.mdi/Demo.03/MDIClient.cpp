
/******************************************************************

$Archive: /MfcExt/Source/MDIClient.cpp $
$Workfile: MDIClient.cpp $
$Author: Bogdan Ledwig $
$Date: 99-01-12 12:48 $
$Revision: 1 $

*******************************************************************/

#include "StdAfx.h"

#include "MDIClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////// 
// Registry keys used for saving/restoring the state
static TCHAR szSection[]      = _T( "MDIClient" );
static TCHAR szDisplayMode[]  = _T( "DisplayMode" );
static TCHAR szBkColor[]      = _T( "BkColor" );
static TCHAR szFileName[]     = _T( "FileName" );
static TCHAR szOriginX[]      = _T( "OriginX" );
static TCHAR szOriginY[]      = _T( "OriginY" );

/////////////////////////////////////////////////////////////////////////////
// CMDIClient

CMDIClient::CMDIClient()
{   
   Reset();
   m_bAutoSaveRestore = TRUE;
}

CMDIClient::~CMDIClient()
{
}

void CMDIClient::PreSubclassWindow()
{
   CWnd::PreSubclassWindow();
   if ( m_bAutoSaveRestore == TRUE )
      RestoreState();
}

void CMDIClient::Reset()
{
   m_ptOrigin.x = m_ptOrigin.y = 0;
   m_sizeImage.cx = m_sizeImage.cy = 0;
   m_eDisplayMode = dispTile;
   m_strFileName.Empty();      
   SetBkColor( ::GetSysColor( COLOR_APPWORKSPACE ) );
   m_bitmap.DeleteObject();
   if ( IsWindow( m_hWnd ) )
      Invalidate();
}

BOOL CMDIClient::SetBitmap( LPCTSTR lpszFileName, UINT uFlags )
{
   HANDLE handle = ::LoadImage( AfxGetInstanceHandle(),
                      lpszFileName,
                      IMAGE_BITMAP,
                      0, 0,
                      uFlags | LR_LOADFROMFILE );
   
   if ( !handle )    // There were some problems during loading the image
      return FALSE;
   
   m_bitmap.DeleteObject();
   m_bitmap.Attach( (HBITMAP)handle );
   if ( IsWindow( m_hWnd ) )
      Invalidate();
   m_strFileName = lpszFileName;

   BITMAP bi;
   m_bitmap.GetBitmap( &bi );
   m_sizeImage.cx = bi.bmWidth;
   m_sizeImage.cy = bi.bmHeight;

   return TRUE;
}

BOOL CMDIClient::SetBitmap( UINT nBitmapID, COLORMAP* pClrMap, int nCount )
{
   m_bitmap.DeleteObject();
   if ( pClrMap == NULL )  // Load normal
   {
      if ( m_bitmap.LoadBitmap( nBitmapID ) == FALSE )
         return FALSE;
   }
   else                    // Load mapped 
   {      
      if ( m_bitmap.LoadMappedBitmap( nBitmapID, 0, pClrMap, nCount ) == FALSE )
         return FALSE;
   }

   BITMAP bi;
   m_bitmap.GetBitmap( &bi );
   m_sizeImage.cx = bi.bmWidth;
   m_sizeImage.cy = bi.bmHeight;

   if ( IsWindow( m_hWnd ) )
      Invalidate();
   return TRUE;
}

void CMDIClient::SetBkColor( COLORREF clrValue )
{
   m_clrBackground = clrValue;
   m_brush.DeleteObject();
   m_brush.CreateSolidBrush( m_clrBackground );
   if ( IsWindow( m_hWnd ) )
      Invalidate();
}

void CMDIClient::SetDisplayMode( CMDIClient::DisplayModesEnum eDisplayMode )
{
   m_eDisplayMode = eDisplayMode;      
   if ( IsWindow( m_hWnd ) )
      Invalidate();
}

void CMDIClient::SaveState()
{
   AfxGetApp()->WriteProfileInt( szSection, szDisplayMode, GetDisplayMode() );
   AfxGetApp()->WriteProfileInt( szSection, szBkColor, GetBkColor() );
   AfxGetApp()->WriteProfileString( szSection, szFileName, GetFileName() );
   AfxGetApp()->WriteProfileInt( szSection, szOriginX, GetOrigin().x );
   AfxGetApp()->WriteProfileInt( szSection, szOriginY, GetOrigin().y );   
}

void CMDIClient::RestoreState()
{   
   m_eDisplayMode = (DisplayModesEnum)AfxGetApp()->GetProfileInt( szSection, szDisplayMode, dispTile );      
   m_ptOrigin.x = AfxGetApp()->GetProfileInt( szSection, szOriginX, 0 );
   m_ptOrigin.y = AfxGetApp()->GetProfileInt( szSection, szOriginY, 0 );
   SetBkColor( AfxGetApp()->GetProfileInt( szSection, szBkColor, GetSysColor( COLOR_APPWORKSPACE ) ) );
   CString str = AfxGetApp()->GetProfileString( szSection, szFileName, _T( "" ) );
   if ( str.GetLength() )
      SetBitmap( str );
}

BEGIN_MESSAGE_MAP(CMDIClient, CWnd)
   //{{AFX_MSG_MAP(CMDIClient)
   ON_WM_DESTROY()
   ON_WM_PAINT()
   ON_WM_SIZE()
   ON_WM_ERASEBKGND()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMDIClient message handlers

void CMDIClient::OnPaint() 
{
   CPaintDC dc( this );
   CRect rc;
   GetClientRect( rc );
    
   if ( !(HBITMAP)m_bitmap )   // If no bitmap is selected
      dc.FillRect( rc, &m_brush );
 
   if ( (HBITMAP)m_bitmap )
   {
      CDC* pDC;
      CDC memDC;
      CBitmap bmp; 
            
      BOOL bDrawOnMemDC = ( GetDisplayMode() != dispTile ) ? TRUE : FALSE;
      if ( bDrawOnMemDC )
      {
         if ( GetDisplayMode() != dispStretch )
            bmp.CreateCompatibleBitmap( &dc, rc.right, rc.bottom );
         else
            bmp.CreateCompatibleBitmap( &dc, m_sizeImage.cx, m_sizeImage.cy );
         memDC.CreateCompatibleDC( &dc );
         memDC.SelectObject( &bmp );
         pDC = &memDC;
      }
      else
         pDC = &dc;      
      
      switch ( GetDisplayMode() )
      {
         case dispCustom:
            {
               pDC->FillRect( rc, &m_brush );               
               pDC->DrawState( m_ptOrigin, m_sizeImage, &m_bitmap, DST_BITMAP | DSS_NORMAL );
            }
            break;

         case dispCenter:
            {
               pDC->FillRect( rc, &m_brush );
               CPoint point( ( rc.Width() - m_sizeImage.cx ) / 2, 
                             ( rc.Height() - m_sizeImage.cy ) / 2 );
               pDC->DrawState( point, m_sizeImage, &m_bitmap, DST_BITMAP | DSS_NORMAL );
            }
            break;

         case dispTile:
            {
               CPoint point;
               for ( point.y = 0; point.y < rc.Height(); point.y += m_sizeImage.cy )
                  for ( point.x = 0; point.x < rc.Width(); point.x += m_sizeImage.cx )
                     pDC->DrawState( point, m_sizeImage, &m_bitmap, DST_BITMAP | DSS_NORMAL );
            }
            break;

         case dispStretch:
            {
               memDC.DrawState( CPoint(0,0), m_sizeImage, &m_bitmap, DST_BITMAP | DSS_NORMAL );
               dc.SetStretchBltMode( COLORONCOLOR );
               dc.StretchBlt( 0, 0, rc.right, rc.bottom, &memDC, 
                              0, 0, m_sizeImage.cx, m_sizeImage.cy, SRCCOPY );
            }
            return;
      }
                            
      if ( bDrawOnMemDC == TRUE )
         dc.BitBlt( 0, 0, rc.right, rc.bottom, pDC, 0, 0, SRCCOPY );
   }
}

BOOL CMDIClient::OnEraseBkgnd( CDC* /*pDC*/ ) 
{   
   return TRUE;    // Return TRUE so background is not erased   
}

void CMDIClient::OnSize( UINT nType, int cx, int cy )
{
   if ( nType != SIZE_MINIMIZED && GetDisplayMode() != dispTile )   // Force repainting if center mode is selected
      Invalidate();
   CWnd::OnSize( nType, cx, cy );
}

void CMDIClient::OnDestroy()
{   
   if ( m_bAutoSaveRestore == TRUE )
      SaveState();
   CWnd::OnDestroy();
}
