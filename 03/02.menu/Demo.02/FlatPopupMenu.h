// A flat popup menu for controls
// Copyright (c) 1999 Andy Brown <andy@mirage.dabsol.co.uk>
// You may do whatever you like with this file, I just don't care.


#ifndef _6911179a_6053_11d3_a4b7_00001c0022de
#define _6911179a_6053_11d3_a4b7_00001c0022de


// flat popup menu class

class CFlatPopupMenu
{
public:
// data members

  enum
  {
    itemSeparator=0x1,                            // not valid with anything else
    itemNotSelectable=0x2,                        // cannot select this item
    itemBold=0x4,                                 // display in bold face text
    itemGrayed=0x8                                // display grayed out
  };

  enum menuColor
  {
    colorBorder,                                  // menu border and separator line
    colorBackground,                              // background fill
    colorText,                                    // normal text
    colorGrayedText,                              // grayed out text
    colorHighlightText,                           // selected text
    colorHighlight,                               // selected background
    colorIconTransparent,                         // color that shows through bitmaps
    colorLightShadow,                             // for edges facing the light source
    colorDarkShadow,                              // for edges facing away from the light source

    numColors
  };

public:
// menu item class

  class CItem
  {
  public:
    int             m_Top;                        // top
    int             m_Height;                     // height
    DWORD           m_dwFlags;                    // various flags
    std::string     m_strName;                    // text name
    UINT            m_ItemID;                     // item ID
    int             m_IconIndex;                  // index into the bitmap

    CFlatPopupMenu *m_pPopup;                     // popup menu

  protected:
    void Assign(const CItem& src);                // copy src to this

  public:
    CItem();                                      // default constructor
    CItem(const CItem& src);                      // copy constructor

    CItem& operator=(const CItem& src);           // assignment operator
  };

  static bool        m_bClassRegistered;          // once-per-app window class registration flag

  HINSTANCE          m_hInstance;                 // bitmaps are loaded from here
  UINT               m_BitmapID;                  // bitmap resource ID
  std::vector<CItem> m_Items;                     // items in this menu
  std::string        m_strFont;                   // font name for items
  int                m_FontSize;                  // font point-size for items
  int                m_PopupDelay;                // popup menu delay
  COLORREF           m_Colors[numColors];         // the color settings

// internal state settings

  enum
  {
    stateInactive,
    stateShow,
    stateTrack
  } m_State;

  int                m_Width;
  int                m_FontHeight;
  int                m_BoldFontHeight;
  HWND               m_hWnd;
  HWND               m_hWndCommand;
  int                m_SelectedItem;
  UINT               m_SelectedID;
  bool               m_bWaitRightButton;
  bool               m_bWaitLeftButton;
  bool               m_bModal;
  bool               m_bChild;
  CFlatPopupMenu    *m_pPrevious;

// GDI objects

  HFONT              m_hFont;
  HFONT              m_hBoldFont;
  HPEN               m_hBorderPen;
  HPEN               m_hLightShadowPen;
  HPEN               m_hDarkShadowPen;
  HPEN               m_hBackPen;
  HPEN               m_hSelectedTextPen;
  HPEN               m_hTextPen;
  HBRUSH             m_hBackBrush;
  HBRUSH             m_hSelectedBrush;
  HBITMAP            m_hBitmap;

private:
  CFlatPopupMenu& operator=(const CFlatPopupMenu& src) { return *this; }    // not allowed

protected:
  bool RegisterClass(void);
  void Cleanup(void);
  void CreateObjects(void);
  bool CheckOutsideMenu(HWND hWnd,const RECT& rect,short x,short y);
  void DrawItem(HWND hWnd,HDC hDC,const int index,const CItem& item);
  void DrawTransparentBitmap(HDC hdc,const int xSrcOffset,const int xStart,const int yStart);
  void DrawSeparator(HDC hDC,int top);
  int GetItem(short x,short y,const RECT& rect);
  CItem *GetItem(const UINT itemid,const bool bByPosition);
  void DestroyAll(void);
  void ButtonDown(HWND hWnd,short x,short y,const bool bLeft);
  void SetReturn(const UINT id);

public:
  CFlatPopupMenu();
  ~CFlatPopupMenu();

