#include "Headers.h"
#include "resource.h"
#include "KoulesApp.h"
#include "KoulesWin.h"


BEGIN_MESSAGE_MAP(KoulesApp, DirectDrawApp)
	//{{AFX_MSG_MAP(KoulesApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

KoulesApp theapp;

BOOL KoulesApp::InitInstance()
{
#ifdef _DEBUG
//	afxTraceEnabled=FALSE;
#endif
	KoulesWin* win=new KoulesWin;
	if (!win->Create( "Koules", IDI_ICON ))
		return FALSE;

	m_pMainWnd=win;
	return DirectDrawApp::InitInstance();
}



