/********************************************* 
 REVISION LOG ENTRY 
 Revision By: Noam Rathaus
 Revised on 26/5/1999 14:57:00
 Comments: RgnButton.cpp : implementation file 
**********************************************/ 

#include "stdafx.h"
#include "CRgnedButton.h"
#include "RgnButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRgnButton

CRgnButton::CRgnButton()
{
}

CRgnButton::~CRgnButton()
{
}


BEGIN_MESSAGE_MAP(CRgnButton, CButton)
	//{{AFX_MSG_MAP(CRgnButton)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRgnButton message handlers

/*==========================================================================================*/
// 
// Function: CRgnButton::OnPaint
// 
// Description: 
//Override for the default OnPaint() event 
// 
// Parameters: 
//    None
// 
// Return: 
//    None
/*==========================================================================================*/
void CRgnButton::OnPaint() 
{
  CButton::OnPaint();
  
  CRect RectParent, RectInner;
// RectParent - Used for storing the Parent Button Rectangle (In their Windows prespective)
// RectInner - Used for storing the Parent's Child Button Rectangle (In their Windows prespective)

  CRect RgnRectParent, RgnRectMini;
// RgnRectParent - Used to store the Button's Client Region (In their Client prespective)
// RgnRectMini - Used to store the Button's Child Client Region (In their Client prespective)

  CRgn m_hRgnParent, m_hRgnMini[256];
// m_hRgnParent - Used to store the new CRgn of the Button.
// m_hRgnMini - Used to store the sub Region of the Button (Caused by the childs)

  int i = 0;
// i - An incremental counter for storing up to 256 Overlapping Buttons.
  
  GetClientRect(&RgnRectParent);
  RgnRectParent.InflateRect(6,6);
// This is needed in order for the Button's Rectangle to include its shadows too.

  m_hRgnParent.CreateRectRgn(RgnRectParent.left, RgnRectParent.top, 
    RgnRectParent.right, RgnRectParent.bottom);
  
  GetWindowRect(&RectParent);
  
  CWnd *pWnd = GetParent()->GetWindow(GW_CHILD);
  
  while (pWnd != NULL)
  {
    pWnd->GetWindowRect(&RectInner);
    if ( (RectParent.PtInRect( RectInner.CenterPoint() )) && (pWnd != this) && (pWnd->IsWindowVisible()))
// If the button's center is inside the Button, than it must be an overlapping button,
// A better could be used, (You can use also UnionRect for this test, but I prefer PtInRect())
    {
      pWnd->GetClientRect(&RgnRectMini);
//      MiniRgnRect.OffsetRect(3,3);
// If the buttons (the parent buttons, not the overlapping ones) include a 
// "larger frame" for example their style was set to Modal Frame you need 
// to offset the childs location acordingly... is there a more generalized way? 
// maybe... let me know if it is possible.
      
      pWnd->ClientToScreen(&RgnRectMini);
      ScreenToClient(&RgnRectMini);
      
      m_hRgnMini[i].CreateRectRgn(RgnRectMini.left, RgnRectMini.top, 
        RgnRectMini.right, RgnRectMini.bottom);
      m_hRgnParent.CombineRgn(&m_hRgnParent, &m_hRgnMini[i++], RGN_DIFF);
// Combine the RGN of the parent button with its overlapping "childern".
    }
    pWnd = pWnd->GetNextWindow(GW_HWNDNEXT);
  }
  
  CRgn compareRgn;
  compareRgn.CreateRectRgn(0,0,0,0);
// Create a dummy CRgn so using GetWindowRgn() won't fail.

  if (IsWindowVisible())
// Is this button Visible? if not, why bother with changing its Region?
  {
    GetWindowRgn(compareRgn);
    if (compareRgn.m_hObject != NULL)
    {
      if (!compareRgn.EqualRgn(&m_hRgnParent))
// If the new Region does not equal the current Region, set the Current Region to
// the new one.
        SetWindowRgn(m_hRgnParent, TRUE);
    }
    else
// If there is no Rgn present, set the Current Region to the new one.
      SetWindowRgn(m_hRgnParent, TRUE);
  }
}

void CRgnButton::PreSubclassWindow() 
{
  ModifyStyle(0,WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
// Prevent this button from drawing on all the button area. (Both are not need in all
// cases, but in a very specail case so both were added.
  
	CButton::PreSubclassWindow();
}
