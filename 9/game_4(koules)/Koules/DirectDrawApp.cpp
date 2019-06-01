#include "Headers.h"
#include "DirectDrawApp.h"
#include "DirectDrawWin.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(DirectDrawApp, CWinApp)
	//{{AFX_MSG_MAP(DirectDrawApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

DirectDrawApp::DirectDrawApp()
{
	ddwin=0;
	m_gamerun=TRUE;
	m_pMainWnd=NULL;
}

BOOL DirectDrawApp::InitInstance()
{
	ASSERT(m_pMainWnd);
	m_pMainWnd->ShowWindow( SW_SHOWNORMAL );
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BOOL DirectDrawApp::OnIdle(LONG) 
{
	if(!m_gamerun)
		return TRUE;
	if (ddwin->PreDrawScene())
		ddwin->DrawScene();
	return TRUE;
}

int DirectDrawApp::ExitInstance() 
{
	if(ddwin)
	{
		delete ddwin;
		ddwin=NULL;
	}
	return CWinApp::ExitInstance();
}


void DirectDrawApp::Exit()
{
	m_gamerun=FALSE;
	GetDDWin()->ClearSurface(GetDDWin()->primsurf,0,NULL);
	GetDDWin()->ClearSurface(GetDDWin()->backsurf,0,NULL);
	GetDDWin()->Restore();
	GetDDWin()->ShowWindow(SW_HIDE);
	CAboutDlg dlg;
	m_pMainWnd=&dlg;
	dlg.DoModal();
	PostQuitMessage(0);
}
