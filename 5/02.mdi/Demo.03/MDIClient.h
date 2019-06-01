
/******************************************************************

$Archive: /MfcExt/Source/MDIClient.h $
$Workfile: MDIClient.h $
$Author: Bogdan Ledwig $
$Date: 99-01-12 12:48 $
$Revision: 1 $

*******************************************************************/

/*
 Written by Bogdan Ledwig (bogdanle@opole.mtl.pl).
 Copyright © 1999 Bogdan Ledwig. All Rights Reserved.

 This code may be used in compiled form in any way you wish. This
 file may be redistributed unmodified by any means PROVIDING it is
 not sold for profit without the authors written consent, and
 providing that this notice and the authors name is included. If the
 source code is used in any commercial application then an email letting
 me know that you are using it would be nice. However, this code may
 not be sold as a part of any commercial library in compiled or source
 form. In any other cases the code is free to whoever wants it anyway.

 This software is provided "as is" without express or implied warranty. 
 Use it at you own risk! The author accepts no liability for any damages 
 to your computer or data this product may cause.
*/

#if !defined (__MDIClient_h)
#define __MDIClient_h

/////////////////////////////////////////////////////////////////////////////
// CMDIClient window

class CMDIClient : public CWnd
{
public:
   enum DisplayModesEnum {
      dispTile,
      dispCenter,
      dispStretch,
      dispCustom
   };
   
// Construction
public:
   CMDIClient();

// Attributes
public:
   // Set background color
   void SetBkColor( COLORREF clrValue );
   COLORREF GetBkColor() const;

   // Load background bitmap from given file
   BOOL SetBitmap( LPCTSTR lpszFileName, UINT uFlags = LR_LOADMAP3DCOLORS );

   // Load background bitmap from resource. You can map some colors using 
   // COLORMAP struct (see LoadMappedBitmap() for details how to use it)
   BOOL SetBitmap( UINT nBitmapID, COLORMAP* pClrMap = NULL, int nCount = 0 );

   // Set desired display mode (tile, center, stretch or custom)
   void SetDisplayMode( DisplayModesEnum eDisplayMode );
   DisplayModesEnum GetDisplayMode() const;

   // Specify coordinates of image's top-left corner. Used when 
   // dispCustom is selected
   void SetOrigin( int x, int y, BOOL bRedraw = TRUE );
   void SetOrigin( const CPoint& point, BOOL bRedraw = TRUE );
   const CPoint& GetOrigin() const;

   // Return the current image size.
   const CSize& GetImageSize() const;

   // Return the filename of the bitmap
   const CString& GetFileName() const;

   // If set to TRUE, the current state is automatically 
   // saved on WM_DESTROY and restored on PreSubclassWindow()
   void SetAutoSaveRestore( BOOL bNewValue );
   BOOL GetAutoSaveRestore() const;

// Operations
public:
   // Restore original (system-wide) settings
   void Reset();

   // Load/Store current settings in registry
   void SaveState();
   void RestoreState();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CMDIClient)
   virtual void PreSubclassWindow();
   //}}AFX_VIRTUAL

// Implementation
public:
   virtual ~CMDIClient();

   // Generated message map functions
protected:
   //{{AFX_MSG(CMDIClient)
   afx_msg void OnPaint();
   afx_msg void OnDestroy();
   afx_msg BOOL OnEraseBkgnd( CDC* pDC );
   afx_msg void OnSize( UINT nType, int cx, int cy );   
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   
   CBitmap m_bitmap;             // The background bitmap
   CBrush m_brush;               // Brush used for background painting
   COLORREF m_clrBackground;     // The background color
   BOOL m_bAutoSaveRestore;      // Automatically save/restore the state
   CString m_strFileName;        // The filename if bitmap was loaded from a file
   CPoint m_ptOrigin;            // Coordinates of top-left corner of image. Used when dispCustom is selected
   CSize m_sizeImage;            // Cache the image size;
   DisplayModesEnum m_eDisplayMode;   
};

/////////////////////////////////////////////////////////////////////////////
// CMDIClient inlines

inline
COLORREF CMDIClient::GetBkColor() const
{
   return m_clrBackground;
}

inline
CMDIClient::DisplayModesEnum CMDIClient::GetDisplayMode() const
{
   return m_eDisplayMode;
}

inline
const CString& CMDIClient::GetFileName() const
{
   return m_strFileName;
}

inline
void CMDIClient::SetOrigin( int x, int y, BOOL bRedraw )
{
   m_ptOrigin.x = x;
   m_ptOrigin.y = y;
   if ( bRedraw == TRUE && IsWindow( m_hWnd ) )
      Invalidate();   
}

inline
void CMDIClient::SetOrigin( const CPoint& point, BOOL bRedraw )
{
   m_ptOrigin = point;
   if ( bRedraw == TRUE && IsWindow( m_hWnd ) )
      Invalidate();      
}

inline
const CPoint& CMDIClient::GetOrigin() const
{
   return m_ptOrigin;
}

inline
const CSize& CMDIClient::GetImageSize() const
{   
   return m_sizeImage;
}

inline
void CMDIClient::SetAutoSaveRestore( BOOL bNewValue )
{
   m_bAutoSaveRestore = bNewValue;
}

inline
BOOL CMDIClient::GetAutoSaveRestore() const
{
   return m_bAutoSaveRestore;   
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __MDIClient_h