  void SetColor(const menuColor id,const COLORREF cr);
  void SetFont(LPCTSTR pszFont);
  void SetFontSize(const int size);
  void SetPopupDelay(const int delay);

  bool Create(HINSTANCE hInstance,const UINT bitmap_id=(UINT)-1);
  bool AppendItem(const DWORD dwFlags,LPCTSTR pszName,const UINT itemid,const int icon=-1);
  bool AppendPopup(const DWORD dwFlags,LPCTSTR pszName,CFlatPopupMenu& popup,const int icon=-1);
  bool SetMenuItemText(const UINT itemid,LPCTSTR pszName,const bool bByPosition=false);
  bool SetMenuItemFlags(const UINT itemid,const DWORD dwFlags,const bool bByPosition=false);
  bool SetMenuItemIcon(const UINT itemid,const int icon,const bool bByPosition=false);
  bool GetString(const UINT itemid,LPTSTR pszText,const UINT cchText,const bool bByPosition=false);
  UINT Track(int x,int y,HWND hWnd,const bool bModal,const bool bPopup=false);

  void OnPaint(HWND hWnd,HDC hDC);
  void OnEraseBkgnd(HWND hWnd,HDC hDC);
  void OnLButtonDown(HWND hWnd,short x,short y);
  void OnRButtonDown(HWND hWnd,short x,short y);
  void OnLButtonUp(HWND hWnd,short x,short y);
  void OnRButtonUp(HWND hWnd,short x,short y);
  void OnDestroy(HWND hWnd);
  void OnMouseMove(HWND hWnd,short x,short y);
  void OnTimer(HWND hWnd,unsigned short id);
  void OnChar(HWND hWnd,TCHAR c);
};


// set the popup menu delay time

inline void CFlatPopupMenu::SetPopupDelay(const int delay)
{
  m_PopupDelay=delay;
}


// Set a color

inline void CFlatPopupMenu::SetColor(const menuColor id,const COLORREF cr)
{
  m_Colors[id]=cr;
}


// Set the font

inline void CFlatPopupMenu::SetFont(LPCTSTR pszFont)
{
  m_strFont=pszFont;
}


// Set the font size

inline void CFlatPopupMenu::SetFontSize(const int size)
{
  m_FontSize=size;
}


// WM_PAINT

inline void CFlatPopupMenu::OnPaint(HWND hWnd,HDC hDC)
{
  std::vector<CItem>::const_iterator it;
  int pos;

// draw each item

  pos=0;
  for(it=m_Items.begin();it!=m_Items.end();it++)
    DrawItem(hWnd,hDC,pos++,*it);
}


// WM_LBUTTONDOWN

inline void CFlatPopupMenu::OnLButtonDown(HWND hWnd,short x,short y)
{
  ButtonDown(hWnd,x,y,true);
}


// WM_RBUTTONDOWN

inline void CFlatPopupMenu::OnRButtonDown(HWND hWnd,short x,short y)
{
  ButtonDown(hWnd,x,y,false);
}


// Destroy all menus

inline void CFlatPopupMenu::DestroyAll(void)
{
  CFlatPopupMenu *pMenu;

// find the root

  for(pMenu=this;pMenu->m_pPrevious;pMenu=pMenu->m_pPrevious);
  DestroyWindow(pMenu->m_hWnd);
}


// CItem constructor

inline CFlatPopupMenu::CItem::CItem()
{
}


// CItem copy constructor

inline CFlatPopupMenu::CItem::CItem(const CItem& src)
{
  Assign(src);
}


// CItem = operator

inline CFlatPopupMenu::CItem& CFlatPopupMenu::CItem::operator=(const CItem& src)
{
  Assign(src);
  return *this;
}


#endif
