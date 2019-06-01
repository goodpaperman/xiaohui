// MainToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "BCGIEDemo.h"
#include "MainToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainToolBar

CMainToolBar::CMainToolBar()
{
}

CMainToolBar::~CMainToolBar()
{
}


BEGIN_MESSAGE_MAP(CMainToolBar, CBCGToolBar)
	//{{AFX_MSG_MAP(CMainToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainToolBar message handlers

BOOL CMainToolBar::RestoreOriginalstate ()
{
	RemoveAllButtons ();

	CString str;

	CMenu menuHistory;
	menuHistory.LoadMenu (IDR_HISTORY_POPUP);

	str.LoadString(IDS_BACK);
	InsertButton (CBCGToolbarMenuButton (ID_GO_BACK, menuHistory, 0, str));

	str.LoadString(IDS_FORWARD);
	InsertButton (CBCGToolbarMenuButton (ID_GO_FORWARD, menuHistory, 1, str));

	str.LoadString(IDS_STOP);
	InsertButton (CBCGToolbarButton (ID_VIEW_STOP, 2, str));

	str.LoadString(IDS_REFRESH);
	InsertButton (CBCGToolbarButton (ID_VIEW_REFRESH, 3, str));

	str.LoadString(IDS_HOME);
	InsertButton (CBCGToolbarButton (ID_GO_START_PAGE, 4, str));

	str.LoadString(IDS_SEARCH);
	InsertButton (CBCGToolbarButton (ID_GO_SEARCH_THE_WEB, 5, str));

	CMenu menuFavorites;
	menuFavorites.LoadMenu (IDR_FAVORITES_POPUP);
	str.LoadString(IDS_FAVORITES);
	InsertButton (CBCGToolbarMenuButton (-1, menuFavorites, 6, str));

	InsertSeparator ();

	str.LoadString(IDS_PRINT);
	InsertButton (CBCGToolbarButton (ID_FILE_PRINT, 7, str));

	CMenu menuFonts;
	menuFonts.LoadMenu (IDR_FONT_POPUP);
	str.LoadString(IDS_FONT);
	InsertButton (CBCGToolbarMenuButton (-1, menuFonts/**menuFonts.GetSubMenu (0)*/, 8, str));

	AdjustLayout ();

	SetWindowText (_T("Standard"));
	return TRUE;
}
