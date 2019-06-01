// MainToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "wordpad.h"
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
	int nPen = GetSystemMetrics(SM_PENWINDOWS) ? NUM_PEN_TOGGLE :
		NUM_PEN_ITEMS;

	BOOL bRes = SetButtons(toolbar, sizeof(toolbar)/sizeof(UINT) - nPen);

	AdjustLayout ();
	Invalidate ();

	return bRes;
}

void CMainToolBar::TogglePen ()
{
	static int nPen = 0;
	SetButtons(toolbar, sizeof(toolbar)/sizeof(UINT) - nPen);
	nPen = (nPen == 0) ? NUM_PEN_TOGGLE : 0;
	Invalidate();
	GetParentFrame()->RecalcLayout();
}
