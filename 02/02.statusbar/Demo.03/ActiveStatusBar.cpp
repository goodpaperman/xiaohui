// ActiveStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "StatusBar.h"
#include "ActiveStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActiveStatusBar

CActiveStatusBar::CActiveStatusBar()
{
}

CActiveStatusBar::~CActiveStatusBar()
{
}


BEGIN_MESSAGE_MAP(CActiveStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CActiveStatusBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveStatusBar message handlers

/****************************************************************************
*                       CActiveStatusBar::OnCommand
* Inputs:
*       WPARAM wParam:
*	LPARAM lParam:
* Result: LRESULT
*       
* Effect: 
*       Passes the command upwards if it is one of our commands
****************************************************************************/

BOOL CActiveStatusBar::OnCommand(WPARAM wParam, LPARAM lParam)
    {
     switch(LOWORD(wParam))
	{ /* one of ours? */
	 case ID_INDICATOR_COMBO:
	 case ID_INDICATOR_EDIT:
	    return GetParent()->SendMessage(WM_COMMAND, wParam, lParam);
	} /* one of ours? */

     // Not one of ours
     return CControlBar::OnCommand(wParam, lParam);
    } // CActiveStatusBar::OnCommand
