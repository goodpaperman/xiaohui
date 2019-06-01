// BCGMainClientAreaWnd.cpp : implementation file
//

#include "stdafx.h"
#include "BCGMainClientAreaWnd.h"
#include "BCGMDIFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGMainClientAreaWnd

CBCGMainClientAreaWnd::CBCGMainClientAreaWnd()
{
}

CBCGMainClientAreaWnd::~CBCGMainClientAreaWnd()
{
}


BEGIN_MESSAGE_MAP(CBCGMainClientAreaWnd, CWnd)
	//{{AFX_MSG_MAP(CBCGMainClientAreaWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MDISETMENU,OnSetMenu)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBCGMainClientAreaWnd message handlers

afx_msg LRESULT CBCGMainClientAreaWnd::OnSetMenu (WPARAM wp, LPARAM lp)
{
	CBCGMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CBCGMDIFrameWnd, GetParentFrame ());
	if (pMainFrame != NULL)
	{
		pMainFrame->OnSetMenu ((HMENU) wp);
	}

	return DefWindowProc (WM_MDISETMENU, NULL, lp);
}
