// PageWnd.cpp : implementation file
//

#include "stdafx.h"
#include "StackUpApp.h"
#include "StackUpWnd.h"
#include "GlobalsExtern.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStackUpWnd

CStackUpWnd::CStackUpWnd()
{
  m_pApp = (CStackUpApp*)AfxGetApp();
}

CStackUpWnd::~CStackUpWnd()
{
}

BEGIN_MESSAGE_MAP(CStackUpWnd, CWnd)
	//{{AFX_MSG_MAP(CStackUpWnd)
	ON_WM_ACTIVATEAPP()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStackUpWnd message handlers

BOOL CStackUpWnd::Create() 
{
  CRect rect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

  LPCSTR strClass = AfxRegisterWndClass(CS_DBLCLKS,
                                     ::LoadCursor(NULL,IDC_ARROW),
                                     (HBRUSH)GetStockObject(WHITE_BRUSH),
                                     AfxGetApp()->LoadIcon(IDR_MAINFRAME));

  if(CreateEx(WS_EX_APPWINDOW, strClass, STACKUP, WS_SYSMENU | WS_POPUP | WS_VISIBLE,
     0, 0, rect.right, rect.bottom, NULL, NULL, 0) == FALSE)
    return FALSE;

  UpdateWindow();
  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

void CStackUpWnd::PostNcDestroy() 
{
  CWnd::PostNcDestroy();
  m_pApp->ShutDown(); 
  delete this;
}

/////////////////////////////////////////////////////////////////////////////

void CStackUpWnd::OnActivateApp(BOOL bActive, HTASK hTask) 
{
  CWnd::OnActivateApp(bActive, hTask);
  m_pApp->SetActive(bActive);
}

/////////////////////////////////////////////////////////////////////////////

BOOL CStackUpWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
  ::SetCursor(NULL);
  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

/*
void CStackUpWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  switch(nChar)
  {
   case VK_ESCAPE:
     PostMessage(WM_CLOSE,0,0);
     break;
  }

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
*/

/////////////////////////////////////////////////////////////////////////////
