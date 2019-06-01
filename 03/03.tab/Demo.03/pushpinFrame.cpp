/*
Module : PUSHPINFRAME.CPP
Purpose: Implementation of a push pin property dialog similar 
         to the ones seen in VC 4/5
Created: PJN / 24-11-1997
History: PJN / 16-04-1998 window now only closes if the window which is
                          going active is owned by the same parent as 
                          the pushpin frame

Copyright (c) 1997 by PJ Naughter.  
All rights reserved.
*/


/////////////////////////////////  Includes  //////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "PushPinFrame.h"



//////////////////////////////////  Macros  ///////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



////////////////////////////////// Implementation /////////////////////////////
IMPLEMENT_DYNCREATE(CPushPinFrame, CFrameWnd)


CPushPinFrame::CPushPinFrame()
{
	m_pModelessPropSheet = NULL;
  m_pRuntimeModelessPropSheet = NULL;
}


CPushPinFrame::~CPushPinFrame()
{
}


BEGIN_MESSAGE_MAP(CPushPinFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CPushPinFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
	ON_WM_ACTIVATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CPushPinFrame::SetAttachedPropertySheet(CRuntimeClass* pRuntimeModelessPropSheet) 
{ 
  m_pRuntimeModelessPropSheet = pRuntimeModelessPropSheet; 
}


int CPushPinFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

  //create the property page as a child of this frame window

  ASSERT(m_pRuntimeModelessPropSheet);  //forgot to attach the property sheet !!
  m_pModelessPropSheet = (CPropertySheet*) m_pRuntimeModelessPropSheet->CreateObject();
  ASSERT(m_pModelessPropSheet);         //Your class is probably not DECLARE_DYNCREATE
  ASSERT(m_pModelessPropSheet->IsKindOf(RUNTIME_CLASS(CPropertySheet)));
	if (!m_pModelessPropSheet->Create(this, WS_CHILD | WS_VISIBLE, 0))
	{
		delete m_pModelessPropSheet;
		m_pModelessPropSheet = NULL;
		return -1;
	}

	// Resize the mini frame so that it fits around the child property
	// sheet with space for the push pin in top left hand corner
	CRect rectClient, rectWindow;
	m_pModelessPropSheet->GetWindowRect(rectClient);
  rectClient.right += 20;
	rectWindow = rectClient;

	// CFrameWnd::CalcWindowRect adds the extra width and height
	// needed from the mini frame.
	CalcWindowRect(rectWindow);

  //Resize this window to suit the property sheet
	SetWindowPos(NULL, rectWindow.left, rectWindow.top,	rectWindow.Width(), rectWindow.Height(),
		           SWP_NOZORDER | SWP_NOACTIVATE);

  //Move the property sheet into place
  rectWindow.left += 20;
	m_pModelessPropSheet->SetWindowPos(NULL, rectWindow.left, rectWindow.top,
		rectWindow.Width(), rectWindow.Height(),
		SWP_NOZORDER | SWP_NOACTIVATE);

  //Create the push pin in the top left hand corner of the frame window
  m_PushPin.Create("", BS_OWNERDRAW | WS_CHILD | WS_VISIBLE, CRect(2, 8, 0, 0), this, 100);
  m_PushPin.SetPinned(TRUE);
  m_PushPin.SetUseEdgeBitmap(TRUE);

	return 0;
}


void CPushPinFrame::OnClose() 
{
	// Instead of closing the modeless property sheet, just hide it.
	ShowWindow(SW_HIDE);
}


void CPushPinFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
}


void CPushPinFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	// Forward any WM_ACTIVATEs to the property sheet...
	// Like the dialog manager itself, it needs them to save/restore the focus.
	ASSERT_VALID(m_pModelessPropSheet);

	// Use GetCurrentMessage to get unmodified message data.
	const MSG* pMsg = GetCurrentMessage();
	ASSERT(pMsg->message == WM_ACTIVATE);
	m_pModelessPropSheet->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);

  //if we lose activation and we are not pinned and
  //the other window is an owned by the same toplevel window
  //then close this window
  if (nState == WA_INACTIVE && !m_PushPin.IsPinned() && OwnedBySameParent(pWndOther))
    PostMessage(WM_CLOSE);
}


BOOL CPushPinFrame::OwnedBySameParent(CWnd* pWnd)
{
  if (!pWnd)
    return FALSE;

  return (GetTopLevelOwner()->GetSafeHwnd() == pWnd->GetTopLevelOwner()->GetSafeHwnd());
}


void CPushPinFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//Paint the client area of the frame window with 
  //the 3d color to make it look like a modal
  //propery sheet
  CRect r;
  GetClientRect(&r);
  dc.FillSolidRect(r, GetSysColor(COLOR_3DFACE));
}


BOOL CPushPinFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
  //modify the styles to make the frame window 
  //like a modal property sheet

	// WS_4THICKFRAME and MFS_THICKFRAME imply WS_THICKFRAME
	if (cs.style & (MFS_4THICKFRAME | MFS_THICKFRAME))
		cs.style |= WS_THICKFRAME;

	// WS_CAPTION implies WS_EX_TOOLWINDOW
	if (cs.style & WS_CAPTION)
		cs.dwExStyle |= WS_EX_TOOLWINDOW;

  BOOL bSuccess;

	VERIFY(bSuccess = CFrameWnd::PreCreateWindow(cs));
	cs.dwExStyle &= ~(WS_EX_CLIENTEDGE);
	
	return bSuccess;
}

