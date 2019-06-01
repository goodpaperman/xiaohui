// MainClient.cpp : implementation file
//

#include "stdafx.h"
#include "SwitchTB.h"
#include "MainClient.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainClient

CMainClient::CMainClient()
{
	m_nChilds = 0;
}

CMainClient::~CMainClient()
{
}


BEGIN_MESSAGE_MAP(CMainClient, CWnd)
	//{{AFX_MSG_MAP(CMainClient)
	ON_WM_PARENTNOTIFY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainClient message handlers

LRESULT CMainClient::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
/***************************************************************\
| This function calls the main frame window to switch toolbars	|
| when a new MDI menu is set.									|
\***************************************************************/
	LRESULT lRet = CWnd::DefWindowProc(message, wParam, lParam);

	if (message == WM_MDISETMENU) {
		CMainFrame *pFrame;

		pFrame = (CMainFrame *) AfxGetMainWnd ();
		if (::IsWindow (pFrame))
			pFrame->SwitchToolbar ();
	}
	return (lRet);
}

void CMainClient::OnParentNotify(UINT message, LPARAM lParam) 
{
/***************************************************************\
| This function calls the main frame window to switch toolbars	|
| when a all the MDI child windows are closed.					|
\***************************************************************/
	CWnd::OnParentNotify(message, lParam);
	CMainFrame *pFrame;
	CWnd *pWnd;

	pWnd = AfxGetMainWnd ();
	if (pWnd->IsKindOf (RUNTIME_CLASS (CMainFrame)))
		pFrame = (CMainFrame *) AfxGetMainWnd ();
	else
		return; // don't crash the application, just leave
	switch (LOWORD (message)) {
		case WM_CREATE:
			m_nChilds++;
			break;
		case WM_DESTROY:
			m_nChilds--;
			if (m_nChilds == 0)
				pFrame->SwitchToolbar ();
			break;
		default:
			break;
	}
}
