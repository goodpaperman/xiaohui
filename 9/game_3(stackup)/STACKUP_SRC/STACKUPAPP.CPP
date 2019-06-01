// StackUp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Splash.h"
#include "StackUpApp.h"
#include "StackUpWnd.h"
#include "StackUp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStackUpApp

BEGIN_MESSAGE_MAP(CStackUpApp, CWinApp)
	//{{AFX_MSG_MAP(CStackUpApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStackUpApp construction

CStackUpApp::CStackUpApp()
{
  m_bIsActive = TRUE;
  m_bShutDown = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStackUpApp object

CStackUpApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CStackUpApp initialization

BOOL CStackUpApp::InitInstance()
{
  CMySplashWnd* pSplashWnd = new CMySplashWnd(IDB_STACKUP, 0);   // splash window
  pSplashWnd->Create();

  CStackUpWnd* pWnd = new CStackUpWnd();    // main window (filled with black brush)
  if(pWnd->Create() == FALSE)
    return FALSE;

  m_pStackUp = new CStackUp();
  m_bShutDown = !(m_pStackUp->Init());

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

int CStackUpApp::ExitInstance() 
{
  m_pStackUp->Finish();
  delete m_pStackUp;

  return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////

int CStackUpApp::Run() 
{
  MSG msg;

  while(1)
  {
    if(m_bShutDown == TRUE)
    {
      ExitInstance();
      return 0;
    }

    if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
    {
      if(GetMessage(&msg, NULL, 0, 0) == FALSE)
      {
        ExitInstance();
        return msg.wParam;    // WM_QUIT
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      if(m_bIsActive == TRUE)
      {
        if(m_bRedrawScreen)
        {
          m_bRedrawScreen = FALSE;
          m_pStackUp->Activate();
        }
        if(m_pStackUp->Frame())
          AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
      }
      else
        WaitMessage();
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
